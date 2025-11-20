/*
Logikk:
- LED blinker kun hvis knapp holdes inne og mørkt
- Bruker millis() for timing, ikke delay(), slik at loop fortsetter å sjekke sensorene
- Ikke-blokkerende blink sikrer responsivt system
*/

const int btn = 2;
const int lightPin = A0;
const int ledPin = 9;

unsigned long lastToggle = 0;
bool ledState = false;

void loop() {
  int lightVal = analogRead(lightPin);
  bool pressed = digitalRead(btn) == LOW;

  if (pressed && lightVal < 200) {

    if (millis() - lastToggle > 300) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      lastToggle = millis();
    }

  } else {
    digitalWrite(ledPin, LOW);
    ledState = false;
  }
}
