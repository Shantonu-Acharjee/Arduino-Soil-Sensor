const int LED = 10;
const int buttonPin = 5;

int buttonFlag = 0;

void setup() {
   // Define pin #12 as input and activate the internal pull-up resistor
   pinMode(buttonPin, INPUT_PULLUP);
   // Define pin #13 as output, for the LED
   pinMode(LED, OUTPUT);
}

void loop(){
   // Read the value of the input. It can either be 1 or 0
   int buttonValue = digitalRead(buttonPin);

  if (buttonValue == LOW && buttonFlag == 0){
    buttonFlag = 1;
    digitalWrite(LED,HIGH);
    delay(100);
   } 
   
   
  if (buttonValue == HIGH && buttonFlag == 1){
    buttonFlag = 0;
    digitalWrite(LED, LOW);
  }

  else{
    digitalWrite(LED, LOW);
  }
}