#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h"
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)
/* ---------- USER-TUNABLE SECTION -------------------------------- */
#define SYS_CORE_CLK_HZ   168000000U   /* CPU frequency         */
#define APB1_PRESCALE     4U          /* as set in RCC_CFGR     */
#define TIM4CLK_HZ        ( (APB1_PRESCALE == 1U) ? \
                            (SYS_CORE_CLK_HZ / APB1_PRESCALE) : \
                            (SYS_CORE_CLK_HZ / APB1_PRESCALE * 2U) )
#define PWM_FREQ_HZ       20000U      /* Target PWM frequency   */

/* Derive PSC & ARR so that TIM4CLK/(PSC+1)/(ARR+1) = PWM_FREQ_HZ */
#define TIM4_PSC          ( (TIM4CLK_HZ / 1000000U) - 1U )  /* 1 MHz timer tick */
#define TIM4_ARR          ( (1000000U / PWM_FREQ_HZ) - 1U ) /* Period ticks     */

/* Safety clamping macro */
#define CLAMP_100(x)      ( (x) > 100 ? 100 : (x) )

/* ---------- PROTOTYPES ----------------------------------------- */
static void clock_init(void);
static void gpio_init(void);
static void tim4_pwm_init(void);
void        pwm_set_duty(uint8_t duty_pc, uint8_t channel);

/* ---------------- MAIN ----------------------------------------- */
int main(void)
{
    clock_init();      /* Enable GPIOB + TIM4 interface clocks   */
    gpio_init();       /* Put PB8, PB9 into AF2-PWM high-speed PP */
    tim4_pwm_init();   /* 20 kHz PWM on CH3 & CH4                */

    /* Soft-start ramp demo: 0 → 100 % duty, both motors equal     */
    for (uint8_t d = 0; d <= 100; d++) {
        pwm_set_duty(d, 3);           /* CH3 = PB8 */
        pwm_set_duty(d, 4);           /* CH4 = PB9 */
        for (volatile uint32_t i = 0; i < 20000; i++) ; /* ~2 ms delay */
    }
    while (1) {
        /* Place runtime duty updates here—for example from ADC, USART, etc. */
    }
}

/* ------------ Helper Functions --------------------------------- */
static void clock_init(void)
{
    /* 1. Gate clocks to GPIOB + TIM4 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;    /* Enable Port B clock  */
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;     /* Enable TIM4 clock    */
    /* Delay after enabling clocks (RM0090 erratum)[14] */
    __DSB();
}

static void gpio_init(void)
{
    /* PB8, PB9  → Alternate-function (10b) */
    GPIOB->MODER  &= ~((3U << (8 * 2)) | (3U << (9 * 2)));
    GPIOB->MODER  |=  (2U << (8 * 2)) | (2U << (9 * 2));

    /* Push-pull, high speed, no pull-ups */
    GPIOB->OTYPER &= ~((1U << 8) | (1U << 9));
    GPIOB->OSPEEDR |= (3U << (8 * 2)) | (3U << (9 * 2));
    GPIOB->PUPDR  &= ~((3U << (8 * 2)) | (3U << (9 * 2)));

    /* AFRH bits: PB8/PB9 occupy nibbles 0 & 1; AF2 = 0b0010 */
    GPIOB->AFR[1] &= ~(0xF << 0 | 0xF << 4);
    GPIOB->AFR[1] |=  (2U << 0) | (2U << 4);
}

static void tim4_pwm_init(void)
{
    /* 2. Prescaler + period */
    TIM4->PSC = TIM4_PSC;
    TIM4->ARR = TIM4_ARR;

    /* 3. PWM-mode 1 on channels 3 & 4, preload enable */
    TIM4->CCMR2 &= ~(TIM_CCMR2_OC3M | TIM_CCMR2_OC4M |
                     TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE);
    TIM4->CCMR2 |=  (6U << TIM_CCMR2_OC3M_Pos) |   /* 110 = PWM mode 1 */
                    (6U << TIM_CCMR2_OC4M_Pos) |
                    TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;

    /* 4. Enable outputs, active-high polarity */
    TIM4->CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC4P);
    TIM4->CCER |=  TIM_CCER_CC3E | TIM_CCER_CC4E;

    /* 5. Zero duty at startup */
    TIM4->CCR3 = 0;
    TIM4->CCR4 = 0;

    /* 6. Auto-reload preload ON, counter enable */
    TIM4->CR1  |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void pwm_set_duty(uint8_t duty_pc, uint8_t channel)
{
    uint32_t ticks = ( (uint32_t)CLAMP_100(duty_pc) * (TIM4_ARR + 1U) ) / 100U;
    if (channel == 3)      TIM4->CCR3 = ticks;
    else if (channel == 4) TIM4->CCR4 = ticks;
}
