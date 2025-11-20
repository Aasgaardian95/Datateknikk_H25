/*
Logikk:
- BME280 måler temperatur og fuktighet
- ENS160 måler TVOC og eCO2
- ENS160 mates med temperatur og fuktighet for mer presis IAQ
- Motor styrer ventilasjon med hysterese for å unngå hyppig av/på
    - Motor på hvis temp > 27°C eller eCO2 > 850 ppm
    - Motor av hvis temp < 25°C og eCO2 < 750 ppm
- OLED viser temperatur, fuktighet, eCO2, TVOC og motorstatus
- Serial Monitor logger alle verdier for debugging
*/

#include <Wire.h>                     // I2C-kommunikasjon for sensorer og OLED
#include <Adafruit_BME280.h>          // Bibliotek for BME280-sensor (temp, fuktighet, trykk)
#include <Adafruit_SSD1306.h>         // Bibliotek for OLED-skjerm
#include <Adafruit_ENS160.h>          // Bibliotek for ENS160 (luftkvalitet)

#define SCREEN_WIDTH 128              // OLED bredde i piksler
#define SCREEN_HEIGHT 64              // OLED høyde i piksler
#define OLED_RESET -1                 // Ingen reset-pin på OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialiser OLED

Adafruit_BME280 bme;                 // Initialiser BME280
Adafruit_ENS160 ens160 = Adafruit_ENS160(); // Initialiser ENS160

const int motorPin = 9;              // PWM-pin til motor
bool motorOn = false;                // Hysterese-status for motor

void setup() {
  Serial.begin(9600);                // Start seriell monitor
  if(!bme.begin(0x76)) while(1);     // Sjekk at BME280 finnes, stopp program hvis ikke
  if(!ens160.begin()) while(1);      // Sjekk at ENS160 finnes, stopp program hvis ikke
  ens160.iaqInit();                   // Initialiser IAQ-algoritme i ENS160
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while(1); // Initialiser OLED
  display.clearDisplay();             // Tøm OLED
  pinMode(motorPin, OUTPUT);          // Sett motor-pin som output
}

void loop() {
  float temp = bme.readTemperature(); // Les temperatur fra BME280
  float hum = bme.readHumidity();     // Les fuktighet fra BME280
  float pressure = bme.readPressure() / 100.0F; // Les trykk fra BME280 i hPa

  ens160.setEnvironmentalData(temp, hum); // Mate ENS160 med temp/fuktighet for mer presis IAQ
  ens160.iaqMeasure();                     // Oppdater ENS160 IAQ-målinger
  uint16_t tvoc = ens160.TVOC;            // Les TVOC fra ENS160
  uint16_t eco2 = ens160.eCO2;            // Les eCO2 fra ENS160

  // Hysterese-logikk for motor
  if(!motorOn && (temp > 27 || eco2 > 850)) motorOn = true; // Slå på motor hvis temp eller eCO2 høy
  if(motorOn && (temp < 25 && eco2 < 750)) motorOn = false; // Slå av motor hvis temp og eCO2 lave

  int motorSpeed = motorOn ? 255 : 0;      // Sett motorhastighet basert på hysterese-status

  analogWrite(motorPin, motorSpeed);       // Oppdater motor via PWM

  // OLED display
  display.clearDisplay();                   // Tøm OLED
  display.setTextSize(1);                   // Sett tekststørrelse
  display.setTextColor(SSD1306_WHITE);      // Sett tekstfarge
  display.setCursor(0,0);                   // Start øverst til venstre
  display.print("Temp: "); display.print(temp); display.println(" C"); // Vis temperatur
  display.print("Hum: "); display.print(hum); display.println(" %");   // Vis fuktighet
  display.print("Pressure: "); display.print(pressure); display.println(" hPa"); // Vis trykk
  display.print("TVOC: "); display.print(tvoc); display.println(" ppb"); // Vis TVOC
  display.print("eCO2: "); display.print(eco2); display.println(" ppm"); // Vis eCO2
  display.print("Motor: "); display.println(motorOn ? "ON" : "OFF");    // Vis motorstatus
  display.display();                        // Oppdater OLED

  // Serial Monitor logging
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print(" %, ");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" hPa, ");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
  Serial.print("eCO2: "); Serial.print(eco2); Serial.print(" ppm, ");
  Serial.print("Motor: "); Serial.println(motorOn ? "ON" : "OFF");

  delay(1000);                             // Oppdater målinger hvert sekund
}
