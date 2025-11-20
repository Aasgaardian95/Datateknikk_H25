/*
Logikk:
- BME280 måler temperatur og fuktighet
- ENS160 måler luftkvalitet (TVOC og eCO2), kompensert med temp/hum
- Keypad brukes for firesifret kode
- Korrekt kode → alarm av, lås åpnes, grønn LED
- Feil kode → rød LED blinker i tidsvindu
- Tidsvindu utløpt → buzzer (alarm)
- Dørbrudd (sensor) → umiddelbar alarm
- Serial Monitor viser alle sensordata og brukerinput for debugging
*/

#include <Wire.h>                   // I2C-kommunikasjon
#include <SparkFunBME280.h>         // SparkFun BME280-bibliotek
#include <SparkFun_ENS160.h>        // SparkFun ENS160-bibliotek
#include <Keypad.h>                 // Keypad for kodeinntasting

#define DOOR_SENSOR 10               // Dørbruddsensor
#define GREEN_LED 3                 // LED som lyser når alarm er av
#define RED_LED 4                   // LED som lyser ved feil kode / alarm
#define BUZZER 5                    // Buzzer for alarm
#define MOTOR_LOCK 6                // Motor/servo for lås

const String correctCode = "1234";  // Definert korrekt kode
const unsigned long timeout = 10000; // Tidsvindu for kodeinntasting (10 sekunder)

// Keypad-konfigurasjon
const byte ROWS = 4, COLS = 4;      // 4x4 keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Pinner til rader
byte colPins[COLS] = {5, 4, 3, 2}; // Pinner til kolonner
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Keypad objekt

BME280 myBME;                       // BME280 objekt
ENS160 myENS;                        // ENS160 objekt

bool alarmOn = false;                // Alarmstatus
unsigned long codeEntryStart = 0;    // Starttid for kodeinntasting
String inputCode = "";               // Brukerinput

void setup() {
  Serial.begin(9600);                // Start Serial Monitor
  if (!myBME.begin()) {              // Sjekk om BME280 finnes
    Serial.println("BME280 ikke funnet!");
    while (1);                       // Stopp her hvis ikke funnet
  }
  if (myENS.begin() != 0) {          // Sjekk om ENS160 finnes
    Serial.println("ENS160 ikke funnet!");
    while (1);                       // Stopp her hvis ikke funnet
  }
  myENS.iaqInit();                   // Initialiser ENS160 IAQ

  // Aktuatorpinner
  pinMode(GREEN_LED, OUTPUT);        // Grønn LED
  pinMode(RED_LED, OUTPUT);          // Rød LED
  pinMode(BUZZER, OUTPUT);           // Buzzer
  pinMode(MOTOR_LOCK, OUTPUT);       // Motor / lås
  pinMode(DOOR_SENSOR, INPUT_PULLUP); // Hvis sensor kobler til GND når dør åpnes
  digitalWrite(MOTOR_LOCK, HIGH);    // Sett lås til “låst” initialt
}

void loop() {
  // --- Les BME280 ---
  float temp = myBME.readTempC();               // Temperatur i °C
  float hum = myBME.readFloatHumidity();        // Relativ fuktighet %

  // --- Mate ENS160 med temp/hum for kompensasjon ---
  myENS.setEnvironmentalData((int)temp, (int)hum);

  // --- Les ENS160 luftkvalitet ---
  if (myENS.dataReady()) {                       // Sjekk om data klar
    uint16_t tvoc = myENS.getTVOC();            // Total volatile organic compounds
    uint16_t eco2 = myENS.getCO2();             // Estimert CO2
    Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
    Serial.print("eCO2: "); Serial.print(eco2); Serial.print(" ppm, ");
    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
    Serial.print("Hum: "); Serial.println(hum);
  } else {
    Serial.println("ENS-data ikke klar");
  }

  // --- Behandle keypad-input ---
  char key = keypad.getKey();                    // Les knapp
  if (key) {                                     // Hvis knapp trykket
    Serial.print("Tast: "); Serial.println(key);
    if (inputCode.length() == 0) codeEntryStart = millis(); // Start tidsvindu
    if (key >= '0' && key <= '9') {             // Hvis siffer
      inputCode += key;                          // Legg til i input
    } else if (key == '*') {                     // Hvis * → slett
      inputCode = "";
      Serial.println("Input slettet");
    } else if (key == '#') {                     // Hvis # → send kode
      Serial.print("Kode sendt: "); Serial.println(inputCode);
      if (inputCode == correctCode) {           // Korrekt kode
        alarmOff();
        inputCode = "";
      } else {                                   // Feil kode
        Serial.println("Feil kode!");
        digitalWrite(RED_LED, HIGH);           // Rød LED
        codeEntryStart = millis();             // Start tidsvindu på nytt
        inputCode = "";
      }
    }
  }

  // --- Sjekk tidsvindu ---
  if (!alarmOn && codeEntryStart > 0 && (millis() - codeEntryStart > timeout)) {
    Serial.println("Tidsvindu utløpt, alarm!");
    alarmOn = true;
    digitalWrite(RED_LED, HIGH);                // Rød LED
    digitalWrite(BUZZER, HIGH);                // Buzzer
  }

  // --- Dørbrudd ---
  if (digitalRead(DOOR_SENSOR) == LOW) { // Lav = dør åpnet
    Serial.println("Dørbrudd registrert!");
    alarmOn = true;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
}


  delay(100);                                   // Litt delay
}

// --- Funksjon for å slå av alarm ---
void alarmOff() {
  alarmOn = false;                              // Sett alarm av
  digitalWrite(GREEN_LED, HIGH);                // Grønn LED
  digitalWrite(RED_LED, LOW);                   // Rød LED av
  digitalWrite(BUZZER, LOW);                    // Buzzer av
  digitalWrite(MOTOR_LOCK, LOW);                // Lås opp
  delay(3000);                                  // Hold åpen noen sekunder
  digitalWrite(GREEN_LED, LOW);                 // Slukk grønn LED
  digitalWrite(MOTOR_LOCK, HIGH);               // Lås igjen
}
