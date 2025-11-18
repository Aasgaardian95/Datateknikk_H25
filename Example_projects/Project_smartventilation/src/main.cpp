#include <Arduino.h>

/*  
---Caseoppgaven i sin helhet---
Smart ventilasjonssystem for arbeidsrom.

I et arbeidsrom med mange elektroniske komponenter og mennesker kan temperaturen og luftfuktigheten bli høy. Dette kan påvirke både komfort og utstyr. Systemet skal overvåke forholdene og aktivere en vifte ved behov.

Mål: Utvikle et system som overvåker temperatur og fuktighet og styrer en vifte automatisk.

Kravspesifikasjon:

- Måle temperatur og fuktighet.

- Aktivere vifte når verdiene overstiger en grense.

- Gi visuell tilbakemelding om status. 
*/

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}