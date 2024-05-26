#include <SPI.h>
#include <SD.h>

File myFile;


// String to hold one line of text
String buffer;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

 

  // re-open the file for reading:
  myFile = SD.open("TempData.txt");
  if (myFile) {
    

    // read from the file until there's nothing else in it:
    int TempDataSum = 0;
    int TempDataCounter = 0;
    while (myFile.available()) {
      buffer = myFile.readStringUntil('\n');
      //Serial.write(myFile.read());
      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer data str to int
      TempDataCounter = TempDataCounter + 1;
  
      Serial.println(buffer);
      //Serial.println(TempDataSum);
      
    }// While loop end
    
    myFile.close();// close the file:
    
    Serial.print("The Final value is: ");
    Serial.println(TempDataSum / TempDataCounter); // Final Ans--------------

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}


