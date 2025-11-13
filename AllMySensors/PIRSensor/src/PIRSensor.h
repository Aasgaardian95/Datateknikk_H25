#ifndef PIRSENSOR_H
#define PIRSENSOR_H

#include <Arduino.h>
#include "BaseSensor.h"

class PIRSensor : public BaseSensor {
  public:
    PIRSensor(uint8_t sensorPin, uint8_t ledPin = LED_BUILTIN);
    void begin() override;
    void read() override;
    bool motionDetected() const { return _motionDetected; }

  private:
    uint8_t _sensorPin;     // digital pinne til PIR-utgangen
    uint8_t _ledPin;        // LED for visuell indikasjon
    bool _motionDetected;   // status fra forrige avlesing
};

#endif
