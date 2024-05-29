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

// Save FinalTemperature
const int SaveDataButtonPin = A0;
bool SaveDataButtonState = 0;
bool SaveDataButtonFlag = 0;


// Result FinalTemperature
const int ResultDataButtonPin = A1;
bool ResultDataButtonState = 0;
bool ResultDataButtonFlag = 0;


// Delete All FinalTemperature
const int DeleteDataButtonPin = A2;
bool DeleteDataButtonState = 0;
bool DeleteDataButtonFlag = 0;



// Potentiometer
const int vcc = A8;  
const int gnd = A12;  
const int POTENTIOMETER_PIN = A10;  


int TotalSampleData = 0;
int FinalTemperature = 0;
int FinalMoisture = 0;
int FinalConductivity = 0;
int FinalPH = 0;
int FinalNitrogen = 0;
int FinalPhosphorus = 0;
int FinalPotassium = 0;
String CurrentStatus = "TOTAL SAMPLE";


// LCD Start
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
LCDWIKI_KBV mylcd(ILI9486,40,38,39,-1,41); //model,cs,cd,wr,rd,reset

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


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


  Sd_Card_Resul_Data(); // Get SD CARD OLD FinalTemperature TO SHOW OPENING

  // LCD START
  mylcd.Init_LCD();
  LCD_Skin_Data(); // Calling LCD SKIN FinalTemperature FOR TEXT SHOW WHEN START

}//Void Setup End






void loop(){
   
  SaveDataButtonState = digitalRead(SaveDataButtonPin);
  ResultDataButtonState = digitalRead(ResultDataButtonPin);
  DeleteDataButtonState = digitalRead(DeleteDataButtonPin);
  //Serial.println(SaveDataButtonState);


  // Save FinalTemperature Button
  if (SaveDataButtonState == 1 && SaveDataButtonFlag == 0) {
    SaveDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Write_Data(); // Calling Sd card writeing function
    LCD_Skin_Data(); // Calling LCD SKIN FinalTemperature FUNCTION
  }


  // Result FinalTemperature Button
  if (ResultDataButtonState == 1 && ResultDataButtonFlag == 0) {
    ResultDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);
    Sd_Card_Resul_Data(); // Calling Sd card Result Function
    LCD_Skin_Data(); // Calling LCD SKIN FinalTemperature FUNCTION
  }



  // Delete FinalTemperature Button
  if (DeleteDataButtonState == 1 && DeleteDataButtonFlag == 0) {
    DeleteDataButtonFlag = 1;
    digitalWrite(LED, HIGH);
    delay(500);

    Sd_Card_Delete_Data(); // Calling Sd card Result Functio 
    LCD_Skin_Data(); // Calling LCD SKIN FinalTemperature FUNCTION
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

  FinalTemperature = analogRead(POTENTIOMETER_PIN);

  // Temperature Section START ----------------------------------->
  myFile = SD.open("TempData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to TempData.txt...");
    //myFile.println(String(FinalTemperature) + ',' + String(FinalTemperature)); //Saveing Lots of FinalTemperature
    myFile.println(FinalTemperature);
    Serial.println(FinalTemperature);
    // close the file:
    myFile.close();
    Serial.println("Writing to TempData Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TempData.txt");
  }

  // Temperature Section END ------------------XXXXX----------------->





  // Moisture Section START ----------------------------------->
  myFile = SD.open("MoData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to MoData.txt...");

    FinalMoisture = FinalTemperature + 10;
    myFile.println(FinalMoisture); // Save FinalTemperature on SD Card
    Serial.println(FinalMoisture);

    // close the file:
    myFile.close();
    Serial.println("Writing to MoData.txt Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening MoData.txt");
  }

  // Moisture Section END ------------------XXXXX----------------->







  // Conductivity Section START ----------------------------------->
  myFile = SD.open("CoData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to CoData.txt...");
    
    FinalConductivity = FinalTemperature + 20;
    myFile.println(FinalConductivity); // Save FinalTemperature on SD Card
    Serial.println(FinalConductivity);

    // close the file:
    myFile.close();
    Serial.println("Writing to CoData.txt Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening CoData.txt");
  }

  // Conductivity Section END ------------------XXXXX----------------->






  // FinalPH  Section START ----------------------------------->
  myFile = SD.open("PHData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to PHData.txt...");
    
    FinalPH  = FinalTemperature + 20;
    myFile.println(FinalPH); // Save FinalTemperature on SD Card
    Serial.println(FinalPH);

    // close the file:
    myFile.close();
    Serial.println("Writing to FinalPH Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalPH.txt");
  }

  // FinalPH Section END ------------------XXXXX----------------->





// FinalNitrogen  Section START ----------------------------------->
  myFile = SD.open("NiData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to NiData.txt...");
    
    FinalNitrogen  = FinalTemperature + 30;
    myFile.println(FinalNitrogen); // Save FinalTemperature on SD Card
    Serial.println(FinalNitrogen);

    // close the file:
    myFile.close();
    Serial.println("Writing to NiData Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening NiData.txt");
  }

  // FinalNitrogen Section END ------------------XXXXX----------------->





// FinalPhosphorus  Section START ----------------------------------->
  myFile = SD.open("PhoData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to PhoData.txt...");
    
    FinalPhosphorus  = FinalTemperature + 40;
    myFile.println(FinalPhosphorus); // Save FinalTemperature on SD Card
    Serial.println(FinalPhosphorus);

    // close the file:
    myFile.close();
    Serial.println("Writing to PhoData Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening PhoData.txt");
  }

  // FinalPhosphorus Section END ------------------XXXXX----------------->








  // FinalPotassium  Section START ----------------------------------->
  myFile = SD.open("PoData.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to PoData.txt...");
    
    FinalPotassium  = FinalTemperature + 50;
    myFile.println(FinalPotassium); // Save FinalTemperature on SD Card
    Serial.println(FinalPotassium);

    // close the file:
    myFile.close();
    Serial.println("Writing to PoData Done.");
  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening PoData.txt");
  }

  // FinalPotassium Section END ------------------XXXXX----------------->


  CurrentStatus = "SAMPLE TAKEN";
  TotalSampleData = 1;


 
}// Eend Sd_Card_Write_Data Function








void Sd_Card_Resul_Data(){


  // Make All Variable FinalTemperature Clean Before Calculation
  FinalTemperature = 0;
  FinalMoisture  = 0;
  FinalConductivity  = 0;
  FinalPH  = 0;
  FinalNitrogen  = 0;
  FinalPhosphorus    = 0;
  FinalPotassium   = 0;
  
  String buffer; // String to hold one line of text


  Serial.println("****Start Calculation*****");







  // FinalTemperature Data START ========================>>
  myFile = SD.open("TempData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalTemperature = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalTemperature); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TempData.txt..............");
  }


  // FinalTemperature Data END ========================>>










  // FinalMoisture Data START ========================>>
  myFile = SD.open("MoData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalMoisture  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalMoisture); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalMoisture.txt..............");
  }


  // FinalMoisture Data END ========================>>







  // FinalConductivity   Data START ========================>>
  myFile = SD.open("CoData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalConductivity  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalConductivity); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalConductivity.txt..............");
  }


  // FinalConductivity   Data END ========================>>








// FinalPH   Data START ========================>>
  myFile = SD.open("PHData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalPH  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalPH); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalPH.txt..............");
  }


  // FinalPH   Data END ========================>>







  // FinalNitrogen   Data START ========================>>
  myFile = SD.open("NiData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalNitrogen  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalNitrogen); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalPH.txt..............");
  }


  // FinalNitrogen   Data END ========================>>





// FinalPhosphorus    Data START ========================>>
  myFile = SD.open("PhoData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalPhosphorus  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalPhosphorus); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalPhosphorus.txt..............");
  }


  // FinalPhosphorus    Data END ========================>>








// FinalPotassium   Data START ========================>>
  myFile = SD.open("PoData.txt");// Open TEMP SAVE FinalTemperature FILE

  if (myFile) {

    int TempDataSum = 0;
    TotalSampleData = 0;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      buffer = myFile.readStringUntil('\n');

      TempDataSum = TempDataSum + buffer.toInt(); // Convert Buffer FinalTemperature str to int
      TotalSampleData = TotalSampleData + 1;
  
      //Serial.println(buffer);
      
      
    }// While end
    
    myFile.close();// close the file:
    
    FinalPotassium  = TempDataSum / TotalSampleData;
    Serial.print("The Final value is: ");
    Serial.println(FinalPotassium ); // Final Ans--------------

  } 
  
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening FinalPotassium.txt..............");
  }


  // FinalPotassium  Data END ========================>>



}// End Sd_Card_Resul_Data









void Sd_Card_Delete_Data(){

  SD.remove("TempData.txt");
  SD.remove("MoData.txt");
  SD.remove("CoData.txt");
  SD.remove("PHData.txt");
  SD.remove("NiData.txt");
  SD.remove("PhoData.txt");
  SD.remove("PoData.txt");

  Serial.println("All File Delete");


  // Male All None Value While Delete All FinalTemperature
  CurrentStatus = "DELETE ALL";
  TotalSampleData = 0;

  FinalTemperature = 0;
  FinalMoisture  = 0;
  FinalConductivity  = 0;
  FinalPH  = 0;
  FinalNitrogen  = 0;
  FinalPhosphorus = 0;
  FinalPotassium   = 0;



}// End Sd_Card_Delete_Data




void LCD_Skin_Data(){

  // Clean Full Skin
  mylcd.Fill_Screen(BLACK);

  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("SOIL TESTER", 30, 20);



  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(2); 
  mylcd.Print_String(String(CurrentStatus) + ": " + String(TotalSampleData), 75, 90);



  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(2);
  
  mylcd.Print_String("TEMPERATURE: " + String(FinalTemperature) , 20, 150);
  mylcd.Print_String("MOISTURE: " + String(FinalMoisture), 20, 200);
  mylcd.Print_String("CONDUCTIVITY: " + String(FinalConductivity), 20, 250);
  mylcd.Print_String("PH: " + String(FinalPH), 20, 300);
  mylcd.Print_String("NITROGEN: " + String(FinalNitrogen), 20, 350);
  mylcd.Print_String("PHOSPHORUS: " + String(FinalPhosphorus), 20, 400);
  mylcd.Print_String("POTASSIUM: " + String(FinalPotassium), 20, 450);


}

