#ifndef ENS160SENSOR_H
#define ENS160SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <ENS160.h>
#include "BaseSensor.h"

class ENS160Sensor : public BaseSensor {
  public:
    ENS160Sensor(TwoWire& wirePort = Wire);
    void begin() override;
    void read() override;

    uint8_t airQualityIndex() const { return _aqi; }
    uint16_t CO2eq() const { return _eco2; }

  private:
    ENS160 _ens;
    TwoWire* _wire;
    uint8_t _aqi;     // luftkvalitetsindeks (1-5)
    uint16_t _eco2;   // estimert CO2-ekvivalent i ppm
    bool _initialized;
};

#endif
