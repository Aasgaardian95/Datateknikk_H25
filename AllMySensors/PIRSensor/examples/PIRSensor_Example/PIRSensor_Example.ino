#include <Arduino.h>
#include <PIRSensor.h>

// PIR-sensor koblet til digital pinne 7 og LED til innebygd indikator
constexpr uint8_t PIR_PIN = 7;
constexpr uint8_t LED_PIN = LED_BUILTIN;

PIRSensor pir(PIR_PIN, LED_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  pir.begin();
}

void loop() {
  pir.read();
  delay(500); // les to ganger i sekundet for rask respons
}
