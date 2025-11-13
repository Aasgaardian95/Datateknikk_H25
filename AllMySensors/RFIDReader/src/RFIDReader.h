#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "BaseSensor.h"

class RFIDReader : public BaseSensor {
  public:
    RFIDReader(uint8_t ssPin, uint8_t rstPin);
    void begin() override;
    void read() override;

    bool cardDetected() const { return _cardPresent; }
    String getUID() const;
    bool getUIDBytes(byte* destination, byte maxLength, byte& outLength) const;

  private:
    MFRC522 _mfrc522;
    bool _cardPresent;
    byte _uidBuffer[10];   // plass til UID (opptil 10 byte)
    byte _uidLength;        // faktisk lengde på UID
};

#endif
