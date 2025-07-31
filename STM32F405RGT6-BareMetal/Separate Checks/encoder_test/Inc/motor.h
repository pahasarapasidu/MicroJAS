/*
 * motor.h
 *
 *  Created on: Jul 31, 2025
 *      Author: last_knight
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h"
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)

/******************************************************************
 * STM32F405RGT6 → TB6612FNG Dual Motor Driver Control via PWM
 * Motor A: PB8 (PWM), PB4 (AIN1), PB5 (AIN2)
 * Motor B: PB9 (PWM), PB6 (BIN1), PB7 (BIN2)
 * PWM Freq: 20 kHz using TIM4 CH3 & CH4
 ******************************************************************/

#define PWM_FREQ_HZ   20000U         // Target PWM frequency
#define SYSCLK_HZ     168000000U     // MCU clock (via PLL)
#define APB1_PRESCALER 4U            // From STM32F4 clock tree
#define TIMCLK_HZ    ((APB1_PRESCALER == 1) ? (SYSCLK_HZ) : (SYSCLK_HZ / APB1_PRESCALER * 2))

#define TIM4_PSC ((TIMCLK_HZ / 1000000U) - 1)        // 1 MHz time base
#define TIM4_ARR ((1000000U / PWM_FREQ_HZ) - 1)      // Auto-reload for target frequency

#define CLAMP_100(x) ((x) > 100 ? 100 : (x))

/*** Initialization Prototypes ***/
void clock_init(void);
void gpio_init(void);
void tim4_pwm_init(void);

/*** Motor Control Functions ***/
void motorA_forward(uint8_t duty);
void motorA_reverse(uint8_t duty);
void motorA_stop(void);

void motorB_forward(uint8_t duty);
void motorB_reverse(uint8_t duty);
void motorB_stop(void);

#endif /* MOTOR_H_ */
