#include <SPI.h>
#include <SD.h>

File myFile;

const int CsPin = 53; // Arduino Uno-4 Mega-53
const int LED = 10;
const int buttonPin = A1;
bool buttonState = false; // Initialize to false
bool buttonFlag = false; 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
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
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) { // Check for HIGH state (button pressed)
    // Write to SD card only if button is pressed and flag is false
    if (!buttonFlag) {
      buttonFlag = true; // Set flag to prevent multiple writes
      digitalWrite(LED, HIGH);
      delay(50);
      Sd_Card_Write_Data();
    }
  } else {
    buttonFlag = false; // Reset flag when button is released
  }

  digitalWrite(LED, buttonState); // LED reflects button state
}

void Sd_Card_Write_Data() {
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to test.txt...");
    myFile.println("hi My name is Shantonu");

    // Close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // If the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
