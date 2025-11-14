#include "Sensor.h"

// Konstruktør – settes opp når objektet lages
Sensor::Sensor(int pin, String name)
    : pin(pin), name(name) {
  pinMode(pin, INPUT);
}

// Leser analogverdi og konverterer til volt
SensorData Sensor::read() {
  SensorData data;
  data.rawValue = analogRead(pin);
  data.voltage = (data.rawValue / 1023.0) * 5.0; // antar 5V referanse
  return data;
}

// Skriver sensorens status til Serial Monitor
void Sensor::printInfo() {
  SensorData data = read();
  Serial.print(name);
  Serial.print(": ");
  Serial.print(data.rawValue);
  Serial.print(" -> ");
  Serial.print(data.voltage, 2);
  Serial.println(" V");
}

// Returnerer sensorens navn
String Sensor::getName() {
  return name;
}
