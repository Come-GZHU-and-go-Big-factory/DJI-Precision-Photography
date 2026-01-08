// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__TRAITS_HPP_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uav_detect_result/msg/detail/uav_detect_result__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace uav_detect_result
{

namespace msg
{

inline void to_flow_style_yaml(
  const UavDetectResult & msg,
  std::ostream & out)
{
  out << "{";
  // member: num
  {
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
    out << ", ";
  }

  // member: content
  {
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UavDetectResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
    out << "\n";
  }

  // member: content
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UavDetectResult & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace uav_detect_result

namespace rosidl_generator_traits
{

[[deprecated("use uav_detect_result::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uav_detect_result::msg::UavDetectResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  uav_detect_result::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uav_detect_result::msg::to_yaml() instead")]]
inline std::string to_yaml(const uav_detect_result::msg::UavDetectResult & msg)
{
  return uav_detect_result::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uav_detect_result::msg::UavDetectResult>()
{
  return "uav_detect_result::msg::UavDetectResult";
}

template<>
inline const char * name<uav_detect_result::msg::UavDetectResult>()
{
  return "uav_detect_result/msg/UavDetectResult";
}

template<>
struct has_fixed_size<uav_detect_result::msg::UavDetectResult>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uav_detect_result::msg::UavDetectResult>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uav_detect_result::msg::UavDetectResult>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__TRAITS_HPP_
