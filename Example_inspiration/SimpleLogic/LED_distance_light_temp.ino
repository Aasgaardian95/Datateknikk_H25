/*
Logikk:
- LED lyser kun når alle tre betingelser er oppfylt:
  1. Avstand < 20 cm
  2. Lyssensor registrerer mørke
  3. Temperatur innenfor 15–30°C
- Hver sensor sjekkes separat og kombineres med AND (&&)
- Hvis noen betingelse ikke er oppfylt, slås LED av
*/

#include <NewPing.h>

NewPing sonar(7, 6, 200);  // trigger, echo, max distance
const int lightSensor = A0;
const int tempSensor = A1;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int distance = sonar.ping_cm();
  int lightVal = analogRead(lightSensor);
  int tempVal = analogRead(tempSensor);

  float tempC = (tempVal / 1023.0) * 100; // forenklet temperaturkonvertering

  if (distance > 0 && distance < 20 && lightVal < 300 && tempC >= 15 && tempC <= 30) {

    digitalWrite(ledPin, HIGH);

  } else {
    digitalWrite(ledPin, LOW);
  }
}
