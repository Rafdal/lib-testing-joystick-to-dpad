#ifndef POT_2_BTN_H
#define POT_2_BTN_H

#include <Arduino.h>

typedef void (*event_callback_t)(void);

// #define DEBUG(Str) Serial.println(F(Str)); // Uncomment for debug
#ifndef DEBUG   
#define DEBUG(Str)
#endif

class Pot2Btn
{
private:
    enum {
        CLICK,
        LONG_PRESSED,
        DURING_LONG_PRESS,
        RELEASED
    };

    uint8_t _pin;
    bool _state;
    bool _lastState;
    event_callback_t _onClick, _onRelease;

    // on Long Press
    uint8_t _LPState; // Long Press state
    uint8_t _longPressTime = 10; // time for a long press (It's in deciseconds, [10ds = 1s])
    unsigned long _lastMs; // Last ms pressed
    event_callback_t _onLP;

    // while Long Press
    event_callback_t _whileLP;
    uint16_t _whileLPInterval;
    unsigned long _LPInterval_lastMs;

    int _lowUmbral, _highUmbral;

    // Schmitt Trigger
    void _schmitt(bool* lastOutput, int inputPot, int lowUmbral, int highUmbral)
    {
        bool inverted = false;

        // Use a negative value in highUmbral when the output is inverted
        if (highUmbral<0)
        {
            highUmbral *= -1;
            inverted = true;
        }
        
        if (inputPot > highUmbral && !*lastOutput^inverted)
            {*lastOutput = true^inverted;}
        else if (inputPot < lowUmbral && *lastOutput^inverted)
            {*lastOutput = false^inverted;}
    }

public:
    Pot2Btn() {}
    ~Pot2Btn() {}

    void begin(uint8_t pin, int lowUmbral, int highUmbral);
    bool read();

    void onRelease(event_callback_t event);
    void onClick(event_callback_t event);
    void whileLongPress(event_callback_t event, unsigned int while_press_interval);
    void onLongPress(event_callback_t event);
    void setLongPressTime(unsigned int press_time_ms){ _longPressTime = press_time_ms/100; }
};

void Pot2Btn::begin(uint8_t pin, int lowUmbral, int highUmbral)
{
    _pin        = pin;
    _highUmbral = highUmbral;
    _lowUmbral  = lowUmbral;
}

bool Pot2Btn::read()
{
    _schmitt(&_state, analogRead(_pin), _lowUmbral, _highUmbral);

    // State changed
    if (_lastState != _state)
    {
        if (_state && _LPState != LONG_PRESSED)
        {
            if (_onClick != NULL)            
                (*_onClick)();

            DEBUG("Click")
            _LPState = CLICK;
        }
        if (!_state && _LPState != LONG_PRESSED)
        {
            if (_onRelease != NULL)
                (*_onRelease)();

            DEBUG("Release")
            _LPState = RELEASED;
        }
        _lastMs = millis();
    }

    // Reset LPState
    if (_LPState == LONG_PRESSED && !_state)
    {
        _LPState = RELEASED;
    }
    
    
    if (_lastState && _state)
    {
        if (millis() - _lastMs > _longPressTime*100)
        {
            switch (_LPState)
            {
            case CLICK:
                {
                    _LPState = LONG_PRESSED;
                    DEBUG("LP")
                    if (_onLP != NULL)
                        (*_onLP)();
                }
                break;
            case LONG_PRESSED:
                {
                    DEBUG("whileLP")
                    if (_whileLP != NULL)
                    {
                        if (_whileLPInterval != 0 && millis() - _LPInterval_lastMs < _whileLPInterval)
                            {break;}
                        _LPInterval_lastMs = millis();
                        (*_whileLP)();
                    }
                }
            default:
                break;
            }
        }
    }
    
    
    _lastState = _state;
    return _state;
}

void Pot2Btn::onClick(event_callback_t event)
{
    _onClick = event;
}

void Pot2Btn::onRelease(event_callback_t event)
{
    _onRelease = event;
}

void Pot2Btn::onLongPress(event_callback_t event)
{
    _onLP = event;
}

void Pot2Btn::whileLongPress(event_callback_t event, unsigned int while_press_interval = 0)
{
    _whileLP = event;
    _whileLPInterval = while_press_interval;
}


#endif