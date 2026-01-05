// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_HPP_
#define UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__uav_detect_result__msg__UavDetectResult __attribute__((deprecated))
#else
# define DEPRECATED__uav_detect_result__msg__UavDetectResult __declspec(deprecated)
#endif

namespace uav_detect_result
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UavDetectResult_
{
  using Type = UavDetectResult_<ContainerAllocator>;

  explicit UavDetectResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
      this->content = "";
    }
  }

  explicit UavDetectResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : content(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
      this->content = "";
    }
  }

  // field types and members
  using _num_type =
    int64_t;
  _num_type num;
  using _content_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _content_type content;

  // setters for named parameter idiom
  Type & set__num(
    const int64_t & _arg)
  {
    this->num = _arg;
    return *this;
  }
  Type & set__content(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->content = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uav_detect_result::msg::UavDetectResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const uav_detect_result::msg::UavDetectResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uav_detect_result::msg::UavDetectResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uav_detect_result::msg::UavDetectResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uav_detect_result__msg__UavDetectResult
    std::shared_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uav_detect_result__msg__UavDetectResult
    std::shared_ptr<uav_detect_result::msg::UavDetectResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UavDetectResult_ & other) const
  {
    if (this->num != other.num) {
      return false;
    }
    if (this->content != other.content) {
      return false;
    }
    return true;
  }
  bool operator!=(const UavDetectResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UavDetectResult_

// alias to use template instance with default allocator
using UavDetectResult =
  uav_detect_result::msg::UavDetectResult_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uav_detect_result

#endif  // UAV_DETECT_RESULT__MSG__DETAIL__UAV_DETECT_RESULT__STRUCT_HPP_
