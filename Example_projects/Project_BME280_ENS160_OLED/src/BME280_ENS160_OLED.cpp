#include <Wire.h>
#include <SparkFunBME280.h>
#include <SparkFun_ENS160.h>
#include <Adafruit_GFX.h>          // Grafikkbibliotek for skjerm 
#include <Adafruit_SSD1306.h>      // OLED-skjermdriver (SSD1306)

#define SCREEN_WIDTH 128           // OLED bredde i piksler 
#define SCREEN_HEIGHT 64           // OLED høyde i piksler 
#define OLED_RESET -1              // Ingen reset-pin (brukes ikke) 

BME280 mySensor;
SparkFun_ENS160 myENS; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ensStatus; 

void setup()
{
  // --- Konfigurerer BME280 sensor for grunnleggende målinger ---
  Serial.begin(115200);
  Serial.println("Reading basic values from BME280");

  Wire.begin();

  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

  // --- Konfigurerer ENS160 sensor for grunnleggende målinger ---
  {
  if( !myENS.begin() )
	{
		Serial.println("Could not communicate with the ENS160, check wiring.");
		while(1);
	}

  Serial.println("Example 1 Basic Example.");

	// Reset the indoor air quality sensor's settings.
	if( myENS.setOperatingMode(SFE_ENS160_RESET) )
		Serial.println("Ready.");

	delay(100);

	// Device needs to be set to idle to apply any settings.
	// myENS.setOperatingMode(SFE_ENS160_IDLE);

	// Set to standard operation
	// Others include SFE_ENS160_DEEP_SLEEP and SFE_ENS160_IDLE
	myENS.setOperatingMode(SFE_ENS160_STANDARD);

	// There are four values here: 
	// 0 - Operating ok: Standard Operation
	// 1 - Warm-up: occurs for 3 minutes after power-on.
	// 2 - Initial Start-up: Occurs for the first hour of operation.
  //												and only once in sensor's lifetime.
	// 3 - No Valid Output
	ensStatus = myENS.getFlags();
	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
	Serial.println(ensStatus);

	// Konfigurerer OLED-skjerm
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C er standard I2C-adresse 
    Serial.println(F("Fant ikke OLED-skjerm!")); 
    while (true); 
  } 
  display.clearDisplay(); 
  display.setTextSize(1);          // Tekststørrelse 
  display.setTextColor(SSD1306_WHITE); 

  // Velkomstmelding på skjerm 
  display.setCursor(0, 0); 
  display.println("Velkommen!"); 
  display.display(); 
  delay(1500); 
  display.clearDisplay(); 
}
}

void loop()
{
  display.clearDisplay(); 
  display.setCursor(0, 0); 
  display.println("Temperatur: "); 
  display.println(mySensor.readTempC(), 2);
  display.display(); 
  

  Serial.print("Humidity: ");
  Serial.print(mySensor.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 0);

  Serial.print(" Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  Serial.print(mySensor.readFloatAltitudeFeet(), 1);

  Serial.print(" Temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  Serial.print(mySensor.readTempC(), 2);

  Serial.println();

  if( myENS.checkDataStatus() )
	{
		Serial.print("Air Quality Index (1-5) : ");
		Serial.println(myENS.getAQI());

		Serial.print("Total Volatile Organic Compounds: ");
		Serial.print(myENS.getTVOC());
		Serial.println("ppb");

		Serial.print("CO2 concentration: ");
		Serial.print(myENS.getECO2());
		Serial.println("ppm");

	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
    Serial.println(myENS.getFlags());

		Serial.println();


	}
  delay(5000);
}
