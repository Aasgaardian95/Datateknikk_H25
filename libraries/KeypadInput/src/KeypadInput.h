#ifndef KEYPADINPUT_H
#define KEYPADINPUT_H

#include <Arduino.h>
#include <Keypad.h>
#include "BaseSensor.h"

class KeypadInput : public BaseSensor {
  public:
    KeypadInput(const byte* rowPins, const byte* colPins, byte numRows, byte numCols, const char* keymap);
    ~KeypadInput();

    void begin() override;
    void read() override;

    char getKey() const { return _lastKey; }

  private:
    byte* _rowPins;
    byte* _colPins;
    byte _numRows;
    byte _numCols;
    char* _keymap;
    Keypad* _keypad;
    char _lastKey;    // sist registrerte tast (0 hvis ingen)
};

#endif
