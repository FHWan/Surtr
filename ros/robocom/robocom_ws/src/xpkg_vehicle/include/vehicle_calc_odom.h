#ifndef VEHICLE_CALC_ODOM_H
#define VEHICLE_CALC_ODOM_H

#include <ros/ros.h>

/////////////////////////////////////////////////
struct  DataOdom{
  double odom_r = 0.0;
  double odom_l = 0.0;
  double odom_b_r = 0.0;
  double odom_b_l = 0.0;

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  double vx = 0.0;
  double vy = 0.0;
  double vth = 0.0;
};
//////////////////////////////////////////////////
class VehicleCalcOdom
{
public:
  explicit VehicleCalcOdom(void);
  ~VehicleCalcOdom(void);

  void CalcWithSpeed(double v_x,double v_y,double v_r,double dt);
  void CalcWithOdom(double odom_l,double odom_r,double dt,double wheel_track);
  void ShowLocation(void);
  void ResetLocation(void);
public:
  DataOdom m_data_odom;
	bool set_zero;
};

#endif // VEHICLE_CALC_ODOM_H
