# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "xpkg_comm: 3 messages, 0 services")

set(MSG_I_FLAGS "-Ixpkg_comm:/home/eaibot/robocom_ws/src/xpkg_comm/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(xpkg_comm_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_custom_target(_xpkg_comm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "xpkg_comm" "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" "xpkg_comm/xmsg_device"
)

get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_custom_target(_xpkg_comm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "xpkg_comm" "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" ""
)

get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_custom_target(_xpkg_comm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "xpkg_comm" "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg"
  "${MSG_I_FLAGS}"
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm
)
_generate_msg_cpp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm
)
_generate_msg_cpp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm
)

### Generating Services

### Generating Module File
_generate_module_cpp(xpkg_comm
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(xpkg_comm_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(xpkg_comm_generate_messages xpkg_comm_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_cpp _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_cpp _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_cpp _xpkg_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(xpkg_comm_gencpp)
add_dependencies(xpkg_comm_gencpp xpkg_comm_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS xpkg_comm_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg"
  "${MSG_I_FLAGS}"
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm
)
_generate_msg_eus(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm
)
_generate_msg_eus(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm
)

### Generating Services

### Generating Module File
_generate_module_eus(xpkg_comm
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(xpkg_comm_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(xpkg_comm_generate_messages xpkg_comm_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_eus _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_eus _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_eus _xpkg_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(xpkg_comm_geneus)
add_dependencies(xpkg_comm_geneus xpkg_comm_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS xpkg_comm_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg"
  "${MSG_I_FLAGS}"
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm
)
_generate_msg_lisp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm
)
_generate_msg_lisp(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm
)

### Generating Services

### Generating Module File
_generate_module_lisp(xpkg_comm
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(xpkg_comm_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(xpkg_comm_generate_messages xpkg_comm_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_lisp _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_lisp _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_lisp _xpkg_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(xpkg_comm_genlisp)
add_dependencies(xpkg_comm_genlisp xpkg_comm_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS xpkg_comm_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg"
  "${MSG_I_FLAGS}"
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm
)
_generate_msg_nodejs(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm
)
_generate_msg_nodejs(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm
)

### Generating Services

### Generating Module File
_generate_module_nodejs(xpkg_comm
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(xpkg_comm_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(xpkg_comm_generate_messages xpkg_comm_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_nodejs _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_nodejs _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_nodejs _xpkg_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(xpkg_comm_gennodejs)
add_dependencies(xpkg_comm_gennodejs xpkg_comm_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS xpkg_comm_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg"
  "${MSG_I_FLAGS}"
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm
)
_generate_msg_py(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm
)
_generate_msg_py(xpkg_comm
  "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm
)

### Generating Services

### Generating Module File
_generate_module_py(xpkg_comm
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(xpkg_comm_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(xpkg_comm_generate_messages xpkg_comm_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device_list.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_py _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_comm_data.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_py _xpkg_comm_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eaibot/robocom_ws/src/xpkg_comm/msg/xmsg_device.msg" NAME_WE)
add_dependencies(xpkg_comm_generate_messages_py _xpkg_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(xpkg_comm_genpy)
add_dependencies(xpkg_comm_genpy xpkg_comm_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS xpkg_comm_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/xpkg_comm
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/xpkg_comm
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/xpkg_comm
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/xpkg_comm
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/xpkg_comm
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
