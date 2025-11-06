# BaseSensor

Felles grunnklasse for alle sensorbibliotekene i prosjektet. Klassen gir navnsetting, felles tidsstempel for siste avlesing og en enkel `printDebug()`-metode.

## Bruk

Inkluder `BaseSensor.h` og la dine egne sensor-klasser arve fra `BaseSensor` for å dele felles struktur for `begin()` og `read()`.
