/**
 ********************************************************************
 * @file    test_camera_manager.h
 * @brief   这是 "test_camera_manager.c" 的头文件，定义了结构体和
 * (导出的) 函数原型。
 *
 * @copyright (c) 2021 DJI. All rights reserved.
 *
 * 此处包含的所有信息均为 DJI 的财产。
 * 此处包含的智力与技术概念归 DJI 所有，并可能受美国及外国专利、
 * 正在申请的专利以及商业秘密或版权法的保护。
 * 严禁未经 DJI 明确书面许可，以任何形式传播此类信息，
 * 包括但不限于数据及其包含的其他所有权材料。
 *
 * 如果您在未获得 DJI 授权的情况下收到此源代码，您不得进一步传播该信息，
 * 并必须立即删除该源代码并通知 DJI。DJI 保留因您未能执行此操作而造成的
 * 任何损失或损害追究法律责任的权利。
 *
 *********************************************************************
 */

/* 防止递归包含的定义 --------------------------------------------------------*/
#ifndef TEST_CAMERA_MANAGER_H
#define TEST_CAMERA_MANAGER_H

/* 包含文件 ------------------------------------------------------------------*/
#include "dji_typedef.h"
#include "dji_camera_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 导出的常量 ----------------------------------------------------------------*/

/* 导出的类型 ----------------------------------------------------------------*/
typedef enum {
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_SHUTTER_SPEED,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_APERTURE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_EV,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_ISO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_FOCUS_POINT,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_TAP_ZOOM_POINT,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAMERA_ZOOM_PARAM,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOOT_SINGLE_PHOTO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOOT_BURST_PHOTO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOOT_INTERVAL_PHOTO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_RECORD_VIDEO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_DOWNLOAD_AND_DELETE_MEDIA_FILE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_DOWNLOAD_FILE_LIST_BY_SLICES,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_THERMOMETRY,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_GET_LIDAR_RANGING_INFO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_IR_CAMERA_ZOOM_PARAM,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_NIGHT_SCENE_MODE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_CAPTURE_RECORDING_STREAMS,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOW_STORAGE_INFO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_FORMAT_SD_CARD,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_LINK_ZOOM,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_USER_CUSTOM_DIR_FILE_NAME,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_RESET_CAMERA_SETTINGS,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_AE_LOCK_MODE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_FOCUS_RING_VALUE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_CONNECT_STATUS_TEST,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_GET_PHOTO_VIDEO_PARAM,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_METERING_MODE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_METERING_POINT,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_FFC_MODE_AND_TRRIGER,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SET_GAIN_MODE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_GET_CAMERA_STATUS,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SUBSCRIBE_POINT_CLOUD,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_INDEX_MAX
} E_DjiTestCameraManagerSampleSelect;

/* 导出的函数 ----------------------------------------------------------------*/

/*! @brief 使用异步接口设置相机曝光补偿值的示例
 *
 * @note 在此接口中，将先获取当前的曝光补偿值，然后再进行设置。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param exposureCompensation 目标曝光补偿值
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetEV(E_DjiMountPosition position,
                                           E_DjiCameraManagerExposureCompensation exposureCompensation);

/*! @brief 使用异步接口设置相机曝光模式的示例
 *
 * @note 在此接口中，将先获取当前的曝光模式，然后再进行设置。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param exposureMode 目标曝光模式
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetExposureMode(E_DjiMountPosition position,
                                                     E_DjiCameraManagerExposureMode exposureMode);

/*! @brief 使用异步接口设置相机 ISO 值的示例
 *
 * @note 在此接口中，将先获取当前的 ISO 值，然后再进行设置。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param isoData 目标 ISO 值
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetISO(E_DjiMountPosition position,
                                            E_DjiCameraManagerISO isoData);

/*! @brief 使用异步接口设置相机快门速度的示例
 *
 * @note 在此接口中，将先获取当前的快门速度，然后再进行设置。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param shutterSpeed 目标快门速度
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetShutterSpeed(E_DjiMountPosition position,
                                                     E_DjiCameraManagerShutterSpeed shutterSpeed);

/*! @brief 使用异步接口设置相机光圈值的示例
 *
 * @note 在此接口中，将先获取当前的光圈值，然后再进行设置。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param aperture 目标光圈值
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetAperture(E_DjiMountPosition position,
                                                 E_DjiCameraManagerAperture aperture);

/*! @brief 使用异步接口设置相机对焦点的示例
 *
 * @note 在此接口中，对焦模式将被设置为自动(AUTO)。然后对焦点将被设置为 (x, y)。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param tapFocusPos 目标对焦点数据，x 和 y 取值范围 0~1
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetFocusPoint(E_DjiMountPosition position,
                                                   T_DjiCameraManagerFocusPosData tapFocusPos);

/*! @brief 使用异步接口设置相机指点变焦(Tap-Zoom)点的示例
 *
 * @note 在此接口中，将启用指点变焦功能并设置倍率。然后从目标点 (x, y) 开始执行指点变焦。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param multiplier 每次指点变焦的缩放倍率
 * @param tapZoomPosData 目标指点变焦位置数据，x 和 y 取值范围 0~1
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetTapZoomPoint(E_DjiMountPosition position, uint8_t multiplier,
                                                     T_DjiCameraManagerTapZoomPosData tapZoomPosData);

/*! @brief 使用同步接口在相机上执行连续变焦的示例
 *
 * @note 仅支持：安装在 Osmo 上的 X5, X5R 和 X5S 相机（配备镜头 Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ），以及 Z3、Z30 相机。
 * @note 在此接口中，变焦将按指定的方向和速度开始，并在持续指定时间后停止。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param zoomDirection 选择放大(Zoom Out)或缩小(Zoom In)
 * @param zoomSpeed 变焦速度
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartContinuousZoom(E_DjiMountPosition position,
                                                         E_DjiCameraZoomDirection zoomDirection,
                                                         E_DjiCameraZoomSpeed zoomSpeed);

/*! @brief 使用同步接口在相机上执行定点变焦(Position Zoom)的示例
 *
 * @note 仅支持：安装在 Osmo 上的 X5, X5R 和 X5S 相机（配备镜头 Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ），以及 Z3、Z30 相机。
 * @note 在此接口中，变焦倍率将被设置为您的目标值。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param zoomDirection 变焦方向
 * @param factor 目标变焦倍率
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerOpticalZoom(E_DjiMountPosition position,
                                                 E_DjiCameraZoomDirection zoomDirection,
                                                 dji_f32_t factor);

/*! @brief 使用异步接口停止相机连续变焦的示例
 *
 * @note 仅支持：安装在 Osmo 上的 X5, X5R 和 X5S 相机（配备镜头 Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ），以及 Z3、Z30 相机。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopContinuousZoom(E_DjiMountPosition position);

/*! @brief 使用异步接口进行单张拍摄的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始拍摄单张照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootSinglePhoto(E_DjiMountPosition position);

/*! @brief 使用异步接口进行连拍的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始连拍照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param burstCount 每次连拍的照片数量
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootBurstPhoto(E_DjiMountPosition position,
                                                          E_DjiCameraBurstCount burstCount);

/*! @brief 使用异步接口开始定时拍摄(Interval Photo)的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始定时拍摄照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param intervalData 定时拍摄的参数设置
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootIntervalPhoto(E_DjiMountPosition position,
                                                              T_DjiCameraPhotoTimeIntervalSettings intervalData);

/*! @brief 使用异步接口停止拍摄的示例
 *
 * @note 在此接口中，相机将停止所有的拍摄动作。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopShootPhoto(E_DjiMountPosition position);

/*! @brief 使用异步接口开始录制视频的示例
 *
 * @note 在此接口中，相机将被设置为录像模式(RECORD_VIDEO)，然后开始录制。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartRecordVideo(E_DjiMountPosition position);

/*! @brief 使用异步接口停止录制视频的示例
 *
 * @note 在此接口中，相机将停止视频录制。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopRecordVideo(E_DjiMountPosition position);

/**
 * @brief 运行相机管理器示例的主函数
 * @param mountPosition 负载挂载位置
 * @param cameraManagerSampleSelect 选择执行具体的相机功能示例
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerRunSample(E_DjiMountPosition mountPosition,
                                               E_DjiTestCameraManagerSampleSelect cameraManagerSampleSelect);

#ifdef __cplusplus
}
#endif

#endif // TEST_CAMERA_MANAGER_H
/************************ (C) COPYRIGHT DJI Innovations *******文件结束******/