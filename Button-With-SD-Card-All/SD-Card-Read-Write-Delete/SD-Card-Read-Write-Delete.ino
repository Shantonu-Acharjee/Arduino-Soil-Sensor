/*
  
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK/SCK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/


#include <SPI.h>
#include <SD.h>
File myFile;

const int CsPin = 4;
const int LED = 10;
const int buttonPin = A0;
bool buttonState = 0;
bool buttonFlag = 0;


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(LED, OUTPUT);

  // Wait for serial Connection
  while (!Serial) {
    ; 
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(CsPin)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");


}//Void Setup End

void loop(){
   
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);

  if (buttonState == 1 && buttonFlag == 0) {
    Sd_Card_Write_Data(); // Calling Sd card writeing function
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





void Sd_Card_Write_Data(){
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to test.txt...");
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
