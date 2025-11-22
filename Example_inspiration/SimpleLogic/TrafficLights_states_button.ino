/*
Logikk:
- Fire states: GREEN, YELLOW, RED, EMERGENCY
- Normal syklus: 5s grønn → 2s gul → 5s rød
- Emergency: blinkende gul LED når knapp trykkes
- State machine gjør koden modulær og enkel å utvide
- Ikke-blokkerende timing med millis()
*/

const int red = 9, yellow = 10, green = 11;
const int btn = 2;

enum State
{
  GREEN,
  YELLOW,
  RED,
  EMERGENCY
};
State state = GREEN;
unsigned long lastChange = 0;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop()
{
  bool emergency = digitalRead(btn) == LOW;

  if (emergency)
    state = EMERGENCY;

  switch (state)
  {
  case GREEN:
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    if (millis() - lastChange > 5000)
    {
      state = YELLOW;
      lastChange = millis();
    }
    break;
  case YELLOW:
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
    if (millis() - lastChange > 2000)
    {
      state = RED;
      lastChange = millis();
    }
    break;
  case RED:
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    if (millis() - lastChange > 5000)
    {
      state = GREEN;
      lastChange = millis();
    }
    break;
  case EMERGENCY:
    digitalWrite(green, LOW);
    digitalWrite(yellow, millis() % 500 < 250 ? HIGH : LOW); // blink
    digitalWrite(red, LOW);
    break;
  }
}
