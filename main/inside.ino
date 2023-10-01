//void edit(void){
//  
//}
void pps(){
   if ((byte)Str[3] == 'S' && (byte)Str[4] == 'H' && (byte)Str[5] == 'O' && (byte)Str[6] == 'W') {
     Serial.print(ser0);Serial.print(";"); Serial.print(ser1);Serial.print(";"); Serial.print(ser2);Serial.println(";");
     Serial.println("UART SPEED ; ADDR HIGH ; ADDR LOW"); 
   }
}
void ex(void){
  
  if ((byte)Str[3] == 'E' && (byte)Str[4] == 'X' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
        ask(0);
//        if (editmode==0){
        acmode = 0;
        Serial.println("AC MODE OFF");
//        }
//        if (editmode==1){
//        editmode = 0;
//        Serial.println(" EDIT MODE QUIT");
//      }
//  if ((byte)Str[3] == 'E' && (byte)Str[4] == 'D' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
//        ask(0);
//        Serial.println(" EDITING GOES");
//       editmode=1;
//
//      }
}
}

void rst(void) {
  if ((byte)Str[3] == 'R' && (byte)Str[4] == 'S' && (byte)Str[5] == 'T') {
    Serial.println("REBOOTING..");
    delay(100);
    resetFunc();
  }
}

void re(void){
   if ((byte)Str[3] == 'R' && (byte)Str[4] == 'E') {
 ser0 = EEPROM.read(0);
  ser1 = EEPROM.read(1);
  ser2 = EEPROM.read(2);
  Serial.println("RELOAD DONE");
   }
}
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
