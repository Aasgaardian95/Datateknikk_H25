#include <Arduino.h>
#include <Wire.h>
#include <BME280Sensor.h>

// Standard I2C-adresse for modulen i lab-settet er 0x76
constexpr uint8_t BME280_ADDRESS = 0x76;

BME280Sensor klima(BME280_ADDRESS);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (!Wire.isEnabled()) {
    Wire.begin();
  }
  klima.begin();
}

void loop() {
  klima.read();

  Serial.print("Temperatur (cachet): ");
  Serial.print(klima.temperature(), 1);
  Serial.println(" °C");

  delay(2000); // gi sensoren tid mellom avlesinger
}
