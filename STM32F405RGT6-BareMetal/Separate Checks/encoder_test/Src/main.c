#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "systick.h"
#include "motor.h"
#include "encoder.h"

// Variables for encoder positions
// volatile int16_t right_last = 0;       // For TIM2 16-bit counter wrap handling
// volatile int32_t right_pos = 0;        // Accumulated right encoder position

// volatile int32_t left_last  = 0;       // For TIM5 32-bit counter wrap handling
// volatile int32_t left_pos  = 0;        // Accumulated left encoder position

int main(void)
{
    // Initialize UART3 pins (PC10: TX, PC11: RX) and UART3 peripheral to enable printf()
    pc10_af_uart_tx_mode();
    pc11_af_uart_rx_mode();
    uart3_init();

    // Initialize clocks and peripherals for motor PWM and encoder inputs
    clock_init();
    gpio_init();
    tim4_pwm_init();
    
    encoder_gpio_exti_init();
    
    
    
    while (1)
    {
        
        // Print accumulated encoder positions via UART
        printf("Right Pos: %ld, Left Pos: %ld\r\n", encoderA_pos, encoderB_pos);

        // Wait ~1 second delay (assuming systickDelayMs is properly implemented)
        systickDelayMs(1000);
    }
}
