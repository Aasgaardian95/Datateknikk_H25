# PIRSensor

## 📘 Beskrivelse
`PIRSensor` biblioteket håndterer en passiv infrarød sensor som registrerer bevegelse. Klassen arver fra `BaseSensor` og bruker felles grensesnitt for initialisering, avlesning og logging, slik at den kan kombineres med de andre sensorene i prosjektet.

## 📁 Struktur
```
.
├── README.md
├── examples
│   └── PIRSensor_Example
│       └── PIRSensor_Example.ino
└── src
    ├── PIRSensor.cpp
    └── PIRSensor.h
```

### ⚙️ Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/PIRSensor.h` | Header | Deklarerer klassen med støtte for valgfri LED-indikator. |
| `src/PIRSensor.cpp` | Implementasjon | Initialiserer I/O-pinner og skriver statusmeldinger når bevegelse oppdages. |
| `examples/PIRSensor_Example/PIRSensor_Example.ino` | Eksempel | Viser enkel bevegelsesdeteksjon med seriell og LED-indikasjon. |

## 🧠 Bruk
```cpp
#include <Arduino.h>
#include <PIRSensor.h>

// PIR-sensor koblet til digital pinne 7 og LED til innebygd indikator
constexpr uint8_t PIR_PIN = 7;
constexpr uint8_t LED_PIN = LED_BUILTIN;

PIRSensor pir(PIR_PIN, LED_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  pir.begin();
}

void loop() {
  pir.read();
  delay(500); // les to ganger i sekundet for rask respons
}
```
Når bevegelse registreres, skriver programmet «[PIR] Bevegelse oppdaget!» og tenner LED-en. Ved ro slukkes LED-en, og meldingen «[PIR] Ingen bevegelse registrert.» vises.

## 🔌 Tilkobling
- **VCC** til 5 V, **GND** til GND.
- **Signal** til digital pinne 7 (kan endres i konstruktøren).
- Valgfri indikator-LED (standard `LED_BUILTIN`) kan brukes for visuell bekreftelse.
- Husk å la sensoren stabilisere seg i 30–60 sekunder etter oppstart.

## 🧱 Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket

## 👩‍🏫 For undervisning
Egner seg til å diskutere:
- Digital innlesing og debouncing/logikk for bevegelsesdeteksjon.
- Design av hendelsesdrevne systemer med alarmer eller automatisering.
- Gjenbruk av `BaseSensor`-grensesnittet for å kombinere flere sensorer i ett prosjekt.
