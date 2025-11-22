#include <Servo.h>

Servo myServo;

const int potPin = A0;

float filteredValue = 0; // for EMA-smoothing
const float alpha = 0.1; // smoothing factor (0.0–1.0)

int safeAngle;
int mappedValue;

const int deadzone = 3; // ADC deadzone (3/1023 ~ 0.3%)

void setup()
{
    myServo.attach(9);
    Serial.begin(9600);

    filteredValue = analogRead(potPin); // initialize correctly
}

void loop()
{
    int raw = analogRead(potPin);

    // -------- 1) Smooth noisy signal (EMA filter) ------------
    filteredValue = (alpha * raw) + (1 - alpha) * filteredValue;

    // -------- 2) Deadzone around midpoint --------------------
    if (abs(raw - filteredValue) < deadzone)
    {
        filteredValue = filteredValue; // keeps last value stable
    }

    // -------- 3) Mapping to servo angle ----------------------
    mappedValue = map((int)filteredValue, 0, 1023, 0, 180);

    // -------- 4) Realistic servo constraints -----------------
    safeAngle = constrain(mappedValue, 20, 160);

    myServo.write(safeAngle);

    // Debugging output
    Serial.print("Raw: ");
    Serial.print(raw);
    Serial.print("\tFiltered: ");
    Serial.print(filteredValue);
    Serial.print("\tMapped: ");
    Serial.print(mappedValue);
    Serial.print("\tSafe: ");
    Serial.println(safeAngle);

    delay(10);
}
