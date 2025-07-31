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

/* Initialize clocks, GPIOs for Encoder inputs */
void encoder_gpio_init(void);
void encoder_timer_init(void);


#endif /* ENCODER_H_ */
