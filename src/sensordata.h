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
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
#include "tf/transform_datatypes.h"
#include "std_msgs/Float64.h"
#include <fstream>


class SensorData
{
public:

    Mat img;
    ros::NodeHandle nh;
    image_transport::Subscriber  sub_img;
    ros::Subscriber sub_gps,sub_imu,sub_yaw;

    SensorData(const char* fileName);
    ~SensorData();

    //callback function to get the sensor data
    void imgCallback(const sensor_msgs::ImageConstPtr& img_in);
    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& gps_in);
    void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_in);
    void yawCallback(const std_msgs::Float64 output_direction);


private:
    double      Current_y, Current_x;
    double roll, pitch, yaw,direction;
    fstream file;

};

#endif // SENSORDATA_H
