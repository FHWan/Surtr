/*
 * gpio.h
 *
 *  Created on: 2022Äê6ÔÂ12ÈÕ
 *      Author: hett
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#define  Trig_H  GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define  Trig_L  GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define  Echo_H  GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define  Echo_L  GPIO_ResetBits(GPIOB,GPIO_Pin_1)

void ultrasonic_GPIO_Init(void);
void Start_Trig(void);

#endif /* USER_GPIO_H_ */
