# mal-arduino-bibliotek

Dette prosjektet viser hvordan man kan strukturere flere Arduino-sensorbibliotek med en felles baseklasse. Koden og kommentarene er på norsk og laget som undervisningsmateriell for Høgskolen i Østfold.

## Mappestruktur

```
/libraries/
  BaseSensor/
  LDRSensor/
  PIRSensor/
  BME280Sensor/
  ENS160Sensor/
  RFIDReader/
  KeypadInput/
/examples/
  MultiSensorDemo/
```

Hvert bibliotek ligger i egen mappe med `src/` for kildekode og `examples/` for demo-skisser. I tillegg finnes et kombinert eksempel som viser polymorf bruk av `BaseSensor`.

## Komme i gang

1. Pakk biblioteket som `.zip` eller kopier mappestrukturen direkte inn i `Arduino/libraries/`.
2. Installer eksterne avhengigheter via Library Manager:
   - Adafruit BME280 Library
   - ENS160 (for eksempel SparkFun-implementasjonen)
   - MFRC522
   - Keypad
3. Åpne ønsket eksempel i Arduino IDE og velg riktige port/board (Arduino UNO).
4. Last opp og observer seriell monitor på 9600 baud.

## Innhold

- `BaseSensor` – grunnklassen for alle sensorer.
- `LDRSensor` – analog lysmåler.
- `PIRSensor` – digital bevegelsessensor med LED-indikasjon.
- `BME280Sensor` – temperatur, fuktighet og trykk via I2C.
- `ENS160Sensor` – luftkvalitetsmålinger (AQI og CO₂-ekvivalent).
- `RFIDReader` – leser MFRC522-kort og demonstrerer UID-sammenligning med `memcmp`.
- `KeypadInput` – håndterer matrise-tastatur og brukes sammen med RFID i et tilgangskontroll-eksempel.
- `examples/MultiSensorDemo` – demonstrerer polymorfisme ved å behandle alle sensorene gjennom `BaseSensor`-peker.

## Videre arbeid

Utvid bibliotekene med flere sensorer ved å arve fra `BaseSensor` og følge samme struktur. Husk å kommentere på norsk og forklare alle faste verdier slik at studenter enkelt kan følge koden.
