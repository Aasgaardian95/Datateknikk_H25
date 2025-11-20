/*
Logikk:
- BME280 måler nåværende temperatur
- Viften styres med PWM for hastighet
- Retning settes basert på modus:
    - Sommermodus: motor roterer i én retning
    - Vintermodus: motor roterer motsatt
- Hastighet baseres på temperatur:
    - Lav temp → lav hastighet
    - Høy temp → høy hastighet
- Manuell overstyring mulig med en knapp:
    - Hvis knappen trykkes → motor går på full hastighet uavhengig av temp
- Serial Monitor viser temperatur og motorhastighet
*/

#include <Wire.h>
#include <Adafruit_BME280.h>

#define MOTOR_PWM 9             // PWM-pin til motor
#define MOTOR_DIR 8             // Retningspin for motor
#define OVERRIDE_BUTTON 7       // Pin for manuell overstyring

Adafruit_BME280 bme;           // Initialiser BME280

bool summerMode = true;         // Sommer/vintermodus: true = sommer
int motorSpeed = 0;             // Variabel for motorhastighet 0-255

void setup() {
  Serial.begin(9600);           // Start Serial Monitor
  if(!bme.begin(0x76)) while(1); // Sjekk BME280
  pinMode(MOTOR_PWM, OUTPUT);   // Sett motor PWM som output
  pinMode(MOTOR_DIR, OUTPUT);   // Sett motor retning som output
  pinMode(OVERRIDE_BUTTON, INPUT_PULLUP); // Sett knapp som input med pullup
}

void loop() {
  float temp = bme.readTemperature(); // Les temperatur
  bool override = digitalRead(OVERRIDE_BUTTON) == LOW; // Sjekk knapptrykk (aktiv lav)

  // Sett retning basert på sommer/vintermodus
  if(summerMode) digitalWrite(MOTOR_DIR, HIGH); // Sommer = én retning
  else digitalWrite(MOTOR_DIR, LOW);           // Vinter = motsatt retning

  // Beregn motorhastighet basert på temperatur hvis ikke overstyrt
  if(!override){
    if(temp < 20) motorSpeed = 50;          // Lav temp → lav hastighet
    else if(temp < 25) motorSpeed = 120;    // Medium temp → medium hastighet
    else motorSpeed = 255;                  // Høy temp → full hastighet
  } else {
    motorSpeed = 255;                        // Overstyring → full hastighet
  }

  analogWrite(MOTOR_PWM, motorSpeed);        // Oppdater motor PWM

  // Serial Monitor for logging
  Serial.print("Temperatur: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hastighet: "); Serial.print(motorSpeed); Serial.print("/255, ");
  Serial.print("Retning: "); Serial.println(summerMode ? "Sommer" : "Vinter");

  delay(500); // Oppdatering hvert 0,5 sekund
}
