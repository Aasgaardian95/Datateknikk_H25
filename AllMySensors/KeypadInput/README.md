# KeypadInput

## Beskrivelse
`KeypadInput` håndterer et 4x4 matrise-tastatur ved hjelp av `Keypad`-biblioteket. Klassen arver fra `BaseSensor` slik at tastetrykk kan behandles med samme mønster som øvrige sensorer, inkludert logging gjennom `printDebug()`.

Biblioteket inkluderer også hjelpeklassen `PinTilgangskontroll` som kan utføre PIN-validering direkte i biblioteket, mens brukerdefinerte reaksjoner implementeres i `.ino`-filen gjennom callback-funksjoner.

## Struktur
```
.
├── README.md
├── examples
│   └── Keypad_AccessControl
│       └── Keypad_AccessControl.ino
└── src
    ├── KeypadInput.cpp
    └── KeypadInput.h
```

## Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/KeypadInput.h` | Header | Definerer tastaturklassen med dynamisk lagring av rad- og kolonnepinner. |
| `src/KeypadInput.cpp` | Implementasjon | Initialiserer `Keypad`-objektet og skriver tastetrykk til seriellmonitor. |
| `examples/Keypad_AccessControl/Keypad_AccessControl.ino` | Eksempel | Viser PIN-basert tilgang der PIN-sjekk håndteres av biblioteket og tilpasses via callbacks. |

## Bruk
```cpp
#include <Arduino.h>
#include <KeypadInput.h>

// Oppsett for tastatur (4x4 numerisk)
const byte ANTALL_RADER = 4;
const byte ANTALL_KOLONNER = 4;
const char KEYMAP[ANTALL_RADER * ANTALL_KOLONNER] = {
  '1','2','3','A',
  '4','5','6','B',
  '7','8','9','C',
  '*','0','#','D'
};
const byte RAD_PINNER[ANTALL_RADER] = {2, 3, 4, 5};
const byte KOLONNE_PINNER[ANTALL_KOLONNER] = {6, 7, 8, A1};

KeypadInput tastatur(RAD_PINNER, KOLONNE_PINNER, ANTALL_RADER, ANTALL_KOLONNER, KEYMAP);

// Enkel PIN-kode for demo
const char RIKTIG_PIN[] = "1234";
PinTilgangskontroll<sizeof(RIKTIG_PIN)> tilgangskontroll(tastatur, RIKTIG_PIN);

void pinGodkjent() {
  Serial.println("Tilgang gitt – riktig PIN!");
}

void pinAvvist() {
  Serial.println("Feil PIN. Prøv igjen.");
}

void pinProgresjon(const char*, byte lengde) {
  if (lengde == 0) {
    Serial.println("PIN tilbakestilt.");
    return;
  }

  Serial.print("Tast registrert (");
  Serial.print(lengde);
  Serial.println(" sifre lagret)");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tilgangskontroll.setSuksessCallback(pinGodkjent);
  tilgangskontroll.setFeilCallback(pinAvvist);
  tilgangskontroll.setProgresjonCallback(pinProgresjon);
  tilgangskontroll.begin();
}

void loop() {
  tilgangskontroll.oppdater();
  delay(100);
}
```
Programmet gir enkel seriell feedback. Stjerne sletter inndata, #-tasten validerer mot PIN-koden, og alle reaksjoner håndteres i `.ino`-filen gjennom callback-funksjoner.

## Tilkobling
- Radpinner: 2, 3, 4, 5.
- Kolonnepinner: 6, 7, 8, A1.
- Tastaturet krever ingen ekstra motstander; koble en radpinne og kolonnepinne til hver tast.
- Eksempelet demonstrerer enkel PIN-verifisering uten eksterne sensorer.

## Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket
- `Keypad`-biblioteket

## For undervisning
Temaer som kan belyses:
- Matriseskanning og hvordan `Keypad`-biblioteket forenkler logikken.
- Enkel autorisasjon basert på tastaturet alene.
- Objektorientert design hvor tastaturet oppfører seg som en sensor gjennom `BaseSensor`.
