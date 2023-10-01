void at(void) {
  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'T') {
    if ((byte)Str[2] == '+') {
      pps();
      uart();
      rst();
     }
     if ((byte)Str[2] == '?') {
      Serial.println("'AT+UART=[N]' IS UART SETTING TOOLS,NUMBER MEAN:300*2^N ");
      Serial.println("'AT+RST' IS REBOOT COMMAND ");
    }
  }
}

//void ac(void) {
//  if ((byte)Str[0] == 'A' && (byte)Str[1] == 'C') {
//    ask(1);
//    Serial.println("AC MODE ON");
//    acmode = 1;
//  }
//}



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
      uart();
      re();
    }
  }
}

void help(void) {
  if ((byte)Str[0] == 'H' && (byte)Str[1] == 'E' && (byte)Str[2] == 'L' && (byte)Str[3] == 'P')
  {
    //    if (acmode==0)
    Serial.println("AT+UART ; AT+RST ; []+AC ; ? ; AC");
    //    else
    Serial.println("[]? ; []+RST ; []+EXIT ; []+SHOW");
  }
}
