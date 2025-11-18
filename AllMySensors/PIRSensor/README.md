# PIRSensor

## Beskrivelse
`PIRSensor` biblioteket håndterer en passiv infrarød sensor som registrerer bevegelse. Klassen arver fra `BaseSensor` og bruker felles grensesnitt for initialisering, avlesning og logging, slik at den kan kombineres med de andre sensorene i prosjektet.

## Struktur
```
.
├── README.md
├── examples
│   └── PIRSensor_Example
│       └── PIRSensor_Example.ino
└── src
    ├── PIRSensor.cpp
    └── PIRSensor.h
```

## Filoversikt
| Fil | Type | Beskrivelse |
| --- | --- | --- |
| `src/PIRSensor.h` | Header | Deklarerer klassen med støtte for valgfri LED-indikator. |
| `src/PIRSensor.cpp` | Implementasjon | Initialiserer I/O-pinner og skriver statusmeldinger når bevegelse oppdages. |
| `examples/PIRSensor_Example/PIRSensor_Example.ino` | Eksempel | Viser enkel bevegelsesdeteksjon med seriell og LED-indikasjon. |

## Bruk
```cpp
#include <Arduino.h>
const int led = 9; // Led positive terminal to the digital pin 9.              
const  int sensor = 5; // signal pin of sensor to digital pin 5.               
const  int state = LOW;            
const int val = 0;                 

void  setup() { // Void setup is ran only once after each powerup or reset of the Arduino  board.
  pinMode(led, OUTPUT); // Led is determined as an output here.    
  pinMode(sensor, INPUT); // PIR motion sensor is determined is an input here.  
  Serial.begin(9600);      
}

void loop(){ // Void loop is ran over and  over and consists of the main program.
  val = digitalRead(sensor);   
  if  (val == HIGH) {           
    digitalWrite(led, HIGH);   
    delay(500);  // Delay of led is 500             
    
    if (state == LOW) {
      Serial.println("  Motion detected "); 
      state = HIGH;       
    }
  } 
  else {
      digitalWrite(led, LOW);
      delay(500);             
      
      if  (state == HIGH){
        Serial.println("The action/ motion has stopped");
        state = LOW;       
    }
  }
}

```
Når bevegelse registreres, skriver programmet «[PIR] Bevegelse oppdaget!» og tenner LED-en. Ved ro slukkes LED-en, og meldingen «[PIR] Ingen bevegelse registrert.» vises.

## Tilkobling
- **VCC** til 5 V, **GND** til GND.
- **Signal** til digital pinne 7 (kan endres i konstruktøren).
- Valgfri indikator-LED (standard `LED_BUILTIN`) kan brukes for visuell bekreftelse.
- Husk å la sensoren stabilisere seg i 30–60 sekunder etter oppstart.

## Avhengigheter
- Arduino core (`Arduino.h`)
- `BaseSensor`-biblioteket

## For undervisning
Egner seg til å diskutere:
- Digital innlesing og debouncing/logikk for bevegelsesdeteksjon.
- Design av hendelsesdrevne systemer med alarmer eller automatisering.
- Gjenbruk av `BaseSensor`-grensesnittet for å kombinere flere sensorer i ett prosjekt.
