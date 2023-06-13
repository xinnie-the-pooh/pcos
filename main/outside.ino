void at(void) {
  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {
    if ((byte)Str[2] == '+') {
      uart();
      rst();
    }

    else if ((byte)Str[2] == '?') {
      Serial.println("AT>HELP> 'AT+UART=[N]' IS UART SETTING TOOLS,NUMBER MEAN:300*2^N ");
      Serial.println("AT>HELP> 'AT+RST' IS REBOOT COMMAND ");
    }
  }
}


void ac(void) {
  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {

    
    
    ask(1);
    Serial.println("AC MODE ON");
    acmode = 1;


  }

}


void ch(void) {
if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2) &&(byte)Str[2] == '+'  &&(byte)Str[3] == 'A'  &&  (byte)Str[4] == 'C') {
ask(0);
Serial.println("AC MODE ON");
 acmode = 1;
}

}


void ins(void) {
  if ((byte)Str[0] == '?') {
    ask(1);
  }
  
  if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2)) {


    if ((byte)Str[2] == '?') {
      ask(0);
      Serial.println(" STAND BY");
    }


    if ((byte)Str[2] == '+') {
      ex();
      pps();
      rst();
    }


  }
}
void help(void) {
  if ((byte)Str[0] == 'H' && (byte)Str[1] == 'E' && (byte)Str[2] == 'L' && (byte)Str[3] == 'P')
  {
    Serial.println("HELP> NOT READY YET ");
  }
}
