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
    ros::Subscriber sub_rtk_gps,sub_cexiang_gps,sub_garmin_gps,sub_imu,sub_cexiang_orientation;

    SensorData(const char* gpsDataFile,const char* imuDataFile);
    ~SensorData();

    //callback function to get the sensor data
    void imgCallback(const sensor_msgs::ImageConstPtr& img_in);
    void rtk_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& gps_in);
    void cexiang_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& gps_in);
    void garmin_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& gps_in);
    void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_in);
    void yawCallback(const std_msgs::Float64 output_direction);


private:
    double rtk_latitude, rtk_longtitude,rtk_altitude,cexiang_latitude,cexiang_longtitude,cexiang_altitude,garmin_latitude,garmin_longtitude,garmin_altitude;
    double roll, pitch, yaw,direction_cexiang;
    fstream gps_file,imu_file;

};

#endif // SENSORDATA_H
