#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>          // Grafikkbibliotek for skjerm 
#include <Adafruit_SSD1306.h>      // OLED-skjermdriver (SSD1306)

#define SCREEN_WIDTH 128           // OLED bredde i piksler 
#define SCREEN_HEIGHT 64           // OLED høyde i piksler 
#define OLED_RESET -1              // Ingen reset-pin (brukes ikke) 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!bme.begin(0x77)) {   // Try 0x76 OR 0x77
    Serial.println("Could not find BME280!");
    while (1);
  }

  // Konfigurerer OLED-skjerm
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C er standard I2C-adresse 
    Serial.println(F("Fant ikke OLED-skjerm!")); 
    while (true); 
  } 
  display.clearDisplay(); 
  display.setTextSize(1);          // Tekststørrelse 
  display.setTextColor(SSD1306_WHITE); 

  // Velkomstmelding på skjerm 
  display.setCursor(0, 20); 
  display.println("Nummerprinter"); 
  display.display(); 
  delay(1500); 
  display.clearDisplay(); 
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  delay(1000);
}