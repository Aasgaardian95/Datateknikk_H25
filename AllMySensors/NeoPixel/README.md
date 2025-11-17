# NeoPixel

## Beskrivelse

`NeoPixel` er Adafruits serie av adresserbare RGB/RGBW LED-er basert på WS2812/WS2812B/SK6812. Hver LED kan styres individuelt via én datalinje. Dette biblioteket (eller kodeeksempelet) demonstrerer hvordan man initialiserer, setter farger og kjører animasjoner på NeoPixel-striper eller -ringer.

## Struktur

```
.
├── README.md
├── examples
│   └── NeoPixel_4colors
│       └── NeoPixel_4colors.ino
└── src
    ├── Adafruit_NeoPixel.cpp
    └── Adafruit_NeoPixel.h
```
                                    
## Bruk

```cpp
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <NeoPixelWrapper.h>

constexpr uint8_t LED_PIN = 6;     // datapin
constexpr uint16_t NUM_LEDS = 30;  // antall LEDs på stripen

NeoPixelWrapper pixels(NUM_LEDS, LED_PIN);

void setup() {
  Serial.begin(9600);
  pixels.begin();       // initialiser stripen
  pixels.setBrightness(50); // valgfritt: demp lysstyrke
}

void loop() {
  pixels.setColorAll(255, 0, 0);  // sett all LED til rød
  delay(500);

  pixels.rainbow();               // kjør en enkel regnbueeffekt
  delay(1000);
}
```

Verdiene sendes internt som RGB eller RGBW, avhengig av stripens type. Justering av lysstyrke er nyttig for å unngå høyt strømforbruk.

## Tilkobling

* **5V** → til NeoPixel-stripens 5V-inngang (bruk egen strømforsyning ved mange LED).
* **GND** → felles jord mellom Arduino og LED-stripen.
* **DATA IN** → Arduino digital pin (for eksempel D6).
* **300–500 Ω seriemotstand** anbefales på datalinjen.
* **1000 µF kondensator** mellom 5V og GND for å stabilisere spenningen.

**Retning er viktig:** LED-striper har `DIN` (data inn) og `DOUT` (data ut). Sørg for å koble inn på riktig side.

## Avhengigheter

* `Adafruit_NeoPixel`-biblioteket
* Arduino core (`Arduino.h`)

## For undervisning

Temaer som kan dekkes:

* PWM-basert fargestyring og additive fargemodeller (RGB).
* Strømforbruk og effektberegning for LED-striper.
* Timingkritiske protokoller (800 kHz NeoPixel-protokoll).
* Objektorientert design for å kapsle LED-håndtering i egne klasser.
