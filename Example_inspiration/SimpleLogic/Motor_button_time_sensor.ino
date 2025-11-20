/*
Logikk:
- Motor aktiveres når knapp holdes inne og sensor registrerer objekt
- Motor kjører i 3 sek intervall, resettes med millis() for ikke-blokkerende
- motorOn-variabel holder oversikt over aktiv status
*/

const int btn = 2;
const int sensor = A0;
const int motor = 9;

unsigned long lastStart = 0;
const unsigned long interval = 3000;
bool motorOn = false;

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
}

void loop() {
  bool pressed = digitalRead(btn) == LOW;
  int sensorVal = analogRead(sensor);

  if (pressed && sensorVal > 100) {
    if (!motorOn || millis() - lastStart >= interval) {
      digitalWrite(motor, HIGH);
      lastStart = millis();
      motorOn = true;
    }
  }

  if (motorOn && millis() - lastStart >= interval) {
    digitalWrite(motor, LOW);
    motorOn = false;
  }
}
