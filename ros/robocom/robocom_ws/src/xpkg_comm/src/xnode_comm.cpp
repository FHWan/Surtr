//////////////////////////////////////////////////
//xnode for communication V2.0
//xpkg_comm
//////////////////////////////////////////////////
#include <ros/ros.h>
#include <comm_CIF_COM.h>
#include <comm_DCM_manage.h>
#include <xmsg_comm_data.h>
#include <xmsg_device.h>

static vector<unsigned char> data_send;
static vector<unsigned char> data_recv;
/*------------------------------------------------------------------------------------------------------------------
 * name: SendDataCOM
 * detail: receive COM data from topic and send out
 -----------------------------------------------------------------------------------------------------------------*/
void SendDataCOM(const xpkg_comm::xmsg_comm_data& data_com)
{
    unsigned char buff[16];
    buff[0] = 0x55;
    buff[1] = data_com.len+8;
    buff[2] = data_com.id_c;
    buff[3] = data_com.id_t;
    buff[4] = data_com.id_n;
    buff[5] = data_com.id_f;
    memcpy(&buff[6],data_com.data.data(),data_com.len);
    buff[data_com.len+6] = 0x01;
    buff[data_com.len+7] = 0;
    for(int i = 0 ; i < data_com.len+7; i++)
    {
        buff[data_com.len+7] += buff[i];        
    }
    for(int i=0;i<data_com.len+8;i++)
    {
        data_send.push_back(buff[i]);
        //ROS_INFO("%d",(buff[i]));
    }

}
/*------------------------------------------------------------------------------------------------------------------
 * name: main
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    //system("gnome-terminal -x bash -c 'source /opt/ros/melodic/setup.bash;roscore'&");
    ros::init(argc, argv, "xnode_comm");
    ros::NodeHandle xnode_comm("~");
    ros::Rate rate_ms(50);//20ms 50Hz
    ros::Rate rate_s(1);//1s
    int com_enable = 0;
    int tcp_enable = 0;
    bool dev_msg = false;
    static int disconnect_count = 0;
    CommCIFCOM m_comm_CIF_COM;
    CommDCMManage m_comm_DCM;

    ros::Subscriber sub_comm_COM = xnode_comm.subscribe("/xtopic_comm/data_send", 1000, SendDataCOM);
    xnode_comm.param("com_enable", com_enable, 1);
    xnode_comm.param("tcp_enable", tcp_enable, 0);
    xnode_comm.param("dev_msg", dev_msg, false);

    m_comm_DCM.DevMsgEnable(dev_msg);
    //cheak interface//////////////////////////////////////////////////////////////////////
    if(!(com_enable | tcp_enable))
    {
        ROS_ERROR("xnode_comm : All communication interface is closed,please enable one");
        ROS_ERROR("xnode_comm : Xnode close");
        return 0;
    }
    //wait COM open//////////////////////////////////////////////////////////////////////
    if(com_enable && ros::ok())
    {
        while(!m_comm_CIF_COM.COMIsOpen() && ros::ok())
        {
            m_comm_CIF_COM.COMInitDefault();
            rate_s.sleep();
        }
        ROS_INFO("\033[1;32mxnode_comm : COM open successfully \033[0m");
    }
    //wait TCP open//////////////////////////////////////////////////////////////////////
    if(tcp_enable && ros::ok())
    {

    }
    //loop////////////////////////////////////////////////////////////////////////
    while (ros::ok())
    {
        while(m_comm_CIF_COM.COMIsOpen() == false && com_enable && ros::ok()) //reboot COM
        {
            if(m_comm_CIF_COM.COMInitDefault())ROS_INFO("\033[1;32mxnode_comm : COM open successfully \033[0m");
            rate_s.sleep();
        }

        //send com data/////////////////////////////////////////////////////////////
        //ROS_INFO("send data: %d",data_send.size());
        m_comm_CIF_COM.COMDataSend(data_send);
        data_send.clear();

        //handle received com data//////////////////////////////////////////////////
        if(!m_comm_DCM.RecvDataHandle(m_comm_CIF_COM.COMDataRecv()))disconnect_count++;
        else disconnect_count =0;
        if(disconnect_count>200)  //no data check
        {
            m_comm_CIF_COM.COMClose();
            disconnect_count = 0;
            m_comm_DCM.DeviceListClear();
            ROS_ERROR("xnode_comm: COM disconnect because of no data");
        }
        //ROS_INFO_STREAM(""<<disconnect_count);

        ros::spinOnce();
        rate_ms.sleep();
    }
}
