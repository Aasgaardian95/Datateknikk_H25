/*
Logikk:
- Dør åpnes bare når:
  1. PIR detekterer bevegelse
  2. Ultralydsensoren registrerer person foran døren
  3. Magnetkontakt viser at døren er lukket
- LED blinker som forhåndssignal
- Timeout lukker døren automatisk etter 5 sekunder
*/

#include <NewPing.h>

const int pir = 2;
NewPing sonar(7, 6, 150);
const int magnet = 3;
const int motorPin = 9;
const int led = 10;

unsigned long openTime = 0;
bool doorOpen = false;

void loop()
{

  bool motion = digitalRead(pir) == HIGH;
  int dist = sonar.ping_cm();
  bool doorClosed = digitalRead(magnet) == HIGH;

  // Pre-signal
  if (motion && dist > 0 && dist < 40 && doorClosed && !doorOpen)
  {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
  }

  // Open condition
  if (motion && dist > 0 && dist < 40 && doorClosed && !doorOpen)
  {
    analogWrite(motorPin, 255);
    delay(800);
    analogWrite(motorPin, 0);
    doorOpen = true;
    openTime = millis();
  }

  // Auto-close
  if (doorOpen && millis() - openTime > 5000)
  {
    analogWrite(motorPin, 255);
    delay(800);
    analogWrite(motorPin, 0);
    doorOpen = false;
  }
}
