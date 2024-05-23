const int LED = 13;
const int buttonPin = 5;

void setup() {
   // Define pin #12 as input and activate the internal pull-up resistor
   pinMode(buttonPin, INPUT_PULLUP);
   // Define pin #13 as output, for the LED
   pinMode(LED, OUTPUT);
}

void loop(){
   
  int buttonValue = digitalRead(buttonPin);

  if (buttonValue == LOW){
    LedTest();

  } 
  
  else {
    digitalWrite(LED, LOW);
   }
   
}





//Self function
void LedTest() {
 digitalWrite(LED,HIGH);
      
      
}