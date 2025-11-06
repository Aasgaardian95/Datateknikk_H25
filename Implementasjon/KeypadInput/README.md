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
| `examples/Keypad_AccessControl/Keypad_AccessControl.ino` | Eksempel | Viser enkel PIN-basert tilgang uten ekstra sensorer. |

## 🧠 Bruk
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
char inndata[sizeof(RIKTIG_PIN)] = {'\0'};
byte indeks = 0;

void nullstillInndata() {
  indeks = 0;
  memset(inndata, 0, sizeof(inndata));
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tastatur.begin();
}

void loop() {
  tastatur.read();

  char tast = tastatur.getKey();
  if (tast) {
    if (tast == '*') {
      nullstillInndata();
      Serial.println("PIN tilbakestilt.");
    } else if (tast == '#') {
      if (strcmp(inndata, RIKTIG_PIN) == 0) {
        Serial.println("Tilgang gitt – riktig PIN!");
      } else {
        Serial.println("Feil PIN. Prøv igjen.");
      }
      nullstillInndata();
    } else if (indeks < sizeof(inndata) - 1) {
      inndata[indeks++] = tast;
      Serial.print("Tast registrert (");
      Serial.print(indeks);
      Serial.println(" sifre lagret)");
    } else {
      Serial.println("PIN er full. Trykk # for å bekrefte eller * for å slette.");
    }
  }

  delay(100);
}
```
Programmet gir enkel seriell feedback. Stjerne sletter inndata, #-tasten validerer mot PIN-koden.

## 🔌 Tilkobling
- Radpinner: 2, 3, 4, 5.
- Kolonnepinner: 6, 7, 8, A1.
- Tastaturet krever ingen ekstra motstander; koble en radpinne og kolonnepinne til hver tast.
- Eksempelet demonstrerer enkel PIN-verifisering uten eksterne sensorer.

## 🧱 Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket
- `Keypad`-biblioteket

## 👩‍🏫 For undervisning
Temaer som kan belyses:
- Matriseskanning og hvordan `Keypad`-biblioteket forenkler logikken.
- Enkel autorisasjon basert på tastaturet alene.
- Objektorientert design hvor tastaturet oppfører seg som en sensor gjennom `BaseSensor`.
