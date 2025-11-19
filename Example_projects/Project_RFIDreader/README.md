## RFID-leser med autentisering og LED-lys for godkjent og ikke-godkjent kort
...

## Oppkobling
- RFID-modul:
    - SS/SDA til digital pinne 10 (kan endres i konstruktøren).
    - RST til pinne 9.
    - MOSI til pinne 11, MISO til pinne 12, SCK til pinne 13 på Arduino Uno (SPI-standardpinner).
    - Strømforsyning: 3.3 V og GND.
    - Husk å holde kortet i ro noen sekunder for stabil lesing.
- LED (rød):
    - Katode -> 1k ohm -> GND
    - Anode -> digital pinne 5
- LED (grønn):
    - Katode -> 1k ohm -> GND
    - Anode -> digital pinne 6

## Demonstrasjonsvideo

[![Demo Video](https://img.youtube.com/vi/KL8Wdw21BKg/0.jpg)](https://www.youtube.com/shorts/KL8Wdw21BKg)
