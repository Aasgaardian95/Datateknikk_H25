#include "KeypadInput.h"

KeypadInput::KeypadInput(const byte* rowPins, const byte* colPins, byte numRows, byte numCols, const char* keymap)
  : BaseSensor("Keypad"),
    _rowPins(nullptr),
    _colPins(nullptr),
    _numRows(numRows),
    _numCols(numCols),
    _keymap(nullptr),
    _keypad(nullptr),
    _lastKey('\0') {

  _rowPins = new byte[_numRows];
  _colPins = new byte[_numCols];
  for (byte i = 0; i < _numRows; ++i) {
    _rowPins[i] = rowPins[i];
  }
  for (byte j = 0; j < _numCols; ++j) {
    _colPins[j] = colPins[j];
  }

  _keymap = new char[_numRows * _numCols];
  for (byte idx = 0; idx < _numRows * _numCols; ++idx) {
    _keymap[idx] = keymap[idx];
  }

  _keypad = new Keypad(makeKeymap(_keymap), _rowPins, _colPins, _numRows, _numCols);
}

KeypadInput::~KeypadInput() {
  delete _keypad;
  delete[] _keymap;
  delete[] _rowPins;
  delete[] _colPins;
}

void KeypadInput::begin() {
  Serial.println("Tastatur klar til bruk. Trykk på tastene for å teste.");
}

void KeypadInput::read() {
  if (_keypad == nullptr) {
    Serial.println("[Keypad] Ikke initialisert korrekt.");
    return;
  }

  char key = _keypad->getKey();
  if (key) {
    _lastKey = key;
    _lastRead = millis();
    Serial.print("[Keypad] Tast registrert: ");
    Serial.println(key);
  }
}
