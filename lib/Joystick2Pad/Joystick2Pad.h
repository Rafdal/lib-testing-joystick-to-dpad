#ifndef JOYSTICK_2_PAD_H
#define JOYSTICK_2_PAD_H

#include <Arduino.h>
#include "Pot2Btn.h"

// (vertical_pin, horizontal_pin)
class Joystick2Pad
{
private:
public:
    Pot2Btn up, down, left, right;

    Joystick2Pad(uint8_t vertical_pin, uint8_t horizontal_pin);
    ~Joystick2Pad(){}

    void read()
    {
        up.read();
        down.read();
        left.read();
        right.read();
    }
};

// (vertical_pin, horizontal_pin) -> AnalogPins
Joystick2Pad::Joystick2Pad(uint8_t vertical_pin, uint8_t horizontal_pin)
{
    up.begin(vertical_pin, 600, 1013);
    down.begin(vertical_pin, 10, -400);
    right.begin(horizontal_pin, 600, 1013);
    left.begin(horizontal_pin, 10, -400);
}


#endif