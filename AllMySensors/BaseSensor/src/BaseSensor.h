/**
 *  BaseSensor.h
 *  ----------------------------
 *  Grunnklasse for alle sensorer.
 *  Gir felles struktur for init, lesing og debug.
 *  For undervisning ved Høgskolen i Østfold.
 */
#ifndef BASESENSOR_H
#define BASESENSOR_H

#include <Arduino.h>

class BaseSensor {
  public:
    explicit BaseSensor(const String& name) : _name(name) {}
    virtual ~BaseSensor() = default;
    virtual void begin() = 0;    // må implementeres av underklasser
    virtual void read() = 0;     // må implementeres av underklasser
    virtual void printDebug();   // felles debugutskrift
    const String& getName() const { return _name; }

  protected:
    String _name;
    unsigned long _lastRead = 0; // tidspunkt for siste avlesing i millisekunder
};

#endif
