//d0，d1为串口，保留
//数字脚定义
int motorh=2;
int motorl=3;
int motoren=4;
int off1=7;
int off2=6;
int realypin=5;
//模拟脚定义
int readpin=0;
int rp1=1;
int rp2=2;
//变量设置，注意引用次序
int normal=0;
int c=5;
int lowset=normal-c;
int highset=normal+c;



void setup(void) {
  // put your setup code here, to run once:
//Serial.begin(9600); //保留句
pinMode(motorh,OUTPUT);
pinMode(motorl,OUTPUT);
pinMode(motoren,OUTPUT);
pinMode(off1,INPUT_PULLUP);
pinMode(off2,INPUT_PULLUP);
realy(0);
}

void loop() {
  // put your main code here, to run repeatedly:
 normal= map(analogRead(rp1),0,1024,0,250);
 c= map(analogRead(rp2),0,1024,0,10);
if( readvolts()>lowset&&readvolts()<highset){
  realy(1);
  digitalWrite(motoren,LOW);
   
}
else {
  
  control();
}
}
//int readvolts()
//{
//  int now=normal;
//  now=map( analogRead(readpin),0,1023,0,300);
//  return now;
//  }
 void realy(int value)
  {
    digitalWrite(realypin,value);
    
  }
//  void oprate(int state){
//    if(state==1){
//       
//    }
//    if(state==1){
//      motor(1);
//      }
//    
//  }
 void control(){
   if (readvolts()>normal){
    motor(0);
   }
  else if (readvolts()<normal){
    motor(1);
   }
   else{
    motor(2);
   }
//    else {
//     digitalWrite(motoren,LOW);
//   }
 }
void motor(int value){
  if(value==1&&off1==1){
   digitalWrite(motorh,HIGH);   
   digitalWrite(motorl,LOW);
   digitalWrite(motoren,HIGH);
  }
  if(value==0&&off2==1){
     digitalWrite(motorh,LOW);   
   digitalWrite(motorl,HIGH);
   digitalWrite(motoren,HIGH);
  }
  else{
       digitalWrite(motorh,LOW);   
   digitalWrite(motorl,LOW);
   digitalWrite(motoren,LOW);
  }
}
int readvolts(){
  return map(analogRead(readpin),0,1023,0,300);
}
