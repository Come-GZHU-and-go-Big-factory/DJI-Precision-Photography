// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__FUNCTIONS_H_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "uav_detect_result/msg/rosidl_generator_c__visibility_control.h"

#include "uav_detect_result/msg/detail/uav_detect_result__struct.h"

/// Initialize msg/UavDetectResult message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * uav_detect_result__msg__UavDetectResult
 * )) before or use
 * uav_detect_result__msg__UavDetectResult__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__init(uav_detect_result__msg__UavDetectResult * msg);

/// Finalize msg/UavDetectResult message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
void
uav_detect_result__msg__UavDetectResult__fini(uav_detect_result__msg__UavDetectResult * msg);

/// Create msg/UavDetectResult message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * uav_detect_result__msg__UavDetectResult__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
uav_detect_result__msg__UavDetectResult *
uav_detect_result__msg__UavDetectResult__create();

/// Destroy msg/UavDetectResult message.
/**
 * It calls
 * uav_detect_result__msg__UavDetectResult__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
void
uav_detect_result__msg__UavDetectResult__destroy(uav_detect_result__msg__UavDetectResult * msg);

/// Check for msg/UavDetectResult message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__are_equal(const uav_detect_result__msg__UavDetectResult * lhs, const uav_detect_result__msg__UavDetectResult * rhs);

/// Copy a msg/UavDetectResult message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__copy(
  const uav_detect_result__msg__UavDetectResult * input,
  uav_detect_result__msg__UavDetectResult * output);

/// Initialize array of msg/UavDetectResult messages.
/**
 * It allocates the memory for the number of elements and calls
 * uav_detect_result__msg__UavDetectResult__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__Sequence__init(uav_detect_result__msg__UavDetectResult__Sequence * array, size_t size);

/// Finalize array of msg/UavDetectResult messages.
/**
 * It calls
 * uav_detect_result__msg__UavDetectResult__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
void
uav_detect_result__msg__UavDetectResult__Sequence__fini(uav_detect_result__msg__UavDetectResult__Sequence * array);

/// Create array of msg/UavDetectResult messages.
/**
 * It allocates the memory for the array and calls
 * uav_detect_result__msg__UavDetectResult__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
uav_detect_result__msg__UavDetectResult__Sequence *
uav_detect_result__msg__UavDetectResult__Sequence__create(size_t size);

/// Destroy array of msg/UavDetectResult messages.
/**
 * It calls
 * uav_detect_result__msg__UavDetectResult__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
void
uav_detect_result__msg__UavDetectResult__Sequence__destroy(uav_detect_result__msg__UavDetectResult__Sequence * array);

/// Check for msg/UavDetectResult message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__Sequence__are_equal(const uav_detect_result__msg__UavDetectResult__Sequence * lhs, const uav_detect_result__msg__UavDetectResult__Sequence * rhs);

/// Copy an array of msg/UavDetectResult messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
bool
uav_detect_result__msg__UavDetectResult__Sequence__copy(
  const uav_detect_result__msg__UavDetectResult__Sequence * input,
  uav_detect_result__msg__UavDetectResult__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__FUNCTIONS_H_
