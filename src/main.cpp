#include <Arduino.h>
// #include <Pot2Btn.h>

#include <Joystick2Pad.h>
Joystick2Pad pad(0,1);

int count_x, count_y;

void print()
{
	int X = analogRead(0);
	int Y = analogRead(1);

	char buf[28];
	sprintf(buf, "X:%i\tY:%i", 
		count_x,
		count_y
	);
	/* sprintf(buf, "%u\t%u\t%u,%u\t%u,%u\tX:%i\tY:%i", 
		X, 
		Y, 
		pad.down._state, 
		pad.up._state, 
		pad.left._state, 
		pad.right._state, 
		count_x,
		count_y
	); */
	Serial.println(buf);
}

void setup() 
{
	Serial.begin(230400);


	pad.up.onRelease([](){
		count_y++;
		print();
	});
	pad.up.whileLongPress([](){
		count_y++;
		print();
	}, 150);

	pad.down.onRelease([](){
		count_y--;
		print();
	});
	pad.down.whileLongPress([](){
		count_y--;
		print();
	}, 150);

	pad.left.onRelease([](){
		count_x--;
		print();
	});

	pad.right.onRelease([](){
		count_x++;
		print();
	});
}

void loop() 
{
	pad.read();
}