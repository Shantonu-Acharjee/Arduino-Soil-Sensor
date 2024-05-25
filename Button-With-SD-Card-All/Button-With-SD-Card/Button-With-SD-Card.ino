/* 

 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK/SCK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/

#include <SPI.h>
#include <SD.h>
File myFile;

const int LED = 10;
const int buttonPin = 5;
int buttonPinFlag = 0;

void setup() {
  Serial.begin(9600);
  // Define pin #12 as input and activate the internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  // Define pin #13 as output, for the LED
  pinMode(LED, OUTPUT);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
   
}

void loop(){
   // Read the value of the input. It can either be 1 or 0
   int buttonValue = digitalRead(buttonPin);
   if (buttonValue == LOW && buttonPinFlag == 0){
    buttonPinFlag = 1;
      
    digitalWrite(LED,HIGH);
    Sd_Cardsss();
   } 
   
   
   else {
      buttonPinFlag = 0;
      digitalWrite(LED, LOW);
   }
}






void Sd_Cardsss(){

  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}