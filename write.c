#include <EEPROM.h>
void setup() {

}

void loop() {
EEPROM.write(0,5);
EEPROM.write(1,5);
EEPROM.write(2,9);
}
