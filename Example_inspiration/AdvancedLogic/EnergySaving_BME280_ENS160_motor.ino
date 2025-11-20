/*
Logikk:
- BME280 måler temperatur
- ENS160 måler TVOC
- ENS160 mates med temperatur og fuktighet for presis IAQ
- Motor styrer ventilasjon
- Energisparingslogikk:
    - Motor på full hastighet hvis temp > 26°C OG TVOC > 250 ppb
    - Motor på lav hastighet hvis temp lav, men TVOC > 250
    - Ellers motor av
- OLED viser verdier og motorstatus
- Serial Monitor viser verdier for debugging
*/

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ENS160.h>

#define SCREEN_WIDTH 128               // OLED bredde i piksler
#define SCREEN_HEIGHT 64               // OLED høyde i piksler
#define OLED_RESET -1                  // Ingen reset-pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme;                  // Initialiser BME280
Adafruit_ENS160 ens160 = Adafruit_ENS160(); // Initialiser ENS160

const int motorPin = 9;               // PWM-pin til motor

void setup() {
  Serial.begin(9600);                 // Start seriell monitor
  if(!bme.begin(0x76)) while(1);      // Sjekk at BME280 finnes
  if(!ens160.begin()) while(1);       // Sjekk at ENS160 finnes
  ens160.iaqInit();                    // Initialiser IAQ
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while(1); // Initialiser OLED
  display.clearDisplay();              // Tøm OLED
  pinMode(motorPin, OUTPUT);           // Sett motor som output
}

void loop() {
  float temp = bme.readTemperature(); // Les temperatur
  float hum = bme.readHumidity();     // Les fuktighet

  ens160.setEnvironmentalData(temp, hum); // Mate ENS160 med temp/fuktighet
  ens160.iaqMeasure();                     // Oppdater IAQ-målinger
  uint16_t tvoc = ens160.TVOC;            // Les TVOC

  int motorSpeed = 0;                      // Default motor av

  // Energisparingslogikk
  if(temp > 26 && tvoc > 250) motorSpeed = 200; // Høy temp + dårlig luft → full motor
  else if(tvoc > 250) motorSpeed = 120;        // Lav temp + dårlig luft → lav hastighet
  else motorSpeed = 0;                          // Ellers av

  analogWrite(motorPin, motorSpeed);           // Oppdater motor

  // OLED display
  display.clearDisplay();                       
  display.setTextSize(1);                      
  display.setTextColor(SSD1306_WHITE);         
  display.setCursor(0,0);                       
  display.print("Temp: "); display.print(temp); display.println(" C"); // Vis temperatur
  display.print("Hum: "); display.print(hum); display.println(" %");   // Vis fuktighet
  display.print("TVOC: "); display.print(tvoc); display.println(" ppb"); // Vis TVOC
  display.print("Motor: "); display.println(motorSpeed > 0 ? "ON" : "OFF"); // Vis motorstatus
  display.display();                             // Oppdater OLED

  // Serial Monitor logging
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print(" %, ");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
  Serial.print("Motor: "); Serial.println(motorSpeed > 0 ? "ON" : "OFF");

  delay(1000);                                  // Oppdater hvert sekund
}
