// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rcl_interfaces:srv/SetLoggerLevels.idl
// generated code does not contain a copyright notice

#include "rcl_interfaces/srv/detail/set_logger_levels__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__srv__SetLoggerLevels__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3f, 0xf8, 0x6c, 0xb4, 0xe9, 0x1f, 0xbf, 0x9a,
      0xba, 0xe1, 0x5c, 0x23, 0x4e, 0xcc, 0x87, 0x44,
      0x48, 0xde, 0x6e, 0xce, 0x8e, 0x19, 0x34, 0x01,
      0xc0, 0x77, 0xcf, 0x11, 0x6e, 0x4f, 0x6d, 0x78,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__srv__SetLoggerLevels_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4e, 0x77, 0x68, 0xe0, 0xf4, 0xc7, 0x49, 0x20,
      0x5f, 0x35, 0xbc, 0x05, 0x44, 0x9f, 0x83, 0xfa,
      0xd1, 0x8c, 0x42, 0xde, 0x52, 0xc1, 0x6b, 0x19,
      0x34, 0xd6, 0x6c, 0x2f, 0x68, 0xff, 0xd8, 0x62,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__srv__SetLoggerLevels_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xba, 0x51, 0x73, 0x90, 0x27, 0xe5, 0x7c, 0xb9,
      0x12, 0x00, 0x15, 0x73, 0x7f, 0x46, 0x18, 0x57,
      0x96, 0x84, 0x04, 0x7d, 0x86, 0x2b, 0x2b, 0x16,
      0xa7, 0x6b, 0xc3, 0x99, 0xd9, 0x87, 0xd6, 0xd3,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__srv__SetLoggerLevels_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xce, 0x7d, 0x56, 0x3c, 0x54, 0xed, 0xbf, 0xf5,
      0xad, 0xdf, 0xea, 0x9a, 0xe8, 0xf8, 0xbc, 0xb7,
      0xba, 0x75, 0x56, 0x73, 0xcd, 0xc0, 0x76, 0x10,
      0x64, 0xec, 0x0d, 0x4a, 0xdf, 0x18, 0xb6, 0xd9,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "rcl_interfaces/msg/detail/logger_level__functions.h"
#include "rcl_interfaces/msg/detail/set_logger_levels_result__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__LoggerLevel__EXPECTED_HASH = {1, {
    0x95, 0x78, 0x5c, 0xc4, 0x2f, 0x04, 0x8a, 0xb4,
    0xf3, 0x95, 0xaf, 0x65, 0x03, 0x5a, 0xea, 0xf2,
    0x18, 0x1d, 0x8e, 0x1c, 0x7a, 0x44, 0xed, 0xb8,
    0xad, 0x45, 0x58, 0x44, 0x5f, 0xdb, 0x43, 0xc0,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__SetLoggerLevelsResult__EXPECTED_HASH = {1, {
    0x93, 0x16, 0xe5, 0xe6, 0x79, 0xa5, 0xb7, 0x2d,
    0x2d, 0xd7, 0xfd, 0x80, 0xc5, 0x39, 0xba, 0xe9,
    0xe1, 0x06, 0xfa, 0x08, 0x90, 0xa0, 0x6d, 0xc5,
    0xda, 0x3a, 0x81, 0x77, 0xa3, 0xff, 0x69, 0x09,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char rcl_interfaces__srv__SetLoggerLevels__TYPE_NAME[] = "rcl_interfaces/srv/SetLoggerLevels";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rcl_interfaces__msg__LoggerLevel__TYPE_NAME[] = "rcl_interfaces/msg/LoggerLevel";
static char rcl_interfaces__msg__SetLoggerLevelsResult__TYPE_NAME[] = "rcl_interfaces/msg/SetLoggerLevelsResult";
static char rcl_interfaces__srv__SetLoggerLevels_Event__TYPE_NAME[] = "rcl_interfaces/srv/SetLoggerLevels_Event";
static char rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME[] = "rcl_interfaces/srv/SetLoggerLevels_Request";
static char rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME[] = "rcl_interfaces/srv/SetLoggerLevels_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__request_message[] = "request_message";
static char rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__response_message[] = "response_message";
static char rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field rcl_interfaces__srv__SetLoggerLevels__FIELDS[] = {
  {
    {rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rcl_interfaces__srv__SetLoggerLevels_Event__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rcl_interfaces__srv__SetLoggerLevels__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__LoggerLevel__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__SetLoggerLevelsResult__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Event__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__srv__SetLoggerLevels__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rcl_interfaces__srv__SetLoggerLevels__TYPE_NAME, 34, 34},
      {rcl_interfaces__srv__SetLoggerLevels__FIELDS, 3, 3},
    },
    {rcl_interfaces__srv__SetLoggerLevels__REFERENCED_TYPE_DESCRIPTIONS, 7, 7},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__LoggerLevel__EXPECTED_HASH, rcl_interfaces__msg__LoggerLevel__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__LoggerLevel__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__SetLoggerLevelsResult__EXPECTED_HASH, rcl_interfaces__msg__SetLoggerLevelsResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__SetLoggerLevelsResult__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = rcl_interfaces__srv__SetLoggerLevels_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[6].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rcl_interfaces__srv__SetLoggerLevels_Request__FIELD_NAME__levels[] = "levels";

static rosidl_runtime_c__type_description__Field rcl_interfaces__srv__SetLoggerLevels_Request__FIELDS[] = {
  {
    {rcl_interfaces__srv__SetLoggerLevels_Request__FIELD_NAME__levels, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {rcl_interfaces__msg__LoggerLevel__TYPE_NAME, 30, 30},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rcl_interfaces__srv__SetLoggerLevels_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {rcl_interfaces__msg__LoggerLevel__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
      {rcl_interfaces__srv__SetLoggerLevels_Request__FIELDS, 1, 1},
    },
    {rcl_interfaces__srv__SetLoggerLevels_Request__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&rcl_interfaces__msg__LoggerLevel__EXPECTED_HASH, rcl_interfaces__msg__LoggerLevel__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = rcl_interfaces__msg__LoggerLevel__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rcl_interfaces__srv__SetLoggerLevels_Response__FIELD_NAME__results[] = "results";

static rosidl_runtime_c__type_description__Field rcl_interfaces__srv__SetLoggerLevels_Response__FIELDS[] = {
  {
    {rcl_interfaces__srv__SetLoggerLevels_Response__FIELD_NAME__results, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {rcl_interfaces__msg__SetLoggerLevelsResult__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rcl_interfaces__srv__SetLoggerLevels_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {rcl_interfaces__msg__SetLoggerLevelsResult__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
      {rcl_interfaces__srv__SetLoggerLevels_Response__FIELDS, 1, 1},
    },
    {rcl_interfaces__srv__SetLoggerLevels_Response__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&rcl_interfaces__msg__SetLoggerLevelsResult__EXPECTED_HASH, rcl_interfaces__msg__SetLoggerLevelsResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = rcl_interfaces__msg__SetLoggerLevelsResult__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__info[] = "info";
static char rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__request[] = "request";
static char rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field rcl_interfaces__srv__SetLoggerLevels_Event__FIELDS[] = {
  {
    {rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rcl_interfaces__srv__SetLoggerLevels_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__LoggerLevel__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__SetLoggerLevelsResult__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__srv__SetLoggerLevels_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rcl_interfaces__srv__SetLoggerLevels_Event__TYPE_NAME, 40, 40},
      {rcl_interfaces__srv__SetLoggerLevels_Event__FIELDS, 3, 3},
    },
    {rcl_interfaces__srv__SetLoggerLevels_Event__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__LoggerLevel__EXPECTED_HASH, rcl_interfaces__msg__LoggerLevel__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__LoggerLevel__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__SetLoggerLevelsResult__EXPECTED_HASH, rcl_interfaces__msg__SetLoggerLevelsResult__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__SetLoggerLevelsResult__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# A list of loggers to set.\n"
  "LoggerLevel[] levels\n"
  "\n"
  "---\n"
  "# Indicates whether setting each logger succeeded or not and why.\n"
  "SetLoggerLevelsResult[] results";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__srv__SetLoggerLevels__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rcl_interfaces__srv__SetLoggerLevels__TYPE_NAME, 34, 34},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 152, 152},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__srv__SetLoggerLevels_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rcl_interfaces__srv__SetLoggerLevels_Request__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__srv__SetLoggerLevels_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rcl_interfaces__srv__SetLoggerLevels_Response__TYPE_NAME, 43, 43},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__srv__SetLoggerLevels_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rcl_interfaces__srv__SetLoggerLevels_Event__TYPE_NAME, 40, 40},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__srv__SetLoggerLevels__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[8];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 8, 8};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rcl_interfaces__srv__SetLoggerLevels__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__LoggerLevel__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__SetLoggerLevelsResult__get_individual_type_description_source(NULL);
    sources[4] = *rcl_interfaces__srv__SetLoggerLevels_Event__get_individual_type_description_source(NULL);
    sources[5] = *rcl_interfaces__srv__SetLoggerLevels_Request__get_individual_type_description_source(NULL);
    sources[6] = *rcl_interfaces__srv__SetLoggerLevels_Response__get_individual_type_description_source(NULL);
    sources[7] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__srv__SetLoggerLevels_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rcl_interfaces__srv__SetLoggerLevels_Request__get_individual_type_description_source(NULL),
    sources[1] = *rcl_interfaces__msg__LoggerLevel__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__srv__SetLoggerLevels_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rcl_interfaces__srv__SetLoggerLevels_Response__get_individual_type_description_source(NULL),
    sources[1] = *rcl_interfaces__msg__SetLoggerLevelsResult__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__srv__SetLoggerLevels_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rcl_interfaces__srv__SetLoggerLevels_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__LoggerLevel__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__SetLoggerLevelsResult__get_individual_type_description_source(NULL);
    sources[4] = *rcl_interfaces__srv__SetLoggerLevels_Request__get_individual_type_description_source(NULL);
    sources[5] = *rcl_interfaces__srv__SetLoggerLevels_Response__get_individual_type_description_source(NULL);
    sources[6] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
