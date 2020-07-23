#include <Arduino.h>

void setup() 
{
	Serial.begin(230400);
}


int a,b;



bool A_down=false;
bool A_up =false;

void loop() 
{
	// a = analogRead(0);
	// b = analogRead(1);

	char buf[24];

	// Schmitt(&A_down, b, 250, 60);
	// Schmitt(&A_up, b, 800, 950);

	sprintf(buf, "%u,\t%u\t\t%u\t%u", a, b, A_down, A_up);
	Serial.println(buf);

	delay(20);
}