#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_ENS160.h>
#include <SparkFunBME280.h>

// Definerer skjermstørrelse og adresse for OLED-skjerm
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Oppretter objekter av ENS160, BME280 og OLED-skjerm
SparkFun_ENS160 myENS;
BME280 myBME280;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variabler for å sikre at kompensasjonsverdier kun skrives ut én gang
bool printedCompensation = false;
int ensStatus;

// Pin definisjoner
const int H_input1 = 3;
const int H_input2 = 2;
const int H_enablePin = 5;
const int ldrPin = A0;
const int ledGreen = 7;
const int ledRed = 8;
const int ledYellow = 9;
const int ledBlue = 10;
int motorRPM = 0;

// Variabler for BME280
float rh;
float tempC;

// Variabler som skal brukes i if-setninger
float temperatureUpperThreshold = 24.0; // Terskelverdi for øvre grense av temperatur
float heaterLowerThreshold = 21.0;      // Terskelverdi for nedre grense av temperatur før varmer aktiveres
float heaterUpperThreshold = 22.0;      // Terskelverdi for øvre grense av temperatur før varmer deaktiveres
int aqiThreshold = 3;                   // Terskelverdi for AQI-nivå
float tvocThreshold = 50.0;             // Terskelverdi for TVOC-nivå
float co2Threshold = 800.0;             // Terskelverdi for CO2-nivå
float lightThreshold = 750.0;           // Terskelverdi for lysnivå
int mappedLightValue;

void setup()
{
  // Starter I2C kommunikasjon
  Wire.begin();

  // Starter serial kommunikasjon for debugging
  Serial.begin(115200);

  // Setter pinMode for pinner brukt i systemet
  pinMode(H_input1, OUTPUT);
  pinMode(H_input2, OUTPUT);
  pinMode(H_enablePin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  // *** Initialiserer ENS160 sensor ***
  if (!myENS.begin())
  {
    Serial.println("Air Quality Sensor did not begin.");
    while (1) // Frys
      ;
  }

  // *** Initialiserer BME280 sensor ***
  if (myBME280.beginI2C() == false) // Starter kommunikasjon over I2C
  {
    Serial.println("The Environmental did not respond. Please check wiring or I2C Address.");
    while (1) // Frys
      ;
  }

  // *** Initialiserer OLED skjerm ***
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) // Ikke gå videre - loop for evig og alltid
      ;
  }

  display.display(); // Viser frem oppstartsbilde i 2 sekunder
  delay(2000);
  display.clearDisplay(); // Tømmer skjermen

  // *** Kompensering av ENS160 med BME280 verdier ***
  rh = myBME280.readFloatHumidity(); // Leser relativ fuktighet fra BME280
  tempC = myBME280.readTempC();      // Leser temperatur fra BME280
  Serial.println("Example 4 Humidity and Temperature Sensor Compensation - BME280.");
  Serial.print("Relative Humidity (%): ");
  Serial.println(rh); // Skriver ut relativ fuktighet
  Serial.print("Temperature (Celsius): ");
  Serial.println(tempC); // Skriver ut temperatur

  // Resetter ENS160 før kompensering
  if (myENS.setOperatingMode(SFE_ENS160_RESET)) // Setter ENS160 i reset-modus og sjekker om reset var vellykket
  {
    Serial.println("ENS160 reset successful.");
  }
  else
  {
    Serial.println("ENS160 reset failed.");
  }
  delay(100);

  // Sender inn kompenseringsverdier til ENS160
  myENS.setTempCompensationCelsius(tempC); // Mater inn temperatur til ENS160
  myENS.setRHCompensationFloat(rh);        // Mater inn relativ fuktighet til ENS160

  delay(500);

  // Setter ENS160 i standard operasjonsmodus
  myENS.setOperatingMode(SFE_ENS160_STANDARD);

  // Her er det totalt fire statusflagger:
  // 0 - Standard Operation
  // 1 - Warm up period
  // 2 - Initial Start Up
  // 3 - Invalid Compensation Values
  ensStatus = myENS.getFlags();
  Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
  Serial.println(ensStatus); // Skriver ut statusflaggen til serial monitor
}

void loop()
{

  // *** Constrain og mapping av verdier ***
  int lightValue = analogRead(ldrPin);
  mappedLightValue = map(lightValue, 0, 1023, 0, 100); // Mapper lysverdien fra LDR til prosent (0-100%)

  // *** Logikk for hva/hvordan systemet skal varsle, og når ***

  // if-test for at systemet skal varsle basert på terskelverdier fra AQI og temperatur
  // Denne if-testen sjekker at AQI og temperatur er under gitt terskelverdi

  // Hvis både AQI og temperatur er over terskelverdien, lyser rødt lys og motor ventilerer rommet
  if (myENS.getAQI() > aqiThreshold && myBME280.readTempC() > temperatureUpperThreshold)
  {
    analogWrite(H_enablePin, 255);
    digitalWrite(H_input1, HIGH);
    digitalWrite(H_input2, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    delay(50);
  }

  // Hvis bare temperaturen er over terskelverdien, lyser rødt lys og motor ventilerer klasserommet
  else if (myBME280.readTempC() > temperatureUpperThreshold)
  {
    analogWrite(H_enablePin, 255);
    digitalWrite(H_input1, HIGH);
    digitalWrite(H_input2, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    delay(50);
  }

  // Hvis bare AQI er over terskelverdien, lyser rødt lys og motor ventilerer klasserommet
  else if (myENS.getAQI() > aqiThreshold)
  {
    analogWrite(H_enablePin, 255);
    digitalWrite(H_input1, HIGH);
    digitalWrite(H_input2, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    delay(50);
  }

  // Hvis temperaturen er mellom de to terskelverdiene (21-22 grader) for varmer, lyser blått lys og motor varmer opp rommet
  else if (myBME280.readTempC() < heaterUpperThreshold && myBME280.readTempC() > heaterLowerThreshold)
  {
    digitalWrite(ledBlue, HIGH);
  }

  // Hvis ingen av verdiene er over terskelverdien, lyser grønt lys og motor er av
  else
  {
    analogWrite(H_enablePin, 0);
    digitalWrite(H_input1, LOW);
    digitalWrite(H_input2, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, LOW);
    delay(50);
  }

  // if-test for at systemet skal varsle basert på lysnivå
  // Hvis lysnivået er under terskelverdien, lyser gult lys for å bedre lysforholdene i klasserommet
  if (analogRead(ldrPin) < lightThreshold)
  {
    digitalWrite(ledYellow, HIGH);
  }
  else
  {
    digitalWrite(ledYellow, LOW);
  }

  // *** Serial monitor for debugging ***
  Serial.print("Lightvalue: ");
  Serial.println(mappedLightValue); // Skriver ut lysverdien til serial monitor

  if (myENS.checkDataStatus())
  {

    if (printedCompensation == false)
    {
      Serial.println("---------------------------");
      Serial.print("Compensation Relative Humidity (%): ");
      Serial.println(myENS.getRH()); // Skriver ut kompenseringsfuktighet til serial monitor
      Serial.println("---------------------------");
      Serial.print("Compensation Temperature (Celsius): ");
      Serial.println(myENS.getTempCelsius()); // Skriver ut kompensasjonstemperatur til serial monitor
      Serial.println("---------------------------");
      printedCompensation = true;
      delay(500);
    }

    Serial.print("Air Quality Index (1-5) : ");
    Serial.println(myENS.getAQI()); // Skriver ut AQI-verdi til serial monitor

    Serial.print("Total Volatile Organic Compounds: ");
    Serial.print(myENS.getTVOC()); // Skriver ut TVOC-verdi til serial monitor
    Serial.println("ppb");

    Serial.print("CO2 concentration: ");
    Serial.print(myENS.getECO2()); // Skriver ut CO2-verdi til serial monitor
    Serial.println("ppm");

    Serial.print("Temperature (Celsius): ");
    Serial.println(myBME280.readTempC()); // Skriver ut temperatur til serial monitor

    Serial.print("Relative Humidity (%): ");
    Serial.println(myBME280.readFloatHumidity()); // Skriver ut relativ fuktighet til serial monitor

    Serial.println();
  }

  // *** Logikk for visning på OLED-skjerm ***

  display.setTextColor(SSD1306_WHITE); // Velger hvit tekstfarge til OLED-skjermen
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);        // Setter tekstkursor til øverste venstre hjørne
  display.print("Temperature: "); // Printer temperatur til OLED-skjermen
  display.print(myBME280.readTempC());
  display.println(" C");

  display.setCursor(0, 10);      // Setter tekstkursor til neste linje
  display.print("Lightvalue: "); // Printer lysverdi til OLED-skjermen
  display.print(mappedLightValue);
  display.println(" %");

  display.setCursor(0, 20); // Setter tekstkursor til neste linje
  display.print("AQI:");    // Printer AQI-verdi til OLED-skjermen
  display.print(myENS.getAQI());
  display.print("  Humid: ");
  display.print(myBME280.readFloatHumidity());
  display.print("%");
  display.display();

  delay(500);
}
