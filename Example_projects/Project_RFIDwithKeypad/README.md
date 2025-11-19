## RFID-leser med keypad og 2FA autentisering
...

## Oppkobling
Fra RFIDreader prosjektet:
- RFID-modul:
    - SS/SDA til digital pinne 10 (kan endres i konstruktøren).
    - RST til pinne 9.
    - MOSI til pinne 11, MISO til pinne 12, SCK til pinne 13 på Arduino Uno (SPI-standardpinner).
    - Strømforsyning: 3.3 V og GND.
    - Husk å holde kortet i ro noen sekunder for stabil lesing.
- LED (rød):
    - Katode -> 220/1k ohm -> GND
    - Anode -> digital pinne 5
- LED (grønn):
    - Katode -> 220/1k ohm -> GND
    - Anode -> digital pinne 6

Fra KEYPAD prosjektet:
- Membrane switch module:
    - Rad 1 -> digital pinne 9
    - Rad 2 -> digital pinne 8
    - Rad 3 -> digital pinne 7
    - Rad 4 -> digital pinne 6
    - Kolonne 1 -> digital pinne 5
    - Kolonne 2 -> digital pinne 4
    - Kolonne 3 -> digital pinne 3
    - Kolonne 4 -> digital pinne 2
- LED (rød):
    - Katode -> 220/1k ohm -> GND
    - Anode -> digital pinne 10
- LED (grønn):
    - Katode -> 220/1k ohm -> GND
    - Anode -> digital pinne 11

## Demonstrasjonsvideo

[![Demo Video](https://img.youtube.com/vi/KL8Wdw21BKg/0.jpg)](https://www.youtube.com/shorts/KL8Wdw21BKg)
