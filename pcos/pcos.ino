#define btm 300  //���ڱ���
#if defined(__AVR_ATmega2560__)  //��������
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
	//0-20������״̬
	ser0 = EEPROM.read(0);//
	ser1 = EEPROM.read(1);
	ser2 = EEPROM.read(2);
	if (ser0!=255) sped=btm *pow(2,ser0);//�洢���ǿ�װ�벨����
	Serial.begin(sped);
	Serial.print("LOAD UART PROFILE DONE @"); Serial.println(sped);
	if(ser1!=255&&ser2!=255==1){//��ȡ������ newflag
		ack();
		Serial.println(" : AC MODE ON");
		acmode = 1;
		for (byte p=0;p<=dpinsnum;p++)pinMode(p,EEPROM.read(p+20));//�������÷��� ��20-100
	}
	else Serial.println("AC MODE FAILED");
	delay(1000);
}
void loop(void)
{
	nod(Str);
	if (Str != "") {
		Serial.print("INPUT->"); Serial.println(Str);//����
		//δ�����ַ���������:atģʽ:����\��ַ\����\չʾ\����,
		if (acmode == 0)at();
		if (acmode == 1)ins();
		help;//ȫ�ַ������
	}
	/*	delay(100); // ��ʱ 100 ����,���ʱ���ڴ���˫״̬����ʱ����Ҫ*/
}
//����Ӧ�ڲ�����
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
//����Ӧ�ڲ�����
void ack(void){//ͳ����Ӧ��������Ӧ˳��
	if (ser1!=255&&ser2!=255)   {
		delay(ser1 * 100 + ser2 * 10);
		Serial.print(ser1);Serial.print(ser2);Serial.print(":");
	}
	else;
	
}
//d
void d(void) {//����:25+D13E 25�ڵ�d13�������
	if ( (byte)Str[3] == 'D'  && (byte)Str[4] != ""&& (byte)Str[5]!= "" ) {
		if ((byte)Str[6]== 'E') digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),1);
		if ((byte)Str[6]== 'F')  digitalWrite((unascii((byte)Str[4])*10+unascii((byte)Str[5])),0);
		if ((byte)Str[6]== "R") {
			ack();
			Serial.println(digitalRead((unascii((byte)Str[4])*10+unascii((byte)Str[5]))));//�������Ӧ
		}
	}
}
//���̺���
byte ascii(byte pic) {return pic + 48;}
byte unascii(byte tok)	{return tok - 48;}
void nod(String& Str) {
	String tempStr = ""; // �������� tempStr��������ʱ�洢�������������
	while (Serial.available())tempStr += (char)Serial.read();  // ������������ʱ��ѭ��ִ�� �Ѷ�ȡ�Ĵ������ݣ������ϵ�inStr������
	Str = tempStr; // ������ָ��ı�����ֵΪ tempStr
}
//�ײ�����
void at(void) {//��ײ��
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
void ins(void) {//������+
	if ((byte)Str[0] == '?') ack();//��ѯ
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
			Serial.print("COMMAND JUST LIKE: AT+[]");//atģʽ:����\��ַ\����\չʾ
			Serial.println("[]COULD BE:SHOW;SERIAL;AC;RST;");
		}
		if (acmode==1)
		Serial.println("[]? ; []+RST ; []+EXIT ; []+SHOW");
	}
}