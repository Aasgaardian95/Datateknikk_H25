/*
Logikk:
- BME280 måler temperatur og relativ fuktighet
- ENS160 måler luftkvalitet (TVOC og eCO2), kompensert med BME-data
- OLED viser sanntidsdata: Temp, Hum, TVOC, eCO2 og pumpe-status
- Vannpumpe styres med PWM basert på:
    - Lav fuktighet (< 40%) → start vanning
    - Dårlig luftkvalitet (TVOC/CO2 høyt) → stopp vanning for sikkerhet
- Manuell overstyring via knapp → full pumpehastighet
*/

#include <Wire.h>             // I2C-kommunikasjon
#include <SparkFunBME280.h>   // SparkFun BME280-bibliotek
#include <SparkFun_ENS160.h>  // SparkFun ENS160-bibliotek
#include <Adafruit_GFX.h>     // OLED grafikkbibliotek
#include <Adafruit_SSD1306.h> // OLED skjermbibliotek

#define SCREEN_WIDTH 128 // OLED bredde i piksler
#define SCREEN_HEIGHT 64 // OLED høyde i piksler
#define OLED_RESET -1    // Ingen reset-pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PUMP_PIN 9        // PWM-pin til vannpumpe
#define OVERRIDE_BUTTON 7 // Knapp for manuell overstyring

BME280 myBME; // BME280 objekt
ENS160 myENS; // ENS160 objekt

void setup()
{
  Serial.begin(9600); // Start Serial Monitor

  // --- Initialiser BME280 ---
  if (!myBME.begin())
  {
    Serial.println("BME280 ikke funnet!");
    while (1)
      ;
  }

  // --- Initialiser ENS160 ---
  if (myENS.begin() != 0)
  {
    Serial.println("ENS160 ikke funnet!");
    while (1)
      ;
  }
  myENS.iaqInit(); // Initialiser IAQ-måling

  // --- Initialiser OLED ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // I2C 0x3C
    Serial.println("OLED ikke funnet!");
    while (1)
      ;
  }
  display.clearDisplay(); // Tøm skjerm
  display.setTextSize(1); // Tekststørrelse
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Vanning");
  display.display();

  pinMode(PUMP_PIN, OUTPUT);              // PWM pumpe
  pinMode(OVERRIDE_BUTTON, INPUT_PULLUP); // Knapp som input med pullup
}

void loop()
{
  // --- Les BME280 ---
  float temp = myBME.readTempC();        // Temperatur i °C
  float hum = myBME.readFloatHumidity(); // Relativ fuktighet %

  // --- Mate ENS160 med temp/hum ---
  myENS.setEnvironmentalData((int)temp, (int)hum);
  myENS.iaqMeasure(); // Start IAQ-måling

  // --- Les ENS160 ---
  uint16_t tvoc = myENS.getTVOC(); // TVOC i ppb
  uint16_t eco2 = myENS.getCO2();  // eCO2 i ppm

  // --- Les knapp for manuell overstyring ---
  bool override = digitalRead(OVERRIDE_BUTTON) == LOW; // Aktiv lav

  int pumpSpeed = 0; // Init pumpehastighet

  // --- Beregn pumpehastighet basert på fuktighet og luftkvalitet ---
  if (!override)
  {
    if (hum < 40 && tvoc < 350 && eco2 < 1000)
    {                  // Lav fuktighet og god luft
      pumpSpeed = 255; // Full hastighet
    }
    else
    { // Ellers stopp pumpe
      pumpSpeed = 0;
    }
  }
  else
  {                  // Overstyring aktiv
    pumpSpeed = 255; // Full hastighet
  }

  analogWrite(PUMP_PIN, pumpSpeed); // Sett PWM til pumpe

  // --- Oppdater OLED ---
  display.clearDisplay(); // Tøm skjerm
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");
  display.print("Hum: ");
  display.print(hum);
  display.println(" %");
  display.print("TVOC: ");
  display.print(tvoc);
  display.println(" ppb");
  display.print("eCO2: ");
  display.print(eco2);
  display.println(" ppm");
  display.print("Pumpe: ");
  display.println(pumpSpeed == 0 ? "AV" : "PÅ");
  display.display(); // Vis innhold

  // --- Serial Monitor for debugging ---
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C, ");
  Serial.print("Hum: ");
  Serial.print(hum);
  Serial.print(" %, ");
  Serial.print("TVOC: ");
  Serial.print(tvoc);
  Serial.print(" ppb, ");
  Serial.print("eCO2: ");
  Serial.print(eco2);
  Serial.print(" ppm, ");
  Serial.print("Pumpe: ");
  Serial.println(pumpSpeed == 0 ? "AV" : "PÅ");

  delay(500); // Oppdater hvert 0,5 sekund
}
