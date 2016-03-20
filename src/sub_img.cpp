/*
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Drogonfly_ImgRead.h"

void imgCallback(const sensor_msgs::ImageConstPtr& img_in)
{
	Mat img;
	ros::Time curTime=ros::Time::now();
	cv_bridge::toCvShare(img_in,"bgr8")->image.copyTo(img);
	std::cout<<curTime.toSec()<<endl;
	cv::imshow("img",img);
	cv:waitKey(5);
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "sub_img");

	ros::NodeHandle nh;
	image_transport::Subscriber  sub_img;
	image_transport::ImageTransport it(nh);
    sub_img = it.subscribe("img", 2,imgCallback);
    ros::spin();

	return 0;
}
*/
#include"sensordata.h"


int main(int argc, char **argv){
    ros::init(argc, argv, "sub_img");
    SensorData data;
    ros::spin();
}
