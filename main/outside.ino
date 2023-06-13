void at(void){
if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {
  if ((byte)Str[2] == '+') {
    if ((byte)Str[3] == 'U' && (byte)Str[4] == 'A' && (byte)Str[5] == 'R' && (byte)Str[6] == 'T') {
      if ((byte)Str[7] == '=') {
       
        if ((byte)Str[8] != "") {
          speed = btm*sqrt(ascii((byte)Str[8]));//'0'=0,'1'=btm ,'2'=4btm '4'=16btm
        }
        
        Serial.println("SETTING UART SPEED DONE");
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


}
void ac(){

if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {
  Serial.println("AC MODE ON");
  ask(1);
  acmode = 1;


}

}

void help(void){
 if ((byte)Str[0] == 'H' && (byte)Str[1] == 'E' && (byte)Str[2] == 'L' && (byte)Str[3] == 'P')
{
  Serial.println("HELP> NOT READY YET ");
}
}
