#include <Arduino.h>
#include <Wire.h>
#include <ENS160Sensor.h>

constexpr float STANDARD_TEMPERATUR_C = 22.0f;
constexpr float STANDARD_LUFTFUKTIGHET_PROSENT = 45.0f;

ENS160Sensor luftkvalitet(Wire);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  luftkvalitet.begin();
  luftkvalitet.setAmbientConditions(STANDARD_TEMPERATUR_C, STANDARD_LUFTFUKTIGHET_PROSENT);
}

void loop() {
  luftkvalitet.setAmbientConditions(STANDARD_TEMPERATUR_C, STANDARD_LUFTFUKTIGHET_PROSENT);
  luftkvalitet.read();

  Serial.print("AQI fra objektet: ");
  Serial.println(luftkvalitet.airQualityIndex());

  delay(3000); // vent tre sekunder mellom målingene for stabilitet
}
