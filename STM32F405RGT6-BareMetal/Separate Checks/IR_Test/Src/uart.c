#include "uart.h"

#define GPIOCEN     (1UL << 2)
#define USART3EN    (1UL << 18)

#define CR1_TE      (1UL << 3)
#define CR1_RE      (1UL << 2)
#define SR_RXNE     (1UL << 5)
#define SR_TXE      (1UL << 7)

#define CR1_UE      (1UL << 13)

#define SYS_FREQ    16000000U
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE 115200U



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);

char uart3_read(void);

int __io_putchar(int ch)
{
  uart3_write(ch);
  return ch;
}

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

void uart_init(void){
    /*Enable USART3 clock*/
    RCC->APB1ENR |= USART3EN;

    /*Set Baudrate*/
    uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

    /*Set transfer Direction*/
    USART2 ->CR1 = (CR1_TE | CR1_RE);

    /*Enable USART3*/
    USART3->CR1 |= CR1_UE;
}

char uart3_read(void)
{
  /*Make sure the receive data register is not empty*/
  while(!(USART3 ->SR & SR_RXNE)){}

  /*Read Data*/
  return USART3 ->DR;
}

int uart3_write(int ch)
{
    /*****Write Data to transmit*****/

  /*Make sure the transmit data register is empty*/
	while(!(USART3 ->SR & SR_TXE)){}

  /*Write to transmit data register*/ 
    USART3 ->DR = (ch & 0xFF);

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
