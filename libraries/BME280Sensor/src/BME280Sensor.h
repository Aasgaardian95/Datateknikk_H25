#ifndef BME280SENSOR_H
#define BME280SENSOR_H

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include "BaseSensor.h"

class BME280Sensor : public BaseSensor {
  public:
    explicit BME280Sensor(uint8_t i2cAddress = 0x76);
    void begin() override;
    void read() override;

    float temperature() const { return _temperature; }
    float humidity() const { return _humidity; }
    float pressure() const { return _pressure; }

  private:
    Adafruit_BME280 _bme;
    uint8_t _address;     // I2C-adresse for sensoren (0x76 eller 0x77)
    float _temperature;   // sist målte temperatur i Celsius
    float _humidity;      // sist målte relativ luftfuktighet i prosent
    float _pressure;      // sist målte trykk i hPa
    bool _initialized;    // om sensoren er klar til bruk
};

#endif
