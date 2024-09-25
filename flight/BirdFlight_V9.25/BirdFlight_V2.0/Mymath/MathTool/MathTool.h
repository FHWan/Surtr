#ifndef __MATHTOOL_H
#define __MATHTOOL_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"


float ConstrainFloat(float amt, float low, float high);
int16_t ConstrainInt16(int16_t amt, int16_t low, int16_t high);
uint16_t ConstrainUint16(uint16_t amt, uint16_t low, uint16_t high);
int32_t ConstrainInt32(int32_t amt, int32_t low, int32_t high);

float Sq(float v);
float safe_asin(float v);
float Pythagorous2(float a, float b);
float Pythagorous3(float a, float b, float c);
float Pythagorous4(float a, float b, float c, float d);
float invSqrt(float x);

#endif
