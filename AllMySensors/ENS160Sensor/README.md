# ENS160Sensor

## Beskrivelse
`ENS160Sensor` gir tilgang til luftkvalitetssensoren ENS160 og rapporterer både luftkvalitetsindeks (AQI) og estimert CO₂-ekvivalent. Klassen arver fra `BaseSensor`, slik at avlesningene følger samme mønster som de øvrige sensorbibliotekene.

## Struktur
```
.
├── README.md
├── examples
│   └── ENS160Sensor_Example
│       └── ENS160Sensor_Example.ino
└── src
    ├── ENS160Sensor.cpp
    └── ENS160Sensor.h
```

## Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/ENS160Sensor.h` | Header | Deklarerer klassen med tilgang til AQI og eCO₂-verdier. |
| `src/ENS160Sensor.cpp` | Implementasjon | Initialiserer sensoren, setter standard målemodus og skriver verdier til seriellmonitor. |
| `examples/ENS160Sensor_Example/ENS160Sensor_Example.ino` | Eksempel | Viser hvordan målinger hentes og presenteres i et intervall. |

## Bruk
```cpp
#include <Arduino.h>
#include <Wire.h>
#include <ENS160Sensor.h>

constexpr float STANDARD_TEMPERATUR_C = 22.0f;
constexpr float STANDARD_LUFTFUKTIGHET_PROSENT = 45.0f;

ENS160Sensor luftkvalitet(Wire);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  luftkvalitet.begin();
  luftkvalitet.setAmbientConditions(STANDARD_TEMPERATUR_C, STANDARD_LUFTFUKTIGHET_PROSENT);
}

void loop() {
  luftkvalitet.setAmbientConditions(STANDARD_TEMPERATUR_C, STANDARD_LUFTFUKTIGHET_PROSENT);
  luftkvalitet.read();

  Serial.print("AQI fra objektet: ");
  Serial.println(luftkvalitet.airQualityIndex());

  delay(3000); // vent tre sekunder mellom målingene for stabilitet
}
```
Kjør eksempelet med seriellmonitoren åpen for å se både sanntidsutskrift fra `read()` og den bufrede AQI-verdien fra objektet.

Bruk `setAmbientConditions()` for å gi ENS160 referanseverdier for temperatur og relativ luftfuktighet. Dette gjør at sensoren
kan kompensere målingene sine dersom du kombinerer den med for eksempel en BME280 eller andre klimamoduler.

## Tilkobling
- I²C-adresse `0x52` (fast for ENS160).
- Koble **SDA** til A4 og **SCL** til A5 på Arduino Uno (bruk riktig I²C-par for andre kort).
- Strøm med 3.3 V (sensoren krever gjerne 3.3 V) og GND.
- Del I²C-bussen med andre sensorer ved å bruke `Wire`-objektet.

## Avhengigheter
- Arduino core (`Arduino.h`, `Wire.h`)
- `BaseSensor`-biblioteket
- Eksternt `ENS160`-bibliotek for Sensirion-modulen

## For undervisning
Bruk sensoren til å diskutere:
- Luftkvalitetsmålinger og tolkning av AQI.
- Hvordan flere sensorer kan dele samme I²C-buss.
- Objektorientert innkapsling av relativt komplekse sensordrivere.
