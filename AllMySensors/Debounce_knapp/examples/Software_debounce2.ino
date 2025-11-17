const int buttonPin = 2; // The number of the pushbutton pin
const int ledPin = 8;    // The number of the LED pin

int ledState = HIGH;      // The current state of the output pin
int buttonState;          // The current reading from the input pin
int lastButtonState = LOW; // The previous reading from the input pin

unsigned long lastDebounceTime = 0; // The last time the output pin was toggled
unsigned long debounceDelay = 50;   // The debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) { // Assuming a pull-down resistor or INPUT_PULLUP
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
    }
  }
  lastButtonState = reading;
}