#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define      L1      PAin(11) 
#define      L2		 PAin(6) 
#define      M       PAin(12)
#define      R2      PAin(7)
#define      R1      PAin(15)

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);

#endif
