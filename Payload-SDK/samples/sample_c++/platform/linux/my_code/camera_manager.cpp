#include "camera_manager.h"
/*Include file*/
#include <utils/util_misc.h>
#include <time.h>
#include "dji_camera_manager.h"
//系统句柄库
#include "dji_platform.h"
//系统日志库
#include "dji_logger.h"
//高速传输库
#include "dji_mop_channel.h"

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
                                           E_DjiCameraManagerExposureCompensation exposureCompensation)
{
    //生成错误句柄
    T_DjiReturnCode returnCode;
    //生成曝光补偿值
    E_DjiCameraManagerExposureCompensation exposureCompensationTemp;

    //获取曝光补偿值
    returnCode = DjiCameraManager_GetExposureCompensation(position, &exposureCompensationTemp);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Get mounted position %d exposure compensation failed, error code: 0x%08X.",
                       position, returnCode);
    }
    //若曝光值相同则不进行曝光值设置
    if (exposureCompensationTemp == exposureCompensation) {
        USER_LOG_INFO("The mount position %d camera's exposure compensation is already what you expected.",
                      position);
        return DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS;
    }
    //设置曝光值
    returnCode = DjiCameraManager_SetExposureCompensation(position, exposureCompensation);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Set mounted position %d camera's exposure compensation %d failed,"
                       "error code: 0x%08X.", position, exposureCompensation, returnCode);
    }

    USER_LOG_INFO("Finish");

    return returnCode;
}
/*! @brief 使用异步接口设置相机对焦点的示例
 *
 * @note 在此接口中，对焦模式将被设置为自动(AUTO)。然后对焦点将被设置为 (x, y)。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param tapFocusPos 目标对焦点数据，x 和 y 取值范围 0~1
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetFocusPoint(E_DjiMountPosition position,
                                                   T_DjiCameraManagerFocusPosData focusPoint)
{
    T_DjiReturnCode returnCode;

    /*!< set camera focus mode to be CameraModule::FocusMode::AUTO */
    USER_LOG_INFO("Set mounted position %d camera's focus mode to auto mode.",
                  position);
    returnCode = DjiCameraManager_SetFocusMode(position, DJI_CAMERA_MANAGER_FOCUS_MODE_AUTO);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Set mounted position %d camera's focus mode(%d) failed,"
                       " error code :0x%08X.", position, DJI_CAMERA_MANAGER_FOCUS_MODE_AUTO,
                       returnCode);
        return returnCode;
    }

    USER_LOG_INFO("Set mounted position %d camera's focus point to (%0.1f, %0.1f).",
                  position, focusPoint.focusX, focusPoint.focusY);
    returnCode = DjiCameraManager_SetFocusTarget(position, focusPoint);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Set mounted position %d camera's focus point(%0.1f, %0.1f) failed,"
                       " error code :0x%08X.", position, focusPoint.focusX, focusPoint.focusY,
                       returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口设置相机指点变焦(Tap-Zoom)点的示例
 *
 * @note 在此接口中，将启用指点变焦功能并设置倍率。然后从目标点 (x, y) 开始执行指点变焦。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param multiplier 每次指点变焦的缩放倍率
 * @param tapZoomPosData 目标指点变焦位置数据，x 和 y 取值范围 0~1
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerSetTapZoomPoint(E_DjiMountPosition position, uint8_t multiplier,
                                                     T_DjiCameraManagerTapZoomPosData tapZoomPosData)
{
    T_DjiReturnCode returnCode;

    /*!< set camera tap zoom enable parameter to be enable */
    USER_LOG_INFO("Enable mounted position %d camera's tap zoom status.",
                  position);
    returnCode = DjiCameraManager_SetTapZoomEnabled(position, true);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Enable mounted position %d camera's tap zoom function failed,"
                       " error code :0x%08X.", position, returnCode);
        return returnCode;
    }

    /*!< set camera tap zoom multiplier parameter */
    USER_LOG_INFO("Set mounted position %d camera's tap zoom multiplier to %d x.",
                  position, multiplier);
    returnCode = DjiCameraManager_SetTapZoomMultiplier(position, multiplier);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Set mounted position %d camera's tap zoom multiplier(%d) failed,"
                       " error code :0x%08X.", position, multiplier, returnCode);
        return returnCode;
    }

    USER_LOG_INFO("Set mounted position %d camera's tap zoom point to (%f, %f).",
                  position, tapZoomPosData.focusX, tapZoomPosData.focusY);
    returnCode = DjiCameraManager_TapZoomAtTarget(position, tapZoomPosData);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Set mounted position %d camera's tap zoom target point(%f ,%f) failed,"
                       " error code :0x%08X.", position, tapZoomPosData.focusX, tapZoomPosData.focusY,
                       returnCode);
    }

    return returnCode;
}
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
                                                         E_DjiCameraZoomSpeed zoomSpeed)
{
    T_DjiReturnCode returnCode;

    //    USER_LOG_INFO("Mounted position %d camera start continuous optical zoom.\r\n", position);
    returnCode = DjiCameraManager_StartContinuousOpticalZoom(position, zoomDirection, zoomSpeed);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera start continuous zoom  failed,"
                       " error code :0x%08X.", position, returnCode);
    }

    return returnCode;
}

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
                                                 dji_f32_t factor)
{
    T_DjiReturnCode returnCode;
    T_DjiCameraManagerOpticalZoomParam opticalZoomParam;

    returnCode = DjiCameraManager_GetOpticalZoomParam(position, &opticalZoomParam);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Get mounted position %d camera's zoom param failed, error code :0x%08X",
                       position, returnCode);
        return returnCode;
    }

    USER_LOG_INFO("The mounted position %d camera's current optical zoom factor is:%0.1f x, "
                  "max optical zoom factor is :%0.1f x", position, opticalZoomParam.currentOpticalZoomFactor,
                  opticalZoomParam.maxOpticalZoomFactor);

    USER_LOG_INFO("Set mounted position %d camera's zoom factor: %0.1f x.", position, factor);
    returnCode = DjiCameraManager_SetOpticalZoomParam(position, zoomDirection, factor);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_INFO("Set mounted position %d camera's zoom factor(%0.1f) failed, error code :0x%08X",
                      position, factor, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口停止相机连续变焦的示例
 *
 * @note 仅支持：安装在 Osmo 上的 X5, X5R 和 X5S 相机（配备镜头 Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ），以及 Z3、Z30 相机。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopContinuousZoom(E_DjiMountPosition position)
{
    T_DjiReturnCode returnCode;

    USER_LOG_INFO("Mounted position %d camera stop continuous optical zoom.\r\n", position);
    returnCode = DjiCameraManager_StopContinuousOpticalZoom(position);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera stop continuous zoom failed,"
                       " error code :0x%08X", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口进行单张拍摄的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始拍摄单张照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootSinglePhoto(E_DjiMountPosition position)
{
    T_DjiReturnCode returnCode;
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    E_DjiCameraManagerWorkMode workMode;

    /*!< set camera work mode as shoot photo */
    USER_LOG_INFO("Set mounted position %d camera's work mode as shoot-photo mode", position);
    returnCode = DjiCameraManager_SetMode(position, DJI_CAMERA_MANAGER_WORK_MODE_SHOOT_PHOTO);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("set mounted position %d camera's work mode as shoot-photo mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }

    osalHandler->TaskSleepMs(1000);

    returnCode = DjiCameraManager_GetMode(position, &workMode);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("get mounted position %d camera's work mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }
    USER_LOG_INFO("Camera current workmode is %d", workMode);

    /*!< set shoot-photo mode */
    USER_LOG_INFO("Set mounted position %d camera's shoot photo mode as single-photo mode", position);
    returnCode = DjiCameraManager_SetShootPhotoMode(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_SINGLE);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("set mounted position %d camera's shoot photo mode as single-photo mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }

    /*! wait the APP change the shoot-photo mode display */
    USER_LOG_INFO("Sleep 0.5s...");
    osalHandler->TaskSleepMs(500);

    /*!< start to shoot single photo */
    USER_LOG_INFO("Mounted position %d camera start to shoot photo", position);
    returnCode = DjiCameraManager_StartShootPhoto(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_SINGLE);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Mounted position %d camera shoot photo failed, "
                       "error code :0x%08X", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口进行连拍的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始连拍照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param burstCount 每次连拍的照片数量
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootBurstPhoto(E_DjiMountPosition position,
                                                          E_DjiCameraBurstCount burstCount)
{
    T_DjiReturnCode returnCode;
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    E_DjiCameraManagerWorkMode workMode;

    /*!< set camera work mode as shoot photo */
    USER_LOG_INFO("set mounted position %d camera's work mode as shoot photo mode.", position);
    returnCode = DjiCameraManager_SetMode(position, DJI_CAMERA_MANAGER_WORK_MODE_SHOOT_PHOTO);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("set mounted position %d camera's work mode as shoot photo mode failed,"
                       " error code :0x%08X.", position, returnCode);
        return returnCode;
    }

    osalHandler->TaskSleepMs(1000);

    returnCode = DjiCameraManager_GetMode(position, &workMode);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("get mounted position %d camera's work mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }
    USER_LOG_INFO("Camera current workmode is %d", workMode);

    /*!< set shoot-photo mode */
    USER_LOG_INFO("Set mounted position %d camera's shoot photo mode as burst-photo mode", position);
    returnCode = DjiCameraManager_SetShootPhotoMode(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_BURST);
    if (returnCode == DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        return returnCode;
    }

    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("set mounted position %d camera's shoot photo mode as burst-photo mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }

    /*! wait the APP change the shoot-photo mode display */
    USER_LOG_INFO("Sleep 0.5s...");
    osalHandler->TaskSleepMs(500);

    /*!< set shoot-photo mode parameter */
    USER_LOG_INFO("Set mounted position %d camera's burst count to %d", position, burstCount);
    returnCode = DjiCameraManager_SetPhotoBurstCount(position, burstCount);

    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("set mounted position %d camera's burst count(%d) failed,"
                       " error code :0x%08X.", position, burstCount, returnCode);
        return returnCode;
    }
    /*!< start to shoot single photo */
    USER_LOG_INFO("Mounted position %d camera start to shoot photo.", position);
    returnCode = DjiCameraManager_StartShootPhoto(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_BURST);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Mounted position %d camera shoot photo failed, "
                       "error code :0x%08X.", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口开始定时拍摄(Interval Photo)的示例
 *
 * @note 在此接口中，相机将被设置为拍照模式(SHOOT_PHOTO)，然后开始定时拍摄照片。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param intervalData 定时拍摄的参数设置
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartShootIntervalPhoto(E_DjiMountPosition position,
                                                              T_DjiCameraPhotoTimeIntervalSettings intervalData)
{
    T_DjiReturnCode returnCode;
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    E_DjiCameraManagerWorkMode workMode;

    /*!< set camera work mode as shoot photo */
    USER_LOG_INFO("set mounted position %d camera's work mode as shoot photo mode.", position);
    returnCode = DjiCameraManager_SetMode(position, DJI_CAMERA_MANAGER_WORK_MODE_SHOOT_PHOTO);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("set mounted position %d camera's work mode as shoot photo mode failed,"
                       " error code :0x%08X.", position, returnCode);
        return returnCode;
    }

    osalHandler->TaskSleepMs(1000);

    returnCode = DjiCameraManager_GetMode(position, &workMode);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("get mounted position %d camera's work mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }
    USER_LOG_INFO("Camera current workmode is %d", workMode);

    /*!< set shoot-photo mode */
    USER_LOG_INFO("Set mounted position %d camera's shoot photo mode as interval-photo mode", position);
    returnCode = DjiCameraManager_SetShootPhotoMode(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_INTERVAL);
    if (returnCode == DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        return returnCode;
    }

    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("set mounted position %d camera's shoot photo mode as interval-photo mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }

    /*! wait the APP change the shoot-photo mode display */
    USER_LOG_INFO("Sleep 0.5s...");
    osalHandler->TaskSleepMs(500);

    /*!< set shoot-photo mode parameter */
    USER_LOG_INFO("Set mounted position %d camera's interval time to %d s", position, intervalData.timeIntervalSeconds);
    returnCode = DjiCameraManager_SetPhotoTimeIntervalSettings(position, intervalData);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("set mounted position %d camera's time interval parameter"
                       "(photo number:%d, time interval:%d) failed, error code :0x%08X.",
                       position, intervalData.captureCount, intervalData.timeIntervalSeconds, returnCode);
        return returnCode;
    }

    /*! wait the APP change the shoot-photo mode display */
    USER_LOG_INFO("Sleep 0.5s...");
    osalHandler->TaskSleepMs(500);

    /*!< start to shoot single photo */
    USER_LOG_INFO("Mounted position %d camera start to shoot photo.", position);
    returnCode = DjiCameraManager_StartShootPhoto(position, DJI_CAMERA_MANAGER_SHOOT_PHOTO_MODE_INTERVAL);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera shoot photo failed, "
                       "error code :0x%08X.", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口停止拍摄的示例
 *
 * @note 在此接口中，相机将停止所有的拍摄动作。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopShootPhoto(E_DjiMountPosition position)
{
    T_DjiReturnCode returnCode;

    USER_LOG_INFO("Mounted position %d camera stop to shoot photo.", position);
    returnCode = DjiCameraManager_StopShootPhoto(position);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera stop to shoot photo failed,"
                       " error code:0x%08X.", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口开始录制视频的示例
 *
 * @note 在此接口中，相机将被设置为录像模式(RECORD_VIDEO)，然后开始录制。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStartRecordVideo(E_DjiMountPosition position)
{
    T_DjiReturnCode returnCode;
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    E_DjiCameraManagerWorkMode workMode;

    /*!< set camera work mode as record video */
    USER_LOG_INFO("set mounted position %d camera's work mode as record-video mode", position);
    returnCode = DjiCameraManager_SetMode(position, DJI_CAMERA_MANAGER_WORK_MODE_RECORD_VIDEO);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("set mounted position %d camera's work mode as record-video mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }

    osalHandler->TaskSleepMs(1000);

    returnCode = DjiCameraManager_GetMode(position, &workMode);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("get mounted position %d camera's work mode failed,"
                       " error code :0x%08X", position, returnCode);
        return returnCode;
    }
    USER_LOG_INFO("Camera current workmode is %d", workMode);

    /*!< start to take video */
    USER_LOG_INFO("Mounted position %d camera start to record video.", position);
    returnCode = DjiCameraManager_StartRecordVideo(position);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera start to record video failed,"
                       " error code:0x%08X.", position, returnCode);
    }

    return returnCode;
}

/*! @brief 使用异步接口停止录制视频的示例
 *
 * @note 在此接口中，相机将停止视频录制。
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_CameraManagerStopRecordVideo(E_DjiMountPosition position)
{
    T_DjiReturnCode returnCode;
    USER_LOG_INFO("Mounted position %d camera stop to record video.", position);
    returnCode = DjiCameraManager_StopRecordVideo(position);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Mounted position %d camera stop to record video failed,"
                       " error code:0x%08X.", position, returnCode);
    }

    return returnCode;
}