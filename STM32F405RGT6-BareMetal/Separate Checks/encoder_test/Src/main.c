#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)
#include "uart.h" //Include the uart header file
#include "systick.h" //Include the systick header file
#include "motor.h" //Include the motor header file
#include "encoder.h" //Include the encoder header file

volatile int32_t right_last = 0, right_pos = 0;
volatile int32_t left_last  = 0, left_pos  = 0;


int main(void)
{
    pc10_af_uart_tx_mode();
    pc11_af_uart_rx_mode();
    clock_init();
    gpio_init();
    tim4_pwm_init();
    encoder_gpio_init();
    encoder_timer_init();
    uart3_init();

    // Optionally preload counters to zero
    TIM2->CNT = 0;
    TIM5->CNT = 0;

    // Initial last-read values
    right_last = (int16_t)(TIM2->CNT);
    left_last  = TIM5->CNT;

    // Test Motors: A forward, B reverse at 50% speed
//    motorA_reverse(50);
//    motorB_forward(50);

    while (1) {
        // Right Encoder (TIM2 is 16-bit signed)
        int16_t rcnt = (int16_t)(TIM2->CNT);
        int16_t rdelta = rcnt - (int16_t)right_last; // Handles wraparound
        right_last = rcnt;
        right_pos += rdelta;

        // Left Encoder (TIM5 is 32-bit)
        int32_t lcnt = TIM5->CNT;
        int32_t ldelta = lcnt - left_last;
        left_last = lcnt;
        left_pos += ldelta;

        printf("Right Pos: %ld, Left Pos: %ld\r\n", right_pos, left_pos);

        systickDelayMs(1000);
    }
}
