// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from std_msgs:msg/UInt8.idl
// generated code does not contain a copyright notice

#include "std_msgs/msg/detail/u_int8__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
const rosidl_type_hash_t *
std_msgs__msg__UInt8__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x61, 0x38, 0xbd, 0x83, 0xd8, 0xc3, 0x56, 0x9c,
      0xb8, 0x0a, 0x66, 0x7d, 0xb0, 0x3c, 0xfc, 0x16,
      0x29, 0xf5, 0x29, 0xfe, 0xe7, 0x9d, 0x94, 0x4c,
      0x39, 0xc3, 0x4e, 0x35, 0x2e, 0x72, 0xf0, 0x10,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char std_msgs__msg__UInt8__TYPE_NAME[] = "std_msgs/msg/UInt8";

// Define type names, field names, and default values
static char std_msgs__msg__UInt8__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field std_msgs__msg__UInt8__FIELDS[] = {
  {
    {std_msgs__msg__UInt8__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
std_msgs__msg__UInt8__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {std_msgs__msg__UInt8__TYPE_NAME, 18, 18},
      {std_msgs__msg__UInt8__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# This was originally provided as an example message.\n"
  "# It is deprecated as of Foxy\n"
  "# It is recommended to create your own semantically meaningful message.\n"
  "# However if you would like to continue using this please use the equivalent in example_msgs.\n"
  "\n"
  "uint8 data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
std_msgs__msg__UInt8__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {std_msgs__msg__UInt8__TYPE_NAME, 18, 18},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 262, 262},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
std_msgs__msg__UInt8__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *std_msgs__msg__UInt8__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
