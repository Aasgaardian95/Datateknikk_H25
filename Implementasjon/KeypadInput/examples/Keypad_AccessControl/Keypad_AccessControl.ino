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

// Enkel PIN-kode for demo
const char RIKTIG_PIN[] = "1234";
char inndata[sizeof(RIKTIG_PIN)] = {'\0'};
byte indeks = 0;

void nullstillInndata() {
  indeks = 0;
  memset(inndata, 0, sizeof(inndata));
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tastatur.begin();
}

void loop() {
  tastatur.read();

  char tast = tastatur.getKey();
  if (tast) {
    if (tast == '*') {
      nullstillInndata();
      Serial.println("PIN tilbakestilt.");
    } else if (tast == '#') {
      if (strcmp(inndata, RIKTIG_PIN) == 0) {
        Serial.println("Tilgang gitt – riktig PIN!");
      } else {
        Serial.println("Feil PIN. Prøv igjen.");
      }
      nullstillInndata();
    } else if (indeks < sizeof(inndata) - 1) {
      inndata[indeks++] = tast;
      Serial.print("Tast registrert (");
      Serial.print(indeks);
      Serial.println(" sifre lagret)");
    } else {
      Serial.println("PIN er full. Trykk # for å bekrefte eller * for å slette.");
    }

    void leggTilSiffer(char tast) {
      if (_indeks < PIN_LENGDE - 1) {
        _inndata[_indeks++] = tast;
        Serial.print("Tast registrert (");
        Serial.print(_indeks);
        Serial.println(" sifre lagret)");
      } else {
        Serial.println("PIN er full. Trykk # for å bekrefte eller * for å slette.");
      }
    }
};

// Enkel PIN-kode for demo
const char RIKTIG_PIN[] = "1234";
PinTilgangskontroll<sizeof(RIKTIG_PIN)> tilgangskontroll(tastatur, RIKTIG_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tilgangskontroll.begin();
}

void loop() {
  tilgangskontroll.oppdater();
  delay(100);
}
