
#include <SPI.h>
#include <SD.h>

const int chipSelect = 53;

const int vcc = A8;  
const int gnd = A12;  
const int POTENTIOMETER_PIN = A10;  

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(POTENTIOMETER_PIN, INPUT);

  // Create versual VCC AND GND
  pinMode(vcc, OUTPUT);  
  pinMode(gnd, OUTPUT); 
  digitalWrite(vcc, HIGH);  
  digitalWrite(gnd, LOW);


  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  
  int sensor = analogRead(POTENTIOMETER_PIN); //Read sensor value
  dataString += String(sensor);
    
  

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}









