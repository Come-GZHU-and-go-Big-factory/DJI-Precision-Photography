#ifndef AI_DETECT_H
#define AI_DETECT_H

#include "rclcpp/rclcpp.hpp"

class ai_detect:public rclcpp::Node
{
    public:
    //构造函数
    ai_detect(int argv,char ** argc):rclcpp::Node("camera_controller")
    {
        //视频流初始化
        

    }
    private:
    //
};


#endif