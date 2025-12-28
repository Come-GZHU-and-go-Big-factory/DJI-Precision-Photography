#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H
/*Include file*/
//dji 类型
#include "dji_typedef.h"
//dji 相机管理模块
#include "dji_camera_manager.h"
//dji 高速通道
#include "dji_mop_channel.h"
//dji 平台相关信息
#include "dji_platform.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Exported functions definition ---------------------------------------------*/
/*! @brief 异步 API 示例：设置相机的曝光补偿值
 *
 *  @note 在此接口中，曝光补偿值会先获取再设置。
 *  @param index 有效载荷节点索引，输入限制参见枚举
 * DJI::OSDK::PayloadIndexType
 *  @param dataTarget 目标曝光补偿值
 *  @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetEV(E_DjiMountPosition position,
                                           E_DjiCameraManagerExposureCompensation exposureCompensation);
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


#ifdef __cplusplus
}
#endif

#endif