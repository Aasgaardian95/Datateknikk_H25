#ifndef LDRSENSOR_H
#define LDRSENSOR_H

#include <Arduino.h>
#include "BaseSensor.h"

class LDRSensor : public BaseSensor {
  public:
    explicit LDRSensor(uint8_t pin);
    void begin() override;
    void read() override;
    int getValue() const { return _value; }

  private:
    uint8_t _pin;   // analog pinne koblet til LDR
    int _value;     // sist målte lysverdi (0-1023)
};

#endif
