#include <Adafruit_NeoPixel.h>
const int pin = 6;
const int ant = 4;
int i = 0;

Adafruit_NeoPixel pixels(ant, pin, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();
}

void loop()
{
  pixels.clear();
  pixels.setBrightness(125);
  
  for (i=0; i<ant; i++) {
  	 pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }

  pixels.show();
  delay(500);
   for (i=0; i<ant; i++) {
  	 pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }

  pixels.show();
  delay(500);
   for (i=0; i<ant; i++) {
  	 pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }

  pixels.show();
  delay(500);
}
