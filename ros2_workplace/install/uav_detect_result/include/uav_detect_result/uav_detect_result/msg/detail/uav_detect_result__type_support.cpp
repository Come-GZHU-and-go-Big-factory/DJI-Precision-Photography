// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from uav_detect_result:msg/UavDetectResult.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "uav_detect_result/msg/detail/uav_detect_result__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace uav_detect_result
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void UavDetectResult_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) uav_detect_result::msg::UavDetectResult(_init);
}

void UavDetectResult_fini_function(void * message_memory)
{
  auto typed_message = static_cast<uav_detect_result::msg::UavDetectResult *>(message_memory);
  typed_message->~UavDetectResult();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UavDetectResult_message_member_array[2] = {
  {
    "num",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uav_detect_result::msg::UavDetectResult, num),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "content",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uav_detect_result::msg::UavDetectResult, content),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UavDetectResult_message_members = {
  "uav_detect_result::msg",  // message namespace
  "UavDetectResult",  // message name
  2,  // number of fields
  sizeof(uav_detect_result::msg::UavDetectResult),
  UavDetectResult_message_member_array,  // message members
  UavDetectResult_init_function,  // function to initialize message memory (memory has to be allocated)
  UavDetectResult_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UavDetectResult_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UavDetectResult_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace uav_detect_result


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<uav_detect_result::msg::UavDetectResult>()
{
  return &::uav_detect_result::msg::rosidl_typesupport_introspection_cpp::UavDetectResult_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, uav_detect_result, msg, UavDetectResult)() {
  return &::uav_detect_result::msg::rosidl_typesupport_introspection_cpp::UavDetectResult_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
