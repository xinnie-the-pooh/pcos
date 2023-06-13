void edit(void){
  
}
void pps(){
   if ((byte)Str[3] == 'S' && (byte)Str[4] == 'H' && (byte)Str[5] == 'O' && (byte)Str[6] == 'W') {

     Serial.print(ser0);
     Serial.print(ser1);
    Serial.print(ser1);
     Serial.println("");
   
      Serial.println("UART SPEED ; ADDR HIGH ; ADDR LOW");
    
   }
   
}
void ex(void){
  
  if ((byte)Str[3] == 'E' && (byte)Str[4] == 'X' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
        ask(0);
        
//        if (editmode==0){
        acmode = 0;
        Serial.println(" AC MODE OFF,AT MODE ON");
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
    Serial.println("AT> REBOOTING..");
    delay(100);
    resetFunc();
  }
}

void uart(void) {
  if ((byte)Str[3] == 'U' && (byte)Str[4] == 'A' && (byte)Str[5] == 'R' && (byte)Str[6] == 'T') {
    if ((byte)Str[7] == '=') {

      if ((byte)Str[8] != "") {
        sped = btm * sqrt(ascii((byte)Str[8])); //'0'=0,'1'=btm ,'2'=4btm '4'=16btm
      }

      Serial.println("SETTING UART SPEED DONE");
      EEPROM.write(0, sped / btm);
    }



    else if ((byte)Str[7] != ""){
         Serial.println(sped);
    }

  }
}
