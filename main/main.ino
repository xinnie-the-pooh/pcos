

// Define User Types below here or use a .h file
//

#include <EEPROM.h>
String Str;

// Define Function Prototypes that use User Types below here or use a .h file
//
int btm = 300;
int mul_1 = 1;
int mul_2 = 2;
int at_flag = 0;
int sped = 9600; //defalut
int config = SERIAL_8N1;
int ser0;
int ser1;
int ser2;
int acmode;
//int editmode;

void(* resetFunc) (void) = 0;

void setup(void)
{
  acmode = 0;
//  editmode = 0;
  ser1 = EEPROM.read(1);
  ser2 = EEPROM.read(2);
  //speed=EEPROM.read(0)*btm;

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
    }

       
  }
  delay(100); // 延时 100 毫秒
}
