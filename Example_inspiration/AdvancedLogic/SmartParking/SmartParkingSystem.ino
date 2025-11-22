/*
Logikk:
- HC-SR04 ultralydsensor måler avstand til bilen
- LED-stripe viser avstanden visuelt:
    - Lengre avstand → grønn del av stripen lyser
    - Kortere avstand → gul/rød del av stripen lyser
- Egen LED viser om plassen er ledig (grønn) eller opptatt (rød)
- Ledig dersom avstand > 50 cm
- Opptatt dersom avstand <= 50 cm
- Serial Monitor viser avstand for debugging
*/

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define TRIG_PIN 7    // HC-SR04 trig pin
#define ECHO_PIN 6    // HC-SR04 echo pin
#define PIXEL_PIN 5   // Pin for LED-stripe
#define NUM_PIXELS 10 // Antall LEDer i stripen
#define GREEN_LED 3   // LED = ledig
#define RED_LED 4     // LED = opptatt

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);         // Start Serial Monitor
  pinMode(TRIG_PIN, OUTPUT);  // Set trig pin som output
  pinMode(ECHO_PIN, INPUT);   // Set echo pin som input
  pinMode(GREEN_LED, OUTPUT); // Grønn LED ledig
  pinMode(RED_LED, OUTPUT);   // Rød LED opptatt
  strip.begin();              // Start LED-stripe
  strip.show();               // Initielt slukket
}

void loop()
{
  long duration, distance;

  // Send ultralyd-puls
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Les varighet av ekko
  duration = pulseIn(ECHO_PIN, HIGH);

  // Regn om til avstand i cm
  distance = duration * 0.034 / 2;

  Serial.print("Avstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED-stripe visualisering
  int ledsToLight = map(distance, 0, 100, NUM_PIXELS, 0); // Flere cm → færre LEDer
  ledsToLight = constrain(ledsToLight, 0, NUM_PIXELS);

  for (int i = 0; i < NUM_PIXELS; i++)
  {
    if (i < ledsToLight)
    {
      if (distance > 50)
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Grønn lang avstand
      else if (distance > 20)
        strip.setPixelColor(i, strip.Color(255, 255, 0)); // Gul medium avstand
      else
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Rød kort avstand
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Slukk resterende LEDer
    }
  }
  strip.show();

  // Ledig/opptatt logikk
  if (distance > 50)
  {
    digitalWrite(GREEN_LED, HIGH); // LED = ledig
    digitalWrite(RED_LED, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH); // LED = opptatt
  }

  delay(200); // Oppdatering hvert 0,2 sekund
}
