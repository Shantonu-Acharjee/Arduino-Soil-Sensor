// This attempt uses the SoftwareSerial & raw Modbus packets.
//
// RS485 module wired up as:
// RS485 DI signal to pin 3
// RS485 RO signal to pin 2
// RS485 RE signal to pin 8
// RS485 DE signal to pin 7
// RS485 VCC to 5V
// RS485 GND to GND
//
#include <SoftwareSerial.h>

#define RE 8
#define DE 7

const uint32_t TIMEOUT = 500UL;

// canned message to your RS485 device
// change this for any other canned modbus message you like
// remember to make sure that the checksum is correct!
uint8_t msg[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
uint8_t rxByte;

SoftwareSerial swSerial(2, 3); // Receive (data in) pin, Transmit (data out) pin

void setup() {
  Serial.begin(9600);
  swSerial.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(1000);
}

void loop() {
  uint32_t startTime = 0;

  Serial.print("TX: ");
  printHexMessage( msg, sizeof(msg) );

  // send the command
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay( 10 );
  swSerial.write( msg, sizeof(msg) );
  swSerial.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  Serial.print("RX: ");
  
  // read any data received and print it out
  startTime = millis();
  while ( millis() - startTime <= TIMEOUT ) {
    if (swSerial.available()) {
      printHexByte(swSerial.read());
    }
  }
  Serial.println();
  delay(2000);
}

void printHexMessage( uint8_t values[], uint8_t sz ) {
  for (uint8_t i = 0; i < sz; i++) {
    printHexByte( values[i] );
  }
  Serial.println();
}

void printHexByte(byte b)
{
  Serial.print((b >> 4) & 0xF, HEX);
  Serial.print(b & 0xF, HEX);
  Serial.print(' ');
}