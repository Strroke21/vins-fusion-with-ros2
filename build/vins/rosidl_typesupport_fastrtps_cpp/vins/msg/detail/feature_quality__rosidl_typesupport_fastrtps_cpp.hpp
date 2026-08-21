// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vins/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "vins/msg/detail/feature_quality__struct.hpp"

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

namespace vins
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vins
cdr_serialize(
  const vins::msg::FeatureQuality & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vins
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vins::msg::FeatureQuality & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vins
get_serialized_size(
  const vins::msg::FeatureQuality & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vins
max_serialized_size_FeatureQuality(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vins

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vins
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vins, msg, FeatureQuality)();

#ifdef __cplusplus
}
#endif

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
