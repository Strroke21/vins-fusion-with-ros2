// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vins:msg/FeatureQuality.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vins/msg/detail/feature_quality__struct.h"
#include "vins/msg/detail/feature_quality__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vins__msg__feature_quality__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[41];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vins.msg._feature_quality.FeatureQuality", full_classname_dest, 40) == 0);
  }
  vins__msg__FeatureQuality * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // tracked
    PyObject * field = PyObject_GetAttrString(_pymsg, "tracked");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->tracked = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // long_tracks_gt_5
    PyObject * field = PyObject_GetAttrString(_pymsg, "long_tracks_gt_5");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->long_tracks_gt_5 = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // new_features
    PyObject * field = PyObject_GetAttrString(_pymsg, "new_features");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->new_features = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // total
    PyObject * field = PyObject_GetAttrString(_pymsg, "total");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->total = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // visual_features
    PyObject * field = PyObject_GetAttrString(_pymsg, "visual_features");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->visual_features = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // vx
    PyObject * field = PyObject_GetAttrString(_pymsg, "vx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vx = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vy
    PyObject * field = PyObject_GetAttrString(_pymsg, "vy");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vy = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vz
    PyObject * field = PyObject_GetAttrString(_pymsg, "vz");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vz = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // velocity_norm
    PyObject * field = PyObject_GetAttrString(_pymsg, "velocity_norm");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->velocity_norm = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ba_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "ba_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ba_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ba_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "ba_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ba_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ba_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "ba_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ba_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ba_norm
    PyObject * field = PyObject_GetAttrString(_pymsg, "ba_norm");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ba_norm = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bg_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "bg_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bg_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bg_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "bg_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bg_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bg_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "bg_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bg_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bg_norm
    PyObject * field = PyObject_GetAttrString(_pymsg, "bg_norm");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bg_norm = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vins__msg__feature_quality__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of FeatureQuality */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vins.msg._feature_quality");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "FeatureQuality");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vins__msg__FeatureQuality * ros_message = (vins__msg__FeatureQuality *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tracked
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->tracked);
    {
      int rc = PyObject_SetAttrString(_pymessage, "tracked", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // long_tracks_gt_5
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->long_tracks_gt_5);
    {
      int rc = PyObject_SetAttrString(_pymessage, "long_tracks_gt_5", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // new_features
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->new_features);
    {
      int rc = PyObject_SetAttrString(_pymessage, "new_features", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // total
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->total);
    {
      int rc = PyObject_SetAttrString(_pymessage, "total", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // visual_features
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->visual_features);
    {
      int rc = PyObject_SetAttrString(_pymessage, "visual_features", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vy
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vy);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vz
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vz);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vz", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velocity_norm
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->velocity_norm);
    {
      int rc = PyObject_SetAttrString(_pymessage, "velocity_norm", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ba_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ba_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ba_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ba_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ba_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ba_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ba_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ba_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ba_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ba_norm
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ba_norm);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ba_norm", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bg_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bg_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bg_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bg_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bg_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bg_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bg_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bg_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bg_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bg_norm
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bg_norm);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bg_norm", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
