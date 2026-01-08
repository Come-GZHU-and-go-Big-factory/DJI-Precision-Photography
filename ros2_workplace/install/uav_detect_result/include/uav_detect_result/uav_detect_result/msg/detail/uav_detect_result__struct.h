// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_H_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/UavDetectResult in the package uav_detect_result.
typedef struct uav_detect_result__msg__UavDetectResult
{
  int64_t num;
  rosidl_runtime_c__String content;
} uav_detect_result__msg__UavDetectResult;

// Struct for a sequence of uav_detect_result__msg__UavDetectResult.
typedef struct uav_detect_result__msg__UavDetectResult__Sequence
{
  uav_detect_result__msg__UavDetectResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uav_detect_result__msg__UavDetectResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_H_
