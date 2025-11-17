# Sensorbiblioteker

## Oversikt
Denne katalogen samler alle Arduino-bibliotekene som brukes i undervisningsprosjektet. Hvert bibliotek arver fra `BaseSensor` og følger samme struktur med en `src/`-mappe for kode og en `examples/`-mappe med minst ett komplett `.ino`-program. Les README-filen i hvert bibliotek for detaljert bruk, koblingsskjema og læringsmål.

## Struktur
```
.
├── BME280Sensor/
├── BaseSensor/
├── ENS160Sensor/
├── KeypadInput/
├── LDRSensor/
├── PIRSensor/
└── RFIDReader/
```

## Biblioteksliste
| Bibliotek | Formål | Eksempelfil |
| --- | --- | --- |
| `BME280Sensor` | Leser temperatur, fuktighet og trykk over I²C. | `examples/BME280Sensor_Example/BME280Sensor_Example.ino` |
| `BaseSensor` | Abstrakt grunnklasse som standardiserer `begin()`, `read()` og logging. | Brukes av alle andre biblioteker | 
| `ENS160Sensor` | Håndterer luftkvalitetssensoren ENS160 med eCO₂- og AQI-data. | `examples/ENS160Sensor_Example/ENS160Sensor_Example.ino` |
| `KeypadInput` | Leser 4x4-matrise-tastatur og leverer siste tastetrykk. | `examples/Keypad_AccessControl/Keypad_AccessControl.ino` |
| `LDRSensor` | Leser analogt lysnivå fra LDR i spenningsdeler. | `examples/LDRSensor_Example/LDRSensor_Example.ino` |
| `PIRSensor` | Registrerer bevegelse fra en PIR-sensor og styrer indikator-LED. | `examples/PIRSensor_Example/PIRSensor_Example.ino` |
| `RFIDReader` | Styrer MFRC522 RFID-leser via SPI og eksponerer kortets UID. | `examples/RFIDReader_Example/RFIDReader_Example.ino` |

## Bruk av bibliotekene
1. Kopier mappen til `Documents/Arduino/libraries/`.
2. Start Arduino IDE og åpne eksemplene fra `Fil → Eksempler → <Biblioteksnavn>`.
3. Kompiler og last opp til et kompatibelt kort (Arduino Uno, Nano o.l.).

Alle bibliotekene kan kombineres gjennom `BaseSensor`-grensesnittet for å demonstrere objektorientert design og polymorfisme.

## For undervisning
Strukturen gjør det enkelt å diskutere:
- Hvordan arv og virtuelle metoder brukes for å gi felles API til ulike sensorer.
- Forskjeller mellom analoge, digitale, I²C- og SPI-baserte sensorer.
- Hvordan komplette undervisningsopplegg kan bygges ved å kombinere flere sensorer og felles baseklasser.
