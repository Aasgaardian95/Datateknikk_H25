#include "PIRSensor.h"

PIRSensor::PIRSensor(uint8_t sensorPin, uint8_t ledPin)
  : BaseSensor("PIR"), _sensorPin(sensorPin), _ledPin(ledPin), _motionDetected(false) {}

void PIRSensor::begin() {
  pinMode(_sensorPin, INPUT);
  pinMode(_ledPin, OUTPUT);
  digitalWrite(_ledPin, LOW);
  Serial.println("PIR-sensor initialisert. Vent et halvt minutt for stabilisering.");
}

void PIRSensor::read() {
  _motionDetected = digitalRead(_sensorPin) == HIGH;
  _lastRead = millis();

  if (_motionDetected) {
    Serial.println("[PIR] Bevegelse oppdaget!");
    digitalWrite(_ledPin, HIGH); // tenn LED for å vise aktivitet
  } else {
    Serial.println("[PIR] Ingen bevegelse registrert.");
    digitalWrite(_ledPin, LOW);  // slukk LED når det er rolig
  }
}
