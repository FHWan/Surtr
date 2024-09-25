/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :MedianFiler.c
 * 描述   :中位值滤波函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "MedianFiler.h"
/*************中位值平均滤波***************/
float Median_filter(int data,int measureNum,int *Filterdata)
{
  unsigned int i = 0;
	unsigned int j = 0;
	int temp;
	unsigned int MAX_error_targe = 0;
	int MAX_error1;
	Filterdata[measureNum-1] = data;
	for(i=0;i<measureNum-1;i++)
	{
	 Filterdata[i]=Filterdata[i+1];
	}
	for(i = 0 ; i < measureNum-1 ; i++)
	{
			for(j = 0 ; j < measureNum-1-i; j++)
			{
					if(Filterdata[j] > Filterdata[j+1] )
					{
							temp = Filterdata[j];
							Filterdata[j] =  Filterdata[j+1];
							Filterdata[j+1] = temp;
					}
			}
	}
	MAX_error1 = Filterdata[1] - Filterdata[0];
	for(i = 1 ; i < measureNum-1 ; i++)
	{
			if(MAX_error1 < Filterdata[i+1] - Filterdata[i] )
			{
					MAX_error1 =  Filterdata[i+1] - Filterdata[i];
					MAX_error_targe = i; 
			}
	}
	float Average_data=0;
	if(MAX_error_targe+1 > (measureNum+1)/2)
	{
			for(i = 0 ; i <= MAX_error_targe ; i++)
			{
					Average_data += Filterdata[i];
			}
			Average_data /= (MAX_error_targe+1);
	}
	else
	{
			for(i = MAX_error_targe + 1 ; i < measureNum ; i++)
			{
					Average_data += Filterdata[i];
			}
			Average_data /= (measureNum - MAX_error_targe -1);
	}
	return Average_data;
	
}
