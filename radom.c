int tmp[10];
unsigned long previousMillis = 0;       
const long interval = 1000;           

void sigema(){
 tmp[0]=random(0,10);
 while (oprate(1)) tmp[1]=random(0,10);
 while (oprate(2)) tmp[2]=random(0,10);
 while (oprate(3)) tmp[3]=random(0,10); 
 while (oprate(4)) tmp[4]=random(0,10); 
 while (oprate(5)) tmp[5]=random(0,10); 
 while (oprate(6)) tmp[6]=random(0,10); 
 while (oprate(7)) tmp[7]=random(0,10); 
 while (oprate(8)) tmp[8]=random(0,10); 
 while (oprate(9)) tmp[9]=random(0,10); 
 Serial.print(tmp[0]);
 Serial.print(tmp[1]);
 Serial.print(tmp[2]);
 Serial.print(tmp[3]);
 Serial.print(tmp[4]);
 Serial.print(tmp[5]);
 Serial.print(tmp[6]);
 Serial.print(tmp[7]);
 Serial.print(tmp[8]);
 Serial.println(tmp[9]);
}


void loop() {
unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sigema();
  }
}
int oprate(int numb){
  for(int i=numb-1;i<0;i--){
    if (tmp[numb]==tmp[i])return 1;
    else return 0;
  }
}
