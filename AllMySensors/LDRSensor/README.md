# LDRSensor

## Beskrivelse
`LDRSensor` leser lysstyrke med en lysavhengig motstand (LDR). Biblioteket arver fra `BaseSensor`, slik at metoder som `begin()`, `read()` og `printDebug()` kan brukes på samme måte som for andre sensorer.

## Struktur
```
.
├── README.md
├── examples
│   └── LDRSensor_Example
│       └── LDRSensor_Example.ino
└── src
    ├── LDRSensor.cpp
    └── LDRSensor.h
```

## Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/LDRSensor.h` | Header | Deklarerer LDR-klassen med pinnekonfigurasjon og metode for å hente siste verdi. |
| `src/LDRSensor.cpp` | Implementasjon | Initialiserer analogt inngangspin og skriver målinger til seriellmonitor. |
| `examples/LDRSensor_Example/LDRSensor_Example.ino` | Eksempel | Viser grunnleggende bruk av biblioteket for å lese lysnivå hvert sekund. |

## Bruk
```cpp
#include <Arduino.h>
#include <LDRSensor.h>

// LDR koblet til analog inngang A0 (standard for lyssensor i labben)
constexpr uint8_t LDR_PIN = A0;

LDRSensor ldr(LDR_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // vent på seriell tilkobling når man bruker USB-baserte kort
  }
  ldr.begin();
}

void loop() {
  ldr.read();
  delay(1000); // les hvert sekund for å se endringer i lysnivå
}
```
Seriellmonitoren skriver verdier mellom 0 og 1023, der høye tall betyr mye lys. Beveg hånden over LDR-en eller bruk en lommelykt for å se tydelige endringer.

## Tilkobling
- LDR og 10 kΩ motstand kobles som spenningsdeler mellom 5 V og GND.
- Midtpunktet mellom LDR og motstand kobles til analog inngang A0.
- Sørg for stabile tilkoblinger for å unngå støy i målingene.

## Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket

## For undervisning
Temaer som kan dekkes:
- Analog måling med `analogRead()` og spenningsdelere.
- Hvordan sensorverdier kan tolkes og visualiseres i sanntid.
- Objektorientert struktur som muliggjør felles bruk av `BaseSensor`-metodene.
