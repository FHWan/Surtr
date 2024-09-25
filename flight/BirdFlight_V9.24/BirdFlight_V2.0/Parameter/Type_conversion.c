/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Type_conversion.c
 * ����   :��������ת��
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Type_conversion.h"


/* ��������ʮ������ת�� */
/* floatNum�������ͱ���  */
/* byteArry���ֽ��4���ֽڵ��׵�ַ  */
void FloatToByte(float floatNum,unsigned char* byteArry)
{
	int i;
	char* pchar=(char*)&floatNum;
	for(i=0;i<sizeof(float);i++)
	{
		*byteArry=*pchar;
		pchar++;
		byteArry++;
	}
}

/* 16λ���͵�ʮ������ת�� */
/* intNum�����ͱ���  */
/* byteArry���ֽ��2���ֽڵ��׵�ַ  */
void IntToByte(int intNum,unsigned char* byteArry)
{
	int i;
	char* pchar=(char*)&intNum;
	for(i=0;i<sizeof(int);i++)
	{
		*byteArry=*pchar;
		pchar++;
		byteArry++;
	}
}

/* 16λ�޷������͵�ʮ������ת�� */
/* uintNum���޷������ͱ���  */
/* byteArry���ֽ��2���ֽڵ��׵�ַ  */
void UintToByte(unsigned int uintNum,unsigned char* byteArry)
{
	int i;
	char* pchar=(char*)&uintNum;
	for(i=0;i<sizeof(unsigned int);i++)
	{
		*byteArry=*pchar;
		pchar++;
		byteArry++;
	}
}

/* ʮ�����Ƶ�������     */
/* Byte���ֽڵ��׵�ַ   */
/* num���ϲ����ֽ�����  */
float Hex_To_Decimal(unsigned char *Byte,int num)
{
	int i;
	char cByte[4];
	for (i=0;i<num;i++)
	{
	cByte[i] = Byte[i];
	}
	float pfValue=*(float*)&cByte;
	return pfValue;
}

/* ʮ������ת��������    */
/* Byte���ֽڵ��׵�ַ   */
/* num���ϲ����ֽ�����  */
int Hex_To_Int(unsigned char *Byte,int num)
{
	int i;
	char cByte[2];
	for (i=0;i<num;i++)
	{
		cByte[i] = Byte[i];
	}
	short int pfValue=*(int*)&cByte;
	return pfValue;
}

/* ʮ�����Ƶ��޷������� */
/* Byte���ֽڵ��׵�ַ   */
/* num���ϲ����ֽ�����  */
unsigned int Hex_To_Uint(unsigned char *Byte,int num)
{
	int i;
	char cByte[2];
	for (i=0;i<num;i++)
	{
		cByte[i] = Byte[i];
	}
	unsigned int pfValue=*(unsigned int*)&cByte;
	return pfValue;
}


void arrycat(u8 *dst,u8 index,u8 *src,u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		*(dst+index+i)=*(src+i);
	}
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		float ,(volatile unsigned char *str)
*��������:		��ȡ�ַ����е� ��Ч����
���������
		unsigned char *str    �ַ�������
		���������ʾ��ֵ��  �����ַ��� "1230.01"  �����������󣬷��ظ����ֵΪ1230.01
*******************************************************************************/
float Asc_to_f(volatile unsigned char *str)
{
  signed char temp,flag1,flag2; 
  float value,count;
  flag1 = 1;
  flag2 = 0;
  value = 0;
  count = 1;
  temp = *str;
  while(((*str>='0')&&(*str<='9'))||(*str=='-')||(*str=='.')) //���ֻ����Ƿ���
  { 
			temp=*str++;
			if(temp=='-')
			{ 
					if(flag1)
					flag1=-1;
					else
					return(0x00); //��������'-' �����Ч
			}
			else if(temp=='.')
			{ 
				  flag2=1;	  
	    }
		  else
			{ 
		      value=value*10+(temp&0x0f);
          if(flag2)
		    	count*=0.1f;
		  }
  }
  value*=count*flag1; //����λ
  return(value);
}


