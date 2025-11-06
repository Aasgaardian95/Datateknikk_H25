#include "BaseSensor.h"

void BaseSensor::printDebug() {
  Serial.print("[");
  Serial.print(_name);
  Serial.print("] Data oppdatert etter ");
  Serial.print(millis() - _lastRead);
  Serial.println(" ms.");
}
