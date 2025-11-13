# Tilpassingsguide for mal-arduino-biblioteket

Denne veiledningen hjelper deg å ta utgangspunkt i biblioteket og koble det til dine egne sensorer. Innholdet er strukturert slik at du raskt kommer i gang, samtidig som du får en dypere forståelse av hvordan koden er bygget opp.

## Oversikt

Prosjektet består i hovedsak av tre filer:

| Fil | Rolle |
| --- | --- |
| `main.ino` | Skjelettskissen som initialiserer biblioteket og kjører sensorlogikk. |
| `sensor.h` | Grensesnittet og datatypene som beskriver hvordan en sensor skal oppføre seg. |
| `sensor.cpp` | Standardimplementasjonen av sensorlogikken, inkludert eksempel på avlesing og behandling. |

For å tilpasse prosjektet til egne sensorer justerer du hovedsakelig `sensor.h` og `sensor.cpp`, og sørger for at `main.ino` initialiserer de korrekte sensorinstansene.

## 1. Forstå sensorgrensesnittet

I `sensor.h` finner du strukturene og funksjonsprototypene som definerer hvordan en sensor skal initialiseres, avleses og eventuelt kalibreres. Start med å:

1. Åpne `sensor.h` og se på datastrukturen(e) som beskriver en sensor.
2. Identifisere hvilke felt du trenger for din sensor (for eksempel pinnetilkoblinger, kalibreringskonstanter eller tidsintervaller).
3. Legge til nye felter dersom sensoren din krever det. Husk å dokumentere dem med kommentarer slik at det er tydelig hva de brukes til.

## 2. Implementer sensorlogikken

Når grensesnittet er klart, oppdaterer du `sensor.cpp`:

1. Gå til funksjonen som initialiserer sensoren (typisk `initSensor`). Sett opp riktige pinmodes, I²C/SPI-konfigurasjon eller annen init-logikk du trenger.
2. Tilpass avlesingsfunksjonen (`readSensor` eller tilsvarende). Her bruker du Arduino-API-et for å hente data fra sensoren, normalisere verdiene og fylle ut strukturen definert i `sensor.h`.
3. Legg inn eventuell feilbehandling. Sjekk for gyldige målinger, håndter avvik og gi en strukturert returverdi (bool, enum eller feilkode).
4. Dersom du trenger filtrering, glatting eller konvertering til fysiske enheter (°C, %, m/s²), gjør det her.

> **Tips:** Start med en enkel implementasjon som bare returnerer rådata. Når du ser at avlesningen fungerer, kan du legge til kalibrering og videre signalbehandling.

## 3. Oppdater hovedskissen (`main.ino`)

Etter at sensorlogikken er implementert, sørg for at `main.ino` bruker den nye sensoren korrekt:

1. Opprett og initialiser sensorobjektet i `setup()`.
2. Kall avlesingsfunksjonen i `loop()` med ønsket intervall. Bruk `millis()` for å unngå blokkerende `delay()` hvis du trenger flere samtidige oppgaver.
3. Legg til logging via `Serial`, eller send data videre til skjerm, nettverk eller annet grensesnitt.
4. Test med seriell monitor for å bekrefte at dataene ser riktige ut.

## 4. Konfigurasjon og gjenbruk

For å gjøre biblioteket fleksibelt anbefales det å:

- Samle konfigurasjonsverdier (pinnenumre, terskler, kalibreringsfaktorer) i én struktur eller i `#define`/`constexpr`-konstanter.
- Dokumentere enhver sensor-spesifikk forskjell direkte i koden og i denne README-en.
- Vurdere å bruke `#ifdef` eller separate klasser dersom du skal støtte flere sensortyper i samme prosjekt.

## 5. Testing og feilsøking

1. Test én endring om gangen. Start med å bekrefte at sensoren gir livstegn (for eksempel med en enkel `analogRead` eller `digitalRead`).
2. Bruk seriell logging (`Serial.print`) for å spore avvik.
3. Hvis du bruker kommunikasjon som I²C eller SPI, sjekk med et verktøy som I²C-scanner for å bekrefte adressen.
4. Dokumenter funn og justeringer slik at de er enkle å gjenbruke senere.

## 6. Utvidelse

Når én sensor fungerer, kan du utvide til flere:

- Opprett en egen struktur og implementasjon for hver sensortype, eller lag et felles abstrakt grensesnitt som de ulike sensorene implementerer.
- Bruk `std::vector` (med støtte fra ArduinoSTL) eller enkle arrays for å lagre flere instanser.
- Sørg for at `loop()` håndterer avlesing og oppdatering for alle sensorene uten å blokkeres.

## 7. Ressurser

- [Arduino Reference](https://www.arduino.cc/reference/en/) – Offisiell dokumentasjon for funksjoner og API-er.
- Databladet til sensoren din – Inneholder nødvendige timing-, spennings- og kommunikasjonsdetaljer.
- Forum og open source-prosjekter for den aktuelle sensoren – Gode kilder for eksempelimplementasjoner.

## 8. Forslag til videre dokumentasjon

- Lag en egen seksjon i README for hver sensor du støtter, med koblingsskjema og konfigurering.
- Opprett en `docs/`-mappe med diagrammer eller tilkoblingsskisser (for eksempel laget i Fritzing).
- Dokumenter endringer i `CHANGELOG.md` hvis biblioteket skal deles med andre.

Med denne veiledningen skal du kunne tilpasse biblioteket til de fleste sensorer. Husk å iterere: små trinn og jevn testing gir best resultat. Lykke til!
