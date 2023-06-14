#define btm 300
#include <EEPROM.h>
String Str;
int mul_1 = 1;
int mul_2 = 2;
int at_flag = 0;
int sped = 9600; //defalut
int config = SERIAL_8N1;
int ser0;//read
int ser1;
int ser2;
int acmode;
//int editmode;
int nm;//write
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
    else if (acmode == 1)
    {
      ins();
//      help();
    }

       
  }
  delay(100); // 延时 100 毫秒
}
