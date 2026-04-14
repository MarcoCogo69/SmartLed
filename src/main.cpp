//
// Created by sysadmin on 13/04/2026.
//

#include <cstdio>
#include "pico/stdlib.h"
#include "SmartLed.h"

constexpr uint32_t testInterval = 10000;

SmartLed myLed(16, false);
uint32_t testStart;
const uint32_t ledPattern[] ={500, 100, 500, 100, 1000, 500, 1000, 500};
    
_Noreturn int main() {
    stdio_init_all();
    myLed.Off();
    sleep_ms(10000);
    while(true) {
        printf("Testing On Off functions...\n");

        testStart = to_ms_since_boot(get_absolute_time());
        while (to_ms_since_boot(get_absolute_time()) - testStart < testInterval) {
            myLed.On();
            sleep_ms(500);
            myLed.Off();
            sleep_ms(500);
            printf("Last seq. was%lu\n", to_ms_since_boot(get_absolute_time())-testStart);
        }
        myLed.Off();
        printf("Testing Toggle function...\n");
        sleep_ms(5000);

        testStart = to_ms_since_boot(get_absolute_time());
        while (to_ms_since_boot(get_absolute_time()) - testStart < testInterval) {
            myLed.Toggle();
            sleep_ms(2000);
        }
        myLed.Off();
        printf("Testing Blink function...\n");
        sleep_ms(5000);

        testStart = to_ms_since_boot(get_absolute_time());
        myLed.BlinkStart(700, 200);
        while (to_ms_since_boot(get_absolute_time()) - testStart < testInterval) {
            myLed.Update();
        }
        myLed.Off();
        printf("Testing Pattern function infinite loop...\n");
        sleep_ms(5000);

        testStart = to_ms_since_boot(get_absolute_time());
        myLed.Play(ledPattern, 8);
        while (to_ms_since_boot(get_absolute_time()) - testStart < testInterval) {
            myLed.Update();
        }
        myLed.Off();
        printf("Testing Pattern function 10 times...\n");
        sleep_ms(5000);

        myLed.Play(ledPattern, 8, 10);
        while (myLed.getMode() != MODE_STATIC) {
            myLed.Update();
        }
        myLed.Off();
        printf("Testing myLed class finished!\n");
        sleep_ms(5000);
    }
}