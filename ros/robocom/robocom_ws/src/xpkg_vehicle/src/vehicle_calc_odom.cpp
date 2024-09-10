#include "vehicle_calc_odom.h"

VehicleCalcOdom::VehicleCalcOdom()
{
  set_zero =  false;
}
VehicleCalcOdom::~VehicleCalcOdom()
{

}
/*------------------------------------------------------------------------------------------------------------------
 * name: CalcWithSpeed
 * detail: Use speed data to calculate location
 -----------------------------------------------------------------------------------------------------------------*/
void VehicleCalcOdom::CalcWithSpeed(double v_x,double v_y,double v_r,double dt)
{
  double delta_th = v_r * dt;
  double delta_x = (v_x * cos(delta_th) - v_y * sin(delta_th)) * dt;
  double delta_y = (v_x * sin(delta_th) + v_y * cos(delta_th)) * dt;

  m_data_odom.x += cos(m_data_odom.th) * delta_x - sin(m_data_odom.th) * delta_y;
  m_data_odom.y += sin(m_data_odom.th) * delta_x + cos(m_data_odom.th) * delta_y;
  m_data_odom.th += delta_th;

  m_data_odom.vx = v_x;
  m_data_odom.vy = v_y;
  m_data_odom.vth = v_r;  
}
/*------------------------------------------------------------------------------------------------------------------
 * name: CalcWithOdom
 * detail: Use odom data to calculate location
 -----------------------------------------------------------------------------------------------------------------*/
void VehicleCalcOdom::CalcWithOdom(double odom_l,double odom_r,double dt,double wheel_track)
{
  if(!set_zero)
  {
    m_data_odom.odom_l = odom_l;
    m_data_odom.odom_r = odom_r;

  }
  double d_odom_l =odom_l-m_data_odom.odom_l;
  double d_odom_r =odom_r-m_data_odom.odom_r;
  double d_avg = (d_odom_r + d_odom_l) / 2.0;
  double d_th = (d_odom_r - d_odom_l) / wheel_track;
  m_data_odom.vx = d_avg / dt;
  m_data_odom.vy = 0;
  m_data_odom.vth = d_th / dt;

  double delta_x = cos(d_th) * d_avg;
  double delta_y = -sin(d_th) * d_avg;

  m_data_odom.odom_l = odom_l;
  m_data_odom.odom_r= odom_r;
  m_data_odom.x += cos(m_data_odom.th) * delta_x - sin(m_data_odom.th) * delta_y;
  m_data_odom.y += sin(m_data_odom.th) * delta_x + cos(m_data_odom.th) * delta_y;
  m_data_odom.th += d_th;
  set_zero = true;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: ShowLocation
 * detail: Print out location info
 -----------------------------------------------------------------------------------------------------------------*/
void VehicleCalcOdom::ShowLocation(void)
{
  ROS_INFO("convert: x=%fm y=%fm th=%fdeg/%frad",m_data_odom.x,m_data_odom.y,m_data_odom.th/3.14*180,m_data_odom.th);
}
/*------------------------------------------------------------------------------------------------------------------
 * name: ResetLocation
 * detail: Reset location
 -----------------------------------------------------------------------------------------------------------------*/
void VehicleCalcOdom::ResetLocation(void)
{
  m_data_odom.x = 0;
  m_data_odom.y = 0;
  m_data_odom.th = 0;   
}
