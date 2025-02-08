#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)
#include "uart.h" //Include the uart header file
#include "systick.h" //Include the systick header file
//#include "ir.h" //Include the ir header file
#include "dipswitches.h" //Include the dipswitches header file
#include "ir copy.h"


uint32_t sensor_value;

int main(void){
    pc10_af_uart_tx_mode();
    pc11_af_uart_rx_mode();
    ir_led_turn_onc(1);
    ir_led_turn_onc(2);
    ir_led_turn_onc(3);
    ir_reciever_initc();
    uart3_init();

    ir_start_conversionc();

    while (1)
    {
        sensor_value = ir_sensor_value_readc();
        printf("Sensor Value: %d\n", sensor_value);
        systickDelayMs(1000);
        
    }
    


}
