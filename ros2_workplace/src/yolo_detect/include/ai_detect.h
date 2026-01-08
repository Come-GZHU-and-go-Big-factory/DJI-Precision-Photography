#ifndef AI_DETECT_H
#define AI_DETECT_H

/*头文件*/
//控制台输入输出
#include <iostream>
//字符串 向量 队列
#include <string>
#include <vector>
#include <queue>
//日志输出
#include <dji_logger.h>
//用于mkdir
#include <sys/stat.h>
#include <sys/types.h>
//SDK基础类型定义
#include "dji_typedef.h"
//视频流发送接口
#include "dji_payload_camera.h"
//高速通道带宽配置
#include "dji_high_speed_data_channel.h"
//时间戳、线程、时间格式化
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
//文件读写功能
#include <fstream>

//定义类别标签
static const char* s_classLables[] = {
    "person",        "bicycle",       "car",           "motorbike",
    "aeroplane",     "bus",           "train",         "truck",
    "boat",          "traffic light", "fire hydrant",  "stop sign",
    "parking meter", "bench",         "bird",          "cat",
    "dog",           "horse",         "sheep",         "cow",
    "elephant",      "bear",          "zebra",         "giraffe",
    "backpack",      "umbrella",      "handbag",       "tie",
    "suitcase",      "frisbee",       "skis",          "snowboard",
    "sports ball",   "kite",          "baseball bat",  "baseball glove",
    "skateboard",    "surfboard",     "tennis racket", "bottle",
    "wine glass",    "cup",           "fork",          "knife",
    "spoon",         "bowl",          "banana",        "apple",
    "sandwich",      "orange",        "broccoli",      "carrot",
    "hot dog",       "pizza",         "donut",         "cake",
    "chair",         "sofa",          "pottedplant",   "bed",
    "diningtable",   "toilet",        "tvmonitor",     "laptop",
    "mouse",         "remote",        "keyboard",      "cell phone",
    "microwave",     "oven",          "toaster",       "sink",
    "refrigerator",  "book",          "clock",         "vase",
    "scissors",      "teddy bear",    "hair drier",    "toothbrush",
};

//定义日期名
static const char* s_invalidLables[] = {
    "XXX", "WW", "YYYYYYYYYYY", "ZZZZZZZZ"
};

#ifdef OPEN_CV_INSTALLED
//图像处理与DNN推理
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/core.hpp>

//yolo检测封装
#include "liveview/image_processor_yolovfastest.hpp"
#endif
/*ROS2头文件*/
#include "rclcpp/rclcpp.hpp"

/* Private constants ---------------------------------------------------------*/
//标签数量常量
#define YOLO_LABLES_NUM       76
//决定注册Pilot的类别数
#define INVALID_CLASS_NUM     4

class ai_detect:public rclcpp::Node{
    public:
    //构造函数
    ai_detect(int argc,char ** argv):rclcpp::Node("ai_detect")
    {
        //H30T相机位于位置1
        mountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1;
        //设置H30T变焦视频流
        MediaResource = DJI_LIVEVIEW_CAMERA_SOURCE_M30T_ZOOM;

        osalHandler = DjiPlatform_GetOsalHandler();
        // 输出用户选择的码流
        USER_LOG_INFO("Input cammera sourece: ");
        switch(mediaSource)
        {
            case 0:USER_LOG_INFO("app liveview");break;
            case 1:USER_LOG_INFO("1080P for H30T");break;
            case 7:USER_LOG_INFO("4k for H30T");break;
        }

        // 生成带时间戳的输出文件名
        std::string timestamp = getCurrentTimestamp();

        // 创建输出目录，避免目录不存在导致的写文件失败
        mkdir ("data", 0755);
        // 广角端视频流保存名
        std::string h264FileName = "data/output_" + timestamp + ".h264";
        // 变焦段视频流保存名
        std::string zoomh264FileName = "data/zoomoutput_" + timestamp + ".h264";
        // 打开H264输出文件，保存码流
        outFileH264.open(h264FileName, std::ios::out | std::ios::binary | std::ios::app);
        if (!outFileH264) {
            std::cerr << "cant open " << h264FileName << std::endl;
        }


        #ifdef OPEN_CV_INSTALLED
            // 创建s_metaQueueMutexHandle和s_imageQueueMutexHandle互斥锁
            osalHandler->MutexCreate(&s_metaQueueMutexHandle);
            osalHandler->MutexCreate(&s_imageQueueMutexHandle);
            osalHandler->TaskCreate("objectDetectionTask",DjiLiveview_ObjectDetectionThread,1024*1024,NULL, &s_procThreadHandle);
            if (processor.Init() != 0) {
                std::cerr << "Failed to initialize the processor." << std::endl;
                return ;
            }
        #endif 
        //高带宽通道 三类流量带宽占比
        const T_DjiDataChannelBandwidthProportionOfHighspeedChannel bandwidthProportionOfHighspeedChannel =
            {10, 60, 30};
        //配置通道带宽
        returnCode = DjiHighSpeedDataChannel_SetBandwidthProportion(bandwidthProportionOfHighspeedChannel);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR("Liveview init failed, HighSpeed channel init error: 0x%08llX", returnCode);
            return;
        }

        //初始化
        USER_LOG_INFO("step 1: init liveview");
        returnCode = DjiLiveview_Init();
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR("Liveview init faild, ret: 0x%08llX", returnCode);
        }

        //注册标签
        #ifdef OPEN_CV_INSTALLED
            returnCode = DjiLiveview_RegUserAiTargetLableList(YOLO_LABLES_NUM, s_classLables);
        #else
            returnCode = DjiLiveview_RegUserAiTargetLableList(INVALID_CLASS_NUM, s_invalidLables);
        #endif
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR("Reg ai target lable faild, ret: 0x%08llX", returnCode);
        }

        //启动解码，将视频流解码为图像流订阅，并注册回调
        USER_LOG_INFO("step 2: reg encoder callback");
        returnCode = DjiLiveview_RegEncoderCallback(DjiLiveview_EncoderUseCallback);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR( "reg Yuv Encoder callback faild, ret: 0x%08llX", returnCode);
        }
        //启动YUV流
        USER_LOG_INFO("step 3:start yuv stream");
        returnCode = DjiLiveview_StartImageStream(CameraPostion, MediaResource,
                                                PIXFMT_RGB_PACKED ,DjiLiveview_RcvImageCallback);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR( "start to subscribe YUV stream failed, ret: 0x%08llX", returnCode);
        }
    }
    //接受回调函数
    static void DjiLiveview_RcvImageCallback(E_DjiLiveViewCameraPosition position, const uint8_t *buf, uint32_t len, T_DjiLiveviewImageInfo imageInfo);
    //编码器回调函数 存储H264视频
    static void DjiLiveview_EncoderUseCallback(const uint8_t *buf, uint32_t len);
    //识别线程
    void* DjiLiveview_ObjectDetectionThread(void *arg);
    //获取时间戳 用于H264文件
    static std::string getCurrentTimestamp();
    
    //H264码流输出为文件
    static void outH264Tofile(const uint8_t *buf, int32_t len);
    //YUV码流输出为文件
    static void outYUVTofile(const uint8_t *buf, int32_t len);

    private:
    //定义系统级变量
    T_DjiOsalHandler *osalHandler;
    //定义错误代码
    T_DjiReturnCode returnCode;
    //无人机位置变量
    E_DjiMountPosition mountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1;
    //定义视频流来源
    int mediaSource = 7; //support 0(app liveview)/1(1080p)/7(4k) for H30 camera
    //视频源设定
    E_DjiLiveViewCameraSource MediaResource;
    //相机位置
    E_DjiLiveViewCameraPosition CameraPostion;

    //H264码流的文件输出流
    static std::ofstream outFileH264;
    //YUV原始图像数据的文件输出流
    static std::ofstream outFileYUV;
    
    #ifdef OPEN_CV_INSTALLED
        inline static ImageProcessorYolovFastest processor("YOLOvFastest");
        //照片队列
        static std::queue<cv::Mat> s_imageQueue;
        //元数据队列
        static std::queue<T_DjiLiveViewStandardMetaData *> s_metaQueue;
        //检测线程的句柄，用来掌控检测线程
        T_DjiTaskHandle s_procThreadHandle;
        //元数据队列互斥锁
        T_DjiMutexHandle s_metaQueueMutexHandle;
        //图像队列互斥锁
        T_DjiMutexHandle s_imageQueueMutexHandle;
    #endif
};

//处理回调函数
static void* ai_detect::DjiLiveview_ObjectDetectionThread(void *arg) {
    //创建错误代码
    T_DjiReturnCode DjiStat;
    //创建系统句柄
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();

    while(1) {
        #ifdef OPEN_CV_INSTALLED
        //启动imag线程锁
        osalHandler->MutexLock(s_imageQueueMutexHandle);
        if (s_imageQueue.empty()) {
            //如果没有图片则取消image线程锁
            osalHandler->MutexUnlock(s_imageQueueMutexHandle);
            continue;
        }
        //获取队列最前面的一帧图像
        cv::Mat rgb_image = s_imageQueue.front();
        //移除该帧
        s_imageQueue.pop();
        //完成东西获取的任务，取消image线程锁
        osalHandler->MutexUnlock(s_imageQueueMutexHandle);
        //定义存储BGR的图像
        cv::Mat bgr_image;
        //将图像从BGR转变为RGB
        cv::cvtColor(rgb_image, bgr_image, cv::COLOR_RGB2BGR);
        //将转化的BGR转变为share_ptr，方便在内部异步引用
        std::shared_ptr<cv::Mat> image_ptr = std::make_shared<cv::Mat>(bgr_image);
        //定义接收检测结果的容器
        std::vector<T_DjiLiveViewBoundingBox> bounding_boxes;
        
        //推理
        processor.Process(image_ptr, bounding_boxes);

        //记录存在多少个检测框
        T_DjiLiveViewStandardMetaData *metaData = (T_DjiLiveViewStandardMetaData *)malloc(
            sizeof(T_DjiLiveViewStandardMetaData) + bounding_boxes.size() * sizeof(T_DjiLiveViewBoundingBox));
        metaData->   = bounding_boxes.size();
        for (int i = 0; i < bounding_boxes.size(); i++) {
            metaData->boxData[i] = bounding_boxes[i];
        }

        DjiLiveview_SendAiMetaToPilot(metaData);
        //开启元数据队列锁
        osalHandler->MutexLock(s_metaQueueMutexHandle);
        //传入元数据
        s_metaQueue.push(metaData);
        //取消元数据队列锁
        osalHandler->MutexUnlock(s_metaQueueMutexHandle);

        #else
            break;
        #endif
    }
    return NULL;
}

//编码回调保存函数
static void ai_detect::DjiLiveview_EncoderUseCallback(const uint8_t *buf, uint32_t len){
    //定义错误代码
    T_DjiReturnCode returnCode;
    //将H264文件存储到本地
    outH264Tofile(buf, len);
    //如果不是M4D无人机
    if (aircraftInfoBaseInfo.aircraftSeries != DJI_AIRCRAFT_SERIES_M4D)
    {
        //发送视频流
        returnCode = DjiPayloadCamera_SendVideoStream(buf, len);
        if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS)
        {
            USER_LOG_ERROR("failed to send video to pilot, ret: 0x%08llX", returnCode);
        }
    }
}

//图像帧处理回调函数
static void ai_detect::DjiLiveview_RcvImageCallback(E_DjiLiveViewCameraPosition position, const uint8_t *buf, uint32_t len, T_DjiLiveviewImageInfo imageInfo){
    //定义错误代码
    T_DjiReturnCode DjiStat;
    //输出长度变量
    uint32_t OutPutLen;
    //目标框容器
    std::vector<T_DjiLiveViewBoundingBox> bounding_boxes;
    //打印图像信息
    USER_LOG_INFO("catch image frame data, image type = %d  height = %d, width = %d, frameId = %d, bufferLen= %d",
                  imageInfo.pixFmt ,imageInfo.height, imageInfo.width, imageInfo.frameId, len);
    //AI元数据指针
    T_DjiLiveViewStandardMetaData * metaData = nullptr;
    //获取系统级指针
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();

#ifdef OPEN_CV_INSTALLED
    //将图像缓冲区封装为一个opencv的cv::Mat
    cv::Mat rgb_image( imageInfo.height, imageInfo.width, CV_8UC3, const_cast<uint8_t*>(buf));
    //克隆一份备用
    cv::Mat rgb_image_copy = rgb_image.clone();
    //启用image队列锁
    osalHandler->MutexLock(s_imageQueueMutexHandle);
    //消费者无法消化，丢弃一部分帧
    while (s_imageQueue.size() > 30) {
        USER_LOG_WARN("The image queue is full. Drop this strike.");
        s_imageQueue.pop();
    }
    //推入新的帧
    s_imageQueue.push(rgb_image_copy);
    //取消image队列锁
    osalHandler->MutexUnlock(s_imageQueueMutexHandle);

    //启用元数据队列锁
    osalHandler->MutexLock(s_metaQueueMutexHandle);
    //如果元数据不为空，则取出一个元数据
    if (!s_metaQueue.empty()) {
        metaData = s_metaQueue.front();
        s_metaQueue.pop();
    }
    //取消元数据队列锁
    osalHandler->MutexUnlock(s_metaQueueMutexHandle);

    //将RGB帧编码为H264并附带元数据
    DjiLiveview_EncodeAFrameToH264(buf, len, imageInfo, metaData);
    //用完后释放元数据内存
    if(metaData != nullptr) free(metaData);

#else
//原本无Opencv的处理部分
#endif
}

//获取时间戳
static ai_detect::std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);

    std::ostringstream oss;
    oss << (now_tm->tm_year + 1900)
        << (now_tm->tm_mon + 1)
        << now_tm->tm_mday
        << now_tm->tm_hour
        << now_tm->tm_min;

    return oss.str();
}

//H264码流输出为文件
static void ai_detect::outH264Tofile(const uint8_t *buf, int32_t len) {
    if (!outFileH264) {
        USER_LOG_ERROR( "output.h264 is not open");
        return;
    }
    outFileH264.write(reinterpret_cast<const char *>(buf), len);
}

//YUV码流输出为文件
static void ai_detect::outYUVTofile(const uint8_t *buf, int32_t len) {
    if (!outFileYUV) {
        USER_LOG_ERROR( "outyuv.h264 is not open");
        return;
    }
    outFileYUV.write(reinterpret_cast<const char *>(buf), len);
}

#endif