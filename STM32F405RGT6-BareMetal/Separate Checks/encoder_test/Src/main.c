#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "systick.h"
#include "motor.h"
#include "encoder.h"

// Variables for encoder positions
volatile int16_t right_last = 0;
volatile int32_t right_pos = 0;     // Accumulated position can be larger

volatile int32_t left_last  = 0;
volatile int32_t left_pos  = 0;

int main(void)
{
    // Initialize UART pins and UART3 peripheral for printf output
    pc10_af_uart_tx_mode();     // PC10: USART3_TX
    pc11_af_uart_rx_mode();     // PC11: USART3_RX
    uart3_init();

    // Initialize clocks, GPIO, timers for PWM & encoders
    clock_init();
    gpio_init();
    tim4_pwm_init();
    encoder_gpio_init();
    encoder_timer_init();

    // Clear encoder counters at start
    TIM2->CNT = 0;  // Right encoder (16-bit)
    TIM5->CNT = 0;  // Left encoder (32-bit)

    // Initialize last read variables with initial encoder counts
    right_last = (int16_t)(TIM2->CNT);
    left_last = TIM5->CNT;

    while (1)
    {
        // Read right encoder (TIM2 16-bit)
        int16_t rcnt = (int16_t)(TIM2->CNT);
        int16_t rdelta = rcnt - right_last;  // Handles wraparound automatically with signed arithmetic
        right_last = rcnt;
        right_pos += rdelta;

        // Read left encoder (TIM5 32-bit)
        int32_t lcnt = TIM5->CNT;
        int32_t ldelta = lcnt - left_last;
        left_last = lcnt;
        left_pos += ldelta;

        // Print encoder positions over UART
        printf("Right Pos: %ld, Left Pos: %ld\r\n", right_pos, left_pos);

        systickDelayMs(1000);  // Delay 1 second
    }
}
