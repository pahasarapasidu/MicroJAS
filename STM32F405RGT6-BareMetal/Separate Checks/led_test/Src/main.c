#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)
#include "led.h" //Include the led header file


int main(void)
{
    while (1)
    {
        turn_on_led(9);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(9);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(6);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(6);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(5);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(5);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(4);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(4);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(11);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(11);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(10);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(10);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(1);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(1);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(2);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(2);
        for(volatile int i = 0; i < 100000; i++);
        turn_on_led(3);
        for(volatile int i = 0; i < 100000; i++);
        turn_off_led(3);
        for(volatile int i = 0; i < 100000; i++);



    }
    
}
