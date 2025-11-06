#include <Arduino.h>
#include <Wire.h>
#include <BaseSensor.h>
#include <LDRSensor.h>
#include <PIRSensor.h>
#include <BME280Sensor.h>

// Opprett sensorer dynamisk for å demonstrere polymorfisme
BaseSensor* sensorer[] = {
  new LDRSensor(A0),         // LDR koblet til A0
  new PIRSensor(7),          // PIR på digital pinne 7
  new BME280Sensor(0x76)     // BME280 på I2C-adresse 0x76
};

constexpr size_t ANTALL_SENSORER = sizeof(sensorer) / sizeof(sensorer[0]);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Wire.begin();
  Serial.println("Starter multisensordemo...");

  for (size_t i = 0; i < ANTALL_SENSORER; ++i) {
    sensorer[i]->begin();
  }
}

void loop() {
  for (size_t i = 0; i < ANTALL_SENSORER; ++i) {
    sensorer[i]->read();
    sensorer[i]->printDebug();
  }

  Serial.println("---");
  delay(2000); // vent to sekunder før neste runde
}
