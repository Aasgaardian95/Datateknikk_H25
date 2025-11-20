/*
Logikk:
- Systemet venter på en firesifret kode fra brukeren
- Hvis korrekt kode tastes inn:
    - LED grønn tennes
    - Alarm (buzzer) skrus av
    - Motor/lås åpnes
- Hvis feil kode tastes inn:
    - LED rød blinker
    - Brukeren har et tidsvindu (f.eks. 10 sekunder) for å taste korrekt kode
    - Hvis korrekt kode ikke tastes innen tiden → alarm skrur seg på (buzzer)
- Hvis sensorer (f.eks. dør/magnetkontakt) registrerer at døren åpnes uten korrekt kode → alarm umiddelbart
- Serial Monitor viser status og tastetrykk for debugging
*/

#include <Keypad.h>                  // Bibliotek for tastatur
#include <Wire.h>

#define GREEN_LED 3                  // Pin til grønn LED
#define RED_LED 4                    // Pin til rød LED
#define BUZZER 5                     // Pin til buzzer
#define MOTOR_LOCK 6                 // Pin til motor/lås

const String correctCode = "1234";   // Definert korrekt kode

const unsigned long timeout = 10000; // Tidsvindu for å taste korrekt kode (10 sekunder)

char key;                             // Hold tastetrykk
String inputCode = "";                 // Holder det brukeren taster inn

// Tastatur-konfigurasjon (4x4 keypad)
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};   // Tilkoblingspinner
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool alarmOn = false;                  // Status på alarm
unsigned long codeEntryStart = 0;      // Tidsmåler for kode-inntasting

void setup() {
  Serial.begin(9600);                  // Start serial monitor
  pinMode(GREEN_LED, OUTPUT);          // Grønn LED = korrekt kode
  pinMode(RED_LED, OUTPUT);            // Rød LED = feil / alarm
  pinMode(BUZZER, OUTPUT);             // Buzzer = alarm
  pinMode(MOTOR_LOCK, OUTPUT);         // Motor/lås
  digitalWrite(MOTOR_LOCK, HIGH);      // Motor/lås låst ved start
}

void loop() {
  key = keypad.getKey();               // Les tastetrykk

  // Hvis en tast trykkes
  if(key){
    Serial.print("Tastetrykk: "); Serial.println(key);
    
    if(inputCode.length() == 0) codeEntryStart = millis(); // Start timer på første tast

    // Bygg kode fra tastetrykk
    if(key >= '0' && key <= '9'){     
      inputCode += key;                // Legg til tall
    }

    // Slett siste tast
    if(key == '*'){                    
      inputCode = "";                  
      Serial.println("Kode slettet"); 
    }

    // Send kode når # trykkes
    if(key == '#'){                    
      Serial.print("Kode sendt: "); Serial.println(inputCode);
      if(inputCode == correctCode){   // Sjekk korrekt kode
        alarmOff();                    // Slå av alarm
        inputCode = "";                // Nullstill input
      } else {
        Serial.println("Feil kode!");
        digitalWrite(RED_LED, HIGH);  // Blink rød LED (visuell tilbakemelding)
        codeEntryStart = millis();    // Start tidsvindu for korrekt kode
        inputCode = "";               
      }
    }
  }

  // Sjekk om tidsvindu for korrekt kode er utløpt
  if(!alarmOn && millis() - codeEntryStart > timeout && codeEntryStart != 0){
    Serial.println("Tidsvindu utløpt, alarm på!");
    alarmOn = true;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);      // Alarm
  }

  // Sjekk om dør brytes (simulert her med digitalRead, kan kobles til sensor)
  if(digitalRead(2) == HIGH){         // Dør åpnet uten kode
    Serial.println("Innbrudd registrert!");
    alarmOn = true;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }

}

// Funksjon for å slå av alarm
void alarmOff(){
  alarmOn = false;
  digitalWrite(GREEN_LED, HIGH);       // Grønn LED på
  digitalWrite(RED_LED, LOW);          // Rød LED av
  digitalWrite(BUZZER, LOW);           // Buzzer av
  digitalWrite(MOTOR_LOCK, LOW);       // Lås opp
  delay(3000);                          // Hold lås oppe noen sekunder
  digitalWrite(GREEN_LED, LOW);        // Slå av grønn LED igjen
  digitalWrite(MOTOR_LOCK, HIGH);      // Lås tilbake
}
