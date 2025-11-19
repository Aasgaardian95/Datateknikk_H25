#include <Keypad.h>
#include <LiquidCrystal.h>

// -------------------- LCD --------------------
// Vi bruker digitale pinner 2–7 i rekkefølge til LCD
// LiquidCrystal(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// -------------------- Keypad --------------------
const byte ROWS = 4;  // 4 rader
const byte COLS = 4;  // 4 kolonner

// Keymap for 4x4 keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Rader på digitale pinner (8–11)
// Kolonner på analoge pinner (A0–A3)
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {A0, A1, A2, A3};

// Oppretter keypad-objektet
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------------------- LED --------------------
// Bruker analoge pinner A4 og A5 til LED-er
const int greenLED = 12;
const int redLED   = 13;

// -------------------- KODE --------------------
const String correctCode = "1234";  // Riktig kode
String inputCode = "";              // Buffer for innskrevet kode

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);

  // Setter LED-pinner som utgang
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // Starter LCD
  lcd.begin(16, 2);
  lcd.print("Tast kode:");
  lcd.setCursor(0, 1);
  lcd.print("Avslutt med #");
}

// -------------------- LOOP --------------------
void loop() {
  char key = keypad.getKey(); // Leser tastetrykk

  if (key == NO_KEY) return;  // Hopper over hvis ingen tast trykket

  Serial.print("Key Pressed: ");
  Serial.println(key);

  // ---- RESET MED '*' ----
  if (key == '*') {
    inputCode = "";            // Nullstiller buffer
    lcd.clear();
    lcd.print("Kode resatt");
    lcd.setCursor(0, 1);
    lcd.print("Tast ny kode");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    delay(1500);
    lcd.clear();
    lcd.print("Tast kode:");
    lcd.setCursor(0, 1);
    lcd.print("Avslutt med #");
    return;
  }

  // ---- SJEKK MED '#' ----
  if (key == '#') {
    lcd.clear();
    lcd.print("Kode: ");
    lcd.print(inputCode);

    if (inputCode == correctCode) {
      lcd.setCursor(0, 1);
      lcd.print("Riktig kode!");
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Feil kode!");
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    }

    inputCode = ""; // Nullstiller buffer
    delay(2000);
    lcd.clear();
    lcd.print("Tast kode:");
    lcd.setCursor(0, 1);
    lcd.print("Avslutt med #");
    return;
  }

  // ---- LEGG TIL TAST ----
  inputCode += key;
  lcd.clear();
  lcd.print("Kode: ");
  lcd.print(inputCode);
  lcd.setCursor(0, 1);
  lcd.print("Avslutt med #");
}
