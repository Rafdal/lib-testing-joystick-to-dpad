#include <Arduino.h>
// #include <Pot2Btn.h>

#include <Joystick2Pad.h>
Joystick2Pad pad(0,1);

#define PRINT(Str) Serial.println(F(Str));
#ifndef PRINT
#define PRINT(Str)
#endif

void setup() 
{
	Serial.begin(230400);

	// ! UP
	pad.up.onClick([](){
		PRINT("Click")
	});
	pad.up.onRelease([](){
		PRINT("Release")
	});
	pad.up.onLongPress([](){
		PRINT("Long Press")
	});
	pad.up.whileLongPress([](){
		PRINT("During Long Press")
	}, 150);

}

void loop() 
{
	pad.read();
}