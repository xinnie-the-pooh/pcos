

// Define User Types below here or use a .h file
//

#include <EEPROM.h>
String Str;
void(* resetFunc) (void) = 0;
// Define Function Prototypes that use User Types below here or use a .h file
//
int btm = 300;
int mul_1 = 1;
int mul_2 = 2;
int at_flag = 0;
int speed = 9600; //defalut
int config = SERIAL_8N1;
int ser1;
int ser2;
int acmode;
// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup(void)
{
  acmode=0;
  ser1 = EEPROM.read(1);
  ser2 = EEPROM.read(2);
  //speed=EEPROM.read(0)*btm;

  Serial.begin(speed);
  delay(1000);
  Serial.println("");
  Serial.println("AT COMMAND PROMPT V1.3");
  Serial.println(speed);
  Serial.println("LOAD UART PROFILE FINISHED");
}

// Add the main program code into the continuous loop() function
void loop(void)
{

  nod(Str);
  if (Str != "") {
    Serial.print(">");
    Serial.println(Str);


atmode:
    if (acmode == 0) {
      if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {

        if ((byte)Str[2] == '+') {
          if ((byte)Str[3] == 'U' && (byte)Str[4] == 'A' && (byte)Str[5] == 'R' && (byte)Str[6] == 'T') {
            if ((byte)Str[7] == '=') {
              switch ((byte)Str[8])
              {
                case '0':
                  speed = btm;
                  break;
                case '1':
                  speed = btm * 2;
                  break;
                case '2':
                  speed = btm * 4;
                  break;
                case '3':
                  speed = btm * 8;
                  break;
                case '4':
                  speed = btm * 16;
                  break;
                case '5':
                  speed = btm * 32;
                  break;
                case '6':
                  speed = btm * 64;
                  break;
                case '7':
                  speed = btm * 96;
                  break;
                case '8':
                  speed = btm * 128;
                  break;
                case '9':
                  speed = btm * 192;
                  break;
                case 'A':
                  speed = btm * 192;
                  break;
                case 'B':
                  speed = btm * 384;
                  break;

              }
              Serial.println("SETTING UART SPEED");
              EEPROM.write(0, speed / btm);


            }



            else {
              //   speed=EEPROM.read(0);
              Serial.println(speed);
            }

          }
          else if ((byte)Str[3] == 'R' && (byte)Str[4] == 'S' && (byte)Str[5] == 'T') {
            Serial.println("AT> REBOOTING..");
            delay(100);
            resetFunc();
          }

          else Serial.println("AT> ACCESS DENIED");

        }
        else if ((byte)Str[2] == '?') {
          Serial.println("AT>HELP> 'AT+UART=[N]' IS UART SETTING TOOLS,NUMBER MEAN:300*2^N ");

          Serial.println("AT>HELP> 'AT+RST' IS REBOOT COMMAND ");



        }
        else Serial.println("AT> COMMAND FORMAT ERROR: INSERT 'AT?' TO LEARN MORE");
      }
      if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {
        Serial.println("AC MODE ON");
        ask(1);
        acmode = 1;


      }


      else if ((byte)Str[0] == 'H' && (byte)Str[1] == 'E' && (byte)Str[2] == 'L' && (byte)Str[3] == 'P')
      {
        Serial.println("HELP> NOT READY YET ");
      }
    }
    //   else Serial.println(">ERROR COMMAND NAME, INSERT 'HELP' TO LEARN MORE");

    if (acmode == 1)
    {
       if ((byte)Str[0] == '?') {
        ask(1);
       }
      if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2)) {


        if ((byte)Str[2] == '?') {
          ask(0);
          Serial.println(" STAND BY");
        }

         if ((byte)Str[2] == '+') {
           if ((byte)Str[3] == 'E'&&(byte)Str[4] == 'X'&&(byte)Str[5] == 'I'&&(byte)Str[6] == 'T') {
          ask(0);
         Serial.println(" AC MODE OFF,AT MODE ON");
        acmode = 0;
     
        }
         }


      }

      
      
      }



  }
  delay(100); // 延时 100 毫秒
}



void ask(int detime){
  if (detime==1){
    delay(ser1 * 100 + ser2 * 10);
        Serial.print(ser1);
        Serial.println(ser2);
    }
    else{Serial.print(ser1);
          Serial.print(ser2);
    
    }
}

void nod(String& Str) {
  String tempStr = ""; // 声明变量 tempStr，用于临时存储串口输入的数据
  while (Serial.available()) { // 当串口有数据时，循环执行
    tempStr += (char)Serial.read();  // 把读取的串口数据，逐个组合到inStr变量里
  }
  Str = tempStr; // 把引用指针的变量赋值为 tempStr
}
