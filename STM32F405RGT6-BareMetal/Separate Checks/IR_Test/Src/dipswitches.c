/*Configure DIP switches of Micromouse*/

//Include the STM32F4xx header files

#include "stm32f4xx.h"       //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"     //Include the STM32F411xx header file(Standard peripheral library)


#define GPIOAEN     (1UL << 0) 
#define GPIOCEN     (1UL << 2)

#define PIN8      (1UL << 8)
#define PIN13     (1UL << 13)
#define PIN14     (1UL << 14)
#define PIN15     (1UL << 15)

#define DIPSW1_PIN   PIN13
#define DIPSW2_PIN   PIN14
#define DIPSW3_PIN   PIN15
#define DIPSW4_PIN   PIN8

void init_dip_switches(void){
  /*Enable clock for port A*/
  RCC ->AHB1ENR |= GPIOAEN;
  /*Set the mode register to input mode*/
  GPIOA ->MODER &= ~(1UL << 16);
  GPIOA ->MODER &= ~(1UL << 17);

  /*Enable clock for port C*/
  RCC ->AHB1ENR |= GPIOCEN;
  /*Set the mode register 13 to input mode*/
  GPIOC ->MODER &= (1UL << 26);
  GPIOC ->MODER &= (1UL << 27);
  /*Set the mode register 13 to input mode*/
  GPIOC ->MODER &= (1UL << 28);
  GPIOC ->MODER &= (1UL << 29);
  /*Set the mode register 13 to input mode*/
  GPIOC ->MODER &= (1UL << 30);
  GPIOC ->MODER &= (1UL << 31);

}