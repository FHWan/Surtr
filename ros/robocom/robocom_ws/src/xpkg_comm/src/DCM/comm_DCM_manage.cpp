#include <comm_DCM_manage.h>
#include <string>
#include <vector>
#include <ros/ros.h>
#include <xmsg_device.h>
#include <xmsg_comm_data.h>

CommDCMManage::CommDCMManage()
{
    m_data_recv.clear();
    m_device_list.clear();
    dev_msg = false;
    ros::NodeHandle xnode_comm_DCM;
    //topic of device list////////////////////////////////////
    pub_device_list = xnode_comm_DCM.advertise<xpkg_comm::xmsg_device_list>("/xtopic_comm/device_list", 50);
    //topic of device////////////////////////////////////
    pub_data_vehicle = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_vehicle", 50);
    pub_data_arm = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_arm", 50);
    pub_data_conveyer = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_conveyer", 50);
    pub_data_driver = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_driver", 50);
    pub_data_battery = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_battery", 50);
    pub_data_comm = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_comm", 50);
    pub_data_dist_sensor = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_dist_sensor", 50);
    pub_data_line_sensor = xnode_comm_DCM.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_recv_line_sensor", 50);

}
/*------------------------------------------------------------------------------------------------------------------
 * name: RecvDataHandle
 * detail: Save data to buffer and convert
 -----------------------------------------------------------------------------------------------------------------*/
int CommDCMManage::RecvDataHandle(vector<unsigned char> data)
{
    int count;
    if(data.size() == 0) return 0;
    m_data_recv.insert(m_data_recv.end(),data.begin(),data.end());
    count = m_data_recv.size();
    this->DataConvert();
    if(m_data_recv.size() > 1000)m_data_recv.clear();
    return count;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DeviceListClear
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
void CommDCMManage::DeviceListClear(void)
{
    m_device_list.clear();
    msg_device_list.dev_count = 0;
    msg_device_list.dev_list.clear();
    pub_device_list.publish(msg_device_list);
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DevMsgEnable
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
void CommDCMManage::DevMsgEnable(bool en)
{
    if(en)dev_msg = true;
    else dev_msg = false;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: OnlineCheak
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
void CommDCMManage::OnlineCheck(unsigned char c,unsigned char t,unsigned char n,unsigned char en)
{
    int i;
    for(i=0;i<m_device_list.size();i++)
    {
        if(m_device_list.at(i).s_class == c && m_device_list.at(i).s_type == t && m_device_list.at(i).s_number == n)
        {
            if(m_device_list.at(i).s_enable == en)return;
            m_device_list.at(i).s_enable = en;
            msg_device_list.dev_list.at(i).dev_enable = en;
            pub_device_list.publish(msg_device_list);
            if(dev_msg == false) return;
            ROS_INFO("\033[1;34mxnode_comm: New device list \033[0m");
            for(i=0;i<m_device_list.size();i++)
            {
                ROS_INFO("\033[1;34mNo.%d --- class:%d type:%d number:%d enable:%d \033[0m",
                i+1,m_device_list.at(i).s_class,m_device_list.at(i).s_type,m_device_list.at(i).s_number,m_device_list.at(i).s_enable);
            }
            return;
        }
    }
    //new device///////////////////////////////////////////
    t_DeviceInfo buffer = {c,t,n,en};
    xpkg_comm::xmsg_device msg_device;

    m_device_list.push_back(buffer);
    msg_device_list.dev_count++;
    msg_device.dev_class =c;
    msg_device.dev_number =n;
    msg_device.dev_type =t;
    msg_device.dev_enable =en;
    msg_device_list.dev_list.push_back(msg_device);
    pub_device_list.publish(msg_device_list);
    if(dev_msg == false) return;
    ROS_INFO("\033[1;34mxnode_comm: New device list \033[0m");
    for(i=0;i<m_device_list.size();i++)
    {
        ROS_INFO("\033[1;34mNo.%d --- class:%d type:%d number:%d enable:%d \033[0m",
        i+1,m_device_list.at(i).s_class,m_device_list.at(i).s_type,m_device_list.at(i).s_number,m_device_list.at(i).s_enable);
    }
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DataCheckSum
 * detail: Sum all byte and check
 -----------------------------------------------------------------------------------------------------------------*/
 unsigned char CommDCMManage::DataCheckSum(unsigned char* data)
{
    unsigned char checksum = 0x00;
    for(int i = 0 ; i < data[1] - 1; i++)
    {
        checksum += data[i];
    }
    return checksum;
}
/*------------------------------------------------------------------------------------------------------------------
* name: DataConvertManager
* detail:
-----------------------------------------------------------------------------------------------------------------*/
void CommDCMManage::DataConvert()
{
    static unsigned int data_err_count = 0;
    t_MsgCan can_buff;
    int i;
    if(m_data_recv.size() < 8)return;   //too short data
    for(i=0;i<m_data_recv.size();i++)
    {
        if(m_data_recv.size()-i <8)break;
        if(m_data_recv.at(i) != 0x55 || m_data_recv.at(i+1) <8 || m_data_recv.at(i+1) >16)continue;  //head cheak
        if(m_data_recv.size()-i < m_data_recv.at(i+1))break;//broken data
        if(DataCheckSum(m_data_recv.data()+i) != m_data_recv.at(i + m_data_recv.at(i+1)-1))   //sum cheak
        {
            i += m_data_recv.at(i+1)-1;
            data_err_count++;
            ROS_ERROR("xnode_comm : receive data error No.%d",data_err_count);
            if(data_err_count>10000)data_err_count = 0;
            continue;
        }

        memset(&can_buff,0,sizeof(can_buff));
        can_buff.len = m_data_recv.at(i+1)-8;
        memcpy(&can_buff.id_c,m_data_recv.data()+i+2,4);
        memcpy(can_buff.data,m_data_recv.data()+i+6,can_buff.len);
        i += m_data_recv.at(i+1)-1;

        this->PubMessage(can_buff);

    }
    if(m_data_recv.size()>0)m_data_recv.erase(m_data_recv.begin(),m_data_recv.begin()+i);
}
/*------------------------------------------------------------------------------------------------------------------
* name: PubMessage
* detail:
-----------------------------------------------------------------------------------------------------------------*/
void CommDCMManage::PubMessage(t_MsgCan can_data)
{
    xpkg_comm::xmsg_comm_data comm_msg;
    comm_msg.id_c = can_data.id_c;
    comm_msg.id_t = can_data.id_t;
    comm_msg.id_n =can_data.id_n;
    comm_msg.id_f = can_data.id_f;
    comm_msg.len = can_data.len;
    memcpy(comm_msg.data.data(),&can_data.data[0],8);
    comm_msg.time = ros::Time::now();
    if(can_data.id_f == 0xB0)OnlineCheck(can_data.id_c,can_data.id_t,can_data.id_n,can_data.data[0]);
    switch(can_data.id_c)
    {
        case 1:
            pub_data_vehicle.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 2:
            pub_data_arm.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 3:
            pub_data_conveyer.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 4:
            break;
        case 5:
            pub_data_driver.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 6:
            pub_data_battery.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 7:
            pub_data_comm.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 8:
            pub_data_dist_sensor.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        case 9:
            pub_data_line_sensor.publish(comm_msg);
            //ROS_INFO_STREAM(""<<comm_msg);
            break;
        default:break;


    }
}
