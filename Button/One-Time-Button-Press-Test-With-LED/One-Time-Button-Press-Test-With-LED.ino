const int LED = 10;
const int buttonPin = A0;
bool buttonState = 0;
bool buttonFlag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(LED, OUTPUT);

}

void loop(){
   
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == 1 && buttonFlag == 0) {
    digitalWrite(LED, HIGH);
    buttonFlag = 1;
    delay(200);
  }

  else if (buttonState == 0 && buttonFlag == 1) {
    buttonFlag = 0;
    digitalWrite(LED, LOW);
  }

  else{
    digitalWrite(LED, LOW);
  }
}