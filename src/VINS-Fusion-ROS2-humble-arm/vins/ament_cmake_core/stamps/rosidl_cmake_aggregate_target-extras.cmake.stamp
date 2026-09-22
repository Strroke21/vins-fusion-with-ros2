# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target vins::vins
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${vins_TARGETS}.
if(vins_TARGETS AND NOT TARGET vins::vins)
  add_library(vins::vins INTERFACE IMPORTED)
  set_target_properties(vins::vins PROPERTIES
    INTERFACE_LINK_LIBRARIES "${vins_TARGETS}")
endif()
