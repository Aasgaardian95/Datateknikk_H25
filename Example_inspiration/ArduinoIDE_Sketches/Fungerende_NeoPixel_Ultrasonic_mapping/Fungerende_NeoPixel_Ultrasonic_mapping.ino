// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 5  // On Trinket or Gemma, suggest changing this to 1
#define trigPin 9
#define echoPin 10

float duration, distance;
int mappedDistance, mappedDistanceToColor, green, red, numPixels;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 30  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100  // Time (in milliseconds) to pause between pixels

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {

  // int numMeasurements = 2;
  //
  // for (int i = 0; i < numMeasurements; i++) {
  //   duration += getDuration();
  // }
  //
  // duration = duration / numMeasurements;

  duration = getDuration();

  distance = (duration * .0343) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  distance = constrain(distance, 5, 45);

  mappedDistance = map(distance, 5, 45, NUMPIXELS, 0);
  mappedDistanceToColor = map(distance, 5, 45, 255, 0);

  red = mappedDistanceToColor;
  green = 255 - red;

  numPixels = mappedDistance;

  Serial.print("Mapped distance: ");
  Serial.println(mappedDistance);

  fillStrip(red, green, 0, numPixels);
}

void fillStrip(uint8_t r, uint8_t g, uint8_t b, int numPixels) {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < numPixels) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));  // set color for pixel i
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();  // send the updated colors to the strip
  }
}

long getDuration() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH);
}
