# KeypadInput

## 📘 Beskrivelse
`KeypadInput` håndterer et 4x4 matrise-tastatur ved hjelp av `Keypad`-biblioteket. Klassen arver fra `BaseSensor` slik at tastetrykk kan behandles med samme mønster som øvrige sensorer, inkludert logging gjennom `printDebug()`.

## 📁 Struktur
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

### ⚙️ Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/KeypadInput.h` | Header | Definerer tastaturklassen med dynamisk lagring av rad- og kolonnepinner. |
| `src/KeypadInput.cpp` | Implementasjon | Initialiserer `Keypad`-objektet og skriver tastetrykk til seriellmonitor. |
| `examples/Keypad_AccessControl/Keypad_AccessControl.ino` | Eksempel | Kombinerer tastatur og RFID for enkel tilgangskontroll. |

## 🧠 Bruk
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <RFIDReader.h>
#include <KeypadInput.h>

// Oppsett for RFID
constexpr uint8_t RFID_SS_PIN = 10;
constexpr uint8_t RFID_RST_PIN = 9;
byte autorisertUID[4] = {0xDE, 0xAD, 0xBE, 0xEF};

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
RFIDReader rfid(RFID_SS_PIN, RFID_RST_PIN);

// Enkel PIN-kode for demo
const char KODE[5] = {'1', '2', '3', '4', '\0'};
char inndata[5] = {'\0'};
byte indeks = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Tilgangskontroll: legg kortet på leseren og tast PIN.");

  rfid.begin();
  tastatur.begin();
}

void loop() {
  rfid.read();
  tastatur.read();

  char tast = tastatur.getKey();
  if (tast) {
    if (tast == '*') {
      indeks = 0;
      memset(inndata, 0, sizeof(inndata));
      Serial.println("PIN tilbakestilt.");
    } else if (tast == '#') {
      if (strcmp(inndata, KODE) == 0) {
        byte uidBuffer[10];
        byte uidLength = 0;
        if (rfid.getUIDBytes(uidBuffer, sizeof(uidBuffer), uidLength) &&
            uidLength == sizeof(autorisertUID) &&
            memcmp(uidBuffer, autorisertUID, uidLength) == 0) {
          Serial.println("Tilgang gitt – korrekt kort og kode!");
        } else {
          Serial.println("Kort ikke autorisert eller ikke tilstede.");
        }
      } else {
        Serial.println("Feil PIN. Prøv igjen.");
      }
      indeks = 0;
      memset(inndata, 0, sizeof(inndata));
    } else if (indeks < sizeof(inndata) - 1) {
      inndata[indeks++] = tast;
      Serial.print("Tast registrert (\\*");
      Serial.print(indeks);
      Serial.println(" sifre lagret)");
    }
  }

  delay(100);
}
```
Programmet gir både auditiv (seriell) og taktil feedback. Stjerne sletter inndata, #-tasten validerer mot PIN og RFID-kortet.

## 🔌 Tilkobling
- Radpinner: 2, 3, 4, 5.
- Kolonnepinner: 6, 7, 8, A1.
- Tastaturet krever ingen ekstra motstander; koble en radpinne og kolonnepinne til hver tast.
- Eksempelet viser også hvordan tastatur og RFID-leser kan dele prosjektet.

## 🧱 Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket
- `Keypad`-biblioteket
- (I eksempelet) `RFIDReader` og `SPI`

## 👩‍🏫 For undervisning
Temaer som kan belyses:
- Matriseskanning og hvordan `Keypad`-biblioteket forenkler logikken.
- Kombinasjon av flere sensorer/inn-enheter i ett system.
- Objektorientert design hvor tastaturet oppfører seg som en sensor gjennom `BaseSensor`.
