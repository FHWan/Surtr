#include "Adrc_control.h"

const float ADRC_Unit[3][14]=
{
/* TD跟踪微分器 改进最速TD,h0=N*h         扩张状态观测器            扰动补偿             非线性PID组合       */
/*  r       h      N0            	   	beta_01  beta_02  beta_03        b           beta_0   beta_1   beta_2   alpha0 alpha1  alpha2  zeta*/
	 {9000 ,0.005 , 5,           		   100,      50000,    1000,       2.5,          0,      12.5,    0.006,     -0.6,  0.6,   1.2,   0.001 },//Pitch
	 {9000 ,0.005 , 5,           		   100,      50000,    1000,       2.5,          0,      12.5,    0.006,     -0.6,  0.6,   1.2,   0.001 },//Roll
	 {9000 ,0.005 , 5,          		   300,      35000,    1500,       2.5,          0,      20.5,     0.03,     -0.6,  0.6,   1.2,   0.02 },//Yaw
};

float Constrain_Float(float amt, float low, float high)
{
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

int16_t Sign_ADRC(float Input)
{
    int16_t output=0;
    if(Input>1E-6f) output=1;
    else if(Input<-1E-6f) output=-1;
    else output=0;
    return output;
}

int16_t Fsg_ADRC(float x,float d)
{
  int16_t output=0;
  output=(Sign_ADRC(x+d)-Sign_ADRC(x-d))/2;
  return output;
}

//原点附近 连续线段的连续幂次函数
float Fal_ADRC(float e,float alpha,float zeta)
{
    int16_t s=0;
    float fal_output=0;
    s=(Sign_ADRC(e+zeta)-Sign_ADRC(e-zeta))/2;
    fal_output=e*s/(powf(zeta,1-alpha))+powf(fabsf(e),alpha)*Sign_ADRC(e)*(1-s);
    return fal_output;
}

/******* pitch roll height adrc 参数初始化 ********/
void ADRC_Init(ADRC *PITCH_PARA,ADRC *ROLL_PARA,ADRC *YAW_PARA)
{
    //pitch
    PITCH_PARA->r=ADRC_Unit[0][0];
    PITCH_PARA->h=ADRC_Unit[0][1];
    PITCH_PARA->N0=ADRC_Unit[0][2];
    PITCH_PARA->beta_01=ADRC_Unit[0][3];
    PITCH_PARA->beta_02=ADRC_Unit[0][4];
    PITCH_PARA->beta_03=ADRC_Unit[0][5];
    PITCH_PARA->b=ADRC_Unit[0][6];
    PITCH_PARA->beta_0=ADRC_Unit[0][7];
    PITCH_PARA->beta_1=ADRC_Unit[0][8];
    PITCH_PARA->beta_2=ADRC_Unit[0][9];
    PITCH_PARA->alpha0=ADRC_Unit[0][10];
    PITCH_PARA->alpha1=ADRC_Unit[0][11];
    PITCH_PARA->alpha2=ADRC_Unit[0][12];
    PITCH_PARA->zeta=ADRC_Unit[0][13];

    //roll
    ROLL_PARA->r=ADRC_Unit[1][0];
    ROLL_PARA->h=ADRC_Unit[1][1];
    ROLL_PARA->N0=ADRC_Unit[1][2];
    ROLL_PARA->beta_01=ADRC_Unit[1][3];
    ROLL_PARA->beta_02=ADRC_Unit[1][4];
    ROLL_PARA->beta_03=ADRC_Unit[1][5];
    ROLL_PARA->b=ADRC_Unit[1][6];
    ROLL_PARA->beta_0=ADRC_Unit[1][7];
    ROLL_PARA->beta_1=ADRC_Unit[1][8];
    ROLL_PARA->beta_2=ADRC_Unit[1][9];
    ROLL_PARA->alpha0=ADRC_Unit[1][10];
    ROLL_PARA->alpha1=ADRC_Unit[1][11];
    ROLL_PARA->alpha2=ADRC_Unit[1][12];
    ROLL_PARA->zeta=ADRC_Unit[1][13];

    //yaw
    YAW_PARA->r=ADRC_Unit[2][0];
    YAW_PARA->h=ADRC_Unit[2][1];
    YAW_PARA->N0=ADRC_Unit[2][2];
    YAW_PARA->beta_01=ADRC_Unit[2][3];
    YAW_PARA->beta_02=ADRC_Unit[2][4];
    YAW_PARA->beta_03=ADRC_Unit[2][5];
    YAW_PARA->b=ADRC_Unit[2][6];
    YAW_PARA->beta_0=ADRC_Unit[2][7];
    YAW_PARA->beta_1=ADRC_Unit[2][8];
    YAW_PARA->beta_2=ADRC_Unit[2][9];
    YAW_PARA->alpha0=ADRC_Unit[2][10];
    YAW_PARA->alpha1=ADRC_Unit[2][11];
    YAW_PARA->alpha2=ADRC_Unit[2][12];
    YAW_PARA->zeta=ADRC_Unit[2][13];


}


/****  ADRC 控制 ****/

/**** 	TD跟踪器   ****/
void Fhan_ADRC(ADRC *ADRC_INPUT,float expect_ADRC)
{
  float d=0,a0=0,y=0,a1=0,a2=0,a=0;
  float x1_delta=0;
  x1_delta=ADRC_INPUT->x1-expect_ADRC;               //x1-v(k)
  ADRC_INPUT->h0=ADRC_INPUT->N0*ADRC_INPUT->h;       //用h0代替h，解决最速跟踪微分器速度超调问题
  d=ADRC_INPUT->r*ADRC_INPUT->h0*ADRC_INPUT->h0;     //d=rh^2;
  a0=ADRC_INPUT->h0*ADRC_INPUT->x2;                  //a0=h*x2
  y=x1_delta+a0;                                     //y=x1+a0
  a1=sqrt(d*(d+8*fabsf(y)));                         //a1=sqrt(d*(d+8*ABS(y))])
  a2=a0+Sign_ADRC(y)*(a1-d)/2;                       //a2=a0+sign(y)*(a1-d)/2;
  a=(a0+y)*Fsg_ADRC(y,d)+a2*(1-Fsg_ADRC(y,d));
  ADRC_INPUT->fh=-ADRC_INPUT->r*(a/d)*Fsg_ADRC(a,d)
                  -ADRC_INPUT->r*Sign_ADRC(a)*(1-Fsg_ADRC(a,d));       //获得最速微分加速度跟踪量
  ADRC_INPUT->x1+=ADRC_INPUT->h*ADRC_INPUT->x2;      //x1状态量
  ADRC_INPUT->x2+=ADRC_INPUT->h*ADRC_INPUT->fh;      //x2状态量
}

/************ ESO *************/
void ESO_ADRC(ADRC *ADRC_INPUT,float feedback)
{
  ADRC_INPUT->e=ADRC_INPUT->z1-feedback;//状态误差

  ADRC_INPUT->fe=Fal_ADRC(ADRC_INPUT->e,0.5,ADRC_INPUT->h);//非线性函数
  ADRC_INPUT->fe1=Fal_ADRC(ADRC_INPUT->e,0.25,ADRC_INPUT->h);

  /*************状态量更新**********/
  ADRC_INPUT->z1+=ADRC_INPUT->h*(ADRC_INPUT->z2 - ADRC_INPUT->beta_01 * ADRC_INPUT->e);
  ADRC_INPUT->z2+=ADRC_INPUT->h*(ADRC_INPUT->z3 - ADRC_INPUT->beta_02 * ADRC_INPUT->fe + ADRC_INPUT->b * ADRC_INPUT->u);//+ ADRC_INPUT->b * ADRC_INPUT->u
  ADRC_INPUT->z3+=ADRC_INPUT->h*(-ADRC_INPUT->beta_03*ADRC_INPUT->fe1);

}

/************PID非线性组合**************/
void Nolinear_ADRC(ADRC *ADRC_INPUT)
{
  ADRC_INPUT->u0=ADRC_INPUT->beta_0*Fal_ADRC(ADRC_INPUT->e0,ADRC_INPUT->alpha0,ADRC_INPUT->zeta)
                +ADRC_INPUT->beta_1*Fal_ADRC(ADRC_INPUT->e1,ADRC_INPUT->alpha1,ADRC_INPUT->zeta)
                +ADRC_INPUT->beta_2*Fal_ADRC(ADRC_INPUT->e2,ADRC_INPUT->alpha2,ADRC_INPUT->zeta);
}

float ADRC_Control(ADRC *ADRC_INPUT,float expect_ADRC,float feedback_ADRC){
    /* TD跟踪 */
    Fhan_ADRC(ADRC_INPUT,expect_ADRC);
    /* ESO */
    ESO_ADRC(ADRC_INPUT,feedback_ADRC);
    /* PID非线性组合 */
    ADRC_INPUT->e1 = ADRC_INPUT->x1-ADRC_INPUT->z1;      //KP
    ADRC_INPUT->e0 += (ADRC_INPUT->e1 * ADRC_INPUT->h);  //KI
    ADRC_INPUT->e2 = ADRC_INPUT->x2-ADRC_INPUT->z2;      //KD
    Nolinear_ADRC(ADRC_INPUT);
    /* Z3控制量扰动补偿 */
    ADRC_INPUT->u = ADRC_INPUT->u0 - ADRC_INPUT->z3/ADRC_INPUT->b;
    ADRC_INPUT->u = Constrain_Float(ADRC_INPUT->u,-300,300);

    return ADRC_INPUT->u;
}





