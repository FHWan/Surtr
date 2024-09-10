cmake_minimum_required(VERSION 3.0.2)
project(xpkg_comm)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
    FILES
    xmsg_comm_data.msg
    xmsg_device.msg
    xmsg_device_list.msg
)

#generate_messages必须在catkin_package前面
generate_messages(
 DEPENDENCIES
)

catkin_package(
CATKIN_DEPENDS
message_runtime
)

add_executable(xnode_comm
src/xnode_comm.cpp
src/CIF/comm_CIF_COM.cpp
src/DCM/comm_DCM_manage.cpp
)

include_directories(
include
include/CIF
include/DCM
  ${catkin_INCLUDE_DIRS}
)

target_link_libraries(xnode_comm
   ${catkin_LIBRARIES}
 )



