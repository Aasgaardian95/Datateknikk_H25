#include "BME280Sensor.h"

BME280Sensor::BME280Sensor(uint8_t i2cAddress)
  : BaseSensor("BME280"), _address(i2cAddress), _temperature(NAN), _humidity(NAN), _pressure(NAN), _initialized(false) {}

void BME280Sensor::begin() {
  bool status = _bme.begin(_address);
  if (!status) {
    Serial.print("BME280 ble ikke funnet på adresse 0x");
    Serial.println(_address, HEX);
    Serial.println("Kontroller ledninger og adresse (0x76/0x77).");
    _initialized = false;
    return;
  }

  Serial.println("BME280-sensor initialisert via I2C.");
  _initialized = true;
}

void BME280Sensor::read() {
  if (!_initialized) {
    Serial.println("[BME280] Sensor ikke klar. Kjør begin() og sjekk tilkoblingen.");
    return;
  }

  _temperature = _bme.readTemperature();
  _humidity = _bme.readHumidity();
  _pressure = _bme.readPressure() / 100.0F; // konverter Pascal til hPa
  _lastRead = millis();

  Serial.print("[BME280] Temperatur: ");
  Serial.print(_temperature, 1);
  Serial.println(" °C");

  Serial.print("[BME280] Luftfuktighet: ");
  Serial.print(_humidity, 1);
  Serial.println(" %");

  Serial.print("[BME280] Lufttrykk: ");
  Serial.print(_pressure, 1);
  Serial.println(" hPa");
}
