// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from test_msgs:action/NestedMessage.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
#include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "test_msgs/action/detail/nested_message__functions.h"
#include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `nested_field_no_pkg`
#include "test_msgs/msg/builtins.h"
// Member `nested_field_no_pkg`
#include "test_msgs/msg/detail/builtins__rosidl_typesupport_introspection_c.h"
// Member `nested_field`
#include "test_msgs/msg/basic_types.h"
// Member `nested_field`
#include "test_msgs/msg/detail/basic_types__rosidl_typesupport_introspection_c.h"
// Member `nested_different_pkg`
#include "builtin_interfaces/msg/time.h"
// Member `nested_different_pkg`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_Goal__init(message_memory);
}

void test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_member_array[3] = {
  {
    "nested_field_no_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Goal, nested_field_no_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_field",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Goal, nested_field),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_different_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Goal, nested_different_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_Goal",  // message name
  3,  // number of fields
  sizeof(test_msgs__action__NestedMessage_Goal),
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_member_array,  // message members
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_Goal__get_type_hash,
  &test_msgs__action__NestedMessage_Goal__get_type_description,
  &test_msgs__action__NestedMessage_Goal__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Goal)() {
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, Builtins)();
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, BasicTypes)();
  test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_Goal__rosidl_typesupport_introspection_c__NestedMessage_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `nested_field_no_pkg`
// already included above
// #include "test_msgs/msg/builtins.h"
// Member `nested_field_no_pkg`
// already included above
// #include "test_msgs/msg/detail/builtins__rosidl_typesupport_introspection_c.h"
// Member `nested_field`
// already included above
// #include "test_msgs/msg/basic_types.h"
// Member `nested_field`
// already included above
// #include "test_msgs/msg/detail/basic_types__rosidl_typesupport_introspection_c.h"
// Member `nested_different_pkg`
// already included above
// #include "builtin_interfaces/msg/time.h"
// Member `nested_different_pkg`
// already included above
// #include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_Result__init(message_memory);
}

void test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_member_array[3] = {
  {
    "nested_field_no_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Result, nested_field_no_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_field",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Result, nested_field),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_different_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Result, nested_different_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_Result",  // message name
  3,  // number of fields
  sizeof(test_msgs__action__NestedMessage_Result),
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_member_array,  // message members
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_Result__get_type_hash,
  &test_msgs__action__NestedMessage_Result__get_type_description,
  &test_msgs__action__NestedMessage_Result__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Result)() {
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, Builtins)();
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, BasicTypes)();
  test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_Result__rosidl_typesupport_introspection_c__NestedMessage_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `nested_field_no_pkg`
// already included above
// #include "test_msgs/msg/builtins.h"
// Member `nested_field_no_pkg`
// already included above
// #include "test_msgs/msg/detail/builtins__rosidl_typesupport_introspection_c.h"
// Member `nested_field`
// already included above
// #include "test_msgs/msg/basic_types.h"
// Member `nested_field`
// already included above
// #include "test_msgs/msg/detail/basic_types__rosidl_typesupport_introspection_c.h"
// Member `nested_different_pkg`
// already included above
// #include "builtin_interfaces/msg/time.h"
// Member `nested_different_pkg`
// already included above
// #include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_Feedback__init(message_memory);
}

void test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_member_array[3] = {
  {
    "nested_field_no_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Feedback, nested_field_no_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_field",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Feedback, nested_field),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nested_different_pkg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_Feedback, nested_different_pkg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_Feedback",  // message name
  3,  // number of fields
  sizeof(test_msgs__action__NestedMessage_Feedback),
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_member_array,  // message members
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_Feedback__get_type_hash,
  &test_msgs__action__NestedMessage_Feedback__get_type_description,
  &test_msgs__action__NestedMessage_Feedback__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Feedback)() {
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, Builtins)();
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, msg, BasicTypes)();
  test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_Feedback__rosidl_typesupport_introspection_c__NestedMessage_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "test_msgs/action/nested_message.h"
// Member `goal`
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_SendGoal_Request__init(message_memory);
}

void test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(test_msgs__action__NestedMessage_SendGoal_Request),
  test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_member_array,  // message members
  test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_SendGoal_Request__get_type_hash,
  &test_msgs__action__NestedMessage_SendGoal_Request__get_type_description,
  &test_msgs__action__NestedMessage_SendGoal_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Request)() {
  test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Goal)();
  if (!test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `stamp`
// already included above
// #include "builtin_interfaces/msg/time.h"
// Member `stamp`
// already included above
// #include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_SendGoal_Response__init(message_memory);
}

void test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(test_msgs__action__NestedMessage_SendGoal_Response),
  test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_member_array,  // message members
  test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_SendGoal_Response__get_type_hash,
  &test_msgs__action__NestedMessage_SendGoal_Response__get_type_description,
  &test_msgs__action__NestedMessage_SendGoal_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Response)() {
  test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "test_msgs/action/nested_message.h"
// Member `request`
// Member `response`
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_SendGoal_Event__init(message_memory);
}

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_SendGoal_Event__fini(message_memory);
}

size_t test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_SendGoal_Event__request(
  const void * untyped_member)
{
  const test_msgs__action__NestedMessage_SendGoal_Request__Sequence * member =
    (const test_msgs__action__NestedMessage_SendGoal_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__request(
  const void * untyped_member, size_t index)
{
  const test_msgs__action__NestedMessage_SendGoal_Request__Sequence * member =
    (const test_msgs__action__NestedMessage_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__request(
  void * untyped_member, size_t index)
{
  test_msgs__action__NestedMessage_SendGoal_Request__Sequence * member =
    (test_msgs__action__NestedMessage_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_SendGoal_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const test_msgs__action__NestedMessage_SendGoal_Request * item =
    ((const test_msgs__action__NestedMessage_SendGoal_Request *)
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__request(untyped_member, index));
  test_msgs__action__NestedMessage_SendGoal_Request * value =
    (test_msgs__action__NestedMessage_SendGoal_Request *)(untyped_value);
  *value = *item;
}

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_SendGoal_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  test_msgs__action__NestedMessage_SendGoal_Request * item =
    ((test_msgs__action__NestedMessage_SendGoal_Request *)
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__request(untyped_member, index));
  const test_msgs__action__NestedMessage_SendGoal_Request * value =
    (const test_msgs__action__NestedMessage_SendGoal_Request *)(untyped_value);
  *item = *value;
}

bool test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_SendGoal_Event__request(
  void * untyped_member, size_t size)
{
  test_msgs__action__NestedMessage_SendGoal_Request__Sequence * member =
    (test_msgs__action__NestedMessage_SendGoal_Request__Sequence *)(untyped_member);
  test_msgs__action__NestedMessage_SendGoal_Request__Sequence__fini(member);
  return test_msgs__action__NestedMessage_SendGoal_Request__Sequence__init(member, size);
}

size_t test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_SendGoal_Event__response(
  const void * untyped_member)
{
  const test_msgs__action__NestedMessage_SendGoal_Response__Sequence * member =
    (const test_msgs__action__NestedMessage_SendGoal_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__response(
  const void * untyped_member, size_t index)
{
  const test_msgs__action__NestedMessage_SendGoal_Response__Sequence * member =
    (const test_msgs__action__NestedMessage_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__response(
  void * untyped_member, size_t index)
{
  test_msgs__action__NestedMessage_SendGoal_Response__Sequence * member =
    (test_msgs__action__NestedMessage_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_SendGoal_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const test_msgs__action__NestedMessage_SendGoal_Response * item =
    ((const test_msgs__action__NestedMessage_SendGoal_Response *)
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__response(untyped_member, index));
  test_msgs__action__NestedMessage_SendGoal_Response * value =
    (test_msgs__action__NestedMessage_SendGoal_Response *)(untyped_value);
  *value = *item;
}

void test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_SendGoal_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  test_msgs__action__NestedMessage_SendGoal_Response * item =
    ((test_msgs__action__NestedMessage_SendGoal_Response *)
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__response(untyped_member, index));
  const test_msgs__action__NestedMessage_SendGoal_Response * value =
    (const test_msgs__action__NestedMessage_SendGoal_Response *)(untyped_value);
  *item = *value;
}

bool test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_SendGoal_Event__response(
  void * untyped_member, size_t size)
{
  test_msgs__action__NestedMessage_SendGoal_Response__Sequence * member =
    (test_msgs__action__NestedMessage_SendGoal_Response__Sequence *)(untyped_member);
  test_msgs__action__NestedMessage_SendGoal_Response__Sequence__fini(member);
  return test_msgs__action__NestedMessage_SendGoal_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Event, info),  // bytes offset in struct
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
    offsetof(test_msgs__action__NestedMessage_SendGoal_Event, request),  // bytes offset in struct
    NULL,  // default value
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_SendGoal_Event__request,  // size() function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__request,  // get_const(index) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__request,  // get(index) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_SendGoal_Event__request,  // fetch(index, &value) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_SendGoal_Event__request,  // assign(index, value) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_SendGoal_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_SendGoal_Event, response),  // bytes offset in struct
    NULL,  // default value
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_SendGoal_Event__response,  // size() function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_SendGoal_Event__response,  // get_const(index) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_SendGoal_Event__response,  // get(index) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_SendGoal_Event__response,  // fetch(index, &value) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_SendGoal_Event__response,  // assign(index, value) function pointer
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_SendGoal_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_SendGoal_Event",  // message name
  3,  // number of fields
  sizeof(test_msgs__action__NestedMessage_SendGoal_Event),
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_member_array,  // message members
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_SendGoal_Event__get_type_hash,
  &test_msgs__action__NestedMessage_SendGoal_Event__get_type_description,
  &test_msgs__action__NestedMessage_SendGoal_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Event)() {
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Request)();
  test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Response)();
  if (!test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_members = {
  "test_msgs__action",  // service namespace
  "NestedMessage_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle,
  NULL,  // response message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle
  NULL  // event_message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle
};


static rosidl_service_type_support_t test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_type_support_handle = {
  0,
  &test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_members,
  get_service_typesupport_handle_function,
  &test_msgs__action__NestedMessage_SendGoal_Request__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Request_message_type_support_handle,
  &test_msgs__action__NestedMessage_SendGoal_Response__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Response_message_type_support_handle,
  &test_msgs__action__NestedMessage_SendGoal_Event__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    test_msgs,
    action,
    NestedMessage_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    test_msgs,
    action,
    NestedMessage_SendGoal
  ),
  &test_msgs__action__NestedMessage_SendGoal__get_type_hash,
  &test_msgs__action__NestedMessage_SendGoal__get_type_description,
  &test_msgs__action__NestedMessage_SendGoal__get_type_description_sources,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Response)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Event)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal)() {
  if (!test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_type_support_handle.typesupport_identifier) {
    test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_SendGoal_Event)()->data;
  }

  return &test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_GetResult_Request__init(message_memory);
}

void test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(test_msgs__action__NestedMessage_GetResult_Request),
  test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_member_array,  // message members
  test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_GetResult_Request__get_type_hash,
  &test_msgs__action__NestedMessage_GetResult_Request__get_type_description,
  &test_msgs__action__NestedMessage_GetResult_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Request)() {
  test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "test_msgs/action/nested_message.h"
// Member `result`
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_GetResult_Response__init(message_memory);
}

void test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(test_msgs__action__NestedMessage_GetResult_Response),
  test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_member_array,  // message members
  test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_GetResult_Response__get_type_hash,
  &test_msgs__action__NestedMessage_GetResult_Response__get_type_description,
  &test_msgs__action__NestedMessage_GetResult_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Response)() {
  test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Result)();
  if (!test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/service_event_info.h"
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "test_msgs/action/nested_message.h"
// Member `request`
// Member `response`
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_GetResult_Event__init(message_memory);
}

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_GetResult_Event__fini(message_memory);
}

size_t test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_GetResult_Event__request(
  const void * untyped_member)
{
  const test_msgs__action__NestedMessage_GetResult_Request__Sequence * member =
    (const test_msgs__action__NestedMessage_GetResult_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__request(
  const void * untyped_member, size_t index)
{
  const test_msgs__action__NestedMessage_GetResult_Request__Sequence * member =
    (const test_msgs__action__NestedMessage_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__request(
  void * untyped_member, size_t index)
{
  test_msgs__action__NestedMessage_GetResult_Request__Sequence * member =
    (test_msgs__action__NestedMessage_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_GetResult_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const test_msgs__action__NestedMessage_GetResult_Request * item =
    ((const test_msgs__action__NestedMessage_GetResult_Request *)
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__request(untyped_member, index));
  test_msgs__action__NestedMessage_GetResult_Request * value =
    (test_msgs__action__NestedMessage_GetResult_Request *)(untyped_value);
  *value = *item;
}

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_GetResult_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  test_msgs__action__NestedMessage_GetResult_Request * item =
    ((test_msgs__action__NestedMessage_GetResult_Request *)
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__request(untyped_member, index));
  const test_msgs__action__NestedMessage_GetResult_Request * value =
    (const test_msgs__action__NestedMessage_GetResult_Request *)(untyped_value);
  *item = *value;
}

bool test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_GetResult_Event__request(
  void * untyped_member, size_t size)
{
  test_msgs__action__NestedMessage_GetResult_Request__Sequence * member =
    (test_msgs__action__NestedMessage_GetResult_Request__Sequence *)(untyped_member);
  test_msgs__action__NestedMessage_GetResult_Request__Sequence__fini(member);
  return test_msgs__action__NestedMessage_GetResult_Request__Sequence__init(member, size);
}

size_t test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_GetResult_Event__response(
  const void * untyped_member)
{
  const test_msgs__action__NestedMessage_GetResult_Response__Sequence * member =
    (const test_msgs__action__NestedMessage_GetResult_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__response(
  const void * untyped_member, size_t index)
{
  const test_msgs__action__NestedMessage_GetResult_Response__Sequence * member =
    (const test_msgs__action__NestedMessage_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__response(
  void * untyped_member, size_t index)
{
  test_msgs__action__NestedMessage_GetResult_Response__Sequence * member =
    (test_msgs__action__NestedMessage_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_GetResult_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const test_msgs__action__NestedMessage_GetResult_Response * item =
    ((const test_msgs__action__NestedMessage_GetResult_Response *)
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__response(untyped_member, index));
  test_msgs__action__NestedMessage_GetResult_Response * value =
    (test_msgs__action__NestedMessage_GetResult_Response *)(untyped_value);
  *value = *item;
}

void test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_GetResult_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  test_msgs__action__NestedMessage_GetResult_Response * item =
    ((test_msgs__action__NestedMessage_GetResult_Response *)
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__response(untyped_member, index));
  const test_msgs__action__NestedMessage_GetResult_Response * value =
    (const test_msgs__action__NestedMessage_GetResult_Response *)(untyped_value);
  *item = *value;
}

bool test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_GetResult_Event__response(
  void * untyped_member, size_t size)
{
  test_msgs__action__NestedMessage_GetResult_Response__Sequence * member =
    (test_msgs__action__NestedMessage_GetResult_Response__Sequence *)(untyped_member);
  test_msgs__action__NestedMessage_GetResult_Response__Sequence__fini(member);
  return test_msgs__action__NestedMessage_GetResult_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_GetResult_Event, info),  // bytes offset in struct
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
    offsetof(test_msgs__action__NestedMessage_GetResult_Event, request),  // bytes offset in struct
    NULL,  // default value
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_GetResult_Event__request,  // size() function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__request,  // get_const(index) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__request,  // get(index) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_GetResult_Event__request,  // fetch(index, &value) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_GetResult_Event__request,  // assign(index, value) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_GetResult_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_GetResult_Event, response),  // bytes offset in struct
    NULL,  // default value
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__size_function__NestedMessage_GetResult_Event__response,  // size() function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__NestedMessage_GetResult_Event__response,  // get_const(index) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__get_function__NestedMessage_GetResult_Event__response,  // get(index) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__NestedMessage_GetResult_Event__response,  // fetch(index, &value) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__NestedMessage_GetResult_Event__response,  // assign(index, value) function pointer
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__NestedMessage_GetResult_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_GetResult_Event",  // message name
  3,  // number of fields
  sizeof(test_msgs__action__NestedMessage_GetResult_Event),
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_member_array,  // message members
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_GetResult_Event__get_type_hash,
  &test_msgs__action__NestedMessage_GetResult_Event__get_type_description,
  &test_msgs__action__NestedMessage_GetResult_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Event)() {
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Request)();
  test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Response)();
  if (!test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_members = {
  "test_msgs__action",  // service namespace
  "NestedMessage_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle,
  NULL,  // response message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle
  NULL  // event_message
  // test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle
};


static rosidl_service_type_support_t test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_type_support_handle = {
  0,
  &test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_members,
  get_service_typesupport_handle_function,
  &test_msgs__action__NestedMessage_GetResult_Request__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Request_message_type_support_handle,
  &test_msgs__action__NestedMessage_GetResult_Response__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Response_message_type_support_handle,
  &test_msgs__action__NestedMessage_GetResult_Event__rosidl_typesupport_introspection_c__NestedMessage_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    test_msgs,
    action,
    NestedMessage_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    test_msgs,
    action,
    NestedMessage_GetResult
  ),
  &test_msgs__action__NestedMessage_GetResult__get_type_hash,
  &test_msgs__action__NestedMessage_GetResult__get_type_description,
  &test_msgs__action__NestedMessage_GetResult__get_type_description_sources,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Response)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Event)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult)() {
  if (!test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_type_support_handle.typesupport_identifier) {
    test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_GetResult_Event)()->data;
  }

  return &test_msgs__action__detail__nested_message__rosidl_typesupport_introspection_c__NestedMessage_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"
// already included above
// #include "test_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "test_msgs/action/detail/nested_message__functions.h"
// already included above
// #include "test_msgs/action/detail/nested_message__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "test_msgs/action/nested_message.h"
// Member `feedback`
// already included above
// #include "test_msgs/action/detail/nested_message__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  test_msgs__action__NestedMessage_FeedbackMessage__init(message_memory);
}

void test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_fini_function(void * message_memory)
{
  test_msgs__action__NestedMessage_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(test_msgs__action__NestedMessage_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_members = {
  "test_msgs__action",  // message namespace
  "NestedMessage_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(test_msgs__action__NestedMessage_FeedbackMessage),
  test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_member_array,  // message members
  test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_type_support_handle = {
  0,
  &test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
  &test_msgs__action__NestedMessage_FeedbackMessage__get_type_hash,
  &test_msgs__action__NestedMessage_FeedbackMessage__get_type_description,
  &test_msgs__action__NestedMessage_FeedbackMessage__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_test_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_FeedbackMessage)() {
  test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_msgs, action, NestedMessage_Feedback)();
  if (!test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &test_msgs__action__NestedMessage_FeedbackMessage__rosidl_typesupport_introspection_c__NestedMessage_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
