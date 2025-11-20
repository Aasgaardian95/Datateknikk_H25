/*
Logikk:
- Tre LED’er styrt av lysnivå og PIR-bevegelse
- Natt + bevegelse → grønn LED
- Natt + ingen bevegelse → rød LED
- Dagslys → blå LED
- Enkel IF-struktur med prioritet
*/

const int pir = 2;
const int lightSensor = A0;
const int greenLED = 9;
const int redLED = 10;
const int blueLED = 11;

void setup() {
  pinMode(pir, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  int lightVal = analogRead(lightSensor);
  bool motion = digitalRead(pir);

  if (lightVal < 200 && motion) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  else if (lightVal < 200 && !motion) {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
  }
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
  }
}
