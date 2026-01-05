// generated from rosidl_generator_c/resource/rosidl_generator_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef UAV_DETECT_RESULT__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define UAV_DETECT_RESULT__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_uav_detect_result __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_uav_detect_result __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_uav_detect_result __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_uav_detect_result __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_uav_detect_result
    #define ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result ROSIDL_GENERATOR_C_EXPORT_uav_detect_result
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result ROSIDL_GENERATOR_C_IMPORT_uav_detect_result
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_uav_detect_result __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_uav_detect_result
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_uav_detect_result
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // UAV_DETECT_RESULT__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
