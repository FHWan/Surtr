/*
 * Motor.h
 *
 *  Created on: 2023��7��14��
 *      Author: me
 */

#ifndef Motor_H_
#define Motor_H_

void Motor_Init();
int Motor_SetSpeed(int Motor, int Speed);
void Motor_Forward(int Speed);
void Motor_turn(int lSpeed, int rSpeed);

#endif /* MOTOR_H_ */
