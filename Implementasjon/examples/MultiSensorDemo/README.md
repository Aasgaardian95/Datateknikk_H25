# MultiSensorDemo

## 🎯 Formål
Viser hvordan flere sensorer kan brukes samtidig gjennom polymorfisme med `BaseSensor` som felles grensesnitt. Demonstrasjonen kombinerer analoge, digitale og I²C-baserte sensorer i én løkke.

## 📁 Struktur
```
.
├── MultiSensorDemo.ino
└── README.md
```

## 🧩 Inkluderte sensorer
- `LDRSensor` (lys)
- `PIRSensor` (bevegelse)
- `BME280Sensor` (klima)

## 📘 Eksempel
```cpp
#include <Arduino.h>
#include <Wire.h>
#include <BaseSensor.h>
#include <LDRSensor.h>
#include <PIRSensor.h>
#include <BME280Sensor.h>

// Opprett sensorer dynamisk for å demonstrere polymorfisme
BaseSensor* sensorer[] = {
  new LDRSensor(A0),         // LDR koblet til A0
  new PIRSensor(7),          // PIR på digital pinne 7
  new BME280Sensor(0x76)     // BME280 på I2C-adresse 0x76
};

constexpr size_t ANTALL_SENSORER = sizeof(sensorer) / sizeof(sensorer[0]);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Wire.begin();
  Serial.println("Starter multisensordemo...");

  for (size_t i = 0; i < ANTALL_SENSORER; ++i) {
    sensorer[i]->begin();
  }
}

void loop() {
  for (size_t i = 0; i < ANTALL_SENSORER; ++i) {
    sensorer[i]->read();
    sensorer[i]->printDebug();
  }

  Serial.println("---");
  delay(2000); // vent to sekunder før neste runde
}
```
Seriellmonitoren viser avlesninger fra hver sensor etterfulgt av `printDebug()`-meldingen som dokumenterer hvor lang tid siden forrige lesing. Strek-linjen `---` skiller hver runde for enkel analyse.

## 🔌 Tilkobling
- **LDRSensor**: LDR i spenningsdeler mellom 5 V og GND med midtpunkt på A0.
- **PIRSensor**: VCC til 5 V, GND til GND, utgang til digital pinne 7 og innebygd LED brukes som indikator.
- **BME280Sensor**: I²C (SDA til A4, SCL til A5 på Arduino Uno), strøm 3.3 V og GND.

## 🧱 Avhengigheter
- Arduino core og `Wire`
- Bibliotekene `BaseSensor`, `LDRSensor`, `PIRSensor`, `BME280Sensor`
- Eksterne avhengigheter håndteres gjennom de respektive bibliotekene (f.eks. `Adafruit_BME280`)

## 👩‍🏫 For undervisning
Dette eksempelet er ideelt for å diskutere:
- Polymorfisme i praksis og hvordan baseklassen skjuler implementasjonsdetaljer.
- Koordinering av ulike sensortyper i ett program.
- Ressursstyring (initiering i `setup()` og felles intervallstyring i `loop()`).
