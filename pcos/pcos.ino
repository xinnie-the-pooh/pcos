#define btm 300  //串口倍率
#if defined(__AVR_ATmega2560__)  //引脚数量
#define dpinsnum 53
#define apinsnum 15
#endif

#if  defined(__AVR_ATmega328P__)||defined(__AVR_ATmega168__) //
#define dpinsnum 13
#define apinsnum 7
#endif
#include <EEPROM.h>
String Str;
//byte mul_1 = 1;
//byte mul_2 = 2;
//byte at_flag = 0;
int sped = 9600; //defalut
/*byte count;*/
//int config = SERIAL_8N1;
byte ser0;//read
byte ser1;
byte ser2;
byte acmode;
/*int editmode;*/
void(* resetFunc) (void) = 0;
void setup(void)
{
	acmode = 0;
	//  editmode = 0;
	//0-20保留给状态
	ser0 = EEPROM.read(0);//
	ser1 = EEPROM.read(1);
	ser2 = EEPROM.read(2);
	if (ser0!=255) sped=btm *pow(2,ser0);//存储器非空装入波特率
	Serial.begin(sped);
	Serial.print("LOAD UART PROFILE DONE @"); Serial.println(sped);
	if(ser1!=255&&ser2!=255==1){//读取机器码 newflag
		ack();
		Serial.println(" : AC MODE ON");
		acmode = 1;
		for (byte p=0;p<=dpinsnum;p++)pinMode(p,EEPROM.read(p+20));//引脚配置方法 从20-100
	}
	else Serial.println("AC MODE FAILED");
	delay(1000);
}
void loop(void)
{
	nod(Str);
	if (Str != "") {
		Serial.print("INPUT->"); Serial.println(Str);//回显
		//未激活地址码可用命令:at模式:串口\地址\重启\展示\帮助,
		if (acmode == 0)at();
		if (acmode == 1)ins();
		help;//全局放在外边
	}
	/*	delay(100); // 延时 100 毫秒,这个时延在存在双状态周期时不需要*/
}
//有响应内部命令
//show
void shown(void){
	if ((byte)Str[3] == 'S' && (byte)Str[4] == 'H' && (byte)Str[5] == 'O' && (byte)Str[6] == 'W') {
		ack();
		Serial.print(ser0);Serial.print(";"); Serial.print(ser1);Serial.print(";"); Serial.print(ser2);Serial.println(";");
		/*	Serial.println("UART SPEED ; ADDR HIGH ; ADDR LOW");*/
	}
}
//rst
void rst(void) {
	if ((byte)Str[3] == 'R' && (byte)Str[4] == 'S' && (byte)Str[5] == 'T') {
		Serial.println("REBOOTING..");
		delay(100);
		resetFunc();
	}
}
//ac
void acn(void) {
	if ( (byte)Str[3] == 'A'  &&  (byte)Str[4] == 'C'&&(byte)Str[5] == '='&& (byte)Str[6] != ""&& (byte)Str[7] != ""&&ser1==255&&ser2==255) {
		EEPROM.write(1, unascii((byte)Str[6]));
		EEPROM.write(2, unascii((byte)Str[7]));
		Serial.print(unascii((byte)Str[6]));Serial.print(unascii((byte)Str[7])); Serial.println(" AC MODE ON");
		acmode = 1;
	}
}
//uart
void uart(void) {
	if ((byte)Str[3] == 'U' && (byte)Str[4] == 'A' && (byte)Str[5] == 'R' && (byte)Str[6] == 'T') {
		if ((byte)Str[7] == '=') {
			if ((byte)Str[8] != "") // sped = btm *pow(2,nm); //'0'=300,'1'=600 ,'2'=1200 '4'=2400
			Serial.print(btm *pow(2,unascii((byte)Str[8])));	Serial.println(" SETTING UART SPEED DONE");
			EEPROM.write(0, unascii((byte)Str[8]));
		}
		else   Serial.println(sped);
	}
}
//无响应内部命令
void ack(void){//统计响应次数及相应顺延
	if (ser1!=255&&ser2!=255)   {
		delay(ser1 * 100 + ser2 * 10);
		Serial.print(ser1);Serial.print(ser2);Serial.print(":");
	}
	else;
	
}
//d
void d(void) {//例子:25+D13E 25节点d13号输出高
	if ( (byte)Str[3] == 'D'  && (byte)Str[4] != ""&& (byte)Str[5]!= "" ) {
		if ((byte)Str[6]== 'E') digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),1);
		if ((byte)Str[6]== 'F')  digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),0);
		if ((byte)Str[6]== "R") {
			ack();
			Serial.println(digitalRead((unascii((byte)Str[4])*10+unascii((byte)Str[5]))));//这个有响应
		}
	}
}
//过程函数
byte ascii(byte pic) {return pic + 48;}
byte unascii(byte tok)	{return tok - 48;}
void nod(String& Str) {
	String tempStr = ""; // 声明变量 tempStr，用于临时存储串口输入的数据
	while (Serial.available())tempStr += (char)Serial.read();  // 当串口有数据时，循环执行 把读取的串口数据，逐个组合到inStr变量里
	Str = tempStr; // 把引用指针的变量赋值为 tempStr
}
//底层命令
void at(void) {//最底层的
	if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {
		if ((byte)Str[2] == '+') {
			shown();
			uart();
			rst();
			acn();
			help();
		}
		if ((byte)Str[2] == '?') {
			Serial.println("'AT+UART=[N]' IS UART SETTING TOOLS,NUMBER MEAN:300*2^N ");
			Serial.println("'AT+RST' IS REBOOT COMMAND ");
		}
	}
}
void ins(void) {//机器码+
	if ((byte)Str[0] == '?') ack();//轮询
	if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2)) {
		if ((byte)Str[2] == '+') {
			/*	ex();*/
			shown();
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
		if (acmode==0){
			Serial.print("COMMAND JUST LIKE: AT+[]");//at模式:串口\地址\重启\展示
			Serial.println("[]COULD BE:SHOW;SERIAL;AC;RST;");
		}
		if (acmode==1)
		Serial.println("[]? ; []+RST ; []+EXIT ; []+SHOW");
	}
}