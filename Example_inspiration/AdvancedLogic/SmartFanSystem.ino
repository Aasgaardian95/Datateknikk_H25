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
- OLED viser sanntidsdata: Temp, Hum, TVOC, eCO2, motorhastighet og retning
- Serial Monitor brukes for debugging
*/

#include <Wire.h>                    // I2C-kommunikasjon
#include <SparkFunBME280.h>          // SparkFun BME280 bibliotek
#include <SparkFun_ENS160.h>         // SparkFun ENS160 bibliotek
#include <Adafruit_GFX.h>            // OLED grafikkbibliotek
#include <Adafruit_SSD1306.h>        // OLED displaybibliotek

#define SCREEN_WIDTH 128             // OLED bredde i piksler
#define SCREEN_HEIGHT 64             // OLED høyde i piksler
#define OLED_RESET    -1             // Ingen reset-pin på OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED objekt

#define MOTOR_PWM 9                  // PWM-pin til motor/vifte
#define MOTOR_DIR 8                  // Retningspinne til motor
#define OVERRIDE_BUTTON 7            // Knapp for manuell overstyring

BME280 myBME;                        // Oppretter BME280 objekt
ENS160 myENS;                         // Oppretter ENS160 objekt

bool summerMode = true;               // Modus: sommer/vinter
int motorSpeed = 0;                    // Motorhastighet 0-255

void setup() {
  Serial.begin(9600);                 // Start Serial Monitor for debugging

  // --- Initialiser BME280 ---
  if (!myBME.begin()) {               // Sjekk om sensor finnes
    Serial.println("BME280 ikke funnet!");
    while (1);                        // Stopp her hvis ikke funnet
  }

  // --- Initialiser ENS160 ---
  if (myENS.begin() != 0) {           // Sjekk om sensor finnes
    Serial.println("ENS160 ikke funnet!");
    while (1);
  }
  myENS.iaqInit();                     // Initialiser ENS160 IAQ

  // --- Initialiser OLED ---
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Sjekk om OLED finnes
    Serial.println("OLED ikke funnet!");
    while(1);
  }
  display.clearDisplay();              // Tøm OLED
  display.setTextSize(1);             // Sett tekststørrelse
  display.setTextColor(SSD1306_WHITE);// Sett tekstfarge
  display.setCursor(0,0);             // Start øverst til venstre
  display.println("Smart Vifte");     
  display.display();                   // Vis tekst

  // --- Aktuatorpinner ---
  pinMode(MOTOR_PWM, OUTPUT);         // PWM til motor
  pinMode(MOTOR_DIR, OUTPUT);         // Digital retning
  pinMode(OVERRIDE_BUTTON, INPUT_PULLUP); // Knapp med pullup
}

void loop() {
  float temp = myBME.readTempC();           // Les temperatur °C
  float hum = myBME.readFloatHumidity();    // Les relativ fuktighet %

  myENS.setEnvironmentalData((int)temp, (int)hum); // Mate ENS160 med temp/hum
  myENS.iaqMeasure();                        // Start IAQ-måling

  uint16_t tvoc = myENS.getTVOC();          // Les TVOC (ppb)
  uint16_t eco2 = myENS.getCO2();           // Les eCO2 (ppm)

  bool override = digitalRead(OVERRIDE_BUTTON) == LOW; // Knapp trykket?

  if (summerMode) digitalWrite(MOTOR_DIR, HIGH); // Sommermodus: én retning
  else digitalWrite(MOTOR_DIR, LOW);            // Vintermodus: motsatt retning

  if (!override) {                              // Hvis ikke overstyrt
    if (temp < 20 && tvoc < 250) motorSpeed = 50;      // Lav temp + god luft = lav hastighet
    else if (temp < 25 && tvoc < 300) motorSpeed = 120; // Moderat
    else motorSpeed = 255;                         // Høy temp / dårlig luft
  } else {
    motorSpeed = 255;                              // Overstyring = full hastighet
  }

  analogWrite(MOTOR_PWM, motorSpeed);             // Sett motor PWM

  // --- Oppdater OLED ---
  display.clearDisplay();                        // Tøm skjermen
  display.setCursor(0,0);                        // Start øverst
  display.print("Temp: "); display.print(temp); display.println(" C");
  display.print("Hum: "); display.print(hum); display.println(" %");
  display.print("TVOC: "); display.print(tvoc); display.println(" ppb");
  display.print("eCO2: "); display.print(eco2); display.println(" ppm");
  display.print("Motor: "); display.print(motorSpeed); display.print("/255");
  display.println(summerMode ? " Sommer" : " Vinter");
  display.display();                             // Vis OLED

  // --- Serial Monitor ---
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print(" %, ");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
  Serial.print("eCO2: "); Serial.print(eco2); Serial.print(" ppm, ");
  Serial.print("Motor: "); Serial.print(motorSpeed); Serial.print("/255, ");
  Serial.print("Retning: "); Serial.println(summerMode ? "Sommer" : "Vinter");

  delay(500);                                   // Oppdater hvert 0,5 sek
}
