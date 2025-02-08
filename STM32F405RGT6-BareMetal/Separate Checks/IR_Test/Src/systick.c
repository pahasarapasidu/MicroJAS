#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f411xe.h"//Include the STM32F411 header file(Standard peripheral library)

#define SYSTICK_LOAD_VAL      16000
#define CTRL_ENABLE           (1UL<<0)
#define CTRL_CLKSRC           (1UL<<2)
#define CTRL_COUNTFLAG        (1UL<<16)


void systickDelayMs(int delay)
{
    /*Reload with number of clocks per millisecond*/
    SysTick ->LOAD = SYSTICK_LOAD_VAL;

    /*Clear sysytick current value register*/
    SysTick ->VAL = 0;

    /*Enable systick current value register*/
    SysTick ->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

    /******Millisecond counter******/
    for (int i = 0; i < delay; i++)
    {
        /*Wait until the COUNTFLAG is set*/
        while((SysTick ->CTRL & CTRL_COUNTFLAG)==0){}
    }
    SysTick ->CTRL = 0;
    
}
