#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
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
//云台管理头文件
#include "gimbal_manager.h"

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

#include "dji_camera_manager.h"

#include <chrono>

#include "memory.h"

#include "math.h"

using namespace std::chrono_literals;

enum class TaskState{
    IDLE,           //该状态执行:云台复位、定时拍照
    WideAngleTask,  //该状态执行:在广角端视频流状态下，实现初步对准
    ZoomViewTask,   //该状态执行:STEP1:在1x状态下对准目标，STEP2:放大到目标占据画面的1/3，同时控制云台对准目标
    Capture        //该状态执行:照片捕获
};

class camera_controller:public rclcpp::Node
{
public:
    camera_controller(int argc, char** argv):rclcpp::Node("camera_controller")
    {
        //进行系统初始化
        Application application(argc, argv);

        osalHandler = DjiPlatform_GetOsalHandler();

        //无人机基础Info订阅
        T_DjiAircraftInfoBaseInfo baseInfo;
        returnCode = DjiAircraftInfo_GetBaseInfo(&baseInfo);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Failed to get aircraft base info, return code 0x%08X", returnCode);
        }

        //相机初始化
        //Step1:初始化相机
        USER_LOG_INFO("--> Step 1: Init camera manager module");
        returnCode = DjiCameraManager_Init();
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Init camera manager failed, error code: 0x%08X\r\n", returnCode);
        }
        //Step2:获取相机类型和版本
        USER_LOG_INFO("--> Step 2: Get camera type and version");
        returnCode = DjiCameraManager_GetCameraType(mountPosition, &cameraType);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Get mounted position %d camera's type failed, error code: 0x%08X\r\n",
                        mountPosition, returnCode);
        }
        returnCode = DjiCameraManager_GetFirmwareVersion(mountPosition, &firmwareVersion);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Get mounted position %d camera's firmware version failed, error code: 0x%08X\r\n",
                        mountPosition, returnCode);
        }
        USER_LOG_INFO("Mounted position %d camera's firmware is V%02d.%02d.%02d.%02d\r\n", mountPosition,
                    firmwareVersion.firmware_version[0], firmwareVersion.firmware_version[1],
                    firmwareVersion.firmware_version[2], firmwareVersion.firmware_version[3]);

        //云台初始化
        //  Step 1:云台初始化
        USER_LOG_INFO("--> Step 1: Init gimbal manager module");
        returnCode = DjiGimbalManager_Init();
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Init gimbal manager failed, error code: 0x%08X", returnCode);
        }
        //  Step 2:云台设置为自由运动模式
        USER_LOG_INFO("--> Step 2: Set gimbal to free mode");
        returnCode = DjiGimbalManager_SetMode(mountPosition, gimbalMode);
        //  Step 3:重置云台角度
        USER_LOG_INFO("--> Step 3: Reset gimbal angles.\r\n");
        returnCode = DjiGimbalManager_Reset(mountPosition, DJI_GIMBAL_RESET_MODE_PITCH_AND_YAW);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("Reset gimbal failed, error code: 0x%08X", returnCode);
        }

        //数据订阅
        // 云台状态订阅设置
        USER_LOG_INFO("--> Step 1: Init gimbal data subscribation");
        DjiFcSubscription_Init();
        // 利用函数将数据获取到指定空间
        MY_SubGimbalAngle();

        USER_LOG_INFO("gimbal angle :%f,%f,%f",gimbalAngles.x,gimbalAngles.y,gimbalAngles.z);
        osalHandler->TaskSleepMs(2000);

        camera_controller_loop_timer = this->create_wall_timer(50ms,
            std::bind(&camera_controller::camera_control_loop,this));

        

    }

    int camera_control_loop();

    int camera_control();

    bool nearEqual(const T_DjiFcSubscriptionGimbalAngles& gimbalAngles , const T_DjiFcSubscriptionGimbalAngles& last_desire_GimbalAngle, double eps);

private:
    //状态机变量
    TaskState taskstate = TaskState::IDLE;
    //系统级别变量
    //创建系统句柄
    T_DjiOsalHandler *osalHandler;
    //创建返回错误代码
    T_DjiReturnCode returnCode;

    //相机
    //创建相机类型
    E_DjiCameraType cameraType;
    //创建固件类型
    T_DjiCameraManagerFirmwareVersion firmwareVersion;

    //相机控制内容
    //创建对焦点
    T_DjiCameraManagerFocusPosData focusPosData;
    //创建变焦数据
    T_DjiCameraManagerTapZoomPosData tapZoomPosData;
    //创建相机位置
    E_DjiMountPosition mountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1;
    //创建变焦方向
    E_DjiCameraZoomDirection zoomDirection;
    //创建变焦速度变量
    E_DjiCameraZoomSpeed zoomSpeed;
    
    //云台
    //云台工作模式
    E_DjiGimbalMode gimbalMode = DJI_GIMBAL_MODE_FREE;
    //云台旋转模式
    T_DjiGimbalManagerRotation rotation;

    //数据订阅
    //云台角度
    T_DjiFcSubscriptionGimbalAngles gimbalAngles = {0,0,0};
    //时间戳
    T_DjiDataTimestamp angle_timestamp = {0,0};

    rclcpp::TimerBase::SharedPtr camera_controller_loop_timer;

    //识别结果
    int x;
    int y;
    //指点计算
    float foc_phy = 7.1;
    //当前放大倍数
    float now_factor = 0;
    //上一次期望放大倍数
    float last_desire_factor = 0;
    //这次计算的期望放大倍数
    float desire_factor = 0;
    //目标高度
    float detect_high = 0;
    //目标宽度
    float detect_wide = 0;

    //像素焦距
    float foc_pix = 0;
    //上一次期望的云台角度
    T_DjiFcSubscriptionGimbalAngles last_desire_GimbalAngle = {0,0,0};
    //这一次期望的云台角度
    T_DjiFcSubscriptionGimbalAngles desire_GimbalAngle = {0,0,0};

    //画面像素宽度
    float image_wide = 0;
    //画面像素高度
    float image_high = 0;
    //画面中心
    float center_x = image_wide/2;

    float center_y = image_high/2;

    float sensor_wide = 7.6;

    float desire_yaw = 0;

    float deisre_pitch = 0;
    //设定期望的大小为画面高度的1/4
    float desire_high = 1/4;

    rclcpp::Time last_received_time = 0;

    rclcpp::Time receive_time = 0;
};

bool camera_controller::nearEqual(const T_DjiFcSubscriptionGimbalAngles& gimbalAngles, const T_DjiFcSubscriptionGimbalAngles& last_desire_GimbalAngle, double eps)
{
    double dx = gimbalAngles.x - last_desire_GimbalAngle.x;
    double dy = gimbalAngles.y - last_desire_GimbalAngle.y;
    double dz = gimbalAngles.z - last_desire_GimbalAngle.z;
    return sqrt(dx*dx + dy*dy + dz*dz) < (eps*eps);
}

int camera_controller::camera_control()
{
    switch (this->taskstate) {
        case TaskState::IDLE:
            //  复位至90度、后续按照1s每次拍照
            break;
        case TaskState::WideAngleTask:
            //  根据广角端下计算的角度，进行初步对准
            break;
        case TaskState::ZoomViewTask:
            //  STEP1:在1x条件下，初步对准 STEP2:变焦的同时执行云台对准
            break;
        case TaskState::Capture:
            //  捕获照片，同时在队列中删除这一对象
            break;
    }       
    
}

int camera_controller::camera_control_loop()
{
    //检查信息是否有更新  
    if (receive_time==last_received_time) {return 0;}

    //检查云台角度是否到位
    //获取云台角度
    MY_DataSubGimbalAngle((uint8_t *) &this->gimbalAngles,&this->angle_timestamp);
    //对比云台角度，判断是否到位
    if(!nearEqual(gimbalAngles, last_desire_GimbalAngle,3)){return 0;}
    //对比放大倍数，判断是否到位
    if(!(sqrt((now_factor-last_desire_factor)*(now_factor-last_desire_factor)<0.5))){return 0;}
    //计算云台角度
    foc_pix = (foc_phy*now_factor)*image_wide/sensor_wide;

    


    USER_LOG_INFO("gimbal angle :%f,%f,%f",gimbalAngles.x,gimbalAngles.y,gimbalAngles.z);

    // osalHandler->TaskSleepMs(100);
    //计算变焦大小
    desire_factor = now_factor*(image_high*desire_high/detect_high);

    //检查云台是否到位



    
}
#endif