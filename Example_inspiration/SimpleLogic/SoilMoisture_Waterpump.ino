
int soilPin = A0;
int soilReading = 0;
int waterPumpSwitch = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soilPin, INPUT);
  pinMode(waterPumpSwitch, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  soilReading = analogRead(soilPin);
  Serial.println(soilReading);
  
  digitalWrite(waterPumpSwitch, HIGH);
  Serial.println(digitalRead(waterPumpSwitch));
  delay(2500);
}
