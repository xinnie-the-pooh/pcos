// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       eeprom_writer.ino
    Created:	2023/10/3 13:46:40
    Author:     WIN-E5HO8I21AS1\Administrator
*/



#define space 200
#include <EEPROM.h>

//修改这里来更改配置
byte eep[space]=
{5,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	//serialspeed;machine address high bit;machine address low bit
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	//20.digital pin mode begin	
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0    //80.digital pin mode end
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0    
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0    //100.digital status begin	
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	//160.digital status end	
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	//reserve
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
// The setup() function runs once each time the micro-controller starts
void setup()
{


}

// Add the main program code into the continuous loop() function
void loop()
{
for (int p=0;p<=space;p++)
{
	EEPROM.write(p,eep[p]);//配置方法 
}

}
