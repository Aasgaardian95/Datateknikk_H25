#include <Arduino.h>
#include <LiquidCrystal.h>

// Definerer hvilke Arduino-pinner som er koblet til LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Oppretter et LCD-objekt med de definerte pinnene
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// LDR koblet til analog pin A0 (via spenningsdeler med motstand)
const int ldrPin = A0;

void setup() {
  // Setter opp LCD med 16 kolonner og 2 rader
  lcd.begin(16, 2);

  // Starter seriell kommunikasjon for debugging
  Serial.begin(9600);

  // Skriver en velkomstmelding på LCD
  lcd.print("LDR test klar!");
}

void loop() {
  // Leser verdien fra LDR (0–1023)
  int ldrValue = analogRead(ldrPin);

  // Konverterer til prosent (0–100 %)
  int ldrPercent = map(ldrValue, 0, 1023, 0, 100);

  // Skriver verdien til Serial Monitor
  Serial.print("LDR raw: ");
  Serial.print(ldrValue);
  Serial.print("  Lys: ");
  Serial.print(ldrPercent);
  Serial.println("%");

  // Oppdaterer LCD
  lcd.clear();             // Tøm skjermen
  lcd.setCursor(0, 0);     // Første linje
  lcd.print("Lysstyrke:");
  lcd.setCursor(0, 1);     // Andre linje
  lcd.print(ldrPercent);
  lcd.print("%");

  // Oppdatering hvert 0,5 sekund
  delay(500);
}
