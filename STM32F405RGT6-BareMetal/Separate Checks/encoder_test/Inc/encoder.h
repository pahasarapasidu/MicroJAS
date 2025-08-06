/*
 * encoder.h
 *
 *  Created on: Jul 31, 2025
 *      Author: last_knight
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file
#include "stm32f4xx.h" //Include the STM32F4xx header file(Standard peripheral library)
#include "stm32f405xx.h"//Include the STM32F411 header file(Standard peripheral library)

// ---- User Variables ----
extern volatile int32_t encoderA_pos ; // PA0/PA1 quadrature decoded count
extern volatile int32_t encoderB_pos ; // PA2/PA3 quadrature decoded count
extern volatile uint8_t encoderA_last ;  // Previous AB
extern volatile uint8_t encoderB_last ;  // Previous AB


void encoder_gpio_exti_init(void);
void encoderB_update(void);
void encoderA_update(void);

#endif /* ENCODER_H_ */
