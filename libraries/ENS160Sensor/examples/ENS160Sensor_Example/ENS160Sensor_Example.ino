#include <Arduino.h>
#include <Wire.h>
#include <ENS160Sensor.h>

ENS160Sensor luftkvalitet(Wire);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  luftkvalitet.begin();
}

void loop() {
  luftkvalitet.read();

  Serial.print("AQI fra objektet: ");
  Serial.println(luftkvalitet.airQualityIndex());

  delay(3000); // vent tre sekunder mellom målingene for stabilitet
}
