#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int tmp0;
int tmp1;
int tmp2;
int tmp3;
int tmp4;
int tmp5;
int tmp6;
int tmp7;
int tmp8;
int tmp9;
int startFlag;
unsigned long previousMillis = 0;       
const long interval = 30000;   //half minute pass,numchange 
void random_setup() {
  // put your setup code here, to run once:
 lcd.begin();
pinMode(22,INPUT_PULLUP);//0
pinMode(23,INPUT_PULLUP);//1
pinMode(24,INPUT_PULLUP);
pinMode(25,INPUT_PULLUP);
pinMode(26,INPUT_PULLUP);
pinMode(27,INPUT_PULLUP);
pinMode(28,INPUT_PULLUP);
pinMode(29,INPUT_PULLUP);
pinMode(30,INPUT_PULLUP);//8
pinMode(31,INPUT_PULLUP);//9
pinMode(32,INPUT_PULLUP);//.
Serial.begin(9600);
}

void random_loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(32)==0) startFlag=1;//point 2 begin
  if(startFlag>0){
  lcd.backlight();
  if (digitalRead(tmp0+22)==0) startFlag==2;//first secret num bit(0)
  if (digitalRead(tmp1+22)==0&&startFlag==2) startFlag=3;
  if (digitalRead(tmp2+22)==0&&startFlag==3) startFlag=4;
  if (digitalRead(tmp3+22)==0&&startFlag==4) startFlag=-1;
}
if (startFlag==-1){
  lcd.noBacklight();
  lcd.setCursor(0, 0);
  lcd.print(tmp0);
  lcd.setCursor(0, 2);
  lcd.print(tmp1);
  lcd.setCursor(0, 4);
  lcd.print(tmp2);
  lcd.setCursor(0, 6);
  lcd.print(tmp3);
  lcd.setCursor(0, 8);
  lcd.print(tmp4);
  lcd.setCursor(1, 0);
  lcd.print(tmp5);
  lcd.setCursor(1, 2);
  lcd.print(tmp6);
  lcd.setCursor(1, 4);
  lcd.print(tmp7);
  lcd.setCursor(1, 6);
  lcd.print(tmp8);
  lcd.setCursor(1, 8);
  lcd.print(tmp9);
  startFlag=0;
}

unsigned long currentMillis = millis();//always active a proscess to change num
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sigema();
  }
}

void sigema(){
 tmp0=random(0,10);
 while (tmp1==tmp0) tmp1=random(0,10);
 while (tmp2==tmp1||tmp2==tmp0) tmp2=random(0,10);
 while (tmp3==tmp2||tmp3==tmp1||tmp3==tmp0) tmp3=random(0,10); 
 while (tmp4==tmp3||tmp4==tmp2||tmp4==tmp1||tmp4==tmp0) tmp4=random(0,10); 
 while (tmp5==tmp4||tmp5==tmp3||tmp5==tmp2||tmp5==tmp1||tmp5==tmp0) tmp5=random(0,10); 
 while (tmp6==tmp5||tmp6==tmp4||tmp6==tmp3||tmp6==tmp2||tmp6==tmp1||tmp6==tmp0) tmp6=random(0,10); 
 while (tmp7==tmp6||tmp7==tmp5||tmp7==tmp4||tmp7==tmp3||tmp7==tmp2||tmp7==tmp1||tmp7==tmp0) tmp7=random(0,10); 
 while (tmp8==tmp7||tmp8==tmp6||tmp8==tmp5||tmp8==tmp4||tmp8==tmp3||tmp8==tmp2||tmp8==tmp1||tmp8==tmp0) tmp8=random(0,10); 
 while (tmp9==tmp8||tmp9==tmp7||tmp9==tmp6||tmp9==tmp5||tmp9==tmp4||tmp9==tmp3||tmp9==tmp2||tmp9==tmp1||tmp9==tmp0) tmp9=random(0,10); 
 Serial.print(tmp0);
 Serial.print(tmp1);
 Serial.print(tmp2);
 Serial.print(tmp3);
 Serial.print(tmp4);
 Serial.print(tmp5);
 Serial.print(tmp6);
 Serial.print(tmp7);
 Serial.print(tmp8);
 Serial.println(tmp9);
}
