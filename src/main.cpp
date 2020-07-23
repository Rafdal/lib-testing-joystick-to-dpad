#include <Arduino.h>

void setup() {
	Serial.begin(230400);
}


int val=0;

void loop() {
	val = analogRead(0);
}