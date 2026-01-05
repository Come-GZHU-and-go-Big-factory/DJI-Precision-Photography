// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "uav_detect_result/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "uav_detect_result/msg/detail/uav_detect_result__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace uav_detect_result
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uav_detect_result
cdr_serialize(
  const uav_detect_result::msg::UavDetectResult & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uav_detect_result
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  uav_detect_result::msg::UavDetectResult & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uav_detect_result
get_serialized_size(
  const uav_detect_result::msg::UavDetectResult & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uav_detect_result
max_serialized_size_UavDetectResult(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace uav_detect_result

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uav_detect_result
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, uav_detect_result, msg, UavDetectResult)();

#ifdef __cplusplus
}
#endif

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
