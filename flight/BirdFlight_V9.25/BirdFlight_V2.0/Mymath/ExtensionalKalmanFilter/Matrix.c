//-------------------------------------------//
//此头文件包含一些通常的矩阵运算
//-------------------------------------------//
#ifndef _MATRIX_H_
#define _MATRIX_H_


#include "Matrix.h"
#include <math.h>

#define DF float

//-------------------------------------------//
//函数名称：MatrixAdd
//函数功能：矩阵加法
//函数描述：
//参数说明：
//返回值：
//创建时间：2004.05.18
//修改时间：2004.05.28
//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
void MatrixAdd( float* fMatrixA,float* fMatrixB,float* Result,
		unsigned int m,unsigned int n )
{
	unsigned int index_i = 0;
	unsigned int index_j = 0;
	unsigned int itemp = 0;

	for (index_i=0;index_i<m;index_i++)
		for (index_j=0;index_j<n;index_j++)
		{
			itemp = index_i*n+index_j;
			*(Result+itemp) = *(fMatrixA+itemp) + *(fMatrixB+itemp);
		}
} 	

//-------------------------------------------//
//函数名称：MatrixSub
//函数功能：矩阵减法
//函数描述:
//参数说明:
//返回值：
//创建时间：2004.05.18
//修改时间：2004.05.28
//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
void MatrixSub( float* fMatrixA,float* fMatrixB,float* Result,
		unsigned int m,unsigned int n )
{
	unsigned int index_i = 0;
	unsigned int index_j = 0;
	unsigned int itemp = 0;
	for (index_i=0;index_i<m;index_i++)
		for (index_j=0;index_j<n;index_j++)
		{
			itemp = index_i*n+index_j;
			*(Result+itemp) = *(fMatrixA+itemp) - *(fMatrixB+itemp);
		}
}	//void MatrixSub

//-------------------------------------------//
//函数名称：MatrixMultiply
//函数功能：矩阵乘法
//函数描述：
//参数说明：
//返回值：
//创建时间：2004.05.18
//修改时间：2004.05.28(改为指针操作)、2004.06.02(加入乘前的判断条件)
//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
// MatrixMultiply(F,7,7,P,7,7,A );
void MatrixMultiply( float* fMatrixA,unsigned int uRowA,unsigned int uColA,
float* fMatrixB,unsigned int uRowB,unsigned int uColB,float* MatrixResult )
{
	unsigned int index_i = 0;
	unsigned int index_j = 0;
	unsigned int index_l = 0;
	unsigned int index_u = 0;
	unsigned int index_k = 0;
	unsigned int index_v = 0;
	uRowB = uRowB;
 
	for(index_i=0;index_i<uRowA;index_i++)
		for(index_j=0;index_j<uColB;index_j++)
		{
			index_u = index_i*uColB + index_j;
			MatrixResult[index_u] = 0.0;
			for(index_l=0;index_l<uColA;index_l++)
			{
				index_k = index_i*uColA+index_l;
				index_v = index_l*uColB+index_j;

					*(MatrixResult+index_u) += (*(fMatrixA+index_k)) * (*(   fMatrixB+index_v));
			}
		 }
}	//void MatrixMultiply

//-------------------------------------------//
//函数名称：MatrixTranspose
//函数功能：矩阵转置
//函数描述：
//参数说明：
//返回值：
//创建时间：2004.05.18
//修改时间?2004.05.28?//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
void MatrixTranspose(float* fMatrixA,unsigned int m,unsigned n,float* fMatrixB)
{
	unsigned int index_i = 0;
	unsigned int index_j = 0;
	unsigned int index_u = 0;
	unsigned int index_v = 0;

	for (index_i=0;index_i<m;index_i++)
		for (index_j=0;index_j<n;index_j++)
		{
			index_u = index_j*m+index_i;
			index_v = index_i*n+index_j;
			*(fMatrixB+index_u) = *(fMatrixA+index_v);
		}
}	//MatrixTranspose
void MatrixProduct(float* A, int m, int n, float* B, int k, float* C)							 
{	 int tem=0;
	 int i=0;
	 int j=0;
	 int l=0;
	 int met=0;
	for(tem=0;tem<m;tem++)
		for( met=0; met<k; met++)
		C[tem*k+met] = 0.;
		
		for( i=0;i<m;i++)
			for( j=0;j<k;j++)
				for( l=0;l<n;l++)
					C[i*k+j] = C[i*k+j] + A[i*n+l] * B[l*k+j];
				
				
}

//-------------------------------------------//
//函数名称：MatrixE
//函数功能：单位矩阵生成?//函数描述：
//参数说明：
//返回值：
//创建时间：2004.05.19
//修改时间：
//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
void MatrixE(float* fMatrixA,unsigned int n)
{
	unsigned int index_i = 0;
	unsigned int index_j = 0;

	for (;index_i<n;index_i++)
		for (index_j=0;index_j<n;index_j++)
		{
			if (index_i==index_j)
				*(fMatrixA+index_i*n+index_j) = 1;
			else
				*(fMatrixA+index_i*n+index_j) = 0;
		}
}	//MatrixE

//-------------------------------------------//
//函数名称：MatrixDet2
//函数功能：2阶矩阵行列式的值
//函数描述：
//参数说明：
//返回值：
//创建时间：2004.05.19
//修改时间：
//测试时间：
//测试方法：
//-------------------------------------------//
double MatrixDet2(float* fMatrixA)
{
	return (*fMatrixA)*(*(fMatrixA+3))-(*(fMatrixA+1))*(*(fMatrixA+2));
}	//MatrixDet2

//-------------------------------------------//
//函数名称：MatrixInverse2
//函数功能：2阶矩阵求逆
//函数描述：
//参数说明
//返回值：
//创建时间：2004.05.18
//修改时间：
//测试时间:
//测试方法：
//-------------------------------------------//
int MatrixInverse2(float* fMatrixA,float* fMatrixB)
{
	float fmatrix_vlaue = 0.0;

	fmatrix_vlaue = MatrixDet2(fMatrixA);

	if (fmatrix_vlaue == 0.0f)
	{
		#ifdef _DEBUG_
		UART2_Put_String("The inverse of fMatrixA is not exist!!!");
		#endif
		return 1;
	}

	*fMatrixB = *(fMatrixA+3)/fmatrix_vlaue;
	*(fMatrixB+1) = -(*(fMatrixA+2)/fmatrix_vlaue);
	*(fMatrixB+2) = -(*(fMatrixA+1)/fmatrix_vlaue);
	*(fMatrixB+3) = -(*(fMatrixA)/fmatrix_vlaue);
	return 0;
}	//MatrixInverse2

//-------------------------------------------//
//函数名称：
//函数功能：矩阵求逆
//函数描述：
//参数说明：
//返回值：
//创建时间：004.05.18
//修改时间：?//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
int MatrixInverse(float* fMatrixA,int n,float ep)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int u = 0;
	int v = 0;
	int temp_row[10],temp_col[10];
	int * prow = temp_row,urow = 0;		//找到的最大值的行数
	int * pcol = temp_col,ucol = 0;			//找到的最大值的列数	
	float ftemp_max = 0.0;
	float ftemp = 0.0;

	ep = ep;					//防止ep没有使用的警告

	for (i=0;i<10;i++)
	{
		temp_row[i] = 0;
		temp_col[i] = 0;
	}		

	for (k=0;k<n;k++)
	{
		ftemp_max =0.0;		//找到剩余矩阵项中的最大值
		for (i=k;i<n;i++)
			for (j=k;j<n;j++)
			{
				l = i*n+j;
				ftemp = fabs(*(fMatrixA+l));
				if (ftemp_max<ftemp)
				{
					ftemp_max = ftemp;
					*(prow+k) = urow = i;
					*(pcol+k) = ucol= j;
				}
			}

		if (ftemp_max<ep)
		{
			#ifdef _DEBUG_
			UART2_Put_String("The inverse of fMatrixA is not exist!!!\n");
			#endif
			
			return 0;
		}

		if (urow!=k)			//如果当前行不包含最大值换行
		{
			for (j=0;j<n;j++)
			{
				u = k*n +j;
				v = urow*n+j;
				ftemp = *(fMatrixA+u);
				*(fMatrixA+u) = *(fMatrixA+v);
				*(fMatrixA+v) = ftemp;
			}
		}

		if (ucol!=k)			//如果当前列不包含最大值换列
		{
			for (i=0;i<n;i++)
			{
				u = i*n+k;
				v = i*n+ucol;
				ftemp = *(fMatrixA+u);
				*(fMatrixA+u) = *(fMatrixA+v);
				*(fMatrixA+v) = ftemp;
			}
		}

		l = k*n+k;
		ftemp = *(fMatrixA+l) = 1.0f/(*(fMatrixA+l));

		for (j=0;j<n;j++)
		{
			if (j!=k)
			{
				u = k*n+j;
				*(fMatrixA+u) *= *(fMatrixA+l);
			}
		}

		for (i=0;i<n;i++)			//还不知道为什么
		{
			if (i!=k)
			{
				for (j=0;j<n;j++)
				{
					if (j!=k)
					{
						u = i*n+j;
						*(fMatrixA+u) -= (*(fMatrixA+i*n+k))*(*(fMatrixA+k*n+j));
					}
				}
			}
		}

		for (i=0;i<n;i++)
		{
			if (i!=k)
			{
				u = i*n+k;
				*(fMatrixA+u) = -(*(fMatrixA+u))*(*(fMatrixA+l));
			}
		}
	}

	for (k=n-1;k>=0;k--)
	{
		if ((*(pcol+k))!=k)
		{
			for (j=0;j<n;j++)
			{
				u = k*n+j;
				v = (*(pcol+k))*n+j;
				ftemp = *(fMatrixA+u);
				*(fMatrixA+u) = *(fMatrixA+v);
				*(fMatrixA+v) = ftemp;
			}
		}

		if ((*(prow+k))!=k)
		{
			for (i=0;i<n;i++)
			{
				u = i*n+k;
				v = i*n+(*(prow+k));
				ftemp = *(fMatrixA+u);
				*(fMatrixA+u) = *(fMatrixA+v);
				*(fMatrixA+v) = ftemp;
			}
		}
	}
	return 1;
}	

//MatrixInverse2
//矩阵UD分解 求逆时防止发散
void UD(float * A,int  n,float * U,float * D)
{
	int i,j,k;
	float sum1=0;
	float sum2=0;
   int m=n-1;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				U[i*n+j]=1;
				D[i*n+j]=0;
			}
			else
			{
				D[i*n+j]=0;
				U[i*n+j]=0;
			}
		}
	}

	
	D[m*n+m]=A[m*n+m];


	for(i=0;i<n;i++)
	{
		U[i*n+m]=A[i*n+m]/D[m*n+m];
	}

	
	for(j=n-2;j>=0;j--)
	{

		for(k=j+1;k<n;k++)
		{
			sum2=sum2+D[k*n+k]*U[j*n+k]*U[j*n+k];
		} 

		D[j*n+j]=A[j*n+j]-sum2;
		sum2=0;

		for(i=0;i<j;i++)
		{
			for(k=j+1;k<n;k++)
			{
			   	sum1=sum1+D[k*n+k]*U[i*n+k]*U[j*n+k];
			} 
		
			U[i*n+j]=(A[i*n+j]-sum1)/D[j*n+j];
			sum1=0;
		}

		
	}

}

//-------------------------------------------//
//函数名称：Norm
//函数功能：求矩阵范数
//函数描述：||A||
//参数说明：
//返回值：
//创建时间：2004.07.28
//修改时间：?//测试时间：2004.07.28
//测试方法：功能测试
//-------------------------------------------//
DF Norm(float*fMatrixA,int iRow,int iCol)
{
	int i = 0;
	int j = 0;
	int index = 0;
	float local_result = 0.0;

	for (i=0;i<iRow;i++)
		for (j=0;j<iCol;j++)
		{
			index = i * iCol +j;
			local_result += (*(fMatrixA+index)) * (*(fMatrixA+index));
		}
	local_result = sqrt(local_result);

	return local_result;
}
#endif

