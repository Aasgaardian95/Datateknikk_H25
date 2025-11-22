/*
 Logikk:
 - Fire states: GREEN, YELLOW, RED, EMERGENCY
 - Normal syklus: 5s grønn → 2s gul → 5s rød
 - Emergency: blinkende gul LED når knapp trykkes
 - State machine gjør koden modulær og enkel å utvide
 - Ikke-blokkerende timing med millis()
*/

const int red = 9, yellow = 10, green = 11; // Definerer hvilke pins som styrer LED-ene
const int btn = 2;                          // Pin for knappen

enum State // Definerer en enum med navn på alle tilstander
{
  GREEN,
  YELLOW,
  RED,
  EMERGENCY
};
State state = GREEN;          // Starttilstanden er GREEN
unsigned long lastChange = 0; // Variabel for å lagre tidspunktet siste state-endring skjedde

void setup()
{
  pinMode(red, OUTPUT);       // Setter rød LED-pin som output
  pinMode(yellow, OUTPUT);    // Setter gul LED-pin som output
  pinMode(green, OUTPUT);     // Setter grønn LED-pin som output
  pinMode(btn, INPUT_PULLUP); // Knapp med intern pull-up, aktiv LOW
}

void loop()
{
  bool emergency = digitalRead(btn) == LOW; // Leser knappen: LOW betyr trykket inn (emergency)

  if (emergency)       // Hvis knapp trykkes
    state = EMERGENCY; // Sett state til EMERGENCY umiddelbart

  switch (state) // Velg logikk basert på nåværende state
  {
  case GREEN:                         // Tilstand: GRØNN
    digitalWrite(green, HIGH);        // Skru på grønn LED
    digitalWrite(yellow, LOW);        // Skru av gul LED
    digitalWrite(red, LOW);           // Skru av rød LED
    if (millis() - lastChange > 5000) // Har 5 sekunder gått?
    {
      state = YELLOW;        // Gå til YELLOW
      lastChange = millis(); // Oppdater tidspunktet
    }
    break;

  case YELLOW:                        // Tilstand: GUL
    digitalWrite(green, LOW);         // Skru av grønn
    digitalWrite(yellow, HIGH);       // Skru på gul
    digitalWrite(red, LOW);           // Skru av rød
    if (millis() - lastChange > 2000) // Har 2 sekunder gått?
    {
      state = RED;           // Gå til RØD
      lastChange = millis(); // Oppdater tidspunkt
    }
    break;

  case RED:                           // Tilstand: RØD
    digitalWrite(green, LOW);         // Skru av grønn
    digitalWrite(yellow, LOW);        // Skru av gul
    digitalWrite(red, HIGH);          // Skru på rød
    if (millis() - lastChange > 5000) // Har 5 sekunder gått?
    {
      state = GREEN;         // Gå til GRØNN
      lastChange = millis(); // Oppdater tidspunkt
    }
    break;

  case EMERGENCY:                                            // Tilstand: EMERGENCY
    digitalWrite(green, LOW);                                // Skru av grønn
    digitalWrite(yellow, millis() % 500 < 250 ? HIGH : LOW); // Blink gul: 250ms på, 250ms av
    digitalWrite(red, LOW);                                  // Skru av rød
    break;
  }
}
