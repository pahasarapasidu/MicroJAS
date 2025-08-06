#include "motor.h"


/* --- Enable Clocks to GPIOB and TIM4 --- */
void clock_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    __DSB(); // ensure peripheral ready
}


/* --- Set GPIO Modes --- */
void gpio_init(void)
{
    // Set PB4–PB7 as general-purpose output
    GPIOB->MODER &= ~(
        (3U << (4*2)) | (3U << (5*2)) | 
        (3U << (6*2)) | (3U << (7*2))
    );
    GPIOB->MODER |= (
        (1U << (4*2)) | (1U << (5*2)) | 
        (1U << (6*2)) | (1U << (7*2))
    );
    GPIOB->OTYPER &= ~(
        (1U << 4) | (1U << 5) | (1U << 6) | (1U << 7)
    );
    GPIOB->OSPEEDR |= (
        (3U << (4*2)) | (3U << (5*2)) |
        (3U << (6*2)) | (3U << (7*2))
    );

    // Set PB8, PB9 as alternate function (AF2 = TIM4)
    GPIOB->MODER &= ~((3U << (8*2)) | (3U << (9*2)));
    GPIOB->MODER |=  ((2U << (8*2)) | (2U << (9*2)));
    GPIOB->AFR[1] &= ~((0xF << 0) | (0xF << 4));   // AFRH: PB8, PB9
    GPIOB->AFR[1] |=  ((2U << 0) | (2U << 4));
}


/* --- Setup TIM4 for PWM on CH3 → PB8, CH4 → PB9 --- */
void tim4_pwm_init(void)
{
    TIM4->PSC = TIM4_PSC;
    TIM4->ARR = TIM4_ARR;

    TIM4->CCMR2 &= ~(
        TIM_CCMR2_OC3M | TIM_CCMR2_OC4M | 
        TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE
    );
    TIM4->CCMR2 |=
        (6U << TIM_CCMR2_OC3M_Pos) | TIM_CCMR2_OC3PE |
        (6U << TIM_CCMR2_OC4M_Pos) | TIM_CCMR2_OC4PE;

    TIM4->CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC4P);
    TIM4->CCER |=  TIM_CCER_CC3E | TIM_CCER_CC4E;

    TIM4->CCR3 = 0; // Motor A
    TIM4->CCR4 = 0; // Motor B

    TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}


/* --- Motor A Control Functions --- */
void motorA_forward(uint8_t duty)
{
    duty = CLAMP_100(duty);
    TIM4->CCR3 = ((TIM4->ARR + 1) * duty) / 100;

    GPIOB->BSRR = (1U << 4);   // AIN1 = 1
    GPIOB->BSRR = (1U << (5 + 16)); // AIN2 = 0
}

void motorA_reverse(uint8_t duty)
{
    duty = CLAMP_100(duty);
    TIM4->CCR3 = ((TIM4->ARR + 1) * duty) / 100;

    GPIOB->BSRR = (1U << 5);   // AIN2 = 1
    GPIOB->BSRR = (1U << (4 + 16)); // AIN1 = 0
}

void motorA_stop(void)
{
    TIM4->CCR3 = 0;
    GPIOB->BSRR = (1U << (4 + 16)) | (1U << (5 + 16)); // AIN1 & AIN2 = 0
}


/* --- Motor B Control Functions --- */
void motorB_forward(uint8_t duty)
{
    duty = CLAMP_100(duty);
    TIM4->CCR4 = ((TIM4->ARR + 1) * duty) / 100;

    GPIOB->BSRR = (1U << 6);   // BIN1 = 1
    GPIOB->BSRR = (1U << (7 + 16)); // BIN2 = 0
}

void motorB_reverse(uint8_t duty)
{
    duty = CLAMP_100(duty);
    TIM4->CCR4 = ((TIM4->ARR + 1) * duty) / 100;

    GPIOB->BSRR = (1U << 7);   // BIN2 = 1
    GPIOB->BSRR = (1U << (6 + 16)); // BIN1 = 0
}

void motorB_stop(void)
{
    TIM4->CCR4 = 0;
    GPIOB->BSRR = (1U << (6 + 16)) | (1U << (7 + 16)); // BIN1 & BIN2 = 0
}
