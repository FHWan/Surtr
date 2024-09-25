/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Type_conversion.c
 * 描述   :数据类型转换
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Type_conversion.h"


/* 浮点数到十六进制转换 */
/* floatNum：浮点型变量  */
/* byteArry：分解成4个字节的首地址  */
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

/* 16位整型到十六进制转换 */
/* intNum：整型变量  */
/* byteArry：分解成2个字节的首地址  */
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

/* 16位无符号整型到十六进制转换 */
/* uintNum：无符号整型变量  */
/* byteArry：分解成2个字节的首地址  */
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

/* 十六进制到浮点数     */
/* Byte：字节的首地址   */
/* num：合并的字节数量  */
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

/* 十六进制转换到整型    */
/* Byte：字节的首地址   */
/* num：合并的字节数量  */
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

/* 十六进制到无符号整型 */
/* Byte：字节的首地址   */
/* num：合并的字节数量  */
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

/**************************实现函数********************************************
*函数原型:		float ,(volatile unsigned char *str)
*功　　能:		提取字符串中的 有效数字
输入参数：
		unsigned char *str    字符串数组
		返回数组表示的值。  比如字符串 "1230.01"  经过这个程序后，返回浮点的值为1230.01
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
  while(((*str>='0')&&(*str<='9'))||(*str=='-')||(*str=='.')) //数字或者是符号
  { 
			temp=*str++;
			if(temp=='-')
			{ 
					if(flag1)
					flag1=-1;
					else
					return(0x00); //出现两次'-' 结果无效
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
  value*=count*flag1; //符号位
  return(value);
}


