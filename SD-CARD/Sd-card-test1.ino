#include<SPI.h> //libery for spi commenication
#include<SD.h> //libery for SD Card module


int CS_pin = 10;
/*
CS   - 10
SCK  - 13
MOSI - 11
MISO - 12
*/





void setup() {
  pinMode(CS_pin, OUTPUT);
  Serial.begin(9600);
  while(!Serial); // wait for stablish Serial commenation
  Serial.println('Initializing SD Card');

  if(SD.begin(CS_pin)){
    Serial.println('Initializing Successful'); // if sd card is ok
  }

  else{
    Serial.println('Initializing faild'); // if sd card is not ok
  }

}







void loop() {
  

}
