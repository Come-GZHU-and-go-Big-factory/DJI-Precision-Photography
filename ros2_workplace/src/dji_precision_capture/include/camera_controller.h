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

enum class TestState{
    IDLE,       //云台复位，等待信息
    Calculate,
    GimbalAct,  //云台执行动作，运动到指定位置
    CameraAct,  //相机执行动作，进行变焦
    Capture,    //捕获照片
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
        returnCode = MY_CameraSourceSet(mountPosition,camerasource);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
            USER_LOG_ERROR("init position %d camera's camera source failed, error code: 0x%08X\r\n",
                        mountPosition, returnCode);
        }

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
    //测试状态机
    TestState teststate = TestState::IDLE;
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
    //设置相机使用的视频源
    E_DjiCameraManagerStreamSource camerasource = DJI_CAMERA_MANAGER_SOURCE_ZOOM_CAM;
    
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
    float x;
    float y;
    //指点计算
    float foc_phy = 7.1;
    //当前放大倍数
    dji_f32_t now_factor = 0;
    //上一次期望放大倍数
    dji_f32_t last_desire_factor = 0;
    //这次计算的期望放大倍数
    dji_f32_t desire_factor = 0;
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

    float desire_pitch = 0;
    //设定期望的大小为画面高度的1/4
    float desire_high = 1/4;

    T_DjiCameraManagerOpticalZoomParam now_zoom_param;

    rclcpp::Time last_received_time{0};

    rclcpp::Time receive_time{0};


    //其他标志位
    bool IsGimbalCommandSend = false;
    bool IsCameraCommandSend = false;
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
    switch (teststate) {
        case TestState::IDLE:
            //等待相机获取目标信息
            break;
        case TestState::Calculate:
            //进行计算
            //需要注意当前相机使用的是广角端视频流还是变焦段视频流
            //Step 1:计算像素焦距
            if (camerasource == DJI_CAMERA_MANAGER_SOURCE_ZOOM_CAM) {
                foc_pix = (foc_phy*now_factor)*image_wide/sensor_wide;
            }else if (camerasource == DJI_CAMERA_MANAGER_SOURCE_WIDE_CAM) {
                foc_pix = foc_phy*image_wide/sensor_wide;
            }
            //Step 2:计算旋转角度
            desire_yaw = (x-center_x)/foc_pix;
            desire_pitch = (y-center_y)/foc_pix;
            desire_GimbalAngle.z = desire_yaw;
            desire_GimbalAngle.y = desire_pitch;
            //Step 3:计算放大倍数
            desire_factor = now_factor*(image_high*desire_high/detect_high);

            //状态转换至云台控制
            teststate = TestState::GimbalAct;
            break;
        case TestState::GimbalAct:
            if (!IsGimbalCommandSend) {
                //相对角度变焦
                rotation.rotationMode = DJI_GIMBAL_ROTATION_MODE_RELATIVE_ANGLE;
                //设定角度
                rotation.pitch = desire_pitch;
                rotation.yaw   = desire_yaw;
                rotation.roll  = 0;
                MY_GimbalRotate(mountPosition,rotation);
                IsGimbalCommandSend = true;
            }
            //获取云台角度
            MY_DataSubGimbalAngle((uint8_t *) &this->gimbalAngles,&this->angle_timestamp);
            if(nearEqual(gimbalAngles, desire_GimbalAngle,3)){
                //状态转换至相机控制
                teststate = TestState::CameraAct;
            }
            break;
        case TestState::CameraAct:
            if (!IsCameraCommandSend) {
                //发送指令
                MY_CameraAllDirectionOpticalZoom(mountPosition,desire_factor);
                IsCameraCommandSend = true;
            }
            DjiCameraManager_GetOpticalZoomParam(mountPosition, &now_zoom_param);
            if(!(sqrt((now_zoom_param.currentOpticalZoomFactor-desire_factor)*(now_zoom_param.currentOpticalZoomFactor-desire_factor)<0.3))){
                teststate = TestState::Capture;
            }
            break;
        case TestState::Capture:
                MY_CameraManagerStartShootSinglePhoto(mountPosition);
            break;
    }
}
#endif