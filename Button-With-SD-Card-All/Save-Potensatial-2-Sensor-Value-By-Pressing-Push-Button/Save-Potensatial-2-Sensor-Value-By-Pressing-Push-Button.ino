/*
  
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK/SCK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/


#include <SPI.h>
#include <SD.h>
File myFile;

const int CsPin = 53; //Arduino Uno-4 Mega-53
const int LED = 10;
const int buttonPin = A0;
bool buttonState = 0;
bool buttonFlag = 0;


// Potentiometer
const int vcc = A8;  
const int gnd = A12;  
const int POTENTIOMETER_PIN = A10;  


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



// Potentiometer
pinMode(POTENTIOMETER_PIN, INPUT);

  // Create versual VCC AND GND
  pinMode(vcc, OUTPUT);  
  pinMode(gnd, OUTPUT); 
  digitalWrite(vcc, HIGH);  
  digitalWrite(gnd, LOW);

}//Void Setup End

void loop(){
   
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);

  if (buttonState == 1 && buttonFlag == 0) {
    buttonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Write_Data(); // Calling Sd card writeing function
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

  myFile = SD.open("TempData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to TempData.txt...");
    int data = analogRead(POTENTIOMETER_PIN);
    //myFile.println(String(data) + ',' + String(data)); //Saveing Lots of Data
    myFile.println(data);
    
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TempData.txt");
  }

 
}// Eend Sd_Card_Write_Data Function
