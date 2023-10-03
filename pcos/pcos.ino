#define btm 300
#include <EEPROM.h>
String Str;
//byte mul_1 = 1;
//byte mul_2 = 2;
//byte at_flag = 0;
int sped = 9600; //defalut
byte count;
//int config = SERIAL_8N1;
byte ser0;//read
byte ser1;
byte ser2;
byte newflag;
byte acmode;
/*int editmode;*/
byte nm;//write
void(* resetFunc) (void) = 0;
void setup(void)
{
	acmode = 0;
	//  editmode = 0;
	ser0 = EEPROM.read(0);
	ser1 = EEPROM.read(1);
	ser2 = EEPROM.read(2);
	
	if (ser0!=255) sped=btm *pow(2,ser0);//存储器非空装入波特率
	Serial.begin(sped);
	Serial.print("LOAD UART PROFILE DONE @"); Serial.println(sped);
	if (ser1!=255&&ser2!=255)newflag=1;
	if(newflag==1){
	ack();
	Serial.print(ser1);Serial.print(ser2);
	Serial.println(" : AC MODE ON");
	acmode = 1;
	}
	
	else Serial.println("AC MODE FAILED");
	delay(1000);



	pinMode(13,1);
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
			//      ac();
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
//有响应内部命令

//show
void pps(void){
	if ((byte)Str[3] == 'S' && (byte)Str[4] == 'H' && (byte)Str[5] == 'O' && (byte)Str[6] == 'W') {
		
		Serial.print(ser0);Serial.print(";"); Serial.print(ser1);Serial.print(";"); Serial.print(ser2);Serial.println(";");
		Serial.println("UART SPEED ; ADDR HIGH ; ADDR LOW");
		
	}
}


// 	void ex(void){
//
// 		if ((byte)Str[3] == 'E' && (byte)Str[4] == 'X' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
// 			ask(0);
// 			//        if (editmode==0){
// 			acmode = 0;
// 			Serial.println("AC MODE OFF");
// 			//        }
// 			//        if (editmode==1){
// 			//        editmode = 0;
// 			//        Serial.println(" EDIT MODE QUIT");
// 			//      }
// 			//  if ((byte)Str[3] == 'E' && (byte)Str[4] == 'D' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
// 			//        ask(0);
// 			//        Serial.println(" EDITING GOES");
// 			//       editmode=1;
// 			//
// 			//      }
// 		}
// 	}
// }

//rst
void rst(void) {
	if ((byte)Str[3] == 'R' && (byte)Str[4] == 'S' && (byte)Str[5] == 'T') {
		Serial.println("REBOOTING..");
		delay(100);
		resetFunc();
	}
}

// void re(void){
// 	if ((byte)Str[3] == 'R' && (byte)Str[4] == 'E') {
// 		ser0 = EEPROM.read(0);
// 		ser1 = EEPROM.read(1);
// 		ser2 = EEPROM.read(2);
// 		Serial.println("RELOAD DONE");
// 	}
// }

//ac
void ch(void) {
	if ( (byte)Str[3] == 'A'  &&  (byte)Str[4] == 'C'&&(byte)Str[5] == '='&& (byte)Str[6] != ""&& (byte)Str[7] != ""&&ser1==255&&ser2==255) {
		
		int p1=unascii((byte)Str[6]);
		EEPROM.write(1, p1);
		int  p2=unascii((byte)Str[7]);
		EEPROM.write(2, p2);
		Serial.print(p1);Serial.print(p2); Serial.println(" AC MODE ON");
		acmode = 1;
		
	}
}
//uart
void uart(void) {
	if ((byte)Str[3] == 'U' && (byte)Str[4] == 'A' && (byte)Str[5] == 'R' && (byte)Str[6] == 'T') {
		if ((byte)Str[7] == '=') {
			if ((byte)Str[8] != "") {
				nm=unascii((byte)Str[8]);
				// sped = btm *pow(2,nm); //'0'=300,'1'=600 ,'2'=1200 '4'=2400
			}
			Serial.print(btm *pow(2,nm));
			Serial.println(" SETTING UART SPEED DONE");
			EEPROM.write(0, nm);
		}



		else         Serial.println(sped);
		
	}
}
//无响应内部命令
void ack(void){//统计响应次数及相应顺延
if (newflag == 1)   {  
	delay(ser1 * 100 + ser2 * 10);
	Serial.print(ser1);Serial.print(ser2);
	count++;
	}
else{
	
}
}
//d
void d(void) {//例子:25+D13E 25节点d13号输出高
	if ( (byte)Str[3] == 'D'  && (byte)Str[4] != ""&& (byte)Str[5]!= "" ) {
		if ((byte)Str[6]== 'E')  {
			digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),1);

		}
		if ((byte)Str[6]== 'F')  {
			digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),0);
		}
		
		if ((byte)Str[6]== "R") {
			ack();
			Serial.println(digitalRead((unascii((byte)Str[4])*10+unascii((byte)Str[5]))));
			
		}
		}
}
		
		
		//过程函数
		byte ascii(byte pic) {
			return pic + 48;
		}

		byte unascii(byte tok) {
			return tok - 48;
		}

// 		void ask(int detime) {
// 			if (detime == 1)     delay(ser1 * 100 + ser2 * 10);
// 			Serial.print(ser1);
// 			Serial.print(ser2);
// 		}

		void nod(String& Str) {
			String tempStr = ""; // 声明变量 tempStr，用于临时存储串口输入的数据
			while (Serial.available()) { // 当串口有数据时，循环执行
				tempStr += (char)Serial.read();  // 把读取的串口数据，逐个组合到inStr变量里
			}
			Str = tempStr; // 把引用指针的变量赋值为 tempStr
		}

		// 		void sp(void) {
		// 			Serial.println("");
		// 			Serial.println("USE 'HELP' FOR MORE");
		//
		// 		}
		
		
		
		
		//底层命令
		
		
		
		void at(void) {
			if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {
				if ((byte)Str[2] == '+') {
					pps();
					uart();
					rst();
				}
				if ((byte)Str[2] == '?') {
					Serial.println("'AT+UART=[N]' IS UART SETTING TOOLS,NUMBER MEAN:300*2^N ");
					Serial.println("'AT+RST' IS REBOOT COMMAND ");
				}
			}
		}

		//void ac(void) {
		//  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {
		//    ask(1);
		//    Serial.println("AC MODE ON");
		//    acmode = 1;
		//  }
		//}



		void ins(void) {
			if ((byte)Str[0] == '?') {
				/*ask(1);*/
			}
			if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2)) {
				if ((byte)Str[2] == '?') {
					ack();
					Serial.println(" STAND BY");
				}
				if ((byte)Str[2] == '+') {
				/*	ex();*/
					pps();
					rst();
					uart();
				/*	re();*/
					d();
				}
			}
		}

		void help(void) {
			if ((byte)Str[0] == 'H' && (byte)Str[1] == 'E' && (byte)Str[2] == 'L' && (byte)Str[3] == 'P')
			{
				//    if (acmode==0)
				Serial.println("AT+UART ; AT+RST ; []+AC ; ? ; AC");
				//    else
				Serial.println("[]? ; []+RST ; []+EXIT ; []+SHOW");
			}
		}