#include "sensordata.h"

SensorData::SensorData(const char* fileName)
{
    image_transport::ImageTransport it(nh);
    sub_img = it.subscribe("img", 2,&SensorData::imgCallback,this);
    sub_gps=nh.subscribe("fix",1,&SensorData::gpsCallback,this);
    sub_imu=nh.subscribe("imu_torso/xsens/data",1,&SensorData::imuCallback,this);
    sub_yaw=nh.subscribe("GPS_N280/orientation",1,&SensorData::yawCallback,this);
    file.open(fileName,ios::in|ios::out);
}

SensorData::~SensorData(){
    cout<<"deconstruct"<<endl;
    file.close();
}

void SensorData::yawCallback(const std_msgs::Float64 output_direction){
    direction=output_direction.data;
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
    //使用测向GPS产生的偏航角，不再使用IMU产生的地磁偏航
    file<<timeStampStr<<"  "<<"gps:"<<setprecision(13)<<Current_x<<"  "<<Current_y<<"; yaw:"<<direction<<"\n";

    cv::imwrite(timeStampStr+".jpg",img);
    cv:waitKey(5);
}

  void SensorData::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &gps_in){
      Current_x = gps_in->longitude;
      Current_y = gps_in->latitude;
  }

void SensorData::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_in){
    tf::Quaternion q;
    tf::quaternionMsgToTF(imu_in->orientation, q);
    tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
}
