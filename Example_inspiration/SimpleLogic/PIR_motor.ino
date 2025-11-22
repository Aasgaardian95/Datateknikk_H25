#include <Servo.h>

int pirPin = 2;   // PIR sensor input pin
int servoPin = 9; // Servo motor control pin
int servoPw = 11;

int motionStatus = 0; // Variable to store PIR status
int pirState = 0;     // Current state of PIR
Servo myServo;        // Create servo object

int lowerThreshold = 3;

int pos = 0; // Variable to store servo position

void setup()
{
    Serial.begin(9600);     // Start serial communication at 9600 baud
    pinMode(pirPin, INPUT); // Set PIR pin as input
    pinMode(servoPw, OUTPUT);
    myServo.attach(servoPin); // Attach servo to the specified pin
    myServo.write(0);         // Initialize servo position to 0 degrees
    delay(5000);              // Wait for sensor to stabilize
}

void loop()
{
    motionStatus = digitalRead(pirPin); // Read PIR sensor status
    Serial.println(motionStatus);

    if (motionStatus == HIGH)
    { // If motion is detected
        if (pirState == LOW)
        {
            Serial.println("Motion detected!");
            pirState = HIGH;

            for (pos = 0; pos <= 180; pos += 1)
            { // Move servo from 0 to 180 degrees
                digitalWrite(servoPw, HIGH);
                myServo.write(pos);
                delay(7); // Wait for servo to reach position
                digitalWrite(servoPw, LOW);
            }

            for (pos = 180; pos >= 0; pos -= 1)
            { // Move servo back from 180 to 0 degrees
                digitalWrite(servoPw, HIGH);
                myServo.write(pos);
                delay(7); // Wait for servo to reach position
                digitalWrite(servoPw, LOW);
            }
        }
    }

    else
    {
        if (pirState == HIGH)
        {
            Serial.println("No motion detected");
            pirState = LOW;
            digitalWrite(servoPw, HIGH);
            myServo.write(0);
            digitalWrite(servoPw, LOW);
        }
    }
    delay(1000);
}
