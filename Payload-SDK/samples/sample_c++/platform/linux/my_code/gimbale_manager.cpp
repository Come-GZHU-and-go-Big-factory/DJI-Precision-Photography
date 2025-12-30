#include "gimbal_manager.h"

/*! @brief 云台旋转函数
 *
 * @note 输入结构体rotation 指定旋转模式与旋转参数，对三轴进行旋转
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalRotate(E_DjiMountPosition mountPosition, T_DjiGimbalManagerRotation rotation)
{
    T_DjiReturnCode returnCode;
    returnCode = DjiGimbalManager_Rotate(mountPosition,rotation);

    //获取当前的角度，是否为
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
    USER_LOG_ERROR("Target gimbal pry yaw:%f,pitch:%f,roll:%f failed, error code: 0x%08X",
            rotation.yaw,rotation.pitch,rotation.roll);
    }
    return returnCode;
}

/*! @brief 云台旋转速度控制器
 *
 * @note 输入maxspeed实现控制最大速度的功能
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param maxSpeedPercentage 最大速度值，推荐计算公式为speed = default_max_spd*x/100 使用百分比的方式进行设定
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalSetAllMaxSpeed(E_DjiMountPosition mountPosition, uint8_t maxSpeedPercentage)
{
    //定义错误代码
    T_DjiReturnCode returnCode;
    
    E_DjiGimbalAxis AllAxis[3] = {DJI_GIMBAL_AXIS_PITCH, /*!< Pitch axis. */
        DJI_GIMBAL_AXIS_ROLL, /*!< Roll axis. */
        DJI_GIMBAL_AXIS_YAW, /*!< Yaw axis. */};
    for(int i=0;i<3;i++)
    {
        E_DjiGimbalAxis axis = AllAxis[i];
        returnCode = DjiGimbalManager_SetControllerMaxSpeedPercentage(mountPosition,axis,maxSpeedPercentage);
        if(returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            switch(axis)
            {
                case 0:USER_LOG_INFO("Gimbal's Pitch set max speed %f fail! code:0x%08X",returnCode,maxSpeedPercentage);
                case 1:USER_LOG_INFO("Gimbal's Roll set max speed %f fail! code:0x%08X",returnCode,maxSpeedPercentage);
                case 2:USER_LOG_INFO("Gimbal's Yaw set max speed %f fail! code:0x%08X",returnCode,maxSpeedPercentage);
            }
        }
    }
    
    return returnCode;
}
/*! @brief 云台控制器平滑系数
 *
 * @note 输入平滑系数，实现平滑控制
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @param axis 需要设定速度的轴，输入限制详见枚举 DJI::OSDK::E_DjiGimbalAxis
 * @param smoothingFactor 平滑因子。值越大，云台加速越慢
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalSetAllSmoothFactor(E_DjiMountPosition mountPosition, uint8_t smoothingFactor)
{
    T_DjiReturnCode returnCode;

    E_DjiGimbalAxis AllAxis[3] = {DJI_GIMBAL_AXIS_PITCH, /*!< Pitch axis. */
        DJI_GIMBAL_AXIS_ROLL, /*!< Roll axis. */
        DJI_GIMBAL_AXIS_YAW, /*!< Yaw axis. */};
    for(int i=0;i<3;i++)
    {
        E_DjiGimbalAxis axis = AllAxis[i];
        returnCode = DjiGimbalManager_SetControllerSmoothFactor(mountPosition,axis,smoothingFactor);
        if(returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            switch(axis)
            {
                case 0:USER_LOG_INFO("Gimbal's Pitch set max speed %f fail! code:0x%08X",returnCode,smoothingFactor);
                case 1:USER_LOG_INFO("Gimbal's Roll set max speed %f fail! code:0x%08X",returnCode,smoothingFactor);
                case 2:USER_LOG_INFO("Gimbal's Yaw set max speed %f fail! code:0x%08X",returnCode,smoothingFactor);
            }
        }
    }
    
    return returnCode;
}
/*! @brief 恢复出厂设置
 *
 * @note 调用这个函数，恢复出厂设置
 * @param position 负载挂载位置索引，输入限制详见枚举 DJI::OSDK::PayloadIndexType
 * @return T_DjiReturnCode 错误码
 */
T_DjiReturnCode MY_GimbalResetParam(E_DjiMountPosition mountPosition)
{
    T_DjiReturnCode returnCode;

    returnCode = DjiGimbalManager_RestoreFactorySettings(mountPosition);
    if(returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_INFO("Gimbal Restor fail! error code:0x%08X",returnCode);
    }
    return returnCode;
}