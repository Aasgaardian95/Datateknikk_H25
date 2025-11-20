/*
Logikk:
- BME280 måler temperatur og fuktighet
- ENS160 måler TVOC for å simulere “luftkvalitet”
- ENS160 mates med temp/fuktighet for presis IAQ
- Motor styrer vannpumpe
- Vanning basert på jordfuktighet (simulert her med fuktighet fra BME280)
    - Hvis fuktighet < 40% → pumpe på
    - Hvis fuktighet >= 50% → pumpe av
- OLED viser temp, fuktighet, TVOC og pumpe-status
- Serial Monitor viser alle verdier
*/

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ENS160.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme;                  
Adafruit_ENS160 ens160 = Adafruit_ENS160();

const int pumpPin = 9;                // PWM-pin for vannpumpe

void setup() {
  Serial.begin(9600);                 
  if(!bme.begin(0x76)) while(1);      
  if(!ens160.begin()) while(1);       
  ens160.iaqInit();                    
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while(1);
  display.clearDisplay();              
  pinMode(pumpPin, OUTPUT);            
}

void loop() {
  float temp = bme.readTemperature(); // Les temperatur
  float hum = bme.readHumidity();     // Les fuktighet som jordfuktighet proxy

  ens160.setEnvironmentalData(temp, hum); // Mate ENS160 med temp/fuktighet
  ens160.iaqMeasure();                     // Oppdater IAQ
  uint16_t tvoc = ens160.TVOC;            // Les TVOC

  int pumpSpeed = 0;                       // Default pumpe av

  // Vanningslogikk
  if(hum < 40) pumpSpeed = 255;           // Lav fuktighet → pumpe på full hastighet
  else if(hum >= 50) pumpSpeed = 0;       // Fuktig nok → pumpe av

  analogWrite(pumpPin, pumpSpeed);        // Oppdater pumpe

  // OLED display
  display.clearDisplay();                  
  display.setTextSize(1);                  
  display.setTextColor(SSD1306_WHITE);     
  display.setCursor(0,0);                  
  display.print("Temp: "); display.print(temp); display.println(" C"); // Vis temp
  display.print("Hum: "); display.print(hum); display.println(" %");   // Vis fuktighet
  display.print("TVOC: "); display.print(tvoc); display.println(" ppb"); // Vis TVOC
  display.print("Pump: "); display.println(pumpSpeed > 0 ? "ON" : "OFF"); // Vis pumpe
  display.display();                       

  // Serial Monitor logging
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print(" %, ");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.print(" ppb, ");
  Serial.print("Pump: "); Serial.println(pumpSpeed > 0 ? "ON" : "OFF");

  delay(1000);                              // Oppdater hvert sekund
}
