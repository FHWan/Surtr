/*
 * Kinematics.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Lenovo
 */

#ifndef BSP_KINEMATICS_KINEMATICS_H_
#define BSP_KINEMATICS_KINEMATICS_H_

// 四元数结构体定义
typedef struct
{
    float w;
    float x;
    float y;
    float z;
} quaternion_t;

// 里程计信息结构体定义
typedef struct
{
    float x;                 // 坐标x
    float y;                 // 坐标y
    float yaw;               // yaw
    quaternion_t quaternion; // 姿态四元数
    float linear_speed;      // 线速度
    float angular_speed;     // 角速度
} odom_t;

extern float line_speed;
extern float angle_speed;

// 函数声明
void Euler2Quaternion(float roll, float pitch, float yaw, quaternion_t* q);
float TransAngleInPI(float angle);
void update_bot_odom(void);

// 获取 odom_t 结构体实例的函数声明
odom_t* get_odom(void);

#endif /* BSP_KINEMATICS_KINEMATICS_H_ */
