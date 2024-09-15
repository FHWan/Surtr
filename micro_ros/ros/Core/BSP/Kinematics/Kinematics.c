/*
 * Kinematics.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Lenovo
 */
#include "Kinematics.h"
#include <encoder/encoder.h>
#include <math.h>

// 全局 odom_t 实例
static odom_t odom_;

float line_speed;
float angle_speed;

// 将欧拉角转为四元数
void Euler2Quaternion(float roll, float pitch, float yaw, quaternion_t* q)
{
    // 传入机器人的欧拉角 roll、pitch 和 yaw。
    // 计算欧拉角的 sin 和 cos 值，分别保存在 cr、sr、cy、sy、cp、sp 六个变量中
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);

    // 计算四元数的分量
    q->w = cy * cp * cr + sy * sp * sr;
    q->x = cy * cp * sr - sy * sp * cr;
    q->y = sy * cp * sr + cy * sp * cr;
    q->z = sy * cp * cr - cy * sp * sr;
}

void update_bot_odom(void)
{
//    float dt_s = (float)dt / 1000.0f;
	float dt_s = 0.01;

    static float last_motor1_speed = 0.0f;
    static float last_motor2_speed = 0.0f;

    // 对电机速度进行简单低通滤波
    motor1.speed = 0.9 * last_motor1_speed + 0.1 * motor1.speed;
    motor2.speed = 0.9 * last_motor2_speed + 0.1 * motor2.speed;

    last_motor1_speed = motor1.speed;
    last_motor2_speed = motor2.speed;

	line_speed = (motor1.speed + motor2.speed) / 2.0;   // 计算线速度
	angle_speed = (motor2.speed - motor1.speed) / 0.205;   // 计算角速度

    // 这里假设 linear_speed 和 angular_speed 已经通过其他方法获得并设置好了
    odom_.angular_speed = angle_speed;
    odom_.linear_speed = line_speed; // （m/s）

    // 更新yaw
    odom_.yaw += odom_.angular_speed * dt_s;
    odom_.yaw = TransAngleInPI(odom_.yaw);

    /* 更新x和y轴上移动的距离 */
    float delta_distance = odom_.linear_speed * dt_s; // 单位m
    odom_.x += delta_distance * cosf(odom_.yaw);
    odom_.y += delta_distance * sinf(odom_.yaw);
}

float TransAngleInPI(float angle){
    angle = fmod(angle, 2.0f * 3.14159f);  // 限制在 [-2π, 2π]
    if (angle > 3.14159f) {
        angle -= 2.0f * 3.14159f;
    }
    else if (angle < -3.14159f) {
        angle += 2.0f * 3.14159f;
    }
    return angle;
}


// 返回全局 odom_t 实例的指针
odom_t* get_odom(void)
{
    // 将机器人的欧拉角 yaw 转换为四元数
    Euler2Quaternion(0, 0, odom_.yaw, &odom_.quaternion);
    return &odom_;
}
