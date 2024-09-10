//////////////////////////////////////////////////
//xnode for vehicle control V2.0
//xpkg_vehicle
//////////////////////////////////////////////////
#include <ros/ros.h>
#include <xmsg_comm_data.h>
#include <vehicle_data_convert.h>
#include <vehicle_calc_odom.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>

///////////////////STD device info////////////////
static std::string arr_dev_list[] = {"ECHO-STD","ECHO-PRO","ECHO-PLUS",
                                     "YORK-SLD","YORK-MCNM","YORK-AKM",
                                     "MARK1-DIFF","MARK1-MCNM","MARK2-DIFF","MARK2-MCNM","MARK3-DIFF","MARK3-MCNM","RAY"};
static double arr_dev_wheel_track_list[] = {0.453,0.453,0.453,
                                            0.236,0.236,0.236,
                                            0.5,0.5,0.5,0.5,0.709,0.5};
///////////////////EX device info/////////////////
static std::string arr_dev_list_ex[] ={"AGILEX-SCOUTmini"};
static double arr_dev_wheel_track_list_ex[] = {0.500};
//////////////////////////////////////////////////

static vector<xpkg_comm::xmsg_comm_data> v_data_recv;
static xpkg_comm::xmsg_comm_data data_send;
static geometry_msgs::Twist data_vel;
static bool new_vel = false;

void DataRecvComm(const xpkg_comm::xmsg_comm_data& data)
{
    v_data_recv.push_back(data);
}

void RecvDataVel(const geometry_msgs::Twist& cmd_vel)
{
    data_vel = cmd_vel;
    new_vel = true;
    //ROS_INFO_STREAM(""<<cmd_vel);
}
/*------------------------------------------------------------------------------------------------------------------
 * name: main
 * detail:
 -----------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    //system("gnome-terminal -x bash -c 'source /opt/ros/melodic/setup.bash;roscore'&");
    ros::init(argc, argv, "xnode_vehicle");
    ros::NodeHandle xnode_vehicle("~");
    ros::Rate rate_ms(50);//20ms
    ros::Rate rate_s(1);//1s
    VehicleDataConvert vehicle_dc;
    VehicleCalcOdom vehicle_calc_odom;
    VehicleInfo vehicle_info;
    vector<unsigned char> send_buff;
    ros::Time current_time, last_time;
    tf::TransformBroadcaster odom_broadcaster;

    ros::Subscriber sub_turtle_vel = xnode_vehicle.subscribe("/turtle1/cmd_vel", 50, RecvDataVel);
    ros::Subscriber sub_vel = xnode_vehicle.subscribe("/cmd_vel", 50, RecvDataVel);
    ros::Subscriber sub_comm = xnode_vehicle.subscribe("/xtopic_comm/data_recv_vehicle", 1000, DataRecvComm);
    ros::Publisher pub_odom = xnode_vehicle.advertise<nav_msgs::Odometry>("/odom", 50);
    ros::Publisher pub_comm = xnode_vehicle.advertise<xpkg_comm::xmsg_comm_data>("/xtopic_comm/data_send", 50);


    bool loc_show = false;
    bool cal_speed = false;
    double rate_x = 1.0;
    double rate_y = 1.0;
    double rate_z = 1.0;
    double rate_az = 1.0;
    double wheel_track = 0.4;
    xnode_vehicle.param("loc_show", loc_show, false);
    xnode_vehicle.param("cal_speed", cal_speed, false);
    xnode_vehicle.param("rate_x", rate_x, 1.0);
    xnode_vehicle.param("rate_y", rate_y, 1.0);
    xnode_vehicle.param("rate_z", rate_z, 1.0);
    xnode_vehicle.param("rate_az", rate_az, 1.0);
    //vehicle online check////////////////////////////////////////////////////////
    while(ros::ok())
    {        
        rate_s.sleep();
        ros::spinOnce();
        while(v_data_recv.size())
        {
            vehicle_dc.DataRecvHandle(v_data_recv.at(0));
            v_data_recv.erase(v_data_recv.begin());
        }
        if(vehicle_dc.IsOnline())break;
        ROS_ERROR_ONCE("xnode_vehicle: Vehicle offline");
    }
    vehicle_info = vehicle_dc.GetVehicleInfo();
    if(vehicle_info.s_type > 0xa0)
    {
        ROS_INFO("\033[1;32mxnode_vehicle: %s online \033[0m",arr_dev_list_ex[vehicle_info.s_type - 0xa1].data());
        wheel_track = arr_dev_wheel_track_list_ex[vehicle_info.s_type - 0xa1];
    }
    else
    {
        ROS_INFO("\033[1;32mxnode_vehicle: %s online \033[0m",arr_dev_list[vehicle_info.s_type - 1].data());
        wheel_track = arr_dev_wheel_track_list[vehicle_info.s_type - 1];
    }
    //enable vehicle/////////////////////////////////////////////////
    while(ros::ok())
    {
        pub_comm.publish(vehicle_dc.VehicleSetState(1));
        rate_s.sleep();
        ros::spinOnce();
        while(v_data_recv.size() && ros::ok())
        {
            vehicle_dc.DataRecvHandle(v_data_recv.at(0));
            v_data_recv.erase(v_data_recv.begin());
        }
        vehicle_info = vehicle_dc.GetVehicleInfo();
        if(vehicle_info.s_dev_state)break;
        ROS_ERROR_ONCE("xnode_vehicle: Vehicle disable");
    }
    ROS_INFO("\033[1;32mxnode_vehicle: Vehicle enable \033[0m");
    //set parameter///////////////////////////////////////////////////
    pub_comm.publish(vehicle_dc.VehicleZero());
    pub_comm.publish(vehicle_dc.VehicleMode(MODE_CAN,BEEP_OFF));
    pub_comm.publish(vehicle_dc.VehicleRemoterInfo(0));
    pub_comm.publish(vehicle_dc.VehicleDriverState(0));
    pub_comm.publish(vehicle_dc.VehicleSensorInfo(0));
    pub_comm.publish(vehicle_dc.VehicleDriverMotion(0));
    //loop/////////////////////////////////////////////////////////////////////////////////////////////////////
    rate_s.sleep();
    ros::spinOnce();
    vehicle_calc_odom.ResetLocation();
    last_time = ros::Time::now();

    while (ros::ok())
    {
    current_time = ros::Time::now();
    //handle received data////////////////////////////////////////////
    while(v_data_recv.size() && ros::ok())
    {
        vehicle_dc.DataRecvHandle(v_data_recv.at(0));
        v_data_recv.erase(v_data_recv.begin());
    }
    vehicle_info = vehicle_dc.GetVehicleInfo();
    //send data///////////////////////////////////////////////////////
    if(new_vel)
    {
        pub_comm.publish(vehicle_dc.VehicleMove(data_vel.linear.x*1000*rate_x,data_vel.linear.y*1000*rate_y,data_vel.angular.z*1000*rate_z));
        new_vel = false;
    }    
    //calculate odom//////////////////////////////////////////////////
    if(cal_speed)vehicle_calc_odom.CalcWithSpeed((double)vehicle_info.s_speed_x/1000,(double)vehicle_info.s_speed_y/1000,(double)vehicle_info.s_rotate/1000,(current_time - last_time).toSec());
    else vehicle_calc_odom.CalcWithOdom((double)vehicle_info.s_odo_left/1000,(double)vehicle_info.s_odo_right/1000,(current_time - last_time).toSec(),(double)wheel_track);
    if(loc_show)vehicle_calc_odom.ShowLocation();
    //publish tf//////////////////////////////////////////////////////
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(vehicle_calc_odom.m_data_odom.th);
    geometry_msgs::TransformStamped odom_tf;
    odom_tf.header.stamp = current_time;
    odom_tf.header.frame_id = "odom";
    odom_tf.child_frame_id = "base_link";
    odom_tf.transform.translation.x = vehicle_calc_odom.m_data_odom.x;
    odom_tf.transform.translation.y = vehicle_calc_odom.m_data_odom.y;
    odom_tf.transform.translation.z = 0.0;
    odom_tf.transform.rotation = odom_quat;
    odom_broadcaster.sendTransform(odom_tf);
    //publish odom////////////////////////////////////////////////////
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    odom.pose.pose.position.x = vehicle_calc_odom.m_data_odom.x;
    odom.pose.pose.position.y = vehicle_calc_odom.m_data_odom.y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;
    odom.twist.twist.linear.x = vehicle_calc_odom.m_data_odom.vx;
    odom.twist.twist.linear.y = vehicle_calc_odom.m_data_odom.vy;
    odom.twist.twist.angular.z = vehicle_calc_odom.m_data_odom.vth;
    pub_odom.publish(odom);

    last_time = current_time;
    ros::spinOnce();
    rate_ms.sleep();
    }
}
