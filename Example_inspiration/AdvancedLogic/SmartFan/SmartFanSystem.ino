/*
Logikk:
- BME280 måler temperatur og relativ fuktighet
- ENS160 måler luftkvalitet (TVOC og eCO2), kompensert med temp/hum
- PWM-motor styrer viftehastighet
- Retning settes basert på modus:
    - Sommermodus: én retning
    - Vintermodus: motsatt retning
- Motorhastighet justeres basert på temperatur og luftkvalitet
- Toggle-knapp bytter mellom sommer/vinter-modus ved hvert trykk
- OLED viser sanntidsdata: Temp, Hum, TVOC, eCO2, motorhastighet og retning
- Serial Monitor brukes for debugging
*/

#include <Wire.h>
#include <SparkFunBME280.h>
#include <SparkFun_ENS160.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED bredde i piksler
#define SCREEN_HEIGHT 64 // OLED høyde i piksler
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED objekt

#define MOTOR_PWM 9     // PWM-pin til motor/vifte
#define MOTOR_DIR 8     // Retningspinne til motor
#define TOGGLE_BUTTON 7 // Knapp for å bytte sommer/vinter-modus

BME280 myBME; // BME280 objekt
ENS160 myENS; // ENS160 objekt

bool summerMode = true;      // Modus: sommer/vinter
int motorSpeed = 0;          // Motorhastighet 0-255
bool lastButtonState = HIGH; // Husk forrige knappestatus for toggle

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
  myENS.iaqInit();

  // --- Initialiser OLED ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED ikke funnet!");
    while (1)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Vifte");
  display.display();

  // --- Aktuatorpinner ---
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(TOGGLE_BUTTON, INPUT_PULLUP);
}

void loop()
{

  // --- Les knapp for toggle ---
  bool buttonState = digitalRead(TOGGLE_BUTTON); // Les knappestatus
  if (lastButtonState == HIGH && buttonState == LOW)
  {                           // Registrer trykk (HIGH→LOW)
    summerMode = !summerMode; // Bytt modus
    Serial.print("Modus byttet: ");
    Serial.println(summerMode ? "Sommer" : "Vinter");
    delay(200); // Enkel debounce
  }

  lastButtonState = buttonState; // Oppdaterer forrige status

  // --- Les temperatur og fuktighet ---
  float temp = myBME.readTempC();
  float hum = myBME.readFloatHumidity();

  // --- Mate ENS160 med temp/hum ---
  myENS.setEnvironmentalData((int)temp, (int)hum);
  myENS.iaqMeasure();

  // --- Les luftkvalitet ---
  uint16_t tvoc = myENS.getTVOC();
  uint16_t eco2 = myENS.getCO2();

  // --- Sett motorretning basert på modus ---
  if (summerMode)
    digitalWrite(MOTOR_DIR, HIGH); // True -> sommermodus
  else
    digitalWrite(MOTOR_DIR, LOW); // False -> vintermodus

  // --- Beregn motorhastighet basert på temperatur og luftkvalitet ---
  if (temp < 20 && tvoc < 250)
    motorSpeed = 50;
  else if (temp < 25 && tvoc < 300)
    motorSpeed = 120;
  else
    motorSpeed = 255;

  analogWrite(MOTOR_PWM, motorSpeed); // Sett PWM til motor

  // --- Oppdater OLED ---
  display.clearDisplay();
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
  display.print("Motor: ");
  display.print(motorSpeed);
  display.print("/255");
  display.println(summerMode ? " Sommer" : " Vinter");
  display.display();

  // --- Serial Monitor ---
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
  Serial.print("Motor: ");
  Serial.print(motorSpeed);
  Serial.print("/255, ");
  Serial.print("Retning: ");
  Serial.println(summerMode ? "Sommer" : "Vinter");

  delay(500); // Oppdater hvert 0,5 sek
}
