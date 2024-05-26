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

// Save Data
const int SaveDataButtonPin = A0;
bool SaveDataButtonState = 0;
bool SaveDataButtonFlag = 0;


// Result Data
const int ResultDataButtonPin = A1;
bool ResultDataButtonState = 0;
bool ResultDataButtonFlag = 0;


// Delete All Data
const int DeleteDataButtonPin = A2;
bool DeleteDataButtonState = 0;
bool DeleteDataButtonFlag = 0;



// Potentiometer
const int vcc = A8;  
const int gnd = A12;  
const int POTENTIOMETER_PIN = A10;  


void setup() {

  Serial.begin(9600);

  pinMode(SaveDataButtonPin, INPUT);
  pinMode(ResultDataButtonPin, INPUT);
  pinMode(DeleteDataButtonPin, INPUT);
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
   
  SaveDataButtonState = digitalRead(SaveDataButtonPin);
  ResultDataButtonState = digitalRead(ResultDataButtonPin);
  DeleteDataButtonState = digitalRead(DeleteDataButtonPin);
  //Serial.println(SaveDataButtonState);


  // Save Data Button
  if (SaveDataButtonState == 1 && SaveDataButtonFlag == 0) {
    SaveDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Write_Data(); // Calling Sd card writeing function
  }


  // Result Data Button
  if (ResultDataButtonState == 1 && ResultDataButtonFlag == 0) {
    ResultDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Resul_Data(); // Calling Sd card Result Function
  }



  // Delete Data Button
  if (DeleteDataButtonState == 1 && DeleteDataButtonFlag == 0) {
    DeleteDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Delete_Data(); // Calling Sd card Result Function
  }



  else if (SaveDataButtonState == 0 && SaveDataButtonFlag == 1 || ResultDataButtonState == 0 && ResultDataButtonFlag == 1 || DeleteDataButtonState == 0 && DeleteDataButtonFlag == 1) {
    SaveDataButtonFlag = 0;
    ResultDataButtonFlag = 0;
    DeleteDataButtonFlag = 0;
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
    Serial.println(data);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TempData.txt");
  }

 
}// Eend Sd_Card_Write_Data Function








void Sd_Card_Resul_Data(){

  Serial.println("****Start Calculation*****");

  myFile = SD.open("TempData.txt");// Open TEMP SAVE DATA FILE

  if (myFile) {
    
    
    int TempDataSum = 0;
    int TempDataCounter = 0;
    String buffer; // String to hold one line of text


    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer data str to int
      TempDataCounter = TempDataCounter + 1;
  
      Serial.println(buffer);
      
      
    }// While loop end
    
    myFile.close();// close the file:
    
    Serial.print("The Final value is: ");
    Serial.println(TempDataSum / TempDataCounter); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TempData.txt..............");
  }


}// End Sd_Card_Resul_Data









void Sd_Card_Delete_Data(){

  SD.remove("TempData.txt");
  Serial.println("All File Delete");

}// End Sd_Card_Delete_Data

