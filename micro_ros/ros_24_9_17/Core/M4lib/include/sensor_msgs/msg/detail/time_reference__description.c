// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sensor_msgs:msg/TimeReference.idl
// generated code does not contain a copyright notice

#include "sensor_msgs/msg/detail/time_reference__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
const rosidl_type_hash_t *
sensor_msgs__msg__TimeReference__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdd, 0x66, 0xe8, 0x4c, 0xf4, 0x0b, 0xbb, 0x5d,
      0x5a, 0x40, 0x47, 0x2e, 0x6e, 0xcf, 0x26, 0x75,
      0xa0, 0x31, 0x33, 0x4d, 0x4c, 0x42, 0x6a, 0xbd,
      0xb2, 0xad, 0x41, 0x80, 0x1a, 0x8e, 0xfc, 0x99,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char sensor_msgs__msg__TimeReference__TYPE_NAME[] = "sensor_msgs/msg/TimeReference";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char sensor_msgs__msg__TimeReference__FIELD_NAME__header[] = "header";
static char sensor_msgs__msg__TimeReference__FIELD_NAME__time_ref[] = "time_ref";
static char sensor_msgs__msg__TimeReference__FIELD_NAME__source[] = "source";

static rosidl_runtime_c__type_description__Field sensor_msgs__msg__TimeReference__FIELDS[] = {
  {
    {sensor_msgs__msg__TimeReference__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__TimeReference__FIELD_NAME__time_ref, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__TimeReference__FIELD_NAME__source, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sensor_msgs__msg__TimeReference__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sensor_msgs__msg__TimeReference__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sensor_msgs__msg__TimeReference__TYPE_NAME, 29, 29},
      {sensor_msgs__msg__TimeReference__FIELDS, 3, 3},
    },
    {sensor_msgs__msg__TimeReference__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Measurement from an external time source not actively synchronized with the system clock.\n"
  "\n"
  "std_msgs/Header header      # stamp is system time for which measurement was valid\n"
  "                                  # frame_id is not used\n"
  "\n"
  "builtin_interfaces/Time time_ref  # corresponding time from this external source\n"
  "string source                     # (optional) name of time source";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sensor_msgs__msg__TimeReference__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sensor_msgs__msg__TimeReference__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 382, 382},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sensor_msgs__msg__TimeReference__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sensor_msgs__msg__TimeReference__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
