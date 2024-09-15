// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from visualization_msgs:msg/InteractiveMarkerControl.idl
// generated code does not contain a copyright notice

#include "visualization_msgs/msg/detail/interactive_marker_control__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
const rosidl_type_hash_t *
visualization_msgs__msg__InteractiveMarkerControl__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x60, 0xe2, 0xfa, 0x36, 0x34, 0x4f, 0x5f, 0x47,
      0x91, 0xb2, 0x4a, 0x80, 0x95, 0x42, 0xa1, 0x8b,
      0xff, 0xd5, 0x55, 0xf5, 0x63, 0x55, 0x0d, 0x4b,
      0x22, 0xb3, 0xbb, 0xfc, 0x31, 0xec, 0x0e, 0xd5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/quaternion__functions.h"
#include "geometry_msgs/msg/detail/vector3__functions.h"
#include "builtin_interfaces/msg/detail/duration__functions.h"
#include "visualization_msgs/msg/detail/uv_coordinate__functions.h"
#include "visualization_msgs/msg/detail/marker__functions.h"
#include "visualization_msgs/msg/detail/mesh_file__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "sensor_msgs/msg/detail/compressed_image__functions.h"
#include "geometry_msgs/msg/detail/point__functions.h"
#include "std_msgs/msg/detail/color_rgba__functions.h"
#include "geometry_msgs/msg/detail/pose__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Duration__EXPECTED_HASH = {1, {
    0xe8, 0xd0, 0x09, 0xf6, 0x59, 0x81, 0x6f, 0x75,
    0x8b, 0x75, 0x33, 0x4e, 0xe1, 0xa9, 0xca, 0x5b,
    0x5c, 0x0b, 0x85, 0x98, 0x43, 0x26, 0x1f, 0x14,
    0xc7, 0xf9, 0x37, 0x34, 0x95, 0x99, 0xd9, 0x3b,
  }};
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Pose__EXPECTED_HASH = {1, {
    0xd5, 0x01, 0x95, 0x4e, 0x94, 0x76, 0xce, 0xa2,
    0x99, 0x69, 0x84, 0xe8, 0x12, 0x05, 0x4b, 0x68,
    0x02, 0x6a, 0xe0, 0xbf, 0xae, 0x78, 0x9d, 0x9a,
    0x10, 0xb2, 0x3d, 0xaf, 0x35, 0xcc, 0x90, 0xfa,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Quaternion__EXPECTED_HASH = {1, {
    0x8a, 0x76, 0x5f, 0x66, 0x77, 0x8c, 0x8f, 0xf7,
    0xc8, 0xab, 0x94, 0xaf, 0xcc, 0x59, 0x0a, 0x2e,
    0xd5, 0x32, 0x5a, 0x1d, 0x9a, 0x07, 0x6f, 0xff,
    0xf3, 0x8f, 0xbc, 0xe3, 0x6f, 0x45, 0x86, 0x84,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Vector3__EXPECTED_HASH = {1, {
    0xcc, 0x12, 0xfe, 0x83, 0xe4, 0xc0, 0x27, 0x19,
    0xf1, 0xce, 0x80, 0x70, 0xbf, 0xd1, 0x4a, 0xec,
    0xd4, 0x0f, 0x75, 0xa9, 0x66, 0x96, 0xa6, 0x7a,
    0x2a, 0x1f, 0x37, 0xf7, 0xdb, 0xb0, 0x76, 0x5d,
  }};
static const rosidl_type_hash_t sensor_msgs__msg__CompressedImage__EXPECTED_HASH = {1, {
    0x15, 0x64, 0x07, 0x71, 0x53, 0x15, 0x71, 0x18,
    0x5e, 0x2e, 0xfc, 0x8a, 0x10, 0x0b, 0xaf, 0x92,
    0x39, 0x61, 0xa4, 0xd1, 0x5d, 0x55, 0x69, 0x65,
    0x2e, 0x6c, 0xb6, 0x69, 0x1e, 0x8e, 0x37, 0x1a,
  }};
static const rosidl_type_hash_t std_msgs__msg__ColorRGBA__EXPECTED_HASH = {1, {
    0x77, 0xa7, 0xa5, 0xb9, 0xae, 0x47, 0x73, 0x06,
    0x09, 0x76, 0x65, 0x10, 0x6e, 0x04, 0x13, 0xba,
    0x74, 0x44, 0x02, 0x45, 0xb1, 0xf3, 0xd0, 0xc6,
    0xd6, 0x40, 0x5f, 0xe5, 0xc7, 0x81, 0x3f, 0xe8,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
static const rosidl_type_hash_t visualization_msgs__msg__Marker__EXPECTED_HASH = {1, {
    0x45, 0xb1, 0x3c, 0xcf, 0x79, 0x1f, 0x22, 0x59,
    0x62, 0xbf, 0x74, 0xe7, 0x46, 0xf9, 0x64, 0x45,
    0x18, 0x85, 0x5d, 0x78, 0x3a, 0x6f, 0x42, 0xba,
    0x0c, 0xc1, 0x4f, 0xde, 0x2b, 0x4f, 0x3c, 0xe0,
  }};
static const rosidl_type_hash_t visualization_msgs__msg__MeshFile__EXPECTED_HASH = {1, {
    0x77, 0x10, 0xec, 0xe1, 0x5a, 0x14, 0x8f, 0xb7,
    0xc9, 0xb5, 0x46, 0x36, 0x4c, 0xfb, 0x21, 0x5b,
    0xb0, 0x60, 0x98, 0x08, 0x7b, 0xd6, 0x39, 0x4f,
    0xe5, 0xb7, 0x3a, 0x49, 0x35, 0x08, 0xf8, 0xc4,
  }};
static const rosidl_type_hash_t visualization_msgs__msg__UVCoordinate__EXPECTED_HASH = {1, {
    0xf2, 0x7f, 0x7e, 0xd2, 0x1f, 0xe3, 0x60, 0xc6,
    0x06, 0x69, 0x44, 0xf8, 0x56, 0xb8, 0x01, 0xa0,
    0xc0, 0xd1, 0xe9, 0x4e, 0x81, 0x5b, 0x68, 0x86,
    0x44, 0x4b, 0x42, 0xd9, 0x0b, 0x19, 0x6a, 0x26,
  }};
#endif

static char visualization_msgs__msg__InteractiveMarkerControl__TYPE_NAME[] = "visualization_msgs/msg/InteractiveMarkerControl";
static char builtin_interfaces__msg__Duration__TYPE_NAME[] = "builtin_interfaces/msg/Duration";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char geometry_msgs__msg__Pose__TYPE_NAME[] = "geometry_msgs/msg/Pose";
static char geometry_msgs__msg__Quaternion__TYPE_NAME[] = "geometry_msgs/msg/Quaternion";
static char geometry_msgs__msg__Vector3__TYPE_NAME[] = "geometry_msgs/msg/Vector3";
static char sensor_msgs__msg__CompressedImage__TYPE_NAME[] = "sensor_msgs/msg/CompressedImage";
static char std_msgs__msg__ColorRGBA__TYPE_NAME[] = "std_msgs/msg/ColorRGBA";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char visualization_msgs__msg__Marker__TYPE_NAME[] = "visualization_msgs/msg/Marker";
static char visualization_msgs__msg__MeshFile__TYPE_NAME[] = "visualization_msgs/msg/MeshFile";
static char visualization_msgs__msg__UVCoordinate__TYPE_NAME[] = "visualization_msgs/msg/UVCoordinate";

// Define type names, field names, and default values
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__name[] = "name";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__orientation[] = "orientation";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__orientation_mode[] = "orientation_mode";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__interaction_mode[] = "interaction_mode";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__always_visible[] = "always_visible";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__markers[] = "markers";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__independent_marker_orientation[] = "independent_marker_orientation";
static char visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__description[] = "description";

static rosidl_runtime_c__type_description__Field visualization_msgs__msg__InteractiveMarkerControl__FIELDS[] = {
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__orientation, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__orientation_mode, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__interaction_mode, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__always_visible, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__markers, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {visualization_msgs__msg__Marker__TYPE_NAME, 29, 29},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__independent_marker_orientation, 30, 30},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__InteractiveMarkerControl__FIELD_NAME__description, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription visualization_msgs__msg__InteractiveMarkerControl__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Duration__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__CompressedImage__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__ColorRGBA__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__Marker__TYPE_NAME, 29, 29},
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__MeshFile__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {visualization_msgs__msg__UVCoordinate__TYPE_NAME, 35, 35},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
visualization_msgs__msg__InteractiveMarkerControl__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {visualization_msgs__msg__InteractiveMarkerControl__TYPE_NAME, 47, 47},
      {visualization_msgs__msg__InteractiveMarkerControl__FIELDS, 8, 8},
    },
    {visualization_msgs__msg__InteractiveMarkerControl__REFERENCED_TYPE_DESCRIPTIONS, 12, 12},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Duration__EXPECTED_HASH, builtin_interfaces__msg__Duration__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Duration__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Pose__EXPECTED_HASH, geometry_msgs__msg__Pose__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = geometry_msgs__msg__Pose__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Vector3__EXPECTED_HASH, geometry_msgs__msg__Vector3__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = geometry_msgs__msg__Vector3__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&sensor_msgs__msg__CompressedImage__EXPECTED_HASH, sensor_msgs__msg__CompressedImage__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[6].fields = sensor_msgs__msg__CompressedImage__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__ColorRGBA__EXPECTED_HASH, std_msgs__msg__ColorRGBA__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[7].fields = std_msgs__msg__ColorRGBA__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[8].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&visualization_msgs__msg__Marker__EXPECTED_HASH, visualization_msgs__msg__Marker__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[9].fields = visualization_msgs__msg__Marker__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&visualization_msgs__msg__MeshFile__EXPECTED_HASH, visualization_msgs__msg__MeshFile__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[10].fields = visualization_msgs__msg__MeshFile__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&visualization_msgs__msg__UVCoordinate__EXPECTED_HASH, visualization_msgs__msg__UVCoordinate__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[11].fields = visualization_msgs__msg__UVCoordinate__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Represents a control that is to be displayed together with an interactive marker\n"
  "\n"
  "# Identifying string for this control.\n"
  "# You need to assign a unique value to this to receive feedback from the GUI\n"
  "# on what actions the user performs on this control (e.g. a button click).\n"
  "string name\n"
  "\n"
  "\n"
  "# Defines the local coordinate frame (relative to the pose of the parent\n"
  "# interactive marker) in which is being rotated and translated.\n"
  "# Default: Identity\n"
  "geometry_msgs/Quaternion orientation\n"
  "\n"
  "\n"
  "# Orientation mode: controls how orientation changes.\n"
  "# INHERIT: Follow orientation of interactive marker\n"
  "# FIXED: Keep orientation fixed at initial state\n"
  "# VIEW_FACING: Align y-z plane with screen (x: forward, y:left, z:up).\n"
  "uint8 INHERIT = 0\n"
  "uint8 FIXED = 1\n"
  "uint8 VIEW_FACING = 2\n"
  "\n"
  "uint8 orientation_mode\n"
  "\n"
  "# Interaction mode for this control\n"
  "#\n"
  "# NONE: This control is only meant for visualization; no context menu.\n"
  "# MENU: Like NONE, but right-click menu is active.\n"
  "# BUTTON: Element can be left-clicked.\n"
  "# MOVE_AXIS: Translate along local x-axis.\n"
  "# MOVE_PLANE: Translate in local y-z plane.\n"
  "# ROTATE_AXIS: Rotate around local x-axis.\n"
  "# MOVE_ROTATE: Combines MOVE_PLANE and ROTATE_AXIS.\n"
  "uint8 NONE = 0\n"
  "uint8 MENU = 1\n"
  "uint8 BUTTON = 2\n"
  "uint8 MOVE_AXIS = 3\n"
  "uint8 MOVE_PLANE = 4\n"
  "uint8 ROTATE_AXIS = 5\n"
  "uint8 MOVE_ROTATE = 6\n"
  "# \"3D\" interaction modes work with the mouse+SHIFT+CTRL or with 3D cursors.\n"
  "# MOVE_3D: Translate freely in 3D space.\n"
  "# ROTATE_3D: Rotate freely in 3D space about the origin of parent frame.\n"
  "# MOVE_ROTATE_3D: Full 6-DOF freedom of translation and rotation about the cursor origin.\n"
  "uint8 MOVE_3D = 7\n"
  "uint8 ROTATE_3D = 8\n"
  "uint8 MOVE_ROTATE_3D = 9\n"
  "\n"
  "uint8 interaction_mode\n"
  "\n"
  "\n"
  "# If true, the contained markers will also be visible\n"
  "# when the gui is not in interactive mode.\n"
  "bool always_visible\n"
  "\n"
  "\n"
  "# Markers to be displayed as custom visual representation.\n"
  "# Leave this empty to use the default control handles.\n"
  "#\n"
  "# Note:\n"
  "# - The markers can be defined in an arbitrary coordinate frame,\n"
  "#   but will be transformed into the local frame of the interactive marker.\n"
  "# - If the header of a marker is empty, its pose will be interpreted as\n"
  "#   relative to the pose of the parent interactive marker.\n"
  "Marker[] markers\n"
  "\n"
  "\n"
  "# In VIEW_FACING mode, set this to true if you don't want the markers\n"
  "# to be aligned with the camera view point. The markers will show up\n"
  "# as in INHERIT mode.\n"
  "bool independent_marker_orientation\n"
  "\n"
  "\n"
  "# Short description (< 40 characters) of what this control does,\n"
  "# e.g. \"Move the robot\".\n"
  "# Default: A generic description based on the interaction mode\n"
  "string description";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
visualization_msgs__msg__InteractiveMarkerControl__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {visualization_msgs__msg__InteractiveMarkerControl__TYPE_NAME, 47, 47},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 2579, 2579},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
visualization_msgs__msg__InteractiveMarkerControl__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[13];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 13, 13};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *visualization_msgs__msg__InteractiveMarkerControl__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Duration__get_individual_type_description_source(NULL);
    sources[2] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[4] = *geometry_msgs__msg__Pose__get_individual_type_description_source(NULL);
    sources[5] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    sources[6] = *geometry_msgs__msg__Vector3__get_individual_type_description_source(NULL);
    sources[7] = *sensor_msgs__msg__CompressedImage__get_individual_type_description_source(NULL);
    sources[8] = *std_msgs__msg__ColorRGBA__get_individual_type_description_source(NULL);
    sources[9] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[10] = *visualization_msgs__msg__Marker__get_individual_type_description_source(NULL);
    sources[11] = *visualization_msgs__msg__MeshFile__get_individual_type_description_source(NULL);
    sources[12] = *visualization_msgs__msg__UVCoordinate__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
