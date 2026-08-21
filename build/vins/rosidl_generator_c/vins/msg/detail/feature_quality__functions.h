// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice

#ifndef VINS__MSG__DETAIL__FEATURE_QUALITY__FUNCTIONS_H_
#define VINS__MSG__DETAIL__FEATURE_QUALITY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vins/msg/rosidl_generator_c__visibility_control.h"

#include "vins/msg/detail/feature_quality__struct.h"

/// Initialize msg/FeatureQuality message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vins__msg__FeatureQuality
 * )) before or use
 * vins__msg__FeatureQuality__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__init(vins__msg__FeatureQuality * msg);

/// Finalize msg/FeatureQuality message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
void
vins__msg__FeatureQuality__fini(vins__msg__FeatureQuality * msg);

/// Create msg/FeatureQuality message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vins__msg__FeatureQuality__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
vins__msg__FeatureQuality *
vins__msg__FeatureQuality__create();

/// Destroy msg/FeatureQuality message.
/**
 * It calls
 * vins__msg__FeatureQuality__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
void
vins__msg__FeatureQuality__destroy(vins__msg__FeatureQuality * msg);

/// Check for msg/FeatureQuality message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__are_equal(const vins__msg__FeatureQuality * lhs, const vins__msg__FeatureQuality * rhs);

/// Copy a msg/FeatureQuality message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__copy(
  const vins__msg__FeatureQuality * input,
  vins__msg__FeatureQuality * output);

/// Initialize array of msg/FeatureQuality messages.
/**
 * It allocates the memory for the number of elements and calls
 * vins__msg__FeatureQuality__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__Sequence__init(vins__msg__FeatureQuality__Sequence * array, size_t size);

/// Finalize array of msg/FeatureQuality messages.
/**
 * It calls
 * vins__msg__FeatureQuality__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
void
vins__msg__FeatureQuality__Sequence__fini(vins__msg__FeatureQuality__Sequence * array);

/// Create array of msg/FeatureQuality messages.
/**
 * It allocates the memory for the array and calls
 * vins__msg__FeatureQuality__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
vins__msg__FeatureQuality__Sequence *
vins__msg__FeatureQuality__Sequence__create(size_t size);

/// Destroy array of msg/FeatureQuality messages.
/**
 * It calls
 * vins__msg__FeatureQuality__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
void
vins__msg__FeatureQuality__Sequence__destroy(vins__msg__FeatureQuality__Sequence * array);

/// Check for msg/FeatureQuality message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__Sequence__are_equal(const vins__msg__FeatureQuality__Sequence * lhs, const vins__msg__FeatureQuality__Sequence * rhs);

/// Copy an array of msg/FeatureQuality messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vins
bool
vins__msg__FeatureQuality__Sequence__copy(
  const vins__msg__FeatureQuality__Sequence * input,
  vins__msg__FeatureQuality__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VINS__MSG__DETAIL__FEATURE_QUALITY__FUNCTIONS_H_
