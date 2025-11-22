#include <Arduino.h>

const int transistor = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(transistor, OUTPUT);
}

void loop()
{
  digitalWrite(transistor, HIGH);
  Serial.println("Transistor ON");
  delay(250);
  digitalWrite(transistor, LOW);
  Serial.println("Transistor OFF");
  delay(250);
}
