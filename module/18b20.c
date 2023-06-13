//i use the uno board that i only have,so this program is run on uno.
//
//#include <EEPROM.h>
////////////////////////////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
int ds18b20 = 2;
OneWire onew(ds18b20);
DallasTemperature sensor(&onew);
////////////////////////////////////////////////
int address_up = 1; //zero  unused,command and adress
int address_down = 2;

int test_pin = 13;
int write_value = 0; //i dont want it run at begin when error
int now_value;
int set_value = 0;
int shift_time = 500;
byte record_value_up;//its a shift number
byte record_value_down;
//better in martix
int control_time = 0; //record as second
int last_time;
int now_time;
int set_n;
int address_n;
void 18b20_setup() {

  Serial.begin(9600);

  sensor.begin();

  //record_value_up = EEPROM.read(address_up);//this step for preread,let temp begin with memory number;
  //record_value_down=EEPROM.read(address_down);
  //


}

void 18b20_loop() {


  for (; control_time = 0;) {

    Serial.println(address_up);//print command for ask
    delay(1);//wait for anser
    record_value_up = Serial.read(); //read anser

    Serial.println(address_down);
    delay(1);
    record_value_down = Serial.read();

    Serial.println(address_n);
    delay(1);
    set_n = Serial.read();

    Serial.println(3);//ask for next time step ,ready
    delay(1);
    control_time = Serial.read();
  }

  for (last_time = millis () ; now_time < last_time + control_time ; now_time = millis() ) { //a time loop
    //heat
    for (sensor.requestTemperatures() ; (sensor.getTempCByIndex(0) < set_value + record_value_up ) || (write_value > 254);/* write_value ++*/write_value + (set_value - now_value)*set_n) { //ues this let output between 0-255 and set a corect value quickly,and in*is a pid
      for (last_time = millis () ; now_time < last_time + shift_time ; now_time = millis() ) //run in small time
        analogWrite(test_pin, write_value);
    }
    //cold
    for (sensor.requestTemperatures() ; (sensor.getTempCByIndex(0) > set_value + record_value_down ) || (write_value < 1); /*write_value --*/write_value - (set_value - now_value)*set_n) {
      for (last_time = millis () ; now_time < last_time + shift_time ; now_time = millis() )
        analogWrite(test_pin, write_value);
    }

  }
  control_time = 0; //the end for step loop

}
