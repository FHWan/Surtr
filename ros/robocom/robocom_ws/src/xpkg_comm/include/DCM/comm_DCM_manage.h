#ifndef COMM_DCM_MANAGE_H
#define COMM_DCM_MANAGE_H
#include <ros/ros.h>
#include <string>
#include <vector>
#include <xmsg_device_list.h>

using namespace std;
//////////////////////////////////////////////////////////////////
#pragma pack(1)
struct t_DeviceInfo
{
    //vehicle info
    unsigned char s_class;
    unsigned char s_type;
    unsigned char s_number;
    unsigned char s_enable;
};
struct t_MsgCan
{
    unsigned char len;
    unsigned char id_c;
    unsigned char id_t;
    unsigned char id_n;
    unsigned char id_f;
    unsigned char data[8];
};
#pragma pack()
//////////////////////////////////////////////////////////////////
class CommDCMManage
{
public:
    explicit CommDCMManage(void);
    void DeviceListClear(void);
    void OnlineCheck(unsigned char c,unsigned char t,unsigned char n,unsigned char en);
    int RecvDataHandle(vector<unsigned char> data);
    static unsigned char DataCheckSum(unsigned char* data);
    void DevMsgEnable(bool en);

private:
    vector<unsigned char> m_data_recv;
    vector<t_DeviceInfo> m_device_list;
    xpkg_comm::xmsg_device_list msg_device_list;
    ros::Publisher pub_device_list;
    ros::Publisher pub_data_vehicle;
    ros::Publisher pub_data_arm;
    ros::Publisher pub_data_conveyer;

    ros::Publisher pub_data_driver;
    ros::Publisher pub_data_battery;
    ros::Publisher pub_data_comm;
    ros::Publisher pub_data_dist_sensor;
    ros::Publisher pub_data_line_sensor;

private:
    void DataConvert();
    void PubMessage(t_MsgCan can_data);
    bool dev_msg;

};

#endif // COMM_DCM_MANAGE_H
