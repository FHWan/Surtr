// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rcl_interfaces:srv/SetLoggerLevels.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rcl_interfaces/srv/detail/set_logger_levels__rosidl_typesupport_introspection_c.h"
#include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rcl_interfaces/srv/detail/set_logger_levels__functions.h"
#include "rcl_interfaces/srv/detail/set_logger_levels__struct.h"


// Include directives for member types
// Member `levels`
#include "rcl_interfaces/msg/logger_level.h"
// Member `levels`
#include "rcl_interfaces/msg/detail/logger_level__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetLoggerLevels_Request__init(message_memory);
}

void rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetLoggerLevels_Request__fini(message_memory);
}

size_t rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Request__levels(
  const void * untyped_member)
{
  const rcl_interfaces__msg__LoggerLevel__Sequence * member =
    (const rcl_interfaces__msg__LoggerLevel__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Request__levels(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__msg__LoggerLevel__Sequence * member =
    (const rcl_interfaces__msg__LoggerLevel__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Request__levels(
  void * untyped_member, size_t index)
{
  rcl_interfaces__msg__LoggerLevel__Sequence * member =
    (rcl_interfaces__msg__LoggerLevel__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Request__levels(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__msg__LoggerLevel * item =
    ((const rcl_interfaces__msg__LoggerLevel *)
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Request__levels(untyped_member, index));
  rcl_interfaces__msg__LoggerLevel * value =
    (rcl_interfaces__msg__LoggerLevel *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Request__levels(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__msg__LoggerLevel * item =
    ((rcl_interfaces__msg__LoggerLevel *)
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Request__levels(untyped_member, index));
  const rcl_interfaces__msg__LoggerLevel * value =
    (const rcl_interfaces__msg__LoggerLevel *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Request__levels(
  void * untyped_member, size_t size)
{
  rcl_interfaces__msg__LoggerLevel__Sequence * member =
    (rcl_interfaces__msg__LoggerLevel__Sequence *)(untyped_member);
  rcl_interfaces__msg__LoggerLevel__Sequence__fini(member);
  return rcl_interfaces__msg__LoggerLevel__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_member_array[1] = {
  {
    "levels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetLoggerLevels_Request, levels),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Request__levels,  // size() function pointer
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Request__levels,  // get_const(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Request__levels,  // get(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Request__levels,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Request__levels,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Request__levels  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetLoggerLevels_Request",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetLoggerLevels_Request),
  rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_member_array,  // message members
  rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetLoggerLevels_Request__get_type_hash,
  &rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description,
  &rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Request)() {
  rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, LoggerLevel)();
  if (!rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__functions.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__struct.h"


// Include directives for member types
// Member `results`
#include "rcl_interfaces/msg/set_logger_levels_result.h"
// Member `results`
#include "rcl_interfaces/msg/detail/set_logger_levels_result__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetLoggerLevels_Response__init(message_memory);
}

void rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetLoggerLevels_Response__fini(message_memory);
}

size_t rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Response__results(
  const void * untyped_member)
{
  const rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * member =
    (const rcl_interfaces__msg__SetLoggerLevelsResult__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Response__results(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * member =
    (const rcl_interfaces__msg__SetLoggerLevelsResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Response__results(
  void * untyped_member, size_t index)
{
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * member =
    (rcl_interfaces__msg__SetLoggerLevelsResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Response__results(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__msg__SetLoggerLevelsResult * item =
    ((const rcl_interfaces__msg__SetLoggerLevelsResult *)
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Response__results(untyped_member, index));
  rcl_interfaces__msg__SetLoggerLevelsResult * value =
    (rcl_interfaces__msg__SetLoggerLevelsResult *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Response__results(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__msg__SetLoggerLevelsResult * item =
    ((rcl_interfaces__msg__SetLoggerLevelsResult *)
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Response__results(untyped_member, index));
  const rcl_interfaces__msg__SetLoggerLevelsResult * value =
    (const rcl_interfaces__msg__SetLoggerLevelsResult *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Response__results(
  void * untyped_member, size_t size)
{
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * member =
    (rcl_interfaces__msg__SetLoggerLevelsResult__Sequence *)(untyped_member);
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence__fini(member);
  return rcl_interfaces__msg__SetLoggerLevelsResult__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_member_array[1] = {
  {
    "results",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetLoggerLevels_Response, results),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Response__results,  // size() function pointer
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Response__results,  // get_const(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Response__results,  // get(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Response__results,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Response__results,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Response__results  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetLoggerLevels_Response",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetLoggerLevels_Response),
  rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_member_array,  // message members
  rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetLoggerLevels_Response__get_type_hash,
  &rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description,
  &rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Response)() {
  rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, SetLoggerLevelsResult)();
  if (!rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__functions.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "rcl_interfaces/srv/set_logger_levels.h"
// Member `request`
// Member `response`
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetLoggerLevels_Event__init(message_memory);
}

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetLoggerLevels_Event__fini(message_memory);
}

size_t rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Event__request(
  const void * untyped_member)
{
  const rcl_interfaces__srv__SetLoggerLevels_Request__Sequence * member =
    (const rcl_interfaces__srv__SetLoggerLevels_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__request(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__srv__SetLoggerLevels_Request__Sequence * member =
    (const rcl_interfaces__srv__SetLoggerLevels_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__request(
  void * untyped_member, size_t index)
{
  rcl_interfaces__srv__SetLoggerLevels_Request__Sequence * member =
    (rcl_interfaces__srv__SetLoggerLevels_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__srv__SetLoggerLevels_Request * item =
    ((const rcl_interfaces__srv__SetLoggerLevels_Request *)
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__request(untyped_member, index));
  rcl_interfaces__srv__SetLoggerLevels_Request * value =
    (rcl_interfaces__srv__SetLoggerLevels_Request *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__srv__SetLoggerLevels_Request * item =
    ((rcl_interfaces__srv__SetLoggerLevels_Request *)
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__request(untyped_member, index));
  const rcl_interfaces__srv__SetLoggerLevels_Request * value =
    (const rcl_interfaces__srv__SetLoggerLevels_Request *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Event__request(
  void * untyped_member, size_t size)
{
  rcl_interfaces__srv__SetLoggerLevels_Request__Sequence * member =
    (rcl_interfaces__srv__SetLoggerLevels_Request__Sequence *)(untyped_member);
  rcl_interfaces__srv__SetLoggerLevels_Request__Sequence__fini(member);
  return rcl_interfaces__srv__SetLoggerLevels_Request__Sequence__init(member, size);
}

size_t rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Event__response(
  const void * untyped_member)
{
  const rcl_interfaces__srv__SetLoggerLevels_Response__Sequence * member =
    (const rcl_interfaces__srv__SetLoggerLevels_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__response(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__srv__SetLoggerLevels_Response__Sequence * member =
    (const rcl_interfaces__srv__SetLoggerLevels_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__response(
  void * untyped_member, size_t index)
{
  rcl_interfaces__srv__SetLoggerLevels_Response__Sequence * member =
    (rcl_interfaces__srv__SetLoggerLevels_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__srv__SetLoggerLevels_Response * item =
    ((const rcl_interfaces__srv__SetLoggerLevels_Response *)
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__response(untyped_member, index));
  rcl_interfaces__srv__SetLoggerLevels_Response * value =
    (rcl_interfaces__srv__SetLoggerLevels_Response *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__srv__SetLoggerLevels_Response * item =
    ((rcl_interfaces__srv__SetLoggerLevels_Response *)
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__response(untyped_member, index));
  const rcl_interfaces__srv__SetLoggerLevels_Response * value =
    (const rcl_interfaces__srv__SetLoggerLevels_Response *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Event__response(
  void * untyped_member, size_t size)
{
  rcl_interfaces__srv__SetLoggerLevels_Response__Sequence * member =
    (rcl_interfaces__srv__SetLoggerLevels_Response__Sequence *)(untyped_member);
  rcl_interfaces__srv__SetLoggerLevels_Response__Sequence__fini(member);
  return rcl_interfaces__srv__SetLoggerLevels_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetLoggerLevels_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces__srv__SetLoggerLevels_Event, request),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Event__request,  // size() function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__request,  // get_const(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__request,  // get(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Event__request,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Event__request,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces__srv__SetLoggerLevels_Event, response),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__size_function__SetLoggerLevels_Event__response,  // size() function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_const_function__SetLoggerLevels_Event__response,  // get_const(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__get_function__SetLoggerLevels_Event__response,  // get(index) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__fetch_function__SetLoggerLevels_Event__response,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__assign_function__SetLoggerLevels_Event__response,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__resize_function__SetLoggerLevels_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetLoggerLevels_Event",  // message name
  3,  // number of fields
  sizeof(rcl_interfaces__srv__SetLoggerLevels_Event),
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_member_array,  // message members
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetLoggerLevels_Event__get_type_hash,
  &rcl_interfaces__srv__SetLoggerLevels_Event__get_type_description,
  &rcl_interfaces__srv__SetLoggerLevels_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Event)() {
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Request)();
  rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Response)();
  if (!rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_logger_levels__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_members = {
  "rcl_interfaces__srv",  // service namespace
  "SetLoggerLevels",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle,
  NULL,  // response message
  // rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle
  NULL  // event_message
  // rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle
};


static rosidl_service_type_support_t rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_type_support_handle = {
  0,
  &rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_members,
  get_service_typesupport_handle_function,
  &rcl_interfaces__srv__SetLoggerLevels_Request__rosidl_typesupport_introspection_c__SetLoggerLevels_Request_message_type_support_handle,
  &rcl_interfaces__srv__SetLoggerLevels_Response__rosidl_typesupport_introspection_c__SetLoggerLevels_Response_message_type_support_handle,
  &rcl_interfaces__srv__SetLoggerLevels_Event__rosidl_typesupport_introspection_c__SetLoggerLevels_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rcl_interfaces,
    srv,
    SetLoggerLevels
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rcl_interfaces,
    srv,
    SetLoggerLevels
  ),
  &rcl_interfaces__srv__SetLoggerLevels__get_type_hash,
  &rcl_interfaces__srv__SetLoggerLevels__get_type_description,
  &rcl_interfaces__srv__SetLoggerLevels__get_type_description_sources,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Response)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Event)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels)() {
  if (!rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetLoggerLevels_Event)()->data;
  }

  return &rcl_interfaces__srv__detail__set_logger_levels__rosidl_typesupport_introspection_c__SetLoggerLevels_service_type_support_handle;
}
