// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice
#include "uav_detect_result/msg/detail/uav_detect_result__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `content`
#include "rosidl_runtime_c/string_functions.h"

bool
uav_detect_result__msg__UavDetectResult__init(uav_detect_result__msg__UavDetectResult * msg)
{
  if (!msg) {
    return false;
  }
  // num
  // content
  if (!rosidl_runtime_c__String__init(&msg->content)) {
    uav_detect_result__msg__UavDetectResult__fini(msg);
    return false;
  }
  return true;
}

void
uav_detect_result__msg__UavDetectResult__fini(uav_detect_result__msg__UavDetectResult * msg)
{
  if (!msg) {
    return;
  }
  // num
  // content
  rosidl_runtime_c__String__fini(&msg->content);
}

bool
uav_detect_result__msg__UavDetectResult__are_equal(const uav_detect_result__msg__UavDetectResult * lhs, const uav_detect_result__msg__UavDetectResult * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // num
  if (lhs->num != rhs->num) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->content), &(rhs->content)))
  {
    return false;
  }
  return true;
}

bool
uav_detect_result__msg__UavDetectResult__copy(
  const uav_detect_result__msg__UavDetectResult * input,
  uav_detect_result__msg__UavDetectResult * output)
{
  if (!input || !output) {
    return false;
  }
  // num
  output->num = input->num;
  // content
  if (!rosidl_runtime_c__String__copy(
      &(input->content), &(output->content)))
  {
    return false;
  }
  return true;
}

uav_detect_result__msg__UavDetectResult *
uav_detect_result__msg__UavDetectResult__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uav_detect_result__msg__UavDetectResult * msg = (uav_detect_result__msg__UavDetectResult *)allocator.allocate(sizeof(uav_detect_result__msg__UavDetectResult), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uav_detect_result__msg__UavDetectResult));
  bool success = uav_detect_result__msg__UavDetectResult__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uav_detect_result__msg__UavDetectResult__destroy(uav_detect_result__msg__UavDetectResult * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uav_detect_result__msg__UavDetectResult__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uav_detect_result__msg__UavDetectResult__Sequence__init(uav_detect_result__msg__UavDetectResult__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uav_detect_result__msg__UavDetectResult * data = NULL;

  if (size) {
    data = (uav_detect_result__msg__UavDetectResult *)allocator.zero_allocate(size, sizeof(uav_detect_result__msg__UavDetectResult), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uav_detect_result__msg__UavDetectResult__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uav_detect_result__msg__UavDetectResult__fini(&data[i - 1]);
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
uav_detect_result__msg__UavDetectResult__Sequence__fini(uav_detect_result__msg__UavDetectResult__Sequence * array)
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
      uav_detect_result__msg__UavDetectResult__fini(&array->data[i]);
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

uav_detect_result__msg__UavDetectResult__Sequence *
uav_detect_result__msg__UavDetectResult__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uav_detect_result__msg__UavDetectResult__Sequence * array = (uav_detect_result__msg__UavDetectResult__Sequence *)allocator.allocate(sizeof(uav_detect_result__msg__UavDetectResult__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uav_detect_result__msg__UavDetectResult__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uav_detect_result__msg__UavDetectResult__Sequence__destroy(uav_detect_result__msg__UavDetectResult__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uav_detect_result__msg__UavDetectResult__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uav_detect_result__msg__UavDetectResult__Sequence__are_equal(const uav_detect_result__msg__UavDetectResult__Sequence * lhs, const uav_detect_result__msg__UavDetectResult__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uav_detect_result__msg__UavDetectResult__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uav_detect_result__msg__UavDetectResult__Sequence__copy(
  const uav_detect_result__msg__UavDetectResult__Sequence * input,
  uav_detect_result__msg__UavDetectResult__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uav_detect_result__msg__UavDetectResult);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uav_detect_result__msg__UavDetectResult * data =
      (uav_detect_result__msg__UavDetectResult *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uav_detect_result__msg__UavDetectResult__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uav_detect_result__msg__UavDetectResult__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uav_detect_result__msg__UavDetectResult__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
