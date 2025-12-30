#ifndef GIMBAL_MANAGER_H
#define GIMBAL_MANAGER_H

/*INCLUDE*/
/*平台抽象层 用于定义平台句柄*/
#include "dji_platform.h"
/*日志系统   用于写入日志*/
#include "dji_logger.h"
/*云台管理核心*/
#include "dji_gimbal_manager.h"
/*无人机数据订阅*/
#include "dji_fc_subscription.h"
/*飞行器信息*/
#include "dji_aircraft_info.h"

#include "dji_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief 云台旋转函数
 *
 * @note 输入结构体rotation 指定旋转模式与旋转参数，对三轴进行旋转
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalRotate(E_DjiMountPosition mountPosition, T_DjiGimbalManagerRotation rotation);

/*! @brief 云台旋转速度控制器
 *
 * @note 输入maxspeed实现控制最大速度的功能
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param axis 需要设定速度的轴，输入限制详见枚举 DJI::OSDK::E_DjiGimbalAxis
 * @param maxSpeedPercentage 最大速度值，推荐计算公式为speed = default_max_spd*x/100 使用百分比的方式进行设定
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalSetMaxSpeed(E_DjiMountPosition mountPosition, E_DjiGimbalAxis axis, uint8_t maxSpeedPercentage);

/*! @brief 云台控制器平滑系数
 *
 * @note 输入平滑系数，实现平滑控制
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param axis 需要设定速度的轴，输入限制详见枚举 DJI::OSDK::E_DjiGimbalAxis
 * @param smoothingFactor 平滑因子。值越大，云台加速越慢
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalSetSmoothFactor(E_DjiMountPosition mountPosition, E_DjiGimbalAxis axis, uint8_t smoothingFactor);

/*! @brief 恢复出厂设置
 *
 * @note 调用这个函数，恢复出厂设置
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalResetParam(E_DjiMountPosition mountPosition);

#ifdef __cplusplus
}
#endif

#endif