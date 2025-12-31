# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_dji_precision_capture_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED dji_precision_capture_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(dji_precision_capture_FOUND FALSE)
  elseif(NOT dji_precision_capture_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(dji_precision_capture_FOUND FALSE)
  endif()
  return()
endif()
set(_dji_precision_capture_CONFIG_INCLUDED TRUE)

# output package information
if(NOT dji_precision_capture_FIND_QUIETLY)
  message(STATUS "Found dji_precision_capture: 0.0.0 (${dji_precision_capture_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'dji_precision_capture' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${dji_precision_capture_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(dji_precision_capture_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${dji_precision_capture_DIR}/${_extra}")
endforeach()
