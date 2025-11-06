# RFIDReader

Bibliotek for MFRC522-basert RFID-leser. Viser hvordan man leser UID og kontrollerer kort mot en autorisert liste.

## Maskinvare

- MFRC522 modul koblet via SPI (SS pinne 10, RST pinne 9 som standard)

## Programvare

Installer MFRC522-biblioteket i Arduino IDE.

## Eksempel

Se `examples/RFIDReader_Example` for tilgangskontroll med `memcmp`.
