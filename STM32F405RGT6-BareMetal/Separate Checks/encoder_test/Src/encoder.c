#include "encoder.h"


// ---- User Variables ----
volatile int32_t encoderA_pos = 0; // PA0/PA1 quadrature decoded count
volatile int32_t encoderB_pos = 0; // PA2/PA3 quadrature decoded count
volatile uint8_t encoderA_last = 0;  // Previous AB
volatile uint8_t encoderB_last = 0;  // Previous AB

// ---- Quadrature decode LUT ----
static const int8_t quad_table[16] = {
    0,  -1,   1,   0,
    1,   0,   0,  -1,
   -1,   0,   0,   1,
    0,   1,  -1,   0
};

void encoder_gpio_exti_init(void) {
    // Enable GPIOA and SYSCFG clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Set PA0..PA3 as input mode (default at reset)
    GPIOA->MODER &= ~(
        (3U << (0*2)) | (3U << (1*2)) | (3U << (2*2)) | (3U << (3*2))
    );

    // Optional: Enable pull-ups
    // GPIOA->PUPDR &= ~(
    //     (3U << (0*2)) | (3U << (1*2)) | (3U << (2*2)) | (3U << (3*2))
    // );
    // GPIOA->PUPDR |= (
    //     (1U << (0*2)) | (1U << (1*2)) | (1U << (2*2)) | (1U << (3*2)) // pull-up
    // );

    // Connect PA0-PA3 to EXTI0-3 (EXTICR[0] bits 0-15 == all zero meaning port A)
    SYSCFG->EXTICR[0] &= ~0xFFFF;

    // Unmask, enable rising + falling edge for all lines
    EXTI->IMR |= (0xF << 0);
    EXTI->RTSR |= (0xF << 0);
    EXTI->FTSR |= (0xF << 0);

    // Set NVIC priorities & enable lines 0-3
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_SetPriority(EXTI1_IRQn, 2);
    NVIC_SetPriority(EXTI2_IRQn, 2);
    NVIC_SetPriority(EXTI3_IRQn, 2);

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);

    // Initialize last values
    encoderA_last =
        ((GPIOA->IDR & (1 << 0)) ? 2 : 0) | ((GPIOA->IDR & (1 << 1)) ? 1 : 0);
    encoderB_last =
        ((GPIOA->IDR & (1 << 2)) ? 2 : 0) | ((GPIOA->IDR & (1 << 3)) ? 1 : 0);
}

// ----- Encoder update for Encoder A (PA0, PA1) -----
void encoderA_update(void) {
    uint8_t a = (GPIOA->IDR & (1 << 0)) ? 2 : 0;
    uint8_t b = (GPIOA->IDR & (1 << 1)) ? 1 : 0;
    uint8_t curr = a | b;
    uint8_t idx = ((encoderA_last << 2) | curr) & 0xF;
    encoderA_pos += quad_table[idx];
    encoderA_last = curr;
}

// ----- Encoder update for Encoder B (PA2, PA3) -----
void encoderB_update(void) {
    uint8_t a = (GPIOA->IDR & (1 << 2)) ? 2 : 0;
    uint8_t b = (GPIOA->IDR & (1 << 3)) ? 1 : 0;
    uint8_t curr = a | b;
    uint8_t idx = ((encoderB_last << 2) | curr) & 0xF;
    encoderB_pos += quad_table[idx];
    encoderB_last = curr;
}

// ---- EXTI IRQ handlers ----
void EXTI0_IRQHandler(void) { if (EXTI->PR & (1 << 0)) { encoderA_update(); EXTI->PR = (1 << 0); } }
void EXTI1_IRQHandler(void) { if (EXTI->PR & (1 << 1)) { encoderA_update(); EXTI->PR = (1 << 1); } }
void EXTI2_IRQHandler(void) { if (EXTI->PR & (1 << 2)) { encoderB_update(); EXTI->PR = (1 << 2); } }
void EXTI3_IRQHandler(void) { if (EXTI->PR & (1 << 3)) { encoderB_update(); EXTI->PR = (1 << 3); } }
