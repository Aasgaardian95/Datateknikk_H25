const int eBtnPin = 13;
const int eLedPin = 11;
int eBtn = 1;
int eBtnS = 1;
int e = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(eBtnPin, INPUT_PULLUP);
  pinMode(eLedPin, OUTPUT);
  
}

void loop()
{
  eBtn = digitalRead(eBtnPin);
  
  if (eBtn == 0 && eBtn != eBtnS) {
    if (e == 0) {
      	e = 1;
      	digitalWrite(eLedPin, 1);
    }	else {
      e = 0;
      digitalWrite(eLedPin, 0);
    }
  }
  eBtnS = eBtn;
  
  
  Serial.println(eBtn);
  
}