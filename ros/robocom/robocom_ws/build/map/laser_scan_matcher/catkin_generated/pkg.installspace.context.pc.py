# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;nodelet;sensor_msgs;tf;pcl_ros;pcl_conversions;geometry_msgs;nav_msgs".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-llaser_scan_matcher".split(';') if "-llaser_scan_matcher" != "" else []
PROJECT_NAME = "laser_scan_matcher"
PROJECT_SPACE_DIR = "/home/eaibot/robocom_ws/install"
PROJECT_VERSION = "0.3.2"
