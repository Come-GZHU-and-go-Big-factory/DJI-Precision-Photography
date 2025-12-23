#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H
/*Include file*/
//dji 类型
#include "dji_typedef.h"
//dji 相机管理模块
#include "dji_camera_manager.h"
//dji 高速通道
#include "dji_mop_channel.h"

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


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#endif