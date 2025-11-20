/*
Logikk:
- Vannpumpe slås på hvis jordfuktighet < 400
- LED blinker hvis temperatur > 30°C
- Prioritet: vanning over advarsel
- Sensorverdier konverteres til praktiske verdier
*/

const int soilSensor = A0;
const int tempSensor = A1;
const int pumpPin = 9;
const int ledPin = 10;

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int soil = analogRead(soilSensor);
  int temp = analogRead(tempSensor);
  float tempC = (temp / 1023.0) * 50; 

  if (soil < 400) {
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpPin, LOW);
  }

  if (tempC > 30) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
