#include "InertialFilter.h"

//速度位移预测函数
void inertial_filter_predict(float dt, float x[2], float acc)
{
	x[0] += x[1] * dt + acc * dt * dt / 2.0f;
	x[1] += acc * dt;
}

void inertial_filter_correct(float e, float dt, float x[2], int i, float w)
{
	float ewdt = e * w * dt;
	x[i] += ewdt;

	if (i == 0) {
		x[1] += w * ewdt;
	}
}


