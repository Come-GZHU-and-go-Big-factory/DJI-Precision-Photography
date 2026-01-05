// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__BUILDER_HPP_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uav_detect_result/msg/detail/uav_detect_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uav_detect_result
{

namespace msg
{

namespace builder
{

class Init_UavDetectResult_content
{
public:
  explicit Init_UavDetectResult_content(::uav_detect_result::msg::UavDetectResult & msg)
  : msg_(msg)
  {}
  ::uav_detect_result::msg::UavDetectResult content(::uav_detect_result::msg::UavDetectResult::_content_type arg)
  {
    msg_.content = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uav_detect_result::msg::UavDetectResult msg_;
};

class Init_UavDetectResult_num
{
public:
  Init_UavDetectResult_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UavDetectResult_content num(::uav_detect_result::msg::UavDetectResult::_num_type arg)
  {
    msg_.num = std::move(arg);
    return Init_UavDetectResult_content(msg_);
  }

private:
  ::uav_detect_result::msg::UavDetectResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uav_detect_result::msg::UavDetectResult>()
{
  return uav_detect_result::msg::builder::Init_UavDetectResult_num();
}

}  // namespace uav_detect_result

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__BUILDER_HPP_
