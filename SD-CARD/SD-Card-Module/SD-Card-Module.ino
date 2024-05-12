#include<SPI.h> //libery for spi commenication
#include<SD.h> //libery for SD Card module

/*
CS   - 4
SCK  - 13
MOSI - 11
MISO - 12
*/



File myFile;                  //File object
char data;


void setup() {
  pinMode(4, OUTPUT);        //Set CS pin as output
  Serial.begin(9600);
  while (!Serial);            //Wait for the serial communication to initialize
  Serial.println("Initializing SD Card");
  if (SD.begin(4)) {
    Serial.println("Initialization Successful");
  }
  else {
    Serial.println("Initialization Failed");
  }
  delay(5000);
  createFile("myDat.txt");    //Calling createFile() function
  delay(5000);
  readFile("myDat.txt");      //Calling readFile() function
  delay(5000);
  removeFile("myDat.txt");    //Calling removeFile() function
}

//Funtion to create file
void createFile(String FileName) {
  myFile = SD.open(FileName, FILE_WRITE);
  Serial.println("Creating File");
  if (myFile) {
    Serial.println("File Created: " + FileName);
    myFile.println("TechDelay");
    Serial.println("Writing finished, Closing File now");
    myFile.close();
  }
  else {
    Serial.println("File Cannot be created");
  }
}

//Funtion to read file
void readFile(String FileName) {
  myFile = SD.open(FileName, FILE_READ);
  if (myFile) {
    Serial.println("Reading File");
    while (myFile.available()) {
      data = myFile.read();
      Serial.print(data);
    }
    Serial.println("Reading finished, Closing File now");
    myFile.close();
  }
  else {
    Serial.println("File Cannot be read");
  }
}

//Funtion to remove files
void removeFile(String FileName){
  if(SD.exists(FileName)){
    SD.remove(FileName);
    Serial.println(FileName+ " Deleted Successfully");
  }
  else{
    Serial.println(FileName+ " Cannot be found");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
}