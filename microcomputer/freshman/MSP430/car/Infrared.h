/*
 * Infrared.h
 *
 *  Created on: 2023��7��15��
 *      Author: me
 */

#ifndef INFRARED_H_
#define INFRARED_H_

extern volatile int tar1;
extern volatile int tar2;

void Infrared_Init(void);
void Infrared_find(void);

#endif
