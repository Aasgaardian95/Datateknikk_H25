## Anbefalt stegvis prosess for gjennomføring av Arduinoprosjekter basert på caseoppgave

## Overordnet Strategi

Målet er å levere en **fungerende, godt strukturert og forståelig kode**. Prosessen skal vise **forståelse og selvstendig/fornuftig gjennomføring** av oppgaven.

**Husk:** Prioriter alltid **kravspesifikasjonen**. Du får **kun poeng for kravene**; alt annet er bonus.

1.  Start enkelt.
2.  Lag først en enkel løsning som fungerer, og bygg deretter ut den avanserte varianten.
3.  Få én ting til å virke før du bygger videre.

## Stegvis gjennomføring via 6 trinn

### Trinn 1: Forstå Oppgaven

Dette trinnet handler om grundig analyse.

*   Les oppgaven ekstremt nøye før du gjør noe som helst.
*   Les mål og krav svært nøye.
*   Marker uklarheter umiddelbart.
*   Identifiser hvilke sensorer som faktisk er **relevante** for oppgaven.
*   Tenk gjennom hvordan systemet skal testes.

### Trinn 2: Planlegging

Definer veien til målet.

*   Bryt ned problemet i **delmål**.
*   Lag en **punktvis løsningsplan** (inkluderer sensorkobling, logikk og datastrøm).
*   Tegn en **koblingsskisse** (enkelt håndtegnet).
*   Definer **minimumsfunksjon (MVP)** og eventuelle «kan-legg-til»-funksjoner.
*   Sjekk strømkrav og komponentvalg.

### Trinn 3: Grunnimplementasjon

Få basislogikken og komponentene på plass og verifisert.

*   **Koble opp én sensor først**. Test sensorer én og én.
*   Få den til å **fungere** før du går videre.
*   Koble opp, **print verdier**, og verifiser at verdiene gir mening.
*   Bruk **Serial Monitor aktivt**.
*   Implementer **basislogikk** (måling, utskrift til Serial, styring av én aktuator).
*   Test **løpende** (ikke vent til slutten).
*   *Står du fast?* Mål fysisk. Kabler, pins og feil koblinger er vanligere enn kodefeil.

### Trinn 4: Utvide Funksjonalitet

Bygg systemet lagvis.

*   Legg til de resterende sensorene **én om gangen**.
*   Bygg logikk lagvis (bruk *if–else*, terskler, statuslys osv.).
*   Legg på brukerinput (**Keypad/knapper**) til slutt.
*   Test hvert steg i praksis.

### Trinn 5: Stabilisering og Feilhåndtering

Sikre at systemet er robust og takler grensetilfeller.

*   Håndter **debounce**, feiltilfeller, grenser og nullverdier.
*   Håndter frakoblede sensorer eller svake signaler.
*   Rydd opp i globale variabler, timing og funksjoner.
*   Sjekk at logikken oppfyller alle kravene.
*   Test **hele systemet minst én gang sammenhengende**.

### Trinn 6: Dokumentasjon og Rydding

Dette er avgjørende for å demonstrere forståelse og oppnå høyere karakterer.

*   Kommenter koden tydelig – kommentarer hjelper deg selv.
*   Forklar hva du **antar** og hva du **sjekker** underveis.
*   Sikre at oppsettet (koblingen) er **ryddig og lett å følge**.
*   Skriv kort om:
    *   Hvilke sensorer som brukes.
    *   Hvorfor de er relevante.
    *   Hvordan systemet fungerer.
```