# BaseSensor

## 📘 Beskrivelse
`BaseSensor` er en abstrakt grunnklasse som alle sensorbibliotekene arver fra. Klassen definerer felles grensesnitt for `begin()`, `read()` og en hjelpefunksjon `printDebug()` som skriver når forrige måling ble tatt. Dermed kan alle sensorsubklasser behandles likt i undervisningsopplegg.

## 📁 Struktur
```
.
├── README.md
└── src
    ├── BaseSensor.cpp
    └── BaseSensor.h
```

### ⚙️ Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/BaseSensor.h` | Header | Deklarerer den abstrakte klassen med virtuelle metoder og felles navn-/tidsfelt. |
| `src/BaseSensor.cpp` | Implementasjon | Gir standard `printDebug()` som skriver sensorens navn og tidsstempel til seriellmonitoren. |

## 🧠 Bruk
```cpp
#include <BaseSensor.h>
#include <LDRSensor.h>
#include <PIRSensor.h>

BaseSensor* sensorer[] = {
  new LDRSensor(A0),
  new PIRSensor(7)
};

for (size_t i = 0; i < 2; ++i) {
  sensorer[i]->begin();
}
```
Dette kodeutdraget fra `examples/MultiSensorDemo/MultiSensorDemo.ino` viser hvordan ulike sensorer kan lagres i et `BaseSensor*`-array og initialiseres i en felles løkke.

## 🔌 Tilkobling
`BaseSensor` er kun programvare og har ingen direkte tilkobling. Den fungerer som felles rammeverk for sensorbibliotekene.

## 🧱 Avhengigheter
- Arduino core (`Arduino.h`)

## 👩‍🏫 For undervisning
Bruk klassen til å introdusere:
- Abstrakte klasser og virtuelle funksjoner i C++.
- Hvordan polymorfisme forenkler håndtering av heterogene sensorer.
- Gjenbruk av kode og felles struktur i større undervisningsprosjekter.
