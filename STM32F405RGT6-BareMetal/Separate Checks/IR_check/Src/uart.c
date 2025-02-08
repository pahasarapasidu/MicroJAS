#include "uart.h"

#define GPIOCEN     (1UL << 2)
#define USART3EN    (1UL << 18)

#define SYS_FREQ    16000000U
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE 115200U

void pc10_af_uart_tx_mode(void){
    /*Enable GPIOC clock*/
    RCC->AHB1ENR |= GPIOCEN;
    /*Set PC10 to alternate function mode*/
    GPIOC->MODER |= (1UL << 21);
    GPIOC->MODER &= ~(1UL << 20);

    /*Set PC10 alternate function type to UART_TX (USART3 AF7)*/
    GPIOC->AFR[1] |= (1UL << 8);
    GPIOC->AFR[1] |= (1UL << 9);
    GPIOC->AFR[1] |= (1UL << 10);
    GPIOC->AFR[1] &= ~(1UL << 11);


}

void pc11_af_uart_rx_mode(void){
    /*Enable GPIOC clock*/
    RCC->AHB1ENR |= GPIOCEN;

    /*Set PC11 to alternate function mode*/
    GPIOC->MODER |= (1UL << 23);
    GPIOC->MODER &= ~(1UL << 22);

    /*Set PC11 alternate function type to UART_RX (USART3 AF7)*/
    GPIOC->AFR[1] |= (1UL << 12);
    GPIOC->AFR[1] |= (1UL << 13);
    GPIOC->AFR[1] |= (1UL << 14);
    GPIOC->AFR[1] &= ~(1UL << 15);
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