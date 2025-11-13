# RFIDReader

## 📘 Beskrivelse
`RFIDReader` styrer MFRC522-modulen for å lese RFID-kort. Klassen arver fra `BaseSensor` og eksponerer metoder for å sjekke om et kort er til stede og hente UID som tekst eller bytearray.

## 📁 Struktur
```
.
├── README.md
├── examples
│   └── RFIDReader_Example
│       └── RFIDReader_Example.ino
└── src
    ├── RFIDReader.cpp
    └── RFIDReader.h
```

### ⚙️ Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/RFIDReader.h` | Header | Definerer klassen med hjelpefunksjoner for UID som streng og byte-array. |
| `src/RFIDReader.cpp` | Implementasjon | Initialiserer SPI, sjekker etter nye kort og buffer UID når et kort registreres. |
| `examples/RFIDReader_Example/RFIDReader_Example.ino` | Eksempel | Viser enkel tilgangskontroll med autorisert UID og seriell feedback. |

## 🧠 Bruk
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <RFIDReader.h>

constexpr uint8_t SS_PIN = 10;   // SDA til pinne 10 på Arduino UNO
constexpr uint8_t RST_PIN = 9;   // RST til pinne 9

// Eksempel på autorisert UID (4 byte). Verdiene må oppgis i heks.
byte autorisertKort[4] = {0xDE, 0xAD, 0xBE, 0xEF};

RFIDReader leser(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  leser.begin();
  Serial.println("Legg et kort på leseren for å teste.");
}

void loop() {
  leser.read();

  if (leser.cardDetected()) {
    String uid = leser.getUID();
    Serial.print("Kontrollerer UID ");
    Serial.println(uid);

    byte uidBuffer[10];
    byte uidLength = 0;
    if (leser.getUIDBytes(uidBuffer, sizeof(uidBuffer), uidLength)) {
      if (uidLength == sizeof(autorisertKort) && memcmp(uidBuffer, autorisertKort, uidLength) == 0) {
        Serial.println("Tilgang gitt – kortet er autorisert.");
      } else {
        Serial.println("Tilgang avslått – ukjent kort.");
      }
    }
  }

  delay(500);
}
```
Seriellmonitoren viser UID-en i heks og forteller om kortet er godkjent. Fjernes kortet, kommer meldingen «[RFID] Kort fjernet.» fra biblioteket.

## 🔌 Tilkobling
- **SS/SDA** til digital pinne 10 (kan endres i konstruktøren).
- **RST** til pinne 9.
- **MOSI** til pinne 11, **MISO** til pinne 12, **SCK** til pinne 13 på Arduino Uno (SPI-standardpinner).
- Strømforsyning: 3.3 V og GND.
- Husk å holde kortet i ro noen sekunder for stabil lesing.

## 🧱 Avhengigheter
- Arduino core (`Arduino.h`, `SPI.h`)
- `BaseSensor`-biblioteket
- `MFRC522`-biblioteket for RFID-driver

## 👩‍🏫 For undervisning
Brukes til å diskutere:
- SPI-kommunikasjon og forskjellen mellom master/slave-oppsett.
- Sikkerhet og autentisering via UID sammen med andre sensorer (f.eks. tastatur).
- Polymorf bruk sammen med andre sensorer gjennom `BaseSensor`.
