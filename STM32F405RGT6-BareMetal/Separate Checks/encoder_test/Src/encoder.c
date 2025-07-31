#include "encoder.h"

/* --- GPIOA Setup: PA0-PA3 as alternate function, no pull --- */
void encoder_gpio_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable Port A clock

    // Alternate function (AF1) for PA0, PA1, PA2, PA3
    GPIOA->MODER &= ~((3U<<(0*2))|(3U<<(1*2))|(3U<<(2*2))|(3U<<(3*2)));
    GPIOA->MODER |=  ((2U<<(0*2))|(2U<<(1*2))|(2U<<(2*2))|(2U<<(3*2)));

    // AF1 = 0b0001 for TIM2 and TIM5 on PA0-PA3 (see datasheet)
    GPIOA->AFR[0] &= ~((0xF<<(0*4))|(0xF<<(1*4))|(0xF<<(2*4))|(0xF<<(3*4)));
    GPIOA->AFR[0] |=  ((1U<<(0*4))|(1U<<(1*4))|(1U<<(2*4))|(1U<<(3*4)));

    // No pull-up, no pull-down
    GPIOA->PUPDR &= ~((3U<<(0*2))|(3U<<(1*2))|(3U<<(2*2))|(3U<<(3*2)));
}

/* --- TIM2 (Right) and TIM5 (Left) in Encoder Mode --- */
void encoder_timer_init(void)
{
    // Enable TIM2 and TIM5 clocks
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM5EN;

    // TIM2: Right Encoder, Channels 1/2
    // Encoder Mode 3 (count up/down on both TI1 and TI2 edges)
    TIM2->SMCR  &= ~TIM_SMCR_SMS;
    TIM2->SMCR  |=  TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // SMS=011: Encoder mode 3
    // Input mapping: TI1/TI2 normal polarity, no filtering
    TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S|TIM_CCMR1_CC2S|TIM_CCMR1_IC1F|TIM_CCMR1_IC2F);
    TIM2->CCMR1 |= (1U << TIM_CCMR1_CC1S_Pos) | (1U << TIM_CCMR1_CC2S_Pos);
    // Both inputs non-inverted
    TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
    // 16-bit auto-reload (max count for TIM2)
    TIM2->ARR = 0xFFFF;
    // Start counter
    TIM2->CR1 |= TIM_CR1_CEN;

    // TIM5: Left Encoder, Channels 1/2
    TIM5->SMCR  &= ~TIM_SMCR_SMS;
    TIM5->SMCR  |=  TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
    TIM5->CCMR1 &= ~(TIM_CCMR1_CC1S|TIM_CCMR1_CC2S|TIM_CCMR1_IC1F|TIM_CCMR1_IC2F);
    TIM5->CCMR1 |= (1U << TIM_CCMR1_CC1S_Pos) | (1U << TIM_CCMR1_CC2S_Pos);
    TIM5->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
    TIM5->ARR = 0xFFFFFFFF; // full 32 bits

    TIM5->CR1 |= TIM_CR1_CEN;
}
