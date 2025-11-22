#include <Keypad.h>          // Inkluderer bibliotek for å lese 4x4-tastatur
#include <LiquidCrystal.h>   // Inkluderer bibliotek for LCD-skjermen

// -------------------- LCD --------------------

// Definerer hvilke pinner som brukes til LCD-skjermen
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Oppretter et LCD-objekt som bruker digitale pinner 7–2
// LiquidCrystal(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// -------------------- KEYPAD --------------------
// Definerer antall rader og kolonner på tastaturet
const byte ROWS = 4;
const byte COLS = 4;

// Matrisedefinisjon av tastene i tastaturet
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Tastaturets rader koblet til digitale pinner 8–11
// Kolonner koblet til analoge pinner A0–A3
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {A0, A1, A2, A3};

// Oppretter keypad-objektet med keymap og tilhørende pinner
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------------------- LED --------------------
// LED-er på digitale pinner 12 og 13
const int greenLED = 12;   // Grønn LED for "godkjent"
const int redLED   = 13;   // Rød LED for "feil"

// -------------------- KODE --------------------
// Forhåndsdefinert korrekt kode brukeren må taste
const String correctCode = "1234";

// Variabel som lagrer tastetrykk mens brukeren skriver koden
String inputCode = "";

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);          // Starter seriell kommunikasjon

  // Setter LED-pinnene som utganger og slukker dem
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // Initialiserer LCD med 16 kolonner og 2 rader
  lcd.begin(16, 2);
  lcd.print("Tast kode:");     // Første linje
  lcd.setCursor(0, 1);
  lcd.print("Avslutt med #");  // Andre linje
}

// -------------------- LOOP --------------------
void loop() {

  // Leser tastetrykk fra keypad (returnerer NO_KEY hvis ingen tast er trykket)
  char key = keypad.getKey();
  if (key == NO_KEY) return;   // Hvis ingen tast trykket, gjør ingenting

  // Printer tastetrykk til Serial Monitor for debugging
  Serial.print("Key Pressed: ");
  Serial.println(key);

  // -------------------- RESET MED '*' --------------------
  if (key == '*') {           
    inputCode = "";            // Tømmer buffer for innskrevet kode
    
    // Viser reset-melding på LCD
    lcd.clear();
    lcd.print("Kode resatt");
    lcd.setCursor(0, 1);
    lcd.print("Tast ny kode");

    // Slukker LED-ene
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);

    delay(1500);               // Viser meldingen i 1.5 sek

    // Viser standard-instruksjoner igjen
    lcd.clear();
    lcd.print("Tast kode:");
    lcd.setCursor(0, 1);
    lcd.print("Avslutt med #");

    return;
  }

  // -------------------- SJEKK KODE MED '#' --------------------
  if (key == '#') {

    lcd.clear();
    lcd.print("Kode: ");        // Viser koden brukeren skrev
    lcd.print(inputCode);

    // Sjekker om koden stemmer
    if (inputCode == correctCode) {
      lcd.setCursor(0, 1);
      lcd.print("Riktig kode!");
      digitalWrite(greenLED, HIGH);   // Tenn grønn LED
      digitalWrite(redLED, LOW);
    } 
    else {
      lcd.setCursor(0, 1);
      lcd.print("Feil kode!");
      digitalWrite(redLED, HIGH);     // Tenn rød LED
      digitalWrite(greenLED, LOW);
    }

    inputCode = "";   // Nullstiller buffer etter sjekk
    delay(2000);      // Vent litt før ny input

    // Viser instruksjonene igjen
    lcd.clear();
    lcd.print("Tast kode:");
    lcd.setCursor(0, 1);
    lcd.print("Avslutt med #");

    return;
  }

  // -------------------- LEGG TIL TAST I BUFFER --------------------
  // Legger inn tastene brukeren trykker (unntatt * og #)
  inputCode += key;

  // Oppdaterer LCD med nåværende kodestreng
  lcd.clear();
  lcd.print("Kode: ");
  lcd.print(inputCode);
  lcd.setCursor(0, 1);
  lcd.print("Avslutt med #");
}