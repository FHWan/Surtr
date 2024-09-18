// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:srv/GetParameterTypes.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/srv/detail/get_parameter_types__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `names`
#include "rosidl_runtime_c/string_functions.h"

bool
rcl_interfaces__srv__GetParameterTypes_Request__init(rcl_interfaces__srv__GetParameterTypes_Request * msg)
{
  if (!msg) {
    return false;
  }
  // names
  if (!rosidl_runtime_c__String__Sequence__init(&msg->names, 0)) {
    rcl_interfaces__srv__GetParameterTypes_Request__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Request__fini(rcl_interfaces__srv__GetParameterTypes_Request * msg)
{
  if (!msg) {
    return;
  }
  // names
  rosidl_runtime_c__String__Sequence__fini(&msg->names);
}

bool
rcl_interfaces__srv__GetParameterTypes_Request__are_equal(const rcl_interfaces__srv__GetParameterTypes_Request * lhs, const rcl_interfaces__srv__GetParameterTypes_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // names
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->names), &(rhs->names)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Request__copy(
  const rcl_interfaces__srv__GetParameterTypes_Request * input,
  rcl_interfaces__srv__GetParameterTypes_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // names
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->names), &(output->names)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__srv__GetParameterTypes_Request *
rcl_interfaces__srv__GetParameterTypes_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Request * msg = (rcl_interfaces__srv__GetParameterTypes_Request *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__srv__GetParameterTypes_Request));
  bool success = rcl_interfaces__srv__GetParameterTypes_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__srv__GetParameterTypes_Request__destroy(rcl_interfaces__srv__GetParameterTypes_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__srv__GetParameterTypes_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__init(rcl_interfaces__srv__GetParameterTypes_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Request * data = NULL;

  if (size) {
    data = (rcl_interfaces__srv__GetParameterTypes_Request *)allocator.zero_allocate(size, sizeof(rcl_interfaces__srv__GetParameterTypes_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__srv__GetParameterTypes_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__srv__GetParameterTypes_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__fini(rcl_interfaces__srv__GetParameterTypes_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rcl_interfaces__srv__GetParameterTypes_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rcl_interfaces__srv__GetParameterTypes_Request__Sequence *
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Request__Sequence * array = (rcl_interfaces__srv__GetParameterTypes_Request__Sequence *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__srv__GetParameterTypes_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__destroy(rcl_interfaces__srv__GetParameterTypes_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__srv__GetParameterTypes_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__are_equal(const rcl_interfaces__srv__GetParameterTypes_Request__Sequence * lhs, const rcl_interfaces__srv__GetParameterTypes_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Request__Sequence__copy(
  const rcl_interfaces__srv__GetParameterTypes_Request__Sequence * input,
  rcl_interfaces__srv__GetParameterTypes_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__srv__GetParameterTypes_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__srv__GetParameterTypes_Request * data =
      (rcl_interfaces__srv__GetParameterTypes_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__srv__GetParameterTypes_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__srv__GetParameterTypes_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `types`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rcl_interfaces__srv__GetParameterTypes_Response__init(rcl_interfaces__srv__GetParameterTypes_Response * msg)
{
  if (!msg) {
    return false;
  }
  // types
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->types, 0)) {
    rcl_interfaces__srv__GetParameterTypes_Response__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Response__fini(rcl_interfaces__srv__GetParameterTypes_Response * msg)
{
  if (!msg) {
    return;
  }
  // types
  rosidl_runtime_c__uint8__Sequence__fini(&msg->types);
}

bool
rcl_interfaces__srv__GetParameterTypes_Response__are_equal(const rcl_interfaces__srv__GetParameterTypes_Response * lhs, const rcl_interfaces__srv__GetParameterTypes_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // types
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->types), &(rhs->types)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Response__copy(
  const rcl_interfaces__srv__GetParameterTypes_Response * input,
  rcl_interfaces__srv__GetParameterTypes_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // types
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->types), &(output->types)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__srv__GetParameterTypes_Response *
rcl_interfaces__srv__GetParameterTypes_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Response * msg = (rcl_interfaces__srv__GetParameterTypes_Response *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__srv__GetParameterTypes_Response));
  bool success = rcl_interfaces__srv__GetParameterTypes_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__srv__GetParameterTypes_Response__destroy(rcl_interfaces__srv__GetParameterTypes_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__srv__GetParameterTypes_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__init(rcl_interfaces__srv__GetParameterTypes_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Response * data = NULL;

  if (size) {
    data = (rcl_interfaces__srv__GetParameterTypes_Response *)allocator.zero_allocate(size, sizeof(rcl_interfaces__srv__GetParameterTypes_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__srv__GetParameterTypes_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__srv__GetParameterTypes_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__fini(rcl_interfaces__srv__GetParameterTypes_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rcl_interfaces__srv__GetParameterTypes_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rcl_interfaces__srv__GetParameterTypes_Response__Sequence *
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Response__Sequence * array = (rcl_interfaces__srv__GetParameterTypes_Response__Sequence *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__srv__GetParameterTypes_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__destroy(rcl_interfaces__srv__GetParameterTypes_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__srv__GetParameterTypes_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__are_equal(const rcl_interfaces__srv__GetParameterTypes_Response__Sequence * lhs, const rcl_interfaces__srv__GetParameterTypes_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Response__Sequence__copy(
  const rcl_interfaces__srv__GetParameterTypes_Response__Sequence * input,
  rcl_interfaces__srv__GetParameterTypes_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__srv__GetParameterTypes_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__srv__GetParameterTypes_Response * data =
      (rcl_interfaces__srv__GetParameterTypes_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__srv__GetParameterTypes_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__srv__GetParameterTypes_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "rcl_interfaces/srv/detail/get_parameter_types__functions.h"

bool
rcl_interfaces__srv__GetParameterTypes_Event__init(rcl_interfaces__srv__GetParameterTypes_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    rcl_interfaces__srv__GetParameterTypes_Event__fini(msg);
    return false;
  }
  // request
  if (!rcl_interfaces__srv__GetParameterTypes_Request__Sequence__init(&msg->request, 0)) {
    rcl_interfaces__srv__GetParameterTypes_Event__fini(msg);
    return false;
  }
  // response
  if (!rcl_interfaces__srv__GetParameterTypes_Response__Sequence__init(&msg->response, 0)) {
    rcl_interfaces__srv__GetParameterTypes_Event__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Event__fini(rcl_interfaces__srv__GetParameterTypes_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  rcl_interfaces__srv__GetParameterTypes_Request__Sequence__fini(&msg->request);
  // response
  rcl_interfaces__srv__GetParameterTypes_Response__Sequence__fini(&msg->response);
}

bool
rcl_interfaces__srv__GetParameterTypes_Event__are_equal(const rcl_interfaces__srv__GetParameterTypes_Event * lhs, const rcl_interfaces__srv__GetParameterTypes_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!rcl_interfaces__srv__GetParameterTypes_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!rcl_interfaces__srv__GetParameterTypes_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Event__copy(
  const rcl_interfaces__srv__GetParameterTypes_Event * input,
  rcl_interfaces__srv__GetParameterTypes_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!rcl_interfaces__srv__GetParameterTypes_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!rcl_interfaces__srv__GetParameterTypes_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__srv__GetParameterTypes_Event *
rcl_interfaces__srv__GetParameterTypes_Event__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Event * msg = (rcl_interfaces__srv__GetParameterTypes_Event *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__srv__GetParameterTypes_Event));
  bool success = rcl_interfaces__srv__GetParameterTypes_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__srv__GetParameterTypes_Event__destroy(rcl_interfaces__srv__GetParameterTypes_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__srv__GetParameterTypes_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__init(rcl_interfaces__srv__GetParameterTypes_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Event * data = NULL;

  if (size) {
    data = (rcl_interfaces__srv__GetParameterTypes_Event *)allocator.zero_allocate(size, sizeof(rcl_interfaces__srv__GetParameterTypes_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__srv__GetParameterTypes_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__srv__GetParameterTypes_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__fini(rcl_interfaces__srv__GetParameterTypes_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rcl_interfaces__srv__GetParameterTypes_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rcl_interfaces__srv__GetParameterTypes_Event__Sequence *
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameterTypes_Event__Sequence * array = (rcl_interfaces__srv__GetParameterTypes_Event__Sequence *)allocator.allocate(sizeof(rcl_interfaces__srv__GetParameterTypes_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__srv__GetParameterTypes_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__destroy(rcl_interfaces__srv__GetParameterTypes_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__srv__GetParameterTypes_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__are_equal(const rcl_interfaces__srv__GetParameterTypes_Event__Sequence * lhs, const rcl_interfaces__srv__GetParameterTypes_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__srv__GetParameterTypes_Event__Sequence__copy(
  const rcl_interfaces__srv__GetParameterTypes_Event__Sequence * input,
  rcl_interfaces__srv__GetParameterTypes_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__srv__GetParameterTypes_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__srv__GetParameterTypes_Event * data =
      (rcl_interfaces__srv__GetParameterTypes_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__srv__GetParameterTypes_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__srv__GetParameterTypes_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__srv__GetParameterTypes_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
