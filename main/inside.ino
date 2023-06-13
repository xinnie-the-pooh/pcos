void ins(void){
if ((byte)Str[0] == '?') {
        ask(1);
      }
      if ((byte)Str[0] == ascii(ser1) && (byte)Str[1] == ascii(ser2)) {


        if ((byte)Str[2] == '?') {
          ask(0);
          Serial.println(" STAND BY");
        }

        if ((byte)Str[2] == '+') {
          if ((byte)Str[3] == 'E' && (byte)Str[4] == 'X' && (byte)Str[5] == 'I' && (byte)Str[6] == 'T') {
            ask(0);
            Serial.println(" AC MODE OFF,AT MODE ON");
            acmode = 0;

          }
        }


      }
}
