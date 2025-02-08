#include "uart.h"



#define SYS_FREQ    16000000U
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE 115200U

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    /****Write Calculated Baudrate to any USARTx BRR****/
  USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    /****USART BaudRate devident factor(N) Calculation
                      SYS_CLK/BR = N                  ****/
  return ((PeriphClk + (BaudRate/2U))/BaudRate);
}