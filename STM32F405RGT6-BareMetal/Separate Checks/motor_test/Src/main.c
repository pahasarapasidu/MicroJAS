#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h"
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)

void delay(volatile uint32_t count) {
    while (count--) __asm("nop");
}

int main(void) {
    // 1. Enable GPIOB clock (bit 1 of RCC->AHB1ENR)
    RCC->AHB1ENR |= (1 << 1);

    // 2. Set PB8 and PB9 to general purpose output mode (MODER: 0b01 per pin)
    GPIOB->MODER &= ~((3 << (8 * 2)) | (3 << (9 * 2))); // Clear mode bits for PB8, PB9
    GPIOB->MODER |=  ((1 << (8 * 2)) | (1 << (9 * 2))); // Set mode to '01' for output

    // 3. Optional: Set Output type to push-pull (default after reset)
    GPIOB->OTYPER &= ~((1 << 8) | (1 << 9));

    // 4. Optional: Set output speed (e.g., medium)
    GPIOB->OSPEEDR |= ((1 << (8 * 2)) | (1 << (9 * 2)));

    // 5. Optional: No pull-up, pull-down
    GPIOB->PUPDR &= ~((3 << (8 * 2)) | (3 << (9 * 2)));

    while (1) {
        // Set PB8 high, PB9 low
        GPIOB->BSRR = (1 << 8) | (1 << (9 + 16)); // Set PB8, reset PB9
        delay(1000000);

        // Set PB9 high, PB8 low
        GPIOB->BSRR = (1 << 9) | (1 << (8 + 16)); // Set PB9, reset PB8
        delay(1000000);
    }
}
