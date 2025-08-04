#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

// Read DIP switches and return them packed in lowest 4 bits (1 = OFF, 0 = ON)
uint8_t read_dip_switches(void) {
    uint8_t dip = 0;
    dip |= ((GPIOC->IDR & (1 << 13)) ? 1 : 0) << 0;   // PC13 -> bit 0
    dip |= ((GPIOC->IDR & (1 << 14)) ? 1 : 0) << 1;   // PC14 -> bit 1
    dip |= ((GPIOC->IDR & (1 << 15)) ? 1 : 0) << 2;   // PC15 -> bit 2
    dip |= ((GPIOA->IDR & (1 <<  8)) ? 1 : 0) << 3;   // PA8  -> bit 3
    return dip;
}

void dip_gpio_init(void) {
    // Enable GPIOC and GPIOA clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN;

    // PC13, PC14, PC15 as input (reset state for these is input)
    // PA8 set as input
    GPIOA->MODER &= ~(3U<<(8*2)); // PA8 input

//    // Enable pull-ups on all pins
//    GPIOC->PUPDR &= ~((3U<<(13*2)) | (3U<<(14*2)) | (3U<<(15*2)));
//    GPIOC->PUPDR |=  ((1U<<(13*2)) | (1U<<(14*2)) | (1U<<(15*2))); // pull-up
//
//    GPIOA->PUPDR &= ~(3U<<(8*2));
//    GPIOA->PUPDR |=  (1U<<(8*2)); // Pull-up
}

int main(void) {
	// Initialize UART3 pins (PC10: TX, PC11: RX) and UART3 peripheral to enable printf()
	pc10_af_uart_tx_mode();
	pc11_af_uart_rx_mode();
	uart3_init();

    // Initialize GPIOs for DIP switch
    dip_gpio_init();

    // Main test loop
    while (1) {
        uint8_t dip = read_dip_switches();

        printf("DIP Switch states (1=OFF, 0=ON): PC13=%u, PC14=%u, PC15=%u, PA8=%u\r\n",
               (dip & 1) ? 1 : 0,
               (dip & 2) ? 1 : 0,
               (dip & 4) ? 1 : 0,
               (dip & 8) ? 1 : 0);

        for (volatile int i=0; i<800000; ++i) ; // crude ~delay
    }
}
