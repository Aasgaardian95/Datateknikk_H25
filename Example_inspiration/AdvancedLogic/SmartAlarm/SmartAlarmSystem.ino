/*
Logikk:
- 4x4 Keypad brukes for å taste inn en firesifret kode
- Korrekt kode → alarm slås av, lås åpnes, grønn LED lyser
- Feil kode → rød LED lyser i tidsvindu
- Tidsvindu utløpt → buzzer / alarm aktiveres
- Dørbrudd (sensor) → umiddelbar alarm
- OLED viser sanntidsinformasjon:
  - Tastet kode
  - Alarmstatus
  - Låsstatus
- Serial Monitor brukes for debugging av input og systemstatus
*/

#include <Wire.h>             // I2C-kommunikasjon for OLED
#include <Keypad.h>           // Keypad bibliotek for 4x4 matrise
#include <Adafruit_GFX.h>     // Grafikkbibliotek for OLED
#include <Adafruit_SSD1306.h> // SSD1306 OLED bibliotek

#define SCREEN_WIDTH 128                                                  // OLED bredde i piksler
#define SCREEN_HEIGHT 64                                                  // OLED høyde i piksler
#define OLED_RESET -1                                                     // Reset pin (ikke brukt)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED objekt

#define DOOR_SENSOR 10 // Pin for dør-sensor
#define GREEN_LED 3    // Pin for grønn LED (alarm av)
#define RED_LED 4      // Pin for rød LED (feil kode / alarm)
#define BUZZER 5       // Pin for buzzer
#define MOTOR_LOCK 6   // Pin for motor/servo (låsing)

const String correctCode = "1234";   // Korrekt kode
const unsigned long timeout = 10000; // Tidsvindu for kodeinntasting (ms)

const byte ROWS = 4, COLS = 4; // Keypad størrelse 4x4
char keys[ROWS][COLS] = {      // Definerer tastene
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};                                      // Rader koblet til disse pinnene
byte colPins[COLS] = {5, 4, 3, 2};                                      // Kolonner koblet til disse pinnene
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Keypad objekt

bool alarmOn = false;             // Variabel for alarmstatus
unsigned long codeEntryStart = 0; // Timer start for kodeinntasting
String inputCode = "";            // Brukerens tastede kode

void setup()
{
  Serial.begin(9600); // Starter Serial Monitor for debugging

  // Aktuator-pinner settes som output
  pinMode(GREEN_LED, OUTPUT);         // Grønn LED
  pinMode(RED_LED, OUTPUT);           // Rød LED
  pinMode(BUZZER, OUTPUT);            // Buzzer
  pinMode(MOTOR_LOCK, OUTPUT);        // Motor / lås
  pinMode(DOOR_SENSOR, INPUT_PULLUP); // Dør-sensor med pullup (LOW = dør åpen)

  digitalWrite(MOTOR_LOCK, HIGH); // Sett lås initialt til låst

  // Initialiser OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED init feil!"); // Hvis init mislykkes
    while (1)
      ; // Stopper programmet
  }
  display.clearDisplay();              // Rydd skjermen
  display.setTextSize(1);              // Tekststørrelse
  display.setTextColor(SSD1306_WHITE); // Tekstfarge
  display.setCursor(0, 0);             // Start posisjon øverst til venstre
  display.println("Smart Alarm Init...");
  display.display(); // Oppdater skjerm
  delay(1000);       // Litt pause for visuell effekt
}

void loop()
{
  // --- Les Keypad ---
  char key = keypad.getKey(); // Les knappetrykk
  if (key)
  { // Hvis knapp trykket
    Serial.print("Tast: ");
    Serial.println(key); // Print til Serial
    if (inputCode.length() == 0)
      codeEntryStart = millis(); // Start tidsvindu
    if (key >= '0' && key <= '9')
      inputCode += key; // Legg til siffer i input
    else if (key == '*')
    {
      inputCode = "";
      Serial.println("Input slettet");
    } // Slett
    else if (key == '#')
    { // Send kode for validering
      Serial.print("Kode sendt: ");
      Serial.println(inputCode);
      if (inputCode == correctCode)
      {                 // Korrekt kode
        alarmOff();     // Slå av alarm
        inputCode = ""; // Nullstill input
      }
      else
      { // Feil kode
        Serial.println("Feil kode!");
        digitalWrite(RED_LED, HIGH); // Rød LED på
        codeEntryStart = millis();   // Start tidsvindu på nytt
        inputCode = "";              // Nullstill input
      }
    }
  }

  // --- Sjekk tidsvindu ---
  if (!alarmOn && codeEntryStart > 0 && (millis() - codeEntryStart > timeout))
  {
    Serial.println("Tidsvindu utløpt, alarm!");
    alarmOn = true;              // Sett alarm på
    digitalWrite(RED_LED, HIGH); // Rød LED
    digitalWrite(BUZZER, HIGH);  // Buzzer
  }

  // --- Sjekk dørbrudd ---
  if (digitalRead(DOOR_SENSOR) == LOW)
  { // Lav = dør åpnet
    Serial.println("Dørbrudd registrert!");
    alarmOn = true;              // Sett alarm på
    digitalWrite(RED_LED, HIGH); // Rød LED
    digitalWrite(BUZZER, HIGH);  // Buzzer
  }

  // --- Oppdater OLED ---
  display.clearDisplay();  // Rydd skjerm
  display.setCursor(0, 0); // Start øverst
  display.println("Smart Alarm");
  display.print("Kode: ");
  display.println(inputCode);
  display.print("Alarm: ");
  display.println(alarmOn ? "ON" : "OFF");
  display.print("Lås: ");
  display.println(digitalRead(MOTOR_LOCK) == LOW ? "OPEN" : "LOCKED");
  display.display(); // Oppdater skjerm

  delay(100); // Kort delay for loop
}

// --- Funksjon for å slå av alarm ---
void alarmOff()
{
  alarmOn = false;                // Alarm av
  digitalWrite(GREEN_LED, HIGH);  // Grønn LED på
  digitalWrite(RED_LED, LOW);     // Rød LED av
  digitalWrite(BUZZER, LOW);      // Buzzer av
  digitalWrite(MOTOR_LOCK, LOW);  // Lås opp
  delay(3000);                    // Hold lås åpen noen sekunder
  digitalWrite(GREEN_LED, LOW);   // Slukk grønn LED
  digitalWrite(MOTOR_LOCK, HIGH); // Lås igjen
}
