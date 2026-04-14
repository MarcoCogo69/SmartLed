/*
**  ============================================================
**  Created by  :   Marco Cogo - marco.cogo@outlook.it
**  Last mod    :   13/04/2026
**  Description :   SmartLed class.
**                  A C++ library to use leds in a smart way
**                  with Raspberry Pi Pico boards
**  =============================================================
*/

#ifndef SMART_LED_H
#define SMART_LED_H
#include <cstdint>

#define LED_ON      1
#define LED_OFF     0

/**
 * Represents the possible working mode of the LED.
 */
enum LedMode {
    MODE_STATIC,    /** LED is in a STATIC state, ON or OFF. **/
    MODE_FLASH,     /** LED is in FLASH mode, ON for a fixed interval. **/
    MODE_BLINK,     /** LED is in BLINK mode, ON and OFF state for the respective intervals.**/
    MODE_PATTERN    /** LED blinks based on a predefined ON/OFF sequence. **/
};

class SmartLed {
private:
    uint8_t _pin;
    uint32_t _lastBlinkToggle;
    uint32_t _nextIntervalMs;
    bool _isInverted;
    LedMode _mode;
    uint8_t _patternIdx, _patternLen;
    const uint32_t *_pattern;
    uint32_t _blinkPattern[2];
    uint8_t _repeatPattern, _cntPattern;

public:
    SmartLed(uint8_t pin, bool inverted = false);
    void On();
    void Off();
    void Toggle();
    void Update();
    uint8_t State();
    void BlinkStart(uint32_t msOn, uint32_t msOff = 0);
    void BlinkStop();
    void Play(const uint32_t *pattern, uint8_t len, uint8_t rep = 0);
    LedMode const getMode();
};

#endif // SMART_LED_H