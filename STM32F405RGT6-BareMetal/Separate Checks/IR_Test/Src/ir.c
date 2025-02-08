/*Check the LEDs of Micromouse*/

//Include the STM32F4xx header files

#include "stm32f4xx.h"       //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"     //Include the STM32F411xx header file(Standard peripheral library)


#define GPIOAEN          (1UL << 0)    //0b 0000 0000 0000 0000 0000 0000 0000 0001
#define GPIOBEN          (1UL << 1)    //0b 0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOCEN          (1UL << 2)    //0b 0000 0000 0000 0000 0000 0000 0000 0100

#define PIN0     (1UL << 0)
#define PIN1     (1UL << 1)

#define PIN4     (1UL << 4)
#define PIN5     (1UL << 5)

#define PIN7     (1UL << 7)
#define PIN8     (1UL << 8)
#define PIN9     (1UL << 9)


#define RF_RECIEVER         PIN4
#define R_RECIEVER          PIN5
#define L_RECIEVER          PIN0
#define LF_RECIEVER         PIN1
#define L_EMITTER           PIN7
#define R_EMITTER           PIN8
#define DIAGONAL_EMITTER    PIN9        


#define ADC_CH8   (8UL)    //PB0 for L reciever
#define ADC_CH9   (9UL)    //PB1 for LF reciever
#define ADC_CH4   (4UL)    //PA4 for RF reciever
#define ADC_CH5   (5UL)    //PA5 for R reciever

#define CR2_ADON  (1UL << 0)
#define CR2_SWSTART (1UL << 30)
#define CR2_CONT   (1UL << 1)
#define CSR_EOC    (1UL << 1) | (1UL << 9)


void ir_led_turn_on(int ir_led){
  switch(ir_led){
    case 1:
      /*Enable clock for Port C*/
      RCC ->AHB1ENR |= GPIOCEN;
      /*Set the MODER to general purpose output mode*/
      GPIOC ->MODER |= (1UL << 14);
      GPIOC ->MODER &= ~(1UL << 15);
      /*Set the Pin HIGH*/
      GPIOC ->ODR |= L_EMITTER;
      break;
    case 2:
      /*Enable clock for Port C*/
      RCC ->AHB1ENR |= GPIOCEN;
      /*Set the MODER to general purpose output mode*/
      GPIOC ->MODER |= (1UL << 16);
      GPIOC ->MODER &= ~(1UL << 17);
      /*Set the Pin HIGH*/
      GPIOC ->ODR |= R_EMITTER;
      break;
    case 3:
      /*Enable clock for Port C*/
      RCC ->AHB1ENR |= GPIOCEN;
      /*Set the MODER to general purpose output mode*/
      GPIOC ->MODER |= (1UL << 18);
      GPIOC ->MODER &= ~(1UL << 19);
      /*Set the Pin HIGH*/
      GPIOC ->ODR |= DIAGONAL_EMITTER;
      break;
  }
}

void ir_led_turn_off(int led){
  switch(led){
    case 1:
      /*Set the Pin LOW*/
      GPIOC ->ODR &= ~L_EMITTER;
      break;
    case 2:
      /*Set the Pin LOW*/
      GPIOC ->ODR &= ~R_EMITTER;
      break;
    case 3:
      /*Set the Pin LOW*/
      GPIOC ->ODR &= ~DIAGONAL_EMITTER;
      break;
  }
}

void ir_reciever_init(void){
  /*Enable clock access for port A*/
  RCC ->AHB1ENR |= GPIOAEN;

  /*Set the mode register A to analog mode, pin 4 and 5*/
  GPIOA ->MODER |= (3UL << 8);
  GPIOA ->MODER |= (3UL << 10);

  /*Enable clock access for port B */
  RCC ->AHB1ENR |= GPIOBEN;

  /*Set the mode register B to analog mode, pin 0 and 1*/
  GPIOB ->MODER |= (3UL << 0);
  GPIOB ->MODER |= (3UL << 2);


  /***Configure ADC module ***/

  /*Enable clock access for ADC1, ADC2*/
  RCC ->APB2ENR |= (3UL << 8);

  /*Select multi ADC mode as regular simultaneous mode*/
  //ADC ->CCR|= (6UL << 0);

  /*Conversion sequence start ADC1*/
  ADC1 ->SQR3 = ADC_CH8 | (ADC_CH9 << 5);

  /*Conversion sequence start ADC2*/
  ADC2 ->SQR3 = ADC_CH5 | (ADC_CH4 << 5);

  /*Conversion sequence length*/
  ADC1 ->SQR1 = (1UL << 20);
  ADC2 ->SQR1 = (1UL << 20);

  /*Enable ADC1 and ADC2*/
  ADC1 -> CR2 |= CR2_ADON;
  ADC2 -> CR2 |= CR2_ADON;
  
}

void ir_start_conversion(void){
  /*Enable continuous conversion mode*/
  ADC1 -> CR2 |= CR2_CONT;
  ADC2 -> CR2 |= CR2_CONT;

  /*Start the conversion*/
  ADC1 -> CR2 |= CR2_SWSTART;
  ADC2 -> CR2 |= CR2_SWSTART;

}

uint32_t ir_sensor_value_read(void){
  /*Wait for conversion to be completed*/
  while(!(ADC ->CSR & CSR_EOC)){}

  /*Return the value of the conversion*/
  uint32_t value = ADC -> CDR;
  return value;
}

