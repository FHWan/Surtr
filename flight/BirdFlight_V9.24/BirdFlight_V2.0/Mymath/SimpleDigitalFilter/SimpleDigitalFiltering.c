/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * ���� 	:Xiluna Tech
 * �ļ��� :SimpleDigitalFiltering.c
 * ����   :���˲�����
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
******************************************************************************/
#include "SimpleDigitalFiltering.h"
/*
 *  ����ƽ���˲����������ͣ�
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
 *  ��λֵ�˲������Σ�
 *  length ���Ȳ��˹��󣬷�����ʱ����󣬱�����ȫ��ʹ��7��ֵ�����˲�����
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
    //����
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

