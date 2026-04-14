/*
**  ============================================================
**  Created by  :   Marco Cogo - marco.cogo@outlook.it
**  Last mod    :   13/04/2026
**  Description :   SmartLed class.
**                  A C++ library to use leds in a smart way
**                  with Raspberry Pi Pico boards
**  =============================================================
*/

#include "SmartLed.h"

#include "hardware/gpio.h"
#include "pico/time.h"

/**
 * Constructor for class SmartLed.
 * @param pin GPIO where LED is connected to.
 * @param isInverted True if LED is active LOW, False else
 */
SmartLed::SmartLed (uint8_t pin, bool isInverted) {
    _pin = pin;
    _isInverted = isInverted;

    gpio_init(_pin);
    gpio_set_dir(_pin, GPIO_OUT);
    if (isInverted)
        gpio_set_outover(_pin, GPIO_OVERRIDE_INVERT);

    gpio_put(_pin, LED_OFF);

    _lastBlinkToggle = 0;
    _mode = MODE_STATIC;
}

/**
 * Set LED to ON state
 */
void SmartLed::On() {
    _mode = MODE_STATIC;
    gpio_put(_pin, LED_ON);
}

/**
  * Set LED to OFF state
  */
 void SmartLed::Off() {
    _mode = MODE_STATIC;
    gpio_put(_pin, LED_OFF);
}

/**
 * Toggle LED state
 */
void SmartLed::Toggle() {
    _mode = MODE_STATIC;
    gpio_put(_pin, !gpio_get(_pin));
}

/**
 * Use this inside a loop to update the LED status during
 * blinking phases (BLINK, FLASH, PATTERN).\n\n
 * <b>A faster loop execution ensures greater accuracy for the timing intervals.
 */
void SmartLed::Update() {
    if (_mode == MODE_STATIC)
        return;

    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (_mode == MODE_PATTERN || _mode == MODE_BLINK) {
        if (now - _lastBlinkToggle > _pattern[_patternIdx]) {
            gpio_put(_pin, !gpio_get(_pin));
            _patternIdx++;
            _lastBlinkToggle = now;
            if (_patternIdx == _patternLen) {
                _patternIdx = 0;
                _cntPattern++;
            }
            if (_repeatPattern > 0 && _cntPattern == _repeatPattern)
                Off();
        }
    }
}

/**
 * Returns the actual LED status.
 * @return Returns LED_ON if LED is ON, LED_OFF otherwise.
 */
uint8_t SmartLed::State() {
    return gpio_get(_pin);
}

/**
 * Start Blinking with msOn and msOff intervals in milliseconds.\n
 * Call Update() within a loop to enable blinking. Higher call frequency ensures better timing precision.\n
 * In general, the interval between successive calls to the Update() function, must be shorter than
 * the msOn and msOff parameters.
 * @param msOn ON interval in milliseconds.
 * @param msOff OFF time in milliseconds. If missing or 0, OFF interval will be equal to ON time.
 */
void SmartLed::BlinkStart(uint32_t msOn, uint32_t msOff) {
    _mode = MODE_BLINK;
    _blinkPattern[0] = msOn;
    _blinkPattern[1] = msOff > 0 ? msOff : msOn;
    Play((const uint32_t *)_blinkPattern, 2);
}

/**
 * Stop Bliking the LED. The LED status is set to LED_OFF.
 */
void SmartLed::BlinkStop() {
    _mode = MODE_STATIC;
}

/**
 * Flashes the LED based on a predefined ON/OFF intervals sequence.
 * The buffer containing the intervals, must be even-sized (at least 2 elements), starting with an ON interval
 * and ending with an OFF interval.\n The sequence can be repeated for a given number of cycles
 * or indefinitely (infinite loop).\n
 * Use the Stop() function to terminate it manually.
 * @param pattern Buffer containning the sequence of ON and Off inntervals.
 * @param len The len of the buffer.
 * @param rep The number of times to repeat  the sequence or 0 for an infinite loop. If not specified, rep will be assumed to be 0.
 */
void SmartLed::Play(const uint32_t *pattern, uint8_t len, uint8_t rep) {
    if (len < 2)
        return;
    if (len % 2 != 0)
        len--;
    _mode = MODE_PATTERN;
    _patternLen = len;
    _pattern = pattern;
    _patternIdx = 0;
    _repeatPattern = rep;
    _cntPattern = 0;
    gpio_put(_pin, LED_ON);
    _lastBlinkToggle = to_ms_since_boot(get_absolute_time());
}

LedMode const SmartLed::getMode() {
    return _mode;
}
