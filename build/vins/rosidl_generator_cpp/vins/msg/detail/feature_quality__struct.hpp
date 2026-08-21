// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_HPP_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vins__msg__FeatureQuality __attribute__((deprecated))
#else
# define DEPRECATED__vins__msg__FeatureQuality __declspec(deprecated)
#endif

namespace vins
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FeatureQuality_
{
  using Type = FeatureQuality_<ContainerAllocator>;

  explicit FeatureQuality_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tracked = 0l;
      this->long_tracks_gt_5 = 0l;
      this->new_features = 0l;
      this->total = 0l;
      this->visual_features = 0l;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->velocity_norm = 0.0;
      this->ba_x = 0.0;
      this->ba_y = 0.0;
      this->ba_z = 0.0;
      this->ba_norm = 0.0;
      this->bg_x = 0.0;
      this->bg_y = 0.0;
      this->bg_z = 0.0;
      this->bg_norm = 0.0;
    }
  }

  explicit FeatureQuality_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tracked = 0l;
      this->long_tracks_gt_5 = 0l;
      this->new_features = 0l;
      this->total = 0l;
      this->visual_features = 0l;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->velocity_norm = 0.0;
      this->ba_x = 0.0;
      this->ba_y = 0.0;
      this->ba_z = 0.0;
      this->ba_norm = 0.0;
      this->bg_x = 0.0;
      this->bg_y = 0.0;
      this->bg_z = 0.0;
      this->bg_norm = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _tracked_type =
    int32_t;
  _tracked_type tracked;
  using _long_tracks_gt_5_type =
    int32_t;
  _long_tracks_gt_5_type long_tracks_gt_5;
  using _new_features_type =
    int32_t;
  _new_features_type new_features;
  using _total_type =
    int32_t;
  _total_type total;
  using _visual_features_type =
    int32_t;
  _visual_features_type visual_features;
  using _vx_type =
    double;
  _vx_type vx;
  using _vy_type =
    double;
  _vy_type vy;
  using _vz_type =
    double;
  _vz_type vz;
  using _velocity_norm_type =
    double;
  _velocity_norm_type velocity_norm;
  using _ba_x_type =
    double;
  _ba_x_type ba_x;
  using _ba_y_type =
    double;
  _ba_y_type ba_y;
  using _ba_z_type =
    double;
  _ba_z_type ba_z;
  using _ba_norm_type =
    double;
  _ba_norm_type ba_norm;
  using _bg_x_type =
    double;
  _bg_x_type bg_x;
  using _bg_y_type =
    double;
  _bg_y_type bg_y;
  using _bg_z_type =
    double;
  _bg_z_type bg_z;
  using _bg_norm_type =
    double;
  _bg_norm_type bg_norm;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__tracked(
    const int32_t & _arg)
  {
    this->tracked = _arg;
    return *this;
  }
  Type & set__long_tracks_gt_5(
    const int32_t & _arg)
  {
    this->long_tracks_gt_5 = _arg;
    return *this;
  }
  Type & set__new_features(
    const int32_t & _arg)
  {
    this->new_features = _arg;
    return *this;
  }
  Type & set__total(
    const int32_t & _arg)
  {
    this->total = _arg;
    return *this;
  }
  Type & set__visual_features(
    const int32_t & _arg)
  {
    this->visual_features = _arg;
    return *this;
  }
  Type & set__vx(
    const double & _arg)
  {
    this->vx = _arg;
    return *this;
  }
  Type & set__vy(
    const double & _arg)
  {
    this->vy = _arg;
    return *this;
  }
  Type & set__vz(
    const double & _arg)
  {
    this->vz = _arg;
    return *this;
  }
  Type & set__velocity_norm(
    const double & _arg)
  {
    this->velocity_norm = _arg;
    return *this;
  }
  Type & set__ba_x(
    const double & _arg)
  {
    this->ba_x = _arg;
    return *this;
  }
  Type & set__ba_y(
    const double & _arg)
  {
    this->ba_y = _arg;
    return *this;
  }
  Type & set__ba_z(
    const double & _arg)
  {
    this->ba_z = _arg;
    return *this;
  }
  Type & set__ba_norm(
    const double & _arg)
  {
    this->ba_norm = _arg;
    return *this;
  }
  Type & set__bg_x(
    const double & _arg)
  {
    this->bg_x = _arg;
    return *this;
  }
  Type & set__bg_y(
    const double & _arg)
  {
    this->bg_y = _arg;
    return *this;
  }
  Type & set__bg_z(
    const double & _arg)
  {
    this->bg_z = _arg;
    return *this;
  }
  Type & set__bg_norm(
    const double & _arg)
  {
    this->bg_norm = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vins::msg::FeatureQuality_<ContainerAllocator> *;
  using ConstRawPtr =
    const vins::msg::FeatureQuality_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vins::msg::FeatureQuality_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vins::msg::FeatureQuality_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vins::msg::FeatureQuality_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vins::msg::FeatureQuality_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vins::msg::FeatureQuality_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vins::msg::FeatureQuality_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vins::msg::FeatureQuality_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vins::msg::FeatureQuality_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vins__msg__FeatureQuality
    std::shared_ptr<vins::msg::FeatureQuality_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vins__msg__FeatureQuality
    std::shared_ptr<vins::msg::FeatureQuality_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FeatureQuality_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->tracked != other.tracked) {
      return false;
    }
    if (this->long_tracks_gt_5 != other.long_tracks_gt_5) {
      return false;
    }
    if (this->new_features != other.new_features) {
      return false;
    }
    if (this->total != other.total) {
      return false;
    }
    if (this->visual_features != other.visual_features) {
      return false;
    }
    if (this->vx != other.vx) {
      return false;
    }
    if (this->vy != other.vy) {
      return false;
    }
    if (this->vz != other.vz) {
      return false;
    }
    if (this->velocity_norm != other.velocity_norm) {
      return false;
    }
    if (this->ba_x != other.ba_x) {
      return false;
    }
    if (this->ba_y != other.ba_y) {
      return false;
    }
    if (this->ba_z != other.ba_z) {
      return false;
    }
    if (this->ba_norm != other.ba_norm) {
      return false;
    }
    if (this->bg_x != other.bg_x) {
      return false;
    }
    if (this->bg_y != other.bg_y) {
      return false;
    }
    if (this->bg_z != other.bg_z) {
      return false;
    }
    if (this->bg_norm != other.bg_norm) {
      return false;
    }
    return true;
  }
  bool operator!=(const FeatureQuality_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FeatureQuality_

// alias to use template instance with default allocator
using FeatureQuality =
  vins::msg::FeatureQuality_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vins

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_HPP_
