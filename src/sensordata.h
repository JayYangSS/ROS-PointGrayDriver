#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Drogonfly_ImgRead.h"


class SensorData
{
public:

    Mat img;
    ros::NodeHandle nh;
    image_transport::Subscriber  sub_img;

    SensorData();

    //callback function to get the sensor data
    void imgCallback(const sensor_msgs::ImageConstPtr& img_in);
};

#endif // SENSORDATA_H
