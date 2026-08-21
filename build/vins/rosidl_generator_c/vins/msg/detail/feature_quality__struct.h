// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_H_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/FeatureQuality in the package vins.
typedef struct vins__msg__FeatureQuality
{
  std_msgs__msg__Header header;
  int32_t tracked;
  int32_t long_tracks_gt_5;
  int32_t new_features;
  int32_t total;
  int32_t visual_features;
  double vx;
  double vy;
  double vz;
  double velocity_norm;
  double ba_x;
  double ba_y;
  double ba_z;
  double ba_norm;
  double bg_x;
  double bg_y;
  double bg_z;
  double bg_norm;
} vins__msg__FeatureQuality;

// Struct for a sequence of vins__msg__FeatureQuality.
typedef struct vins__msg__FeatureQuality__Sequence
{
  vins__msg__FeatureQuality * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vins__msg__FeatureQuality__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__STRUCT_H_
