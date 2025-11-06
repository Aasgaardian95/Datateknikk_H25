#include "LDRSensor.h"

LDRSensor::LDRSensor(uint8_t pin)
  : BaseSensor("LDR"), _pin(pin), _value(0) {}

void LDRSensor::begin() {
  pinMode(_pin, INPUT);
  Serial.println("LDR-sensor initialisert. Bruk spenningsdeler for stabil avlesing.");
}

void LDRSensor::read() {
  _value = analogRead(_pin); // analogRead gir verdi 0-1023 for UNO
  _lastRead = millis();

  Serial.print("[LDR] Lysnivå: ");
  Serial.print(_value);
  Serial.println(" (0=svart, 1023=sterkt lys).");
}
