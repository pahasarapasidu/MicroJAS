#include "encoder.h"

/* --- GPIOA Setup for TIM5_CH1/CH2 (PA0, PA1) and TIM2_CH3/CH4 (PA2, PA3) --- */
void encoder_gpio_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable Port A clock

    // Clear mode bits for PA0-PA3 and set to alternate function mode (10b)
    GPIOA->MODER &= ~(
        (3U << (0*2)) | (3U << (1*2)) |
        (3U << (2*2)) | (3U << (3*2))
    );
    GPIOA->MODER |= (
        (2U << (0*2)) | (2U << (1*2)) |
        (2U << (2*2)) | (2U << (3*2))
    );

    // Set AFR for PA0 and PA1 to AF2 (TIM5)
    GPIOA->AFR[0] &= ~(
        (0xF << (0*4)) | (0xF << (1*4))
    );
    GPIOA->AFR[0] |= (
        (2U << (0*4)) | (2U << (1*4))
    );

    // Set AFR for PA2 and PA3 to AF1 (TIM2)
    GPIOA->AFR[0] &= ~(
        (0xF << (2*4)) | (0xF << (3*4))
    );
    GPIOA->AFR[0] |= (
        (1U << (2*4)) | (1U << (3*4))
    );

    // No pull-up, no pull-down on PA0-PA3
    GPIOA->PUPDR &= ~(
        (3U << (0*2)) | (3U << (1*2)) |
        (3U << (2*2)) | (3U << (3*2))
    );
}

/* --- Initialize TIM5 (channels 1 & 2) and TIM2 (channels 3 & 4) as encoder inputs --- */
void encoder_timer_init(void)
{
    // Enable clocks for TIM2 and TIM5
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM5EN;

    /* --- TIM5: encoder mode on CH1 & CH2 (PA0, PA1) --- */
    TIM5->SMCR &= ~TIM_SMCR_SMS;                // Clear SMS bits
    TIM5->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // Encoder mode 3 (count on both TI1 and TI2 edges)

    // Configure capture/compare for CH1 and CH2 as input mapped to TI1 and TI2
    TIM5->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S | TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);
    TIM5->CCMR1 |= (1U << TIM_CCMR1_CC1S_Pos) | (1U << TIM_CCMR1_CC2S_Pos); // CC1S=01, CC2S=01

    // Inputs non-inverted (rising polarity)
    TIM5->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);

    TIM5->ARR = 0xFFFFFFFF; // Max 32-bit auto reload
    TIM5->CNT = 0;          // Reset counter

    TIM5->CR1 |= TIM_CR1_CEN;  // Enable timer

    /* --- TIM2: encoder mode on CH3 & CH4 (PA2, PA3) --- */
    TIM2->SMCR &= ~TIM_SMCR_SMS;                // Clear SMS bits
    TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // Encoder mode 3 (count on both TI1 and TI2 edges)

    // Configure capture/compare for CH3 and CH4 as input mapped to TI3 and TI4
    TIM2->CCMR2 &= ~(TIM_CCMR2_CC3S | TIM_CCMR2_CC4S | TIM_CCMR2_IC3F | TIM_CCMR2_IC4F);
    TIM2->CCMR2 |= (1U << TIM_CCMR2_CC3S_Pos) | (1U << TIM_CCMR2_CC4S_Pos); // CC3S=01, CC4S=01

    // Inputs non-inverted (rising polarity)
    TIM2->CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC4P);

    TIM2->ARR = 0xFFFF; // 16-bit auto reload (or 32K cycles)
    TIM2->CNT = 0;      // Reset counter

    TIM2->CR1 |= TIM_CR1_CEN;  // Enable timer
}
