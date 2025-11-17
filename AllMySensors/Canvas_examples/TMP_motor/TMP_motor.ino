static int tmpPin = A0;
static int trPin = 6;

static int redPin = 13;
static int greenPin = 11;

//25c = 0.75v og 0.01 = 1c dvs 0c = 0.5v
void setup()
{
  Serial.begin(9600);
  pinMode(tmpPin, INPUT);
  pinMode(trPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
	float tmpR = analogRead(tmpPin);
	float tmpV = ((tmpR/1023*5)-0.5)*100;
	
	if (tmpV > 25) {
		digitalWrite(trPin, 1);	
		digitalWrite(redPin, 1);
		digitalWrite(greenPin, 0);
	} else if (tmpV > 20) {
		int fanSpeed = map(tmpV, 20, 25, 100, 255);
		analogWrite(trPin, fanSpeed);
		digitalWrite(redPin, 1);
		digitalWrite(greenPin, 1);
	}
	else {
		digitalWrite(trPin, 0);
		digitalWrite(redPin, 0);
		digitalWrite(greenPin, 1);
		
	}
	
	Serial.println(tmpV);
}

