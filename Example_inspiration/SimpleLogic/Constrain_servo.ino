#include <Servo.h>

Servo myServo;

const int potPin = A0;
int rawValue;
int mappedValue;
int safeAngle;

void setup()
{
    myServo.attach(9);
    Serial.begin(9600);
}

void loop()
{
    rawValue = analogRead(potPin);                // 0–1023
    mappedValue = map(rawValue, 0, 1023, 0, 180); // 0–180°

    // Beskytt servoen – ikke la den gå utenfor trygt område
    safeAngle = constrain(mappedValue, 20, 160); // 20–160°

    myServo.write(safeAngle);

    // Debug for å se hele kjeden
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print("\tMapped: ");
    Serial.print(mappedValue);
    Serial.print("\tSafe: ");
    Serial.println(safeAngle);

    delay(10);
}
