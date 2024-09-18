/*
 * robotic_arm.h
 *
 *  Created on: Sep 7, 2024
 *      Author: Lenovo
 */

#ifndef BSP_ROBOTIC_ARM_ROBOTIC_ARM_H_
#define BSP_ROBOTIC_ARM_ROBOTIC_ARM_H_
#include "usart.h"

extern uint8_t rx_buff_arm;

void CopeSerialData_arm(unsigned char ucData_arm);

#endif /* BSP_ROBOTIC_ARM_ROBOTIC_ARM_H_ */
