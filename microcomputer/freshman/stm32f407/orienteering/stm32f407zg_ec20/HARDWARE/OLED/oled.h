#ifndef _OLED_H
#define _OLED_H
#include "IICSoft.h"
#include <stdio.h>
#include <string.h>
#include "fonts.h"
#include <math.h>

#define OLED_MODE_IIC_SOFT	1
#define OLED_MODE_IIC_HARD	2

#define OLED_MODE						OLED_MODE_IIC_SOFT

#define OLED_IIC						I2C2
#define OLED_IIC_ADDRESS		0x3C

/* ������� */
enum
{
	FC_ST_16 = 0,		/* ����15x16���� ����x�ߣ� */
	FC_ST_12 = 1		/* ����12x12���� ����x�ߣ� */
};

/* �������Խṹ, ����LCD_DispStr() */
typedef struct
{
	uint16_t usFontCode;	/* ������� 0 ��ʾ16���� */
	uint16_t usTextColor;	/* ������ɫ 0 �� 1 */
	uint16_t usBackColor;	/* ���ֱ�����ɫ 0 �� 1 */
	uint16_t usSpace;		/* ���ּ�࣬��λ = ���� */
}FONT_T;


extern  FONT_T tFont12;
extern  FONT_T tFont16;

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

/* �ɹ��ⲿģ����õĺ��� */
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);
void OLED_DisDigital(uint16_t _usX, uint16_t _usY, uint32_t Dig_Data, FONT_T *_tFont);
void OLED_DisDecimal(uint16_t _usX, uint16_t _usY, double Dig_Data,uint8_t DecimalNum, FONT_T *_tFont);

void OLED_Init(void);
void OLED_InitHard(void);
void OLED_DispOn(void);
void OLED_DispOff(void);
void OLED_StartDraw(void);
void OLED_EndDraw(void);
void OLED_ClrScr(uint8_t _ucMode);
void OLED_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont);
void OLED_PutPixel(uint16_t _usX, uint16_t _usY, uint8_t _ucColor);
uint8_t OLED_GetPixel(uint16_t _usX, uint16_t _usY);
void OLED_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint8_t _ucColor);
void OLED_DrawPoints(uint16_t *x, uint16_t *y, uint16_t _usSize, uint8_t _ucColor);
void OLED_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint8_t _ucColor);
void OLED_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint8_t _ucColor);
void OLED_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t *_ptr);
#endif


