#ifndef KEYPADINPUT_H
#define KEYPADINPUT_H

#include <Arduino.h>
#include <Keypad.h>
#include <string.h>
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

template <size_t PIN_LENGDE>
class PinTilgangskontroll {
  public:
    using HendelseCallback = void (*)();
    using ProgresjonCallback = void (*)(const char*, byte);

    PinTilgangskontroll(KeypadInput& tastatur, const char (&riktigPin)[PIN_LENGDE]);

    void setBekreftTaste(char tast) { _bekreftTaste = tast; }
    void setResetTaste(char tast) { _resetTaste = tast; }

    void setSuksessCallback(HendelseCallback callback) { _onSuksess = callback; }
    void setFeilCallback(HendelseCallback callback) { _onFeil = callback; }
    void setProgresjonCallback(ProgresjonCallback callback) { _onProgresjon = callback; }

    void begin();
    void oppdater();
    void nullstill();

    const char* hentInndata() const { return _inndata; }
    byte hentLengde() const { return _indeks; }
    static constexpr byte maksimalLengde() { return PIN_LENGDE > 0 ? PIN_LENGDE - 1 : 0; }

  private:
    KeypadInput& _tastatur;
    char _riktigPin[PIN_LENGDE];
    char _inndata[PIN_LENGDE];
    byte _indeks;
    char _bekreftTaste;
    char _resetTaste;
    HendelseCallback _onSuksess;
    HendelseCallback _onFeil;
    ProgresjonCallback _onProgresjon;

    void leggTilSiffer(char tast);
    void bekreftPin();
};

template <size_t PIN_LENGDE>
PinTilgangskontroll<PIN_LENGDE>::PinTilgangskontroll(KeypadInput& tastatur, const char (&riktigPin)[PIN_LENGDE])
  : _tastatur(tastatur),
    _indeks(0),
    _bekreftTaste('#'),
    _resetTaste('*'),
    _onSuksess(nullptr),
    _onFeil(nullptr),
    _onProgresjon(nullptr) {
  memcpy(_riktigPin, riktigPin, PIN_LENGDE);
  memset(_inndata, 0, sizeof(_inndata));
}

template <size_t PIN_LENGDE>
void PinTilgangskontroll<PIN_LENGDE>::begin() {
  _tastatur.begin();
  nullstill();
}

template <size_t PIN_LENGDE>
void PinTilgangskontroll<PIN_LENGDE>::oppdater() {
  _tastatur.read();

  char tast = _tastatur.getKey();
  if (!tast) {
    return;
  }

  if (tast == _resetTaste) {
    nullstill();
    if (_onProgresjon) {
      _onProgresjon(_inndata, _indeks);
    }
    return;
  }

  if (tast == _bekreftTaste) {
    bekreftPin();
    return;
  }

  leggTilSiffer(tast);
}

template <size_t PIN_LENGDE>
void PinTilgangskontroll<PIN_LENGDE>::nullstill() {
  _indeks = 0;
  memset(_inndata, 0, sizeof(_inndata));
}

template <size_t PIN_LENGDE>
void PinTilgangskontroll<PIN_LENGDE>::leggTilSiffer(char tast) {
  if (_indeks >= maksimalLengde()) {
    if (_onProgresjon) {
      _onProgresjon(_inndata, _indeks);
    }
    return;
  }

  _inndata[_indeks++] = tast;
  if (_onProgresjon) {
    _onProgresjon(_inndata, _indeks);
  }
}

template <size_t PIN_LENGDE>
void PinTilgangskontroll<PIN_LENGDE>::bekreftPin() {
  bool erRiktigLengde = (_indeks == maksimalLengde());
  bool erLik = erRiktigLengde && (strncmp(_inndata, _riktigPin, maksimalLengde()) == 0);

  if (erLik) {
    if (_onSuksess) {
      _onSuksess();
    }
  } else {
    if (_onFeil) {
      _onFeil();
    }
  }

  nullstill();
  if (_onProgresjon) {
    _onProgresjon(_inndata, _indeks);
  }
}

#endif
