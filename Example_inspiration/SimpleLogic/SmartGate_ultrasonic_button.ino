/*
Logikk:
- Gate åpnes når bil nærmer seg (ultralyd) og det er mørkt
- Nødknapp har høyeste prioritet → stopper motor og setter rødt lys
- Grøn LED = åpen, rød LED = stengt
- IF rekkefølge sikrer riktig prioritet
*/

#include <NewPing.h>

const int trig = 7, echo = 6;
const int lightSensor = A0;
const int emergencyBtn = 2;
const int motorPin = 9;
const int greenLED = 10;
const int redLED = 11;

NewPing sonar(trig, echo, 200);

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(emergencyBtn, INPUT_PULLUP);
}

void loop()
{
  bool emergency = digitalRead(emergencyBtn) == LOW;
  int distance = sonar.ping_cm();
  int lightVal = analogRead(lightSensor);

  if (emergency)
  {
    digitalWrite(motorPin, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    return; // prioritet
  }

  if (distance > 0 && distance < 30 && lightVal < 300)
  {
    digitalWrite(motorPin, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  else
  {
    digitalWrite(motorPin, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}
