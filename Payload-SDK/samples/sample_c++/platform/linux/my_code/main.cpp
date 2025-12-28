#include "camera_manager.h"
//应用程序的核心框架
#include "application.hpp"
//PSDK的日志模块
#include "dji_logger.h"
//获取无人机的基本信息
#include "dji_aircraft_info.h"
//C标准头文件 捕获信号后实现平稳退出
#include "signal.h"
//PSDK 头文件
#include "dji_platform.h"


int main(int argc, char **argv)
{
    //创建signal，以便安全退出
    signal(SIGINT, [](int signalNum) -> void { exit(0); });
    //进行系统初始化
    Application application(argc, argv);
    //创建系统句柄
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    //创建返回错误代码
    T_DjiReturnCode returnCode;
    //创建相机类型
    E_DjiCameraType cameraType;
    //创建固件类型
    T_DjiCameraManagerFirmwareVersion firmwareVersion;
    //创建对焦点
    T_DjiCameraManagerFocusPosData focusPosData;
    //创建变焦数据
    T_DjiCameraManagerTapZoomPosData tapZoomPosData;
    //创建相机位置
    E_DjiMountPosition mountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1;

    // 1. 定义变量
    T_DjiCameraManagerFocusPosData focusPoint;

    E_DjiCameraZoomDirection zoomDirection;

    E_DjiCameraZoomSpeed zoomSpeed;

    // 2. 赋值：设置在画面正中心
    focusPoint.focusX = 0.5f;
    focusPoint.focusY = 0.5f;


    //Step1:初始化相机
    USER_LOG_INFO("--> Step 1: Init camera manager module");
    returnCode = DjiCameraManager_Init();
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Init camera manager failed, error code: 0x%08X\r\n", returnCode);
        goto exitCameraModule;
    }
    //Step2:获取相机类型和版本
    USER_LOG_INFO("--> Step 2: Get camera type and version");
    returnCode = DjiCameraManager_GetCameraType(mountPosition, &cameraType);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Get mounted position %d camera's type failed, error code: 0x%08X\r\n",
                       mountPosition, returnCode);
        goto exitCameraModule;
    }

    returnCode = DjiCameraManager_GetFirmwareVersion(mountPosition, &firmwareVersion);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Get mounted position %d camera's firmware version failed, error code: 0x%08X\r\n",
                       mountPosition, returnCode);
        goto exitCameraModule;
    }
    USER_LOG_INFO("Mounted position %d camera's firmware is V%02d.%02d.%02d.%02d\r\n", mountPosition,
                firmwareVersion.firmware_version[0], firmwareVersion.firmware_version[1],
                firmwareVersion.firmware_version[2], firmwareVersion.firmware_version[3]);

    MY_CameraManagerStartContinuousZoom(mountPosition,zoomDirection,zoomSpeed);

    exitCameraModule:
        returnCode = DjiCameraManager_DeInit();
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Camera manager deinit failed ,error code :0x%08X", returnCode);
        }

        USER_LOG_INFO("Camera manager sample end");
        return returnCode;
}