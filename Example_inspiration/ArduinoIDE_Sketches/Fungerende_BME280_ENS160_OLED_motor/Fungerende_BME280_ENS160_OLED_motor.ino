#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_ENS160.h>
#include <SparkFunBME280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

SparkFun_ENS160 myENS;
BME280 myBME280;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool printedCompensation = false;
int ensStatus;

const int H_input1 = 3;
const int H_input2 = 2;
const int H_enablePin = 5;
int motorRPM = 0;

float rh;
float tempC;

void setup() {
  Wire.begin();

  Serial.begin(115200);

  pinMode(H_input1, OUTPUT);
  pinMode(H_input2, OUTPUT);
  pinMode(H_enablePin, OUTPUT);

  if (!myENS.begin()) {
    Serial.println("Air Quality Sensor did not begin.");
    while (1)
      ;
  }

  if (myBME280.beginI2C() == false)  //Begin communication over I2C
  {
    Serial.println("The Environmental did not respond. Please check wiring or I2C Address.");
    while (1)
      ;  //Freeze
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.display();

  delay(2000);

  display.clearDisplay();

  Serial.println("Example 4 Humidity and Temperature Sensor Compensation - BME280.");

  rh = myBME280.readFloatHumidity();
  tempC = myBME280.readTempC();
  Serial.print("Relative Humidity (%): ");
  Serial.println(rh);
  Serial.print("Temperature (Celsius): ");
  Serial.println(tempC);

  // Reset the indoor air quality sensor's settings.
  if (myENS.setOperatingMode(SFE_ENS160_RESET))
    Serial.println("Ready.");

  delay(100);

  // Give values to Air Quality Sensor.
  myENS.setTempCompensationCelsius(tempC);
  myENS.setRHCompensationFloat(rh);

  delay(500);

  // Set to standard operation
  // Others include SFE_ENS160_DEEP_SLEEP and SFE_ENS160_IDLE
  myENS.setOperatingMode(SFE_ENS160_STANDARD);

  // There are four values here:
  // 0 - Operating ok: Standard Opepration
  // 1 - Warm-up: occurs for 3 minutes after power-on.
  // 2 - Initial Start-up: Occurs for the first hour of operation.
  //												and only once in sensor's lifetime.
  // 3 - No Valid Output
  ensStatus = myENS.getFlags();
  Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
  Serial.println(ensStatus);
}

void loop() {

  analogWrite(H_enablePin, 255);
  digitalWrite(H_input1, HIGH);
  digitalWrite(H_input2, LOW);
  delay(2500);
  digitalWrite(H_input1, LOW);
  digitalWrite(H_input2, LOW);
  delay(2500);
  analogWrite(H_enablePin, 255);
  digitalWrite(H_input1, LOW);
  digitalWrite(H_input2, HIGH);
  delay(2500);
  digitalWrite(H_input1, LOW);
  digitalWrite(H_input2, LOW);
  delay(2500);



  if (myENS.checkDataStatus()) {

    if (printedCompensation == false) {
      Serial.println("---------------------------");
      Serial.print("Compensation Relative Humidity (%): ");
      Serial.println(myENS.getRH());
      Serial.println("---------------------------");
      Serial.print("Compensation Temperature (Celsius): ");
      Serial.println(myENS.getTempCelsius());
      Serial.println("---------------------------");
      printedCompensation = true;
      delay(500);
    }

    Serial.print("Air Quality Index (1-5) : ");
    Serial.println(myENS.getAQI());

    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.print(myBME280.readTempC());
    display.println(" C");

    display.setCursor(0, 10);
    display.print("Humidity:    ");
    display.print(myBME280.readFloatHumidity());
    display.println(" %");

    display.setCursor(0, 20);
    display.print("CO2 conc.:   ");
    display.print(myENS.getECO2());
    display.println(" ppm");

    display.display();

    Serial.print("Total Volatile Organic Compounds: ");
    Serial.print(myENS.getTVOC());
    Serial.println("ppb");

    Serial.print("CO2 concentration: ");
    Serial.print(myENS.getECO2());
    Serial.println("ppm");

    Serial.print("Temperature (Celsius): ");
    Serial.println(myBME280.readTempC());

    Serial.print("Relative Humidity (%): ");
    Serial.println(myBME280.readFloatHumidity());

    Serial.println();
  }

  delay(200);
  display.clearDisplay();
}