#include <vehicle_data_convert.h>
#include <string>
#include <vector>
#include <ros/ros.h>

VehicleDataConvert::VehicleDataConvert()
{
    f_vehicle_on = false;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: GetVehicleInfo
 * detail: return vehicle info
 -----------------------------------------------------------------------------------------------------------------*/
VehicleInfo VehicleDataConvert::GetVehicleInfo()
{
    return m_vehicle_info;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: IsOnline
 * detail: return if vehicle is online,use before send cmd
 -----------------------------------------------------------------------------------------------------------------*/
bool VehicleDataConvert::IsOnline(void)
{
    return f_vehicle_on;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DataRecvHandle
 * detail: Convert data from message buffer to std status
 -----------------------------------------------------------------------------------------------------------------*/
void VehicleDataConvert::DataRecvHandle(xpkg_comm::xmsg_comm_data data_recv)
{
    short temp;
    if(data_recv.id_c != 0x01) return;
    static double time_old = 0;
    m_vehicle_info.s_num = data_recv.id_n;
    m_vehicle_info.s_type = data_recv.id_t;    
    switch(data_recv.id_f)
    {
        /************************heart beat***************************************/
        case 0xB0:
            m_vehicle_info.s_dev_state = data_recv.data[0];
            f_vehicle_on = true;
        break;
        /************************firmware version***************************************/
        case 0xA2:
            m_vehicle_info.s_ver_hard = std::to_string(data_recv.data[3]) + std::to_string(data_recv.data[2]) + "." + std::to_string(data_recv.data[1]) + std::to_string(data_recv.data[0]);
            m_vehicle_info.s_ver_soft = std::to_string(data_recv.data[7]) + std::to_string(data_recv.data[6]) + "." + std::to_string(data_recv.data[5]) + std::to_string(data_recv.data[4]);
        break;
        /************************sys status***************************************/
        case 0xB1:
            m_vehicle_info.s_sys_state = data_recv.data[0];
            m_vehicle_info.s_sys_mode = data_recv.data[1];
            memcpy(&temp,&data_recv.data[2],2);
            m_vehicle_info.s_bat_vol = ((float)temp)/10;
            m_vehicle_info.s_beep_state = data_recv.data[4];
            m_vehicle_info.s_err_motor_current = data_recv.data[5] & 0x01;
            m_vehicle_info.s_err_motor_heat = (data_recv.data[5]>>1) & 0x01;
            m_vehicle_info.s_err_driver_heat = (data_recv.data[5]>>2) & 0x01;
            m_vehicle_info.s_err_bat_down = (data_recv.data[5]>>3) & 0x01;
            m_vehicle_info.s_err_bat_low = (data_recv.data[5]>>4) & 0x01;
            m_vehicle_info.s_err_ctrl_lost = (data_recv.data[5]>>5) & 0x01;
            m_vehicle_info.s_err_bump = (data_recv.data[5]>>6) & 0x01;

        break;
        /************************motion status***************************************/
        case 0xB2:
            memcpy(&m_vehicle_info.s_speed_x,&data_recv.data[0],2);
            memcpy(&m_vehicle_info.s_speed_y,&data_recv.data[2],2);
            memcpy(&m_vehicle_info.s_rotate,&data_recv.data[4],2);
            m_vehicle_info.time_interval = data_recv.time.toSec() - time_old;
            time_old = data_recv.time.toSec();
            //ROS_INFO("Time interval: %fs",m_vehicle_info.time_interval);
            //ROS_INFO("%d",(m_vehicle_info.s_speed_x));
        break;
        /************************main odom***************************************/
        case 0xB3:
            memcpy(&m_vehicle_info.s_odo_left,&data_recv.data[0],4);
            memcpy(&m_vehicle_info.s_odo_right,&data_recv.data[4],4);
        break;
        /************************secondary odom***************************************/
        case 0xB4:
            memcpy(&m_vehicle_info.s_odo_left_s,&data_recv.data[0],4);
            memcpy(&m_vehicle_info.s_odo_right_s,&data_recv.data[4],4);
        break;
        /************************ctrl status***************************************/
        case 0xB5:
            m_vehicle_info.s_ctrl_swa =data_recv.data[0] & 0x03;
            m_vehicle_info.s_ctrl_swb =(data_recv.data[0]>>2) & 0x03;
            m_vehicle_info.s_ctrl_swc =(data_recv.data[0]>>4) & 0x03;
            m_vehicle_info.s_ctrl_swd =(data_recv.data[0]>>6) & 0x03;
            m_vehicle_info.s_ctrl_left_h = data_recv.data[1];
            m_vehicle_info.s_ctrl_left_v = data_recv.data[2];
            m_vehicle_info.s_ctrl_right_h = data_recv.data[3];
            m_vehicle_info.s_ctrl_right_v = data_recv.data[4];
            m_vehicle_info.s_ctrl_left_vra = data_recv.data[5];
            m_vehicle_info.s_ctrl_right_vra = data_recv.data[6];
        break;
        /************************safety sensor***************************************/
        case 0xB6:
            for(int i=0;i<8;i++)
            {
                m_vehicle_info.s_bump[i] = (data_recv.data[0]>>i) & 0x01;
            }
            for(int j=1;j<7;j++)
            {
                m_vehicle_info.s_sonic[j-1] = data_recv.data[j];
            }
        break;
        /************************driver motion info***************************************/
        case 0xB7:
            memcpy(&m_vehicle_info.s_driver_speed[data_recv.data[0]],&data_recv.data[1],2);
            memcpy(&m_vehicle_info.s_driver_pulse[data_recv.data[0]],&data_recv.data[3],4);
        break;
        /************************driver status info***************************************/
        case 0xB8:
            memcpy(&temp,&data_recv.data[1],2);
            m_vehicle_info.s_driver_volt[data_recv.data[0]] = ((float)temp)/10;
            memcpy(&temp,&data_recv.data[3],2);
            m_vehicle_info.s_driver_current[data_recv.data[0]] = ((float)temp)/10;
            m_vehicle_info.s_driver_heat[data_recv.data[0]] = (char)(data_recv.data[5]);
            m_vehicle_info.s_motor_heat[data_recv.data[0]] = (char)(data_recv.data[6]);
            m_vehicle_info.s_driver_err_volt_low[data_recv.data[0]] = data_recv.data[7] & 0x01;
            m_vehicle_info.s_driver_err_heat_over[data_recv.data[0]] = (data_recv.data[7]>>1) & 0x01;
            m_vehicle_info.s_motor_err_current_over[data_recv.data[0]] = (data_recv.data[7]>>2) & 0x01;
            m_vehicle_info.s_motor_err_heat_over[data_recv.data[0]] = (data_recv.data[7]>>3) & 0x01;
        break;
        default:
        break;
    }
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleReset
 * detail: Vehicle reset CMD
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleReset()
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x01;
    order.len = 3;
    order.data[0] = 0x01;
    order.data[1] = m_vehicle_info.s_type;
    order.data[2] = m_vehicle_info.s_num;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleClear
 * detail: vehicle clear all error status
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleClear()
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x04;
    order.len = 1;
    order.data[0] = 0xCC;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleVersion
 * detail:Get vehicle version
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleVersion()
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x02;
    order.len = 0;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: VehicleSetState
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleSetState(bool state)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x03;
    order.len = 5;
    order.data[0] = 0x01;
    order.data[1] = m_vehicle_info.s_type;
    order.data[2] = m_vehicle_info.s_num;
    order.data[3] = state;
    order.data[4] = m_vehicle_info.s_num;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleZero
 * detail: Set motion data to zero
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleZero()
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x05;
    order.len = 1;
    order.data[0] = 0xCC;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleMode
 * detail: Set vehicle mode
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleMode(unsigned char mode,bool beep)
{
    if(mode > 2)mode = 0;
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x11;
    order.len = 2;
    order.data[0] = mode;
    order.data[1] = beep;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleMove
 * detail: send move CMD
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleMove(short speed_x, short speed_y, short rotate)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x12;
    order.len = 6;
    memcpy(&order.data[0],&speed_x,2);
    memcpy(&order.data[2],&speed_y,2);
    memcpy(&order.data[4],&rotate,2);
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleRemoterInfo
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleRemoterInfo(unsigned char state)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x15;
    order.len = 1;
    order.data[0] = state;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleSensorInfo
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleSensorInfo(unsigned char state)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x16;
    order.len = 1;
    order.data[0] = state;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleDriverMotion
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleDriverMotion(unsigned char state)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x17;
    order.len = 1;
    order.data[0] = state;
    return order;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: StdVehicleDriverState
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
xpkg_comm::xmsg_comm_data VehicleDataConvert::VehicleDriverState(unsigned char state)
{
    xpkg_comm::xmsg_comm_data order;
    order.id_c = 0x01;
    order.id_t = m_vehicle_info.s_type;
    order.id_n = m_vehicle_info.s_num;
    order.id_f = 0x18;
    order.len = 1;
    order.data[0] = state;
    return order;
}
