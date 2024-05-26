const int LED = 10;
const int buttonPin = A2;
bool buttonState = 0;
int buttonFlag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(LED, OUTPUT);

}

void loop(){
   
  buttonState = digitalRead(buttonPin);
  digitalWrite(LED, buttonState);
  Serial.println(buttonState);
  //delay(200);
}