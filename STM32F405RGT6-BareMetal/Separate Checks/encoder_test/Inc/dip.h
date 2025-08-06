/*
 * dip.h
 *
 *  Created on: Aug 4, 2025
 *      Author: last_knight
 */

#ifndef DIP_H_
#define DIP_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>

uint8_t read_dip_switches(void);
void dip_gpio_init(void);



#endif /* DIP_H_ */
