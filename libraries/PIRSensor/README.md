# PIRSensor

Bibliotek som leser en passiv infrarød (PIR) bevegelsessensor og styrer en indikator-LED. Klassen arver fra `BaseSensor` og gir metoden `motionDetected()` for å sjekke status.

## Maskinvare

- PIR-sensorutgang koblet til digital pinne (standard 7)
- LED-indikator (standard `LED_BUILTIN`)

## Eksempel

Se `examples/PIRSensor_Example` for demo.
