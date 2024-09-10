#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define      L1		 PCin(14)
#define      L2		 PAin(8) 
#define      M       PAin(12)
#define      R2      PAin(15)
#define      R1		 PCin(15)

//#define      L1      PAin(8) 
//#define      L2	   PAin(6) 
//#define      M       PAin(12)
//#define      R2      PAin(7)
//#define      R1      PAin(15)

void PWM_Init(void);
void light_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);

#endif
