#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)
#include "uart.h" //Include the uart header file
#include "systick.h" //Include the systick header file
#include "motor.h" //Include the motor header file


uint32_t sensor_value;
uint32_t sensor_value;

int main(void)
{
    pc10_af_uart_tx_mode();
    pc11_af_uart_rx_mode();
    clock_init();
    gpio_init();
    tim4_pwm_init();

    // Test Motors: A forward, B reverse at 50% speed
    motorA_forward(50);
    motorB_reverse(50);

    while (1) {
        // Add debounce, UART, or input sensing here
    }
}
