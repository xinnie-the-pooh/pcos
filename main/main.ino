#define btm 300
#include <EEPROM.h>
String Str;
//byte mul_1 = 1;
//byte mul_2 = 2;
//byte at_flag = 0;
byte sped = 9600; //defalut
//int config = SERIAL_8N1;
byte ser0;//read
byte ser1;
byte ser2;
byte acmode;
//int editmode;
byte nm;//write
void(* resetFunc) (void) = 0;
void setup(void)
{
  acmode = 0;
//  editmode = 0;
 ser0 = EEPROM.read(0);
  ser1 = EEPROM.read(1);
  ser2 = EEPROM.read(2);
 Serial.begin(sped); 
 delay(1000);
  sp();
}

// Add the main program code into the continuous loop() function
void loop(void)
{
  nod(Str);
  if (Str != "") {
    Serial.print("INPUT->");
    Serial.println(Str);
    if (acmode == 0) {
      at();
      ac();
      ch();
      help();
    }
//  else// if (acmode == 1)
//    {
      ins();
//      help();
//    }
  }
  //herer= gose correct program
  delay(100); // 延时 100 毫秒
}
