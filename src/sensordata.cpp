#include "sensordata.h"

SensorData::SensorData()
{
    image_transport::ImageTransport it(nh);
    sub_img = it.subscribe("img", 2,&SensorData::imgCallback,this);
}


void SensorData::imgCallback(const sensor_msgs::ImageConstPtr& img_in)
{
    static ros::Time baseTime=ros::Time::now();
    cv_bridge::toCvShare(img_in,"bgr8")->image.copyTo(img);
 //   std::cout<<curTime.toSec()<<endl;
    cv::imshow("img",img);
    ros::Time curTime=ros::Time::now();

//save image and make the timeStamp as the name of images
    double timeStamp=curTime.toSec()-baseTime.toSec();
    std::string timeStampStr = boost::lexical_cast<std::string>(timeStamp);
    timeStampStr.replace(timeStampStr.find("."),1,"_");
   // std::cout<<timeStampStr<<endl;
    cv::imwrite(timeStampStr+".jpg",img);
    cv:waitKey(5);
}

