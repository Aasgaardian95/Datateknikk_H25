/*
Logikk:
- Tre tilstander for motoren: NORMAL, ADVARSEL, FARE
- FARE (nødknapp) har alltid høyest prioritet
- ADVARSEL (avstand < 150) har lavere prioritet
- NORMAL (full fart) hvis ingen andre tilstander er aktive
- Rekkefølgen av if-else avgjør prioritet
*/

const int motorPin = 5;
const int btnEmergency = 2;
const int distSensor = A0;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(btnEmergency, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int emergencyPressed = digitalRead(btnEmergency) == LOW;
  int distance = analogRead(distSensor);

  if (emergencyPressed)
  {
    analogWrite(motorPin, 0); // FARE
  }
  else if (distance < 150)
  {
    analogWrite(motorPin, 80); // ADVARSEL
  }
  else
  {
    analogWrite(motorPin, 255); // NORMAL
  }
}
