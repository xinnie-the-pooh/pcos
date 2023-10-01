byte ascii(byte pic) {
  return pic + 48;
}

byte unascii(byte tok) {
  return tok - 48;
}

void ask(int detime) {
  if (detime == 1)     delay(ser1 * 100 + ser2 * 10);
    Serial.print(ser1);
    Serial.print(ser2);
}

void nod(String& Str) {
  String tempStr = ""; // 声明变量 tempStr，用于临时存储串口输入的数据
  while (Serial.available()) { // 当串口有数据时，循环执行
    tempStr += (char)Serial.read();  // 把读取的串口数据，逐个组合到inStr变量里
  }
  Str = tempStr; // 把引用指针的变量赋值为 tempStr
}

void sp(void) {
  Serial.println("");
  Serial.println("USE 'HELP' FOR MORE");
 
}
