#include "Sensor.h"

// Oppretter to sensor-objekter basert på vår egen klasse
Sensor lightSensor(A0, "Lys-sensor");
Sensor tempSensor(A1, "Temp-sensor");

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Leser og viser begge sensorene
  lightSensor.printInfo();
  tempSensor.printInfo();

  delay(1000);
}
