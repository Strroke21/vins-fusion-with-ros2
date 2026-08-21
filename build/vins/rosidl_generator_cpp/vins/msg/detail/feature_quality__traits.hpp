// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__TRAITS_HPP_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vins/msg/detail/feature_quality__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vins
{

namespace msg
{

inline void to_flow_style_yaml(
  const FeatureQuality & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: tracked
  {
    out << "tracked: ";
    rosidl_generator_traits::value_to_yaml(msg.tracked, out);
    out << ", ";
  }

  // member: long_tracks_gt_5
  {
    out << "long_tracks_gt_5: ";
    rosidl_generator_traits::value_to_yaml(msg.long_tracks_gt_5, out);
    out << ", ";
  }

  // member: new_features
  {
    out << "new_features: ";
    rosidl_generator_traits::value_to_yaml(msg.new_features, out);
    out << ", ";
  }

  // member: total
  {
    out << "total: ";
    rosidl_generator_traits::value_to_yaml(msg.total, out);
    out << ", ";
  }

  // member: visual_features
  {
    out << "visual_features: ";
    rosidl_generator_traits::value_to_yaml(msg.visual_features, out);
    out << ", ";
  }

  // member: vx
  {
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << ", ";
  }

  // member: vy
  {
    out << "vy: ";
    rosidl_generator_traits::value_to_yaml(msg.vy, out);
    out << ", ";
  }

  // member: vz
  {
    out << "vz: ";
    rosidl_generator_traits::value_to_yaml(msg.vz, out);
    out << ", ";
  }

  // member: velocity_norm
  {
    out << "velocity_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_norm, out);
    out << ", ";
  }

  // member: ba_x
  {
    out << "ba_x: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_x, out);
    out << ", ";
  }

  // member: ba_y
  {
    out << "ba_y: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_y, out);
    out << ", ";
  }

  // member: ba_z
  {
    out << "ba_z: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_z, out);
    out << ", ";
  }

  // member: ba_norm
  {
    out << "ba_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_norm, out);
    out << ", ";
  }

  // member: bg_x
  {
    out << "bg_x: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_x, out);
    out << ", ";
  }

  // member: bg_y
  {
    out << "bg_y: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_y, out);
    out << ", ";
  }

  // member: bg_z
  {
    out << "bg_z: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_z, out);
    out << ", ";
  }

  // member: bg_norm
  {
    out << "bg_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_norm, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FeatureQuality & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: tracked
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tracked: ";
    rosidl_generator_traits::value_to_yaml(msg.tracked, out);
    out << "\n";
  }

  // member: long_tracks_gt_5
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "long_tracks_gt_5: ";
    rosidl_generator_traits::value_to_yaml(msg.long_tracks_gt_5, out);
    out << "\n";
  }

  // member: new_features
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_features: ";
    rosidl_generator_traits::value_to_yaml(msg.new_features, out);
    out << "\n";
  }

  // member: total
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total: ";
    rosidl_generator_traits::value_to_yaml(msg.total, out);
    out << "\n";
  }

  // member: visual_features
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "visual_features: ";
    rosidl_generator_traits::value_to_yaml(msg.visual_features, out);
    out << "\n";
  }

  // member: vx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << "\n";
  }

  // member: vy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vy: ";
    rosidl_generator_traits::value_to_yaml(msg.vy, out);
    out << "\n";
  }

  // member: vz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vz: ";
    rosidl_generator_traits::value_to_yaml(msg.vz, out);
    out << "\n";
  }

  // member: velocity_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_norm, out);
    out << "\n";
  }

  // member: ba_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ba_x: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_x, out);
    out << "\n";
  }

  // member: ba_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ba_y: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_y, out);
    out << "\n";
  }

  // member: ba_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ba_z: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_z, out);
    out << "\n";
  }

  // member: ba_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ba_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.ba_norm, out);
    out << "\n";
  }

  // member: bg_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bg_x: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_x, out);
    out << "\n";
  }

  // member: bg_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bg_y: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_y, out);
    out << "\n";
  }

  // member: bg_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bg_z: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_z, out);
    out << "\n";
  }

  // member: bg_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bg_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.bg_norm, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FeatureQuality & msg, bool use_flow_style = false)
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

}  // namespace vins

namespace rosidl_generator_traits
{

[[deprecated("use vins::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vins::msg::FeatureQuality & msg,
  std::ostream & out, size_t indentation = 0)
{
  vins::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vins::msg::to_yaml() instead")]]
inline std::string to_yaml(const vins::msg::FeatureQuality & msg)
{
  return vins::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vins::msg::FeatureQuality>()
{
  return "vins::msg::FeatureQuality";
}

template<>
inline const char * name<vins::msg::FeatureQuality>()
{
  return "vins/msg/FeatureQuality";
}

template<>
struct has_fixed_size<vins::msg::FeatureQuality>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vins::msg::FeatureQuality>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vins::msg::FeatureQuality>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__TRAITS_HPP_
