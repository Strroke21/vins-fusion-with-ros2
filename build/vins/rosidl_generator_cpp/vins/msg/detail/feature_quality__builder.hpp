// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__BUILDER_HPP_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vins/msg/detail/feature_quality__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vins
{

namespace msg
{

namespace builder
{

class Init_FeatureQuality_bg_norm
{
public:
  explicit Init_FeatureQuality_bg_norm(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  ::vins::msg::FeatureQuality bg_norm(::vins::msg::FeatureQuality::_bg_norm_type arg)
  {
    msg_.bg_norm = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_bg_z
{
public:
  explicit Init_FeatureQuality_bg_z(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_bg_norm bg_z(::vins::msg::FeatureQuality::_bg_z_type arg)
  {
    msg_.bg_z = std::move(arg);
    return Init_FeatureQuality_bg_norm(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_bg_y
{
public:
  explicit Init_FeatureQuality_bg_y(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_bg_z bg_y(::vins::msg::FeatureQuality::_bg_y_type arg)
  {
    msg_.bg_y = std::move(arg);
    return Init_FeatureQuality_bg_z(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_bg_x
{
public:
  explicit Init_FeatureQuality_bg_x(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_bg_y bg_x(::vins::msg::FeatureQuality::_bg_x_type arg)
  {
    msg_.bg_x = std::move(arg);
    return Init_FeatureQuality_bg_y(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_ba_norm
{
public:
  explicit Init_FeatureQuality_ba_norm(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_bg_x ba_norm(::vins::msg::FeatureQuality::_ba_norm_type arg)
  {
    msg_.ba_norm = std::move(arg);
    return Init_FeatureQuality_bg_x(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_ba_z
{
public:
  explicit Init_FeatureQuality_ba_z(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_ba_norm ba_z(::vins::msg::FeatureQuality::_ba_z_type arg)
  {
    msg_.ba_z = std::move(arg);
    return Init_FeatureQuality_ba_norm(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_ba_y
{
public:
  explicit Init_FeatureQuality_ba_y(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_ba_z ba_y(::vins::msg::FeatureQuality::_ba_y_type arg)
  {
    msg_.ba_y = std::move(arg);
    return Init_FeatureQuality_ba_z(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_ba_x
{
public:
  explicit Init_FeatureQuality_ba_x(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_ba_y ba_x(::vins::msg::FeatureQuality::_ba_x_type arg)
  {
    msg_.ba_x = std::move(arg);
    return Init_FeatureQuality_ba_y(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_velocity_norm
{
public:
  explicit Init_FeatureQuality_velocity_norm(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_ba_x velocity_norm(::vins::msg::FeatureQuality::_velocity_norm_type arg)
  {
    msg_.velocity_norm = std::move(arg);
    return Init_FeatureQuality_ba_x(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_vz
{
public:
  explicit Init_FeatureQuality_vz(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_velocity_norm vz(::vins::msg::FeatureQuality::_vz_type arg)
  {
    msg_.vz = std::move(arg);
    return Init_FeatureQuality_velocity_norm(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_vy
{
public:
  explicit Init_FeatureQuality_vy(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_vz vy(::vins::msg::FeatureQuality::_vy_type arg)
  {
    msg_.vy = std::move(arg);
    return Init_FeatureQuality_vz(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_vx
{
public:
  explicit Init_FeatureQuality_vx(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_vy vx(::vins::msg::FeatureQuality::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_FeatureQuality_vy(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_visual_features
{
public:
  explicit Init_FeatureQuality_visual_features(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_vx visual_features(::vins::msg::FeatureQuality::_visual_features_type arg)
  {
    msg_.visual_features = std::move(arg);
    return Init_FeatureQuality_vx(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_total
{
public:
  explicit Init_FeatureQuality_total(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_visual_features total(::vins::msg::FeatureQuality::_total_type arg)
  {
    msg_.total = std::move(arg);
    return Init_FeatureQuality_visual_features(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_new_features
{
public:
  explicit Init_FeatureQuality_new_features(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_total new_features(::vins::msg::FeatureQuality::_new_features_type arg)
  {
    msg_.new_features = std::move(arg);
    return Init_FeatureQuality_total(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_long_tracks_gt_5
{
public:
  explicit Init_FeatureQuality_long_tracks_gt_5(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_new_features long_tracks_gt_5(::vins::msg::FeatureQuality::_long_tracks_gt_5_type arg)
  {
    msg_.long_tracks_gt_5 = std::move(arg);
    return Init_FeatureQuality_new_features(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_tracked
{
public:
  explicit Init_FeatureQuality_tracked(::vins::msg::FeatureQuality & msg)
  : msg_(msg)
  {}
  Init_FeatureQuality_long_tracks_gt_5 tracked(::vins::msg::FeatureQuality::_tracked_type arg)
  {
    msg_.tracked = std::move(arg);
    return Init_FeatureQuality_long_tracks_gt_5(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

class Init_FeatureQuality_header
{
public:
  Init_FeatureQuality_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FeatureQuality_tracked header(::vins::msg::FeatureQuality::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_FeatureQuality_tracked(msg_);
  }

private:
  ::vins::msg::FeatureQuality msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vins::msg::FeatureQuality>()
{
  return vins::msg::builder::Init_FeatureQuality_header();
}

}  // namespace vins

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__BUILDER_HPP_
