/*
Logikk:
- BME280 måler temperatur og relativ fuktighet
- ENS160 måler luftkvalitet (TVOC og eCO2), kompensert med temp/hum
- PWM-motor styrer viftehastighet
- Retning settes basert på modus:
    - Sommermodus: én retning
    - Vintermodus: motsatt retning
- Motorhastighet justeres basert på temperatur og luftkvalitet
- Manuell overstyring via knapp gir full hastighet
- Serial Monitor viser temperatur, fuktighet, luftkvalitet, motorhastighet og retning
*/

#include <Wire.h>                    // I2C-kommunikasjon
#include <SparkFunBME280.h>          // SparkFun BME280 bibliotek
#include <SparkFun_ENS160.h>         // SparkFun ENS160 bibliotek

#define MOTOR_PWM 9                  // PWM-pin til motor/vifte
#define MOTOR_DIR 8                  // Retningspinne til motor
#define OVERRIDE_BUTTON 7            // Knapp for manuell overstyring

BME280 myBME;                        // Oppretter BME280 objekt
ENS160 myENS;                         // Oppretter ENS160 objekt

bool summerMode = true;               // Modus: sommer/vinter
int motorSpeed = 0;                    // Motorhastighet (0-255)

void setup() {
  Serial.begin(9600);                 // Start Serial Monitor

  // --- Initialiser BME280 ---
  if (!myBME.begin()) {               // Sjekker om sensor svarer
    Serial.println("BME280 ikke funnet!");
    while (1);                        // Stopp koden hvis ikke funnet
  }

  // --- Initialiser ENS160 ---
  if (myENS.begin() != 0) {           // Sjekker om sensor svarer
    Serial.println("ENS160 ikke funnet!");
    while (1);
  }
  myENS.iaqInit();                     // Start IAQ-måling

  // --- Aktuatorpinner ---
  pinMode(MOTOR_PWM, OUTPUT);         // PWM til motorhastighet
  pinMode(MOTOR_DIR, OUTPUT);         // Digital pin for retning
  pinMode(OVERRIDE_BUTTON, INPUT_PULLUP); // Knapp med pullup
}

void loop() {
  // --- Les temperatur og fuktighet ---
  float temp = myBME.readTempC();           // Temperatur i °C
  float hum = myBME.readFloatHumidity();    // Relativ fuktighet %

  // --- Kompenser ENS160 med temp og fuktighet ---
  myENS.setEnvironmentalData((int)temp, (int)hum);
  myENS.iaqMeasure();                        // Start måling

  // --- Les luftkvalitet ---
  uint16_t tvoc = myENS.getTVOC();          // Total volatile organic compounds
  uint16_t eco2 = myENS.getCO2();           // Estimert CO2

  // --- Les knapp for manuell overstyring ---
  bool override = digitalRead(OVERRIDE_BUTTON) == LOW; // Knapp trykket = LOW

  // --- Sett motorretning basert på modus ---
  if (summerMode) digitalWrite(MOTOR_DIR, HIGH);  // Sommer: én retning
  else digitalWrite(MOTOR_DIR, LOW);              // Vinter: motsatt retning

  // --- Beregn motorhastighet basert på temperatur og luftkvalitet ---
  if (!override) {                               // Kun hvis ikke overstyrt
    if (temp < 20 && tvoc < 250) motorSpeed = 50;     // Lav temp og god luft = lav hastighet
    else if (temp < 25 && tvoc < 300) motorSpeed = 120; // Moderat temp/lufthastighet
    else motorSpeed = 255;                        // Høy temp/dårlig luft = full hastighet
  } else {
    motorSpeed = 255;                             // Overstyring = full hastighet
  }

  // --- Sett PWM til motor ---
  analogWrite(MOTOR_PWM, motorSpeed);            // Motorhastighet 0-255

  // --- Serial Monitor for debugging ---
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print(" %, ");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
  Serial.print("eCO2: "); Serial.print(eco2); Serial.print(" ppm, ");
  Serial.print("Motor: "); Serial.print(motorSpeed); Serial.print("/255, ");
  Serial.print("Retning: "); Serial.println(summerMode ? "Sommer" : "Vinter");

  delay(500);  // Oppdatering hvert 0,5 sekund
}
