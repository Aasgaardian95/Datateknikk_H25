/*
Logikk:
- Vifte skrur seg på når temp > 28°C
- Skrur seg av når temp < 25°C
- Hysterese brukes for å unngå flikring pga små endringer i sensorverdier
*/

const int tempPin = A0;
const int fanPin = 9;

bool fanOn = false;

void setup()
{
  pinMode(fanPin, OUTPUT);
}

void loop()
{
  int tempRaw = analogRead(tempPin);
  float tempC = (tempRaw / 1023.0) * 50; // forenklet konvertering

  if (!fanOn && tempC > 28)
  {
    fanOn = true;
  }
  if (fanOn && tempC < 25)
  {
    fanOn = false;
  }

  digitalWrite(fanPin, fanOn);
}
