#pragma once
#include <Arduino.h>

// En enkel struktur for å holde måledata
struct SensorData {
  int rawValue;     // Rå analogverdi (0–1023)
  float voltage;    // Omregnet til volt
};

// En klasse som representerer en sensor koblet til en analog pin
class Sensor {
private:
  int pin;          // hvilken pin sensoren er koblet til
  String name;      // navn for identifikasjon

public:
  // Konstruktør
  Sensor(int pin, String name);

  // Leser verdier fra sensoren og returnerer struktur
  SensorData read();

  // Skriver info til seriell monitor
  void printInfo();

  // Henter navnet på sensoren
  String getName();
};
