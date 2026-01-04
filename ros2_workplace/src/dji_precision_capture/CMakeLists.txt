cmake_minimum_required(VERSION 3.8)
project(dji_precision_capture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# PSDK相关内容
set(PSDK_DIR ../../../Payload-SDK/samples/sample_c++/platform/linux/manifold3)
# 设定交叉编译器
set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++" CACHE STRING "C++ compiler")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# 开启自动生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 添加编译相关的内容
add_compile_definitions(
    _GNU_SOURCE
    PLATFORM_ARCH_AARCH64=1
    SYSTEM_ARCH_LINUX=1
)

# 文件
include_directories(
    ${PSDK_DIR}/../my_code
    ${PSDK_DIR}/../../../module_sample
    ${PSDK_DIR}/../../../../sample_c/module_sample
    ${PSDK_DIR}/../common
    ${PSDK_DIR}/../manifold3/application
    include_directories(${PSDK_DIR}/../../../../../psdk_lib/include)
)

# 包含ROS2中camera_controller的头文件
include_directories(
    ./include
)

#搜索全部程序
file(GLOB_RECURSE MODULE_SAMPLE_SRC
    ${PSDK_DIR}/../../../module_sample/liveview/*.c*
    ${PSDK_DIR}/../../../module_sample/camera_manager/*.c*
    ${PSDK_DIR}/../../../module_sample/hms_manager/*.c*
    ${PSDK_DIR}/../../../module_sample/perception/*.c*
    ${PSDK_DIR}/../../../module_sample/gimbal/*.c*
    ${PSDK_DIR}/../../../module_sample/flight_controller/*.c*
    ${PSDK_DIR}/../../../module_sample/hms_manager/*.c*
    ${PSDK_DIR}/../../../module_sample/widget_manager/*.c*
    ${PSDK_DIR}/../../../../sample_c/module_sample/*.c
    ${PSDK_DIR}/../../../../sample_c/module_sample/widget_interaction_test/*.c
    ${PSDK_DIR}/../../../module_sample/positioning/*.c 
)

#搜索全部程序
file(GLOB_RECURSE MY_CODE ${PSDK_DIR}/../my_code/*.c*)
file(GLOB_RECURSE MODULE_COMMON_SRC ${PSDK_DIR}/../common/*.c*)
file(GLOB_RECURSE MODULE_HAL_SRC ${PSDK_DIR}/hal/*.c*)
file(GLOB_RECURSE MODULE_APP_SRC ${PSDK_DIR}/application/*.c*)

set(TOOLCHAIN_NAME aarch64-linux-gnu-gcc)

link_directories(${PSDK_DIR}/../../../../../psdk_lib/lib/${TOOLCHAIN_NAME})

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${MY_CODE}
    ${MODULE_APP_SRC}
    ${MODULE_SAMPLE_SRC}
    ${MODULE_COMMON_SRC}
    ${MODULE_HAL_SRC}
)
# 找到libpayloadsdk.a文件路径
find_library(PSDK_LIBRARY payloadsdk
    PATHS
    ${PSDK_DIR}/../../../../../psdk_lib/lib/${TOOLCHAIN_NAME}/
)
target_link_libraries(${PROJECT_NAME}
        ${PSDK_LIBRARY}
        #/home/dji/DJI_workshop/LZP_PSDK/Payload-SDK/psdk_lib/lib/aarch64-linux-gnu-gcc/libpayloadsdk.a
        #${PSDK_DIR}/../../../../../psdk_lib/lib/${TOOLCHAIN_NAME}/libpayloadsdk.a
        stdc++
        m
        dl
)

set(CMAKE_PREFIX_PATH "/usr/local/aarch64;${CMAKE_PREFIX_PATH}")
set(OpenCV_DIR "/usr/local/aarch64/lib/cmake/opencv4")

# OpenCV
find_package(OpenCV QUIET)
if (OpenCV_FOUND)
    message("\n${PROJECT_NAME}...")
    message(STATUS "Found OpenCV installed in the system, will use it to display image in AdvancedSensing APIs")
    message(STATUS " - Includes: ${OpenCV_INCLUDE_DIRS}")
    message(STATUS " - Libraries: ${OpenCV_LIBRARIES}")
    add_definitions(-DOPEN_CV_INSTALLED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBRARIES})
else ()
    message(STATUS "Did not find OpenCV in the system, image data is inside RecvContainer as raw data")
endif ()

# FFMPEG
find_package(PkgConfig)
# pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil libswscale)
if (FFMPEG_FOUND)
    message(STATUS "Found FFMPEG installed in the system")
    message(STATUS " - Includes: ${FFMPEG_INCLUDE_DIRS}")
    message(STATUS " - Libraries: ${FFMPEG_LIBRARIES}")

    target_link_libraries(${PROJECT_NAME}  ${FFMPEG_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_INCLUDE_DIRS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE FFMPEG_INSTALLED)
else()
    message(STATUS "Cannot Find FFMPEG")
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# find dependencies
# ROS2 cmake
find_package(ament_cmake REQUIRED)
# ROS2 基本功能
find_package(rclcpp REQUIRED)
# ROS2 标准信息
find_package(std_msgs REQUIRED)

ament_target_dependencies(${PROJECT_NAME}
    rclcpp
    std_msgs
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib/${PROJECT_NAME}
)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
