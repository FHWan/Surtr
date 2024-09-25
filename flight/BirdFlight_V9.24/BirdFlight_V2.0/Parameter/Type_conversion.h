#ifndef __TYPE_CONVERSIONS_H_
#define __TYPE_CONVERSIONS_H_

#include "stm32f4xx.h"
#include <stdio.h>

void FloatToByte(float floatNum,unsigned char* byteArry);
void IntToByte(int intNum,unsigned char* byteArry);
void UintToByte(unsigned int uintNum,unsigned char* byteArry);
float Hex_To_Decimal(unsigned char *Byte,int num);
int Hex_To_Int(unsigned char *Byte,int num);
unsigned int Hex_To_Uint(unsigned char *Byte,int num);
void arrycat(unsigned char *dst,unsigned char index,unsigned char *src,unsigned char len);
float Asc_to_f(volatile unsigned char *str);


#endif /* HARDWARE_TYPE_CONVERSIONS_H_ */
