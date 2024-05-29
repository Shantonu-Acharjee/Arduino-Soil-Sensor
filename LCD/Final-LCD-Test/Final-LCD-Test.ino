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



void setup() 
{
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK); 
}


void loop(){

  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("SOIL TESTER", 30, 20);



  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String("TEMPERATURE: " +  String(40), 20, 100);
  mylcd.Print_String("MOISTURE: ", 20, 140);
  mylcd.Print_String("CONDUCTIVITY: ", 20, 180);
  mylcd.Print_String("PH: ", 20, 220);
  mylcd.Print_String("NITROGEN: ", 20, 260);
  mylcd.Print_String("POTASSIUM: ", 20, 300);

}
