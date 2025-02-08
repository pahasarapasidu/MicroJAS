#include "uart.h"

#define GPIOCEN     (1UL << 2)
#define USART3EN    (1UL << 18)

#define SYS_FREQ    16000000U
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE 115200U

void pc10_af_uart_tx_mode(void){
    /*Enable GPIOC clock*/
    /*Set PC10 to alternate function mode*/
    /*Set PC10 alternate function type to UART_TX (USART3)*/


}

void pc11_af_uart_rx_mode(void){
    /*Enable GPIOC clock*/
    /*Set PC11 to alternate function mode*/
    /*Set PC11 alternate function type to UART_RX (USART3)*/
}

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