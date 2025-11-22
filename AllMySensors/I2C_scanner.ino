#include <Wire.h>

void setup()
{

    Wire.begin(); // start I2C (SDA/SCL)
    Serial.begin(115200);
    // Vent til seriell er klar (nyttig på noen kort)
    while (!Serial)
    {
        ; // gjør ingenting
    }
    Serial.println("I2C-skanner starter...");
}
void loop()
{
    byte error;
    byte address;
    int nDevices = 0;
    Serial.println("Skanner adresser 0x01 til 0x7E...");
    for (address = 1; address < 127; address++)
    {
        // Start en transmisjon til denne adressen:
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("Fant enhet på adresse 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Ukjent feil på adresse 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("Ingen I2C-enheter funnet.\n");
    }
    else
    {
        Serial.println("Skann ferdig.\n");
    }
    delay(2000); // vent litt før neste skann
}