// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sensor_msgs:msg/Temperature.idl
// generated code does not contain a copyright notice

#include "sensor_msgs/msg/detail/temperature__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
const rosidl_type_hash_t *
sensor_msgs__msg__Temperature__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x72, 0x51, 0x4a, 0x14, 0x12, 0x6a, 0xb9, 0xf8,
      0xa9, 0xab, 0xec, 0x97, 0x4c, 0x78, 0xe5, 0x61,
      0x0a, 0x36, 0x7b, 0x59, 0xdb, 0x5d, 0xa3, 0x55,
      0xff, 0x1f, 0xb9, 0x82, 0xd5, 0xba, 0xd4, 0xb8,
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

static char sensor_msgs__msg__Temperature__TYPE_NAME[] = "sensor_msgs/msg/Temperature";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char sensor_msgs__msg__Temperature__FIELD_NAME__header[] = "header";
static char sensor_msgs__msg__Temperature__FIELD_NAME__temperature[] = "temperature";
static char sensor_msgs__msg__Temperature__FIELD_NAME__variance[] = "variance";

static rosidl_runtime_c__type_description__Field sensor_msgs__msg__Temperature__FIELDS[] = {
  {
    {sensor_msgs__msg__Temperature__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__Temperature__FIELD_NAME__temperature, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__Temperature__FIELD_NAME__variance, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sensor_msgs__msg__Temperature__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
sensor_msgs__msg__Temperature__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sensor_msgs__msg__Temperature__TYPE_NAME, 27, 27},
      {sensor_msgs__msg__Temperature__FIELDS, 3, 3},
    },
    {sensor_msgs__msg__Temperature__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
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
  "# Single temperature reading.\n"
  "\n"
  "std_msgs/Header header # timestamp is the time the temperature was measured\n"
  "                             # frame_id is the location of the temperature reading\n"
  "\n"
  "float64 temperature          # Measurement of the Temperature in Degrees Celsius.\n"
  "\n"
  "float64 variance             # 0 is interpreted as variance unknown.";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sensor_msgs__msg__Temperature__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sensor_msgs__msg__Temperature__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 343, 343},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sensor_msgs__msg__Temperature__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sensor_msgs__msg__Temperature__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
