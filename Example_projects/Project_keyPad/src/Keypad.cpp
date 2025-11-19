#include <Keypad.h> 

// -------------------- KONFIGURASJON AV TASTATUR --------------------

const byte ROWS = 4;  // Antall rader og kolonner på keypaden
const byte COLS = 4;

char keys[ROWS][COLS] = { // Definerer hvilke tegn som ligger på hver knapp i tastaturet
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Arduino-pinner koblet til radene på tastaturet

byte colPins[COLS] = {5, 4, 3, 2}; // Arduino-pinner koblet til kolonnene på tastaturet

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Oppretter selve keypad-objektet med knappene og tilhørende pinner

// -------------------- LED-PINNER --------------------
const int greenLED = 11;  // Grønn LED på pin 11 (viser riktig kode)
const int redLED   = 10;  // Rød LED på pin 10 (viser feil kode)

// -------------------- KODEINNSTILLINGER --------------------
const String correctCode = "1234";  // Koden som kreves for å få grønn LED
String inputCode = "";              // Buffer som lagrer tastene brukeren taster inn


// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);        // Starter seriell kommunikasjon på 9600 baud

  // Setter LED-pinner som utgang
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Starter med å ha begge LED av
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // Instruksjoner til brukeren
  Serial.println("Tast inn kode og avslutt med #: ");
}


// -------------------- LOOP --------------------
void loop() {

  // Leser om en tast er trykket
  char key = keypad.getKey();

  // Hvis ingen tast ble trykket, gjør ingenting
  if (key == NO_KEY) return;

  // Skriver til Serial Monitor hver gang en tast trykkes
  Serial.print("Key Pressed: ");
  Serial.println(key);

  // ---- RESET AV INNSKRIVING MED '*' ----
  if (key == '*') {                   // Hvis brukeren trykker *, nullstilles innskrevet kode
    inputCode = "";                   // Sletter bufferen
    Serial.println("Input resatt.");  
    digitalWrite(greenLED, LOW);      // Slukker begge LEDer
    digitalWrite(redLED, LOW);
    return;
  }

  // ---- SJEKKER KODE MED # ----
  // Når brukeren trykker # betyr det "sjekk koden"
  if (key == '#') {

    Serial.print("Kode skrevet: ");
    Serial.println(inputCode);        // Viser hva brukeren skrev

    // Sammenligner brukerens kode med fasiten
    if (inputCode == correctCode) {
      Serial.println("Riktig kode!");
      digitalWrite(greenLED, HIGH);   // Tenn grønn LED
      digitalWrite(redLED, LOW);      // Slukk rød LED
    } 
    else {
      Serial.println("Feil kode!");
      digitalWrite(redLED, HIGH);     // Tenn rød LED
      digitalWrite(greenLED, LOW);    // Slukk grønn LED
    }

    // Tømmer kodebuffer etter sjekk
    inputCode = "";
    return;
  }

  // ---- LEGG TIL TAST I BUFFER ----
  // Hvis ikke * eller #, legger vi til tegnet i inputCode
  inputCode += key;
}
