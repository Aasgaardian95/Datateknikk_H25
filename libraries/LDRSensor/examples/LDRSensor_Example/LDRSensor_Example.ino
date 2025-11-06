#include <Arduino.h>
#include <LDRSensor.h>

// LDR koblet til analog inngang A0 (standard for lyssensor i labben)
constexpr uint8_t LDR_PIN = A0;

LDRSensor ldr(LDR_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // vent på seriell tilkobling når man bruker USB-baserte kort
  }
  ldr.begin();
}

void loop() {
  ldr.read();
  delay(1000); // les hvert sekund for å se endringer i lysnivå
}
