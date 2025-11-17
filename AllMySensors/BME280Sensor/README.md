# BME280Sensor

## Beskrivelse
`BME280Sensor` henter temperatur, luftfuktighet og lufttrykk fra Bosch BME280-modulen via I²C. Klassen arver fra `BaseSensor`, slik at klimadata kan behandles med samme API som de andre sensorene i prosjektet.

## Struktur
```
.
├── README.md
├── examples
│   └── BME280Sensor_Example
│       └── BME280Sensor_Example.ino
└── src
    ├── BME280Sensor.cpp
    └── BME280Sensor.h
```

## Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/BME280Sensor.h` | Header | Definerer klassen med målemetoder for temperatur, fuktighet og trykk. |
| `src/BME280Sensor.cpp` | Implementasjon | Initialiserer modulen og skriver klimadata med tydelige meldinger til seriellmonitor. |
| `examples/BME280Sensor_Example/BME280Sensor_Example.ino` | Eksempel | Viser hvordan man leser data og bruker hjelpefunksjoner som `temperature()`. |

## Bruk
```cpp
#include <Arduino.h>
#include <Wire.h>
#include <BME280Sensor.h>

// Standard I2C-adresse for modulen i lab-settet er 0x76
constexpr uint8_t BME280_ADDRESS = 0x76;

BME280Sensor klima(BME280_ADDRESS);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (!Wire.isEnabled()) {
    Wire.begin();
  }
  klima.begin();
}

void loop() {
  klima.read();

  Serial.print("Temperatur (cachet): ");
  Serial.print(klima.temperature(), 1);
  Serial.println(" °C");

  delay(2000); // gi sensoren tid mellom avlesinger
}
```
Programmet skriver både direkte målinger fra `read()` og viser hvordan cachede verdier kan leses via `temperature()`. Bruk seriellmonitoren for å se temperaturendringer over tid.

## Tilkobling
- I²C-tilkobling: **SDA** til A4 og **SCL** til A5 på Arduino Uno (bruk kortets I²C-pinner på andre plattformer).
- Strøm: 3.3 V og GND.
- BME280 har typisk adresse `0x76`; sett konstruktøren til `0x77` hvis modulens adresse er endret.

## Avhengigheter
- Arduino core (`Arduino.h`, `Wire.h`)
- `BaseSensor`-biblioteket
- `Adafruit_BME280` (eksternt bibliotek for sensordriveren)

## For undervisning
Egner seg for å diskutere:
- I²C-protokollen og adressehåndtering.
- Samspill mellom rå målinger og bearbeidet data (trykk i hPa, temperatur i °C).
- Hvordan objektorientert struktur forenkler integrasjon av klimadata i større prosjekter.
