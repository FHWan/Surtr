#ifndef VEHICLE_DATA_CONVERT_H
#define VEHICLE_DATA_CONVERT_H

#include <string>
#include <vector>
#include <xmsg_comm_data.h>
using namespace std;

////////////////////////////info of vehicle//////////////////////////////////////
#define MODE_STANDBY 0
#define MODE_REMOTE 1
#define MODE_CAN 2

#define BEEP_OFF 0
#define BEEP_ON 1

struct VehicleInfo
{
    //vehicle info
    unsigned char s_type = 0;
    unsigned char s_num = 0;
    //hardware and software version
    std::string s_ver_hard = "--";
    std::string s_ver_soft = "--";
    //system status
    bool s_dev_state = false;
    bool s_sys_state = true;    //0x00 fine,0x01 error
    bool s_beep_state = false;
    unsigned char s_sys_mode = 0x0f;     //wokring mode:0x00 standby,0x01 remote,0x02 CAN
    float s_bat_vol = 0.0;     // *0.1V
    bool s_err_motor_current = true;
    bool s_err_motor_heat = true;
    bool s_err_driver_heat = true;
    bool s_err_bat_down = true; //<22V
    bool s_err_bat_low = true;  //<23V
    bool s_err_ctrl_lost = true;
    bool s_err_bump = true;
    //motion status
    short s_speed_x = 0;   //mm/s
    short s_speed_y = 0;   //mm/s
    short s_rotate = 0;   //mrad/s
    //contraller status
    unsigned char s_ctrl_swa = 0x00;     //0x01 up,0x02 mid,0x03 down
    unsigned char s_ctrl_swb = 0x00;     //0x01 up,0x02 mid,0x03 down
    unsigned char s_ctrl_swc = 0x00;     //0x01 up,0x02 mid,0x03 down
    unsigned char s_ctrl_swd = 0x00;     //0x01 up,0x02 mid,0x03 down
    unsigned char s_ctrl_left_h = 0x00;  //-100~100
    unsigned char s_ctrl_left_v = 0x00;  //-100~100
    unsigned char s_ctrl_right_h = 0x00; //-100~100
    unsigned char s_ctrl_right_v = 0x00; //-100~100
    unsigned char s_ctrl_left_vra = 0x00; //-100~100
    unsigned char s_ctrl_right_vra = 0x00; //-100~100
    //odometer
    int s_odo_left = 0x00000000;   //mm
    int s_odo_right = 0x00000000;  //mm
    int s_odo_left_s = 0x00000000;  //mm
    int s_odo_right_s = 0x00000000;  //mm
    //bumper
    bool s_bump[8] = {1,1,1,1,1,1,1,1};
    //sonic
    unsigned char s_sonic[6] = {0,0,0,0,0,0};
    //driver status
    short s_driver_speed[4] = {0};    //PRM
    float s_driver_current[4] = {0};  //*0.1A
    int s_driver_pulse[4] = {0};
    float s_driver_volt[4] = {0};     //*0.1V
    short s_driver_heat[4] = {0};     //1C
    char s_motor_heat[4] = {0};     //1C
    bool s_driver_err_volt_low[4] = {1,1,1,1};
    bool s_driver_err_heat_over[4] =  {1,1,1,1};
    bool s_motor_err_current_over[4] =  {1,1,1,1};
    bool s_motor_err_heat_over[4] =  {1,1,1,1};
    double time_interval = 0.0;
};

//////////////////////////////////////////////////////////////////


class VehicleDataConvert
{
public:
    explicit VehicleDataConvert(void);
    VehicleInfo GetVehicleInfo(void);
    bool IsOnline(void);
    void DataRecvHandle(xpkg_comm::xmsg_comm_data data_recv);

    xpkg_comm::xmsg_comm_data VehicleReset();
    xpkg_comm::xmsg_comm_data VehicleClear();
    xpkg_comm::xmsg_comm_data VehicleVersion();
    xpkg_comm::xmsg_comm_data VehicleMode(unsigned char mode,bool beep);
    xpkg_comm::xmsg_comm_data VehicleMove(short speed_x,short speed_y,short rotate);
    xpkg_comm::xmsg_comm_data VehicleSetState(bool state);
    xpkg_comm::xmsg_comm_data VehicleRemoterInfo(unsigned char state);
    xpkg_comm::xmsg_comm_data VehicleSensorInfo(unsigned char state);
    xpkg_comm::xmsg_comm_data VehicleDriverMotion(unsigned char state);
    xpkg_comm::xmsg_comm_data VehicleDriverState(unsigned char state);
    xpkg_comm::xmsg_comm_data VehicleZero();

private:
    VehicleInfo m_vehicle_info;
    bool f_vehicle_on;

};

#endif // VEHICLE_DATA_CONVERT_H
