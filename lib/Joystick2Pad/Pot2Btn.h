#ifndef POT_2_BTN_H
#define POT_2_BTN_H

#include <Arduino.h>

typedef void (*event_callback_t)(void);

class Pot2Btn
{
private:
    uint8_t _pin;
    bool _lastState;

    event_callback_t _onClick;


    int _lowUmbral;
    int _highUmbral;

    // Schmitt Trigger (AKA: Waveform rectifier)
    void _schmitt(bool* lastOutput, int inputPot, int lowUmbral, int highUmbral)
    {
        bool inverted=false;
        if (highUmbral<0)
        {
            highUmbral *= -1;
            inverted = true;
        }
        
        if (inputPot > highUmbral && !*lastOutput^inverted)
        {
            *lastOutput = true^inverted;
        }
        else if (inputPot < lowUmbral && *lastOutput^inverted)
        {
            *lastOutput = false^inverted;
        }
    }

public:
    bool _state;
    Pot2Btn() {}
    ~Pot2Btn() {}

    void begin(uint8_t pin, int lowUmbral, int highUmbral);
    void read();

    void onClick(event_callback_t event);
};

void Pot2Btn::begin(uint8_t pin, int lowUmbral, int highUmbral)
{
    _pin        = pin;
    _highUmbral = highUmbral;
    _lowUmbral  = lowUmbral;
}

void Pot2Btn::read()
{
    _schmitt(&_state, analogRead(_pin), _lowUmbral, _highUmbral);

    if (!_lastState && _state && _onClick != NULL)
    {
        (*_onClick)();
    }
    
    _lastState = _state; // !! ESTO SIEMPRE AL FINAL
}

void Pot2Btn::onClick(event_callback_t event)
{
    _onClick = event;
}


#endif