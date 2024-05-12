// script to deminstrate 2 x 16 LCD and 2 x SD card.

#include <SPI.h>                        // required by SD
#include <SD.h>                         // required for SD card

#define SDSS1pin  53                      // on the UNO the Sparkfun SDSS pin is 8 !!!
#define SDSS2pin  13                      // on the UNO the Sparkfun SDSS pin is 8 !!!

File anyFile;                           // for logging day records
File entry;
File root;

String fileName  =  "anyFile.txt";

unsigned long readPosition;
unsigned long byteCount;

byte byteBuffer[4096];

void setup()
{
  pinMode(SDSS1pin, OUTPUT);                  // set SS pin to output (required they say)
  pinMode(SDSS2pin, OUTPUT);                  // set SS pin to output (required they say)
  digitalWrite(SDSS1pin, HIGH);
  digitalWrite(SDSS2pin, HIGH);

  Serial.begin(9600);                         // init seral for serialmonitor
  Serial.println("Starting");


  if (!SD.begin(SDSS1pin))                          // start the SD stuff with 53 as SS pin
  {
    Serial.println("SD.Begin() SD 1 Failed");
    delay(2000);
  }
  Serial.println("\r\nSD1 Begin OK.");
  Serial.println("/r/n Files on SD2 are: ");
  File root = SD.open("/");
  printDirectory(root);                             // list files on SD1
  root.close();
  digitalWrite(SDSS1pin, HIGH);                     // disable SD1

  if (!SD.begin(SDSS2pin))                          // start the SD stuff with 53 as SS pin
  {
    Serial.println("SD.Begin() SD 2 Failed");
    delay(2000);
  }
  Serial.println("\r\nSD2 Begin OK.");
  delay(1000);

  Serial.println("/r/n Files on SD2 are: ");
  root = SD.open("/");
  printDirectory(root);                             // list files on SD2
  SD.remove(fileName);                              // remove the file on SD2 in case it exists
  Serial.println("/r/n Files on SD2 now are: ");
  root = SD.open("/");
  printDirectory(root);                             // list files on SD2 again
  delay(2000);

  Serial.println("\r\n\r\nOpen ANYFILE.TXT on SD1 and copy to SD2");

  digitalWrite(SDSS1pin, HIGH);              //    disable SD1
  digitalWrite(SDSS2pin, HIGH);              //    disable SD2
  readPosition = 0;
};

// ============================================  MAIN LOOP  ====================================
void loop()
{
  if (!SD.begin(SDSS1pin))                          // start the SD stuff with 53 as SS pin
  {
    Serial.println("SD.Begin() SD 1 Failed");
    delay(2000);
  }

  anyFile = SD.open(fileName, FILE_READ);             // Open for read
  while (!anyFile)
  {
    Serial.println("Opening of the sourcefile Failed");
    delay(2000);
  }
  if (readPosition == anyFile.size())
  {
    Serial.print("Copied bytes:    ");
    Serial.println(anyFile.size());
    while (1) delay(10);
  }

  anyFile.seek(readPosition);
  byteCount = 0;
  while (anyFile.available() && byteCount < 4096)
  {
    byteBuffer[byteCount] = anyFile.read();
    byteCount++;
    readPosition++;
  }
  anyFile.close();
  digitalWrite(SDSS1pin, HIGH);              //    disable SD1


  if (!SD.begin(SDSS2pin))                          // start the SD stuff with 53 as SS pin
  {
    Serial.println("SD.Begin() SD 2 Failed");
    delay(2000);
  }

  anyFile = SD.open(fileName, FILE_WRITE);             // Open for write
  anyFile.write(byteBuffer, byteCount);
  anyFile.close();
  digitalWrite(SDSS2pin, HIGH);                     //    disable SD2
};



// ================================ List files and sizes on SD card ==========================
// -------------------------------------------------------------------------------------------
void printDirectory(File dir)               // lists the files and filesize on the SD card (only root)
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (! entry)                       // no more files
    {
      break;
    }
    Serial.print(entry.name());
    Serial.print("    ");
    Serial.println(entry.size(), DEC);
    entry.close();
  }
};