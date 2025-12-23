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

    return returnCode;
}
