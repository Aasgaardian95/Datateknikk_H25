# BME280Sensor

Bibliotek som bruker `Adafruit_BME280` til å lese temperatur, luftfuktighet og lufttrykk. Klassen arver fra `BaseSensor` og lagrer siste måling for enkel tilgang.

## Maskinvare

- BME280-modul koblet til I2C (SDA/SCL)
- Standardadresse 0x76 (sett byttbar til 0x77 ved behov)

## Programvare

Installer Adafruit BME280-biblioteket via Library Manager før kompilering.

## Eksempel

Se `examples/BME280Sensor_Example`.
