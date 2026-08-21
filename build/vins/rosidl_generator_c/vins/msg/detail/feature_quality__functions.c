// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice
#include "vins/msg/detail/feature_quality__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
vins__msg__FeatureQuality__init(vins__msg__FeatureQuality * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vins__msg__FeatureQuality__fini(msg);
    return false;
  }
  // tracked
  // long_tracks_gt_5
  // new_features
  // total
  // visual_features
  // vx
  // vy
  // vz
  // velocity_norm
  // ba_x
  // ba_y
  // ba_z
  // ba_norm
  // bg_x
  // bg_y
  // bg_z
  // bg_norm
  return true;
}

void
vins__msg__FeatureQuality__fini(vins__msg__FeatureQuality * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // tracked
  // long_tracks_gt_5
  // new_features
  // total
  // visual_features
  // vx
  // vy
  // vz
  // velocity_norm
  // ba_x
  // ba_y
  // ba_z
  // ba_norm
  // bg_x
  // bg_y
  // bg_z
  // bg_norm
}

bool
vins__msg__FeatureQuality__are_equal(const vins__msg__FeatureQuality * lhs, const vins__msg__FeatureQuality * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // tracked
  if (lhs->tracked != rhs->tracked) {
    return false;
  }
  // long_tracks_gt_5
  if (lhs->long_tracks_gt_5 != rhs->long_tracks_gt_5) {
    return false;
  }
  // new_features
  if (lhs->new_features != rhs->new_features) {
    return false;
  }
  // total
  if (lhs->total != rhs->total) {
    return false;
  }
  // visual_features
  if (lhs->visual_features != rhs->visual_features) {
    return false;
  }
  // vx
  if (lhs->vx != rhs->vx) {
    return false;
  }
  // vy
  if (lhs->vy != rhs->vy) {
    return false;
  }
  // vz
  if (lhs->vz != rhs->vz) {
    return false;
  }
  // velocity_norm
  if (lhs->velocity_norm != rhs->velocity_norm) {
    return false;
  }
  // ba_x
  if (lhs->ba_x != rhs->ba_x) {
    return false;
  }
  // ba_y
  if (lhs->ba_y != rhs->ba_y) {
    return false;
  }
  // ba_z
  if (lhs->ba_z != rhs->ba_z) {
    return false;
  }
  // ba_norm
  if (lhs->ba_norm != rhs->ba_norm) {
    return false;
  }
  // bg_x
  if (lhs->bg_x != rhs->bg_x) {
    return false;
  }
  // bg_y
  if (lhs->bg_y != rhs->bg_y) {
    return false;
  }
  // bg_z
  if (lhs->bg_z != rhs->bg_z) {
    return false;
  }
  // bg_norm
  if (lhs->bg_norm != rhs->bg_norm) {
    return false;
  }
  return true;
}

bool
vins__msg__FeatureQuality__copy(
  const vins__msg__FeatureQuality * input,
  vins__msg__FeatureQuality * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // tracked
  output->tracked = input->tracked;
  // long_tracks_gt_5
  output->long_tracks_gt_5 = input->long_tracks_gt_5;
  // new_features
  output->new_features = input->new_features;
  // total
  output->total = input->total;
  // visual_features
  output->visual_features = input->visual_features;
  // vx
  output->vx = input->vx;
  // vy
  output->vy = input->vy;
  // vz
  output->vz = input->vz;
  // velocity_norm
  output->velocity_norm = input->velocity_norm;
  // ba_x
  output->ba_x = input->ba_x;
  // ba_y
  output->ba_y = input->ba_y;
  // ba_z
  output->ba_z = input->ba_z;
  // ba_norm
  output->ba_norm = input->ba_norm;
  // bg_x
  output->bg_x = input->bg_x;
  // bg_y
  output->bg_y = input->bg_y;
  // bg_z
  output->bg_z = input->bg_z;
  // bg_norm
  output->bg_norm = input->bg_norm;
  return true;
}

vins__msg__FeatureQuality *
vins__msg__FeatureQuality__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vins__msg__FeatureQuality * msg = (vins__msg__FeatureQuality *)allocator.allocate(sizeof(vins__msg__FeatureQuality), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vins__msg__FeatureQuality));
  bool success = vins__msg__FeatureQuality__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vins__msg__FeatureQuality__destroy(vins__msg__FeatureQuality * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vins__msg__FeatureQuality__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vins__msg__FeatureQuality__Sequence__init(vins__msg__FeatureQuality__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vins__msg__FeatureQuality * data = NULL;

  if (size) {
    data = (vins__msg__FeatureQuality *)allocator.zero_allocate(size, sizeof(vins__msg__FeatureQuality), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vins__msg__FeatureQuality__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vins__msg__FeatureQuality__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vins__msg__FeatureQuality__Sequence__fini(vins__msg__FeatureQuality__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vins__msg__FeatureQuality__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vins__msg__FeatureQuality__Sequence *
vins__msg__FeatureQuality__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vins__msg__FeatureQuality__Sequence * array = (vins__msg__FeatureQuality__Sequence *)allocator.allocate(sizeof(vins__msg__FeatureQuality__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vins__msg__FeatureQuality__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vins__msg__FeatureQuality__Sequence__destroy(vins__msg__FeatureQuality__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vins__msg__FeatureQuality__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vins__msg__FeatureQuality__Sequence__are_equal(const vins__msg__FeatureQuality__Sequence * lhs, const vins__msg__FeatureQuality__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vins__msg__FeatureQuality__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vins__msg__FeatureQuality__Sequence__copy(
  const vins__msg__FeatureQuality__Sequence * input,
  vins__msg__FeatureQuality__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vins__msg__FeatureQuality);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vins__msg__FeatureQuality * data =
      (vins__msg__FeatureQuality *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vins__msg__FeatureQuality__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vins__msg__FeatureQuality__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vins__msg__FeatureQuality__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
