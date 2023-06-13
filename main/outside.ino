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
    else Serial.println("AT> COMMAND FORMAT ERROR: INSERT 'AT?' TO LEARN MORE");
  }
}


void ac() {
  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {
    Serial.println("AC MODE ON");
    ask(1);
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
