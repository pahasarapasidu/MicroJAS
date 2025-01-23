/*Check the LEDs of Micromouse*/

//Include the STM32F4xx header files
#include "stm32f4xx.h"       //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32xf411xe.h"     //Include the STM32F411xx header file(Standard peripheral library)

#define GPIOAEN          (1UL << 0)    //0b 0000 0000 0000 0000 0000 0000 0000 0001
#define GPIOBEN          (1UL << 1)    //0b 0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOCEN          (1UL << 2)    //0b 0000 0000 0000 0000 0000 0000 0000 0100

#define PIN0     (1UL << 0)
#define PIN1     (1UL << 1)
#define PIN2     (1UL << 2)
#define PIN3     (1UL << 3)
#define PIN4     (1UL << 4)
#define PIN5     (1UL << 5)
#define PIN6     (1UL << 6)
#define PIN7     (1UL << 7)
#define PIN8     (1UL << 8)
#define PIN9     (1UL << 9)
#define PIN10    (1UL << 10)
#define PIN11    (1UL << 11)
#define PIN12    (1UL << 12)
#define PIN13    (1UL << 13)
#define PIN14    (1UL << 14)
#define PIN15    (1UL << 15)

#define LED1_PIN    PIN11     //LED16
#define LED2_PIN    PIN12     //LED15
#define LED3_PIN    PIN0      //LED14
#define LED4_PIN    PIN1      //LED13
#define LED5_PIN    PIN2      //LED12
#define LED6_PIN    PIN3      //LED11
#define LED9_PIN    PIN15     //LED8
#define LED10_PIN    PIN6     //LED7
#define LED11_PIN    PIN12    //LED6


