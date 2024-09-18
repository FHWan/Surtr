// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from type_description_interfaces:msg/Field.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "type_description_interfaces/msg/detail/field__rosidl_typesupport_introspection_c.h"
#include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "type_description_interfaces/msg/detail/field__functions.h"
#include "type_description_interfaces/msg/detail/field__struct.h"


// Include directives for member types
// Member `name`
// Member `default_value`
#include "rosidl_runtime_c/string_functions.h"
// Member `type`
#include "type_description_interfaces/msg/field_type.h"
// Member `type`
#include "type_description_interfaces/msg/detail/field_type__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__msg__Field__init(message_memory);
}

void type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_fini_function(void * message_memory)
{
  type_description_interfaces__msg__Field__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_member_array[3] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__Field, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__Field, type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "default_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__Field, default_value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_members = {
  "type_description_interfaces__msg",  // message namespace
  "Field",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces__msg__Field),
  type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_member_array,  // message members
  type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_type_support_handle = {
  0,
  &type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__Field__get_type_hash,
  &type_description_interfaces__msg__Field__get_type_description,
  &type_description_interfaces__msg__Field__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, Field)() {
  type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, FieldType)();
  if (!type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__msg__Field__rosidl_typesupport_introspection_c__Field_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
