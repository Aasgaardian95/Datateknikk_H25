#include <Wire.h>
#include "SparkFunBME280.h"
#include "SparkFun_ENS160.h"
#include <Adafruit_GFX.h>          // Grafikkbibliotek for skjerm 
#include <Adafruit_SSD1306.h>      // OLED-skjermdriver (SSD1306)

#define SCREEN_WIDTH 128           // OLED bredde i piksler 
#define SCREEN_HEIGHT 32           // OLED høyde i piksler 
#define OLED_RESET -1              // Ingen reset-pin (brukes ikke) 

// --- Oppretter objekt av BME280, ENS160 og OLED-skjerm ---
BME280 myBME280;
SparkFun_ENS160 myENS160;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ensStatus;

void setup() {
  // --- Starter seriell kommunikasjon ---
  Serial.begin(115200);
  Wire.begin();

  // --- Initialiserer BME280 ---
  if (myBME280.beginI2C() == false)  //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1)
      ;  //Freeze
  }

  // --- Initialiserer ENS160 ---
  if( !myENS160.begin() )
	{
		Serial.println("Could not communicate with the ENS160, check wiring.");
		while(1);
	}

  Serial.println("Example 1 Basic Example.");

	// Reset the indoor air quality sensor's settings.
	if( myENS160.setOperatingMode(SFE_ENS160_RESET) )
		Serial.println("Ready.");

	delay(100);

	// Device needs to be set to idle to apply any settings.
	// myENS.setOperatingMode(SFE_ENS160_IDLE);

	// Set to standard operation
	myENS160.setOperatingMode(SFE_ENS160_STANDARD);

	ensStatus = myENS160.getFlags();
	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
	Serial.println(ensStatus);

   // --- Initialiserer OLED-skjerm ---
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1500);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
}


void loop() {

  // --- BME280 logikk ---
  Serial.print("Humidity: ");
  Serial.print(myBME280.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(myBME280.readFloatPressure(), 0);

  Serial.print(" Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  Serial.print(myBME280.readFloatAltitudeFeet(), 1);

  Serial.print(" Temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  Serial.print(myBME280.readTempC(), 2);
  Serial.println();

  // --- ENS160 logikk ---
  if (myENS160.checkDataStatus()) {
    Serial.print("Air Quality Index (1-5) : ");
    Serial.println(myENS160.getAQI());

    Serial.print("Total Volatile Organic Compounds: ");
    Serial.print(myENS160.getTVOC());
    Serial.println("ppb");

    Serial.print("CO2 concentration: ");
    Serial.print(myENS160.getECO2());
    Serial.println("ppm");

    Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
    Serial.println(myENS160.getFlags());
    Serial.println();
  } else {
      Serial.println("Ingen endringer oppdaget av ENS160 enda.");
  }

  // --- Visning OLED-skjerm ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temperatur: ");
  display.println(myBME280.readTempC(), 1);
  display.display();

  delay(1250);
}
