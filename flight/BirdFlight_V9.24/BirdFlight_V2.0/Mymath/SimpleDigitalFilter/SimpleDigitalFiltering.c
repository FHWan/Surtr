/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :SimpleDigitalFiltering.c
 * 描述   :简单滤波处理
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "SimpleDigitalFiltering.h"
/*
 *  滑动平均滤波（浮点类型）
 */
float Average_Filter(float FilterData,uint16_t Length,float *FilterArray){
    float AverageValue = 0;
    int i;
    for(i=0;i<Length-1;i++)
    {
        FilterArray[i]=FilterArray[i+1];
    }
    FilterArray[Length - 1] = FilterData;
    for(i=0;i<Length;i++)
    {
        AverageValue += FilterArray[i];
    }
    AverageValue /= Length;
    return AverageValue;
}
/*
 *  中位值滤波（整形）
 *  length 长度不宜过大，否者延时会过大，本例程全部使用7个值进行滤波处理
 */
float Median_Filter(int FilterData,uint16_t Length,int *FilterArray){
    uint16_t i = 0,j = 0;
    int temp = 0;
    int sum = 0;
    float AverageValue = 0;
		FilterArray[Length - 1] = FilterData;
    for(i=0;i<Length-1;i++)
    {
        FilterArray[i]=FilterArray[i+1];
    }
    //排序
    for(i = 0 ; i < Length-1 ; i++)
    {
        for(j = 0 ; j < Length-1-i; j++)
        {
            if(FilterArray[j] > FilterArray[j+1] )
            {
                temp = FilterArray[j];
                FilterArray[j] =  FilterArray[j+1];
                FilterArray[j+1] = temp;
            }
        }
    }
    if(Length%2 == 0){
        for(i = Length/2-2;i < Length/2+2;i++){
            sum += FilterArray[i];
        }
        AverageValue = sum/4;
    }
    else{
        for(i = Length/2-1;i < Length/2+2;i++){
            sum += FilterArray[i];
        }
        AverageValue = sum/3;
    }
    return AverageValue;
}

