#ifndef UART_H_
#define UART_H_

#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)

void pc10_af_uart_tx_mode(void);
void pc11_af_uart_rx_mode(void);
void uart3_init(void);
void uart3_write(int ch);
int __io_putchar(int ch);


#endif /* UART_H_ */