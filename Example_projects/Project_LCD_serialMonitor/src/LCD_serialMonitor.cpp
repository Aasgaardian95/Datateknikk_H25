
// Inkluderer biblioteket som gir funksjoner for å styre LCD
#include <Arduino.h>
#include <LiquidCrystal.h>

// Definerer hvilke Arduino-pinner som er koblet til LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Oppretter et LCD-objekt med de definerte pinnene
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Setter opp LCD med 16 kolonner og 2 rader
  lcd.begin(16, 2);

  // Starter seriell kommunikasjon med PC på 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Sjekker om det finnes data som er sendt inn via seriell porten
  if (Serial.available()) {
    // Venter litt for å sikre at hele meldingen har kommet inn
    delay(100);

    // Tømmer skjermen før ny tekst skrives
    lcd.clear();

    // Leser alle tilgjengelige tegn fra seriell buffer
    while (Serial.available() > 0) {
      // Skriver hvert tegn direkte til LCD-skjermen
      lcd.write(Serial.read());
    }
  }
}
