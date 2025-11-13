#include <Arduino.h>
#include <KeypadInput.h>

// Oppsett for tastatur (4x4 numerisk)
const byte ANTALL_RADER = 4;
const byte ANTALL_KOLONNER = 4;
const char KEYMAP[ANTALL_RADER * ANTALL_KOLONNER] = {
  '1','2','3','A',
  '4','5','6','B',
  '7','8','9','C',
  '*','0','#','D'
};
const byte RAD_PINNER[ANTALL_RADER] = {2, 3, 4, 5};
const byte KOLONNE_PINNER[ANTALL_KOLONNER] = {6, 7, 8, A1};

KeypadInput tastatur(RAD_PINNER, KOLONNE_PINNER, ANTALL_RADER, ANTALL_KOLONNER, KEYMAP);

// Enkel PIN-kode for demo – kan tilpasses fritt
const char RIKTIG_PIN[] = "1234";
PinTilgangskontroll<sizeof(RIKTIG_PIN)> tilgangskontroll(tastatur, RIKTIG_PIN);

void pinGodkjent() {
  Serial.println("Tilgang gitt – riktig PIN!");
}

void pinAvvist() {
  Serial.println("Feil PIN. Prøv igjen.");
}

void pinProgresjon(const char*, byte lengde) {
  if (lengde == 0) {
    Serial.println("PIN tilbakestilt.");
    return;
  }

  Serial.print("Tast registrert (");
  Serial.print(lengde);
  Serial.println(" sifre lagret)");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tilgangskontroll.setSuksessCallback(pinGodkjent);
  tilgangskontroll.setFeilCallback(pinAvvist);
  tilgangskontroll.setProgresjonCallback(pinProgresjon);

  tilgangskontroll.begin();
}

void loop() {
  tilgangskontroll.oppdater();
  delay(100);
}
