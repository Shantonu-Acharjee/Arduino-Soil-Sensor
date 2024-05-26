#include <SPI.h>
#include <SD.h>

File myFile;
const int CsPin = 53; // Adjust based on your module
const int LED = 10;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // Wait for serial connection
  while (!Serial) {
    ;
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(CsPin)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
  myFile = SD.open("data.txt", FILE_READ);

  if (myFile) {
    Serial.println("Reading from data.txt:");
    digitalWrite(LED, HIGH); // Turn on LED for successful opening (optional)

    // Rest of your reading logic here

    myFile.close();
    Serial.println();
    digitalWrite(LED, LOW); // Turn off LED after closing (optional)
  } else {
    Serial.println("error opening data.txt");
  }

  delay(1000); // Wait for 1 second before reading again
}
