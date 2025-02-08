/*
 * ir.h
 *
 *  Created on: Feb 8, 2025
 *      Author: Minura Ashen
 */

#ifndef IR_H_
#define IR_H_

#include <stdio.h>//Include the standard input/output header file
#include <stdint.h> //Include the standard integer header file

void ir_led_turn_on(char ir_led);
void ir_led_turn_off(int led);
void ir_reciever_init(void);
void ir_start_conversion(void);
uint32_t ir_sensor_value_read(void);


#endif /* IR_H_ */
