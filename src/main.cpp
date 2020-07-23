#include <Arduino.h>
// #include <Pot2Btn.h>

#include <Joystick2Pad.h>
Joystick2Pad pad(0,1);

int count_x, count_y;


void setup() 
{
	Serial.begin(230400);

	pad.up.onClick([](){
		Serial.println(F("CLICK UP"));
		count_y++;
	});

	pad.down.onClick([](){
		Serial.println(F("CLICK DOWN"));
		count_y--;
	});

	pad.left.onClick([](){
		Serial.println(F("CLICK LEFT"));
		count_x--;
	});

	pad.right.onClick([](){
		Serial.println(F("CLICK RIGHT"));
		count_x++;
	});
}


int a,b;



bool A_down=false;
bool A_up =false;

void loop() 
{
	pad.read();
	int X = analogRead(0);
	int Y = analogRead(1);

	char buf[24];

	// Schmitt(&A_down, b, 250, 60);
	// Schmitt(&A_up, b, 800, 950);

	sprintf(buf, "%u\t%u\t%u,%u\t%u,%u\tX:%i\tY:%i", 
		X, 
		Y, 
		pad.down._state, 
		pad.up._state, 
		pad.left._state, 
		pad.right._state, 
		count_x,
		count_y
	);
	Serial.println(buf);

	// delay(20);
}