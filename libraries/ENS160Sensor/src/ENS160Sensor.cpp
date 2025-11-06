#include "ENS160Sensor.h"

ENS160Sensor::ENS160Sensor(TwoWire& wirePort)
  : BaseSensor("ENS160"), _wire(&wirePort), _aqi(0), _eco2(0), _initialized(false) {}

void ENS160Sensor::begin() {
  if (!_wire->isEnabled()) {
    _wire->begin();
  }

  if (!_ens.begin(*_wire)) {
    Serial.println("ENS160 ble ikke funnet. Kontroller at adressen (0x52) er korrekt.");
    _initialized = false;
    return;
  }

  Serial.println("ENS160-sensor initialisert. Starter luftkvalitetsmålinger.");
  _ens.setMode(ENS160_OPMODE_STD);
  _initialized = true;
}

void ENS160Sensor::read() {
  if (!_initialized) {
    Serial.println("[ENS160] Sensor ikke klar. Kontroller begin().");
    return;
  }

  _ens.measure(true);
  _aqi = _ens.getAQI();
  _eco2 = _ens.geteCO2();
  _lastRead = millis();

  Serial.print("[ENS160] Luftkvalitetsindeks (1=best): ");
  Serial.println(_aqi);

  Serial.print("[ENS160] Estimert CO2-ekvivalent: ");
  Serial.print(_eco2);
  Serial.println(" ppm");
}
