#include "sensordata.h"

SensorData::SensorData(const char* gpsDataFile,const char* imuDataFile)
{
    image_transport::ImageTransport it(nh);
    sub_img = it.subscribe("/camera/image_color", 2,&SensorData::imgCallback,this);

    sub_rtk_gps=nh.subscribe("rtk/fix",1,&SensorData::rtk_gpsCallback,this);
    sub_cexiang_gps=nh.subscribe("n280/fix",1,&SensorData::cexiang_gpsCallback,this);
    sub_garmin_gps=nh.subscribe("garmin/fix",1,&SensorData::garmin_gpsCallback,this);
    sub_gps_filtered=nh.subscribe("/gps_filtered",1,&SensorData::filtered_gpsCallback,this);

    sub_imu=nh.subscribe("imu_torso/xsens/data",1,&SensorData::imuCallback,this);
    sub_cexiang_orientation=nh.subscribe("n280/GPS_N280/orientation",1,&SensorData::yawCallback,this);
    sub_yaw_filtered=nh.subscribe("yaw_filtered",1,&SensorData::filtered_yawCallback,this);//rad
    gps_file.open(gpsDataFile,ios::in|ios::out);
    imu_file.open(imuDataFile,ios::in|ios::out);
}

SensorData::~SensorData(){
    cout<<"deconstruct"<<endl;
    gps_file.close();
    imu_file.close();
}

void SensorData::yawCallback(const std_msgs::Float64 output_direction){
    direction_cexiang=output_direction.data;
}

void SensorData::filtered_yawCallback(const std_msgs::Float64 output_direction){
    filtered_yaw=output_direction.data;
}


void SensorData::imgCallback(const sensor_msgs::ImageConstPtr& img_in)
{
    static ros::Time baseTime=ros::Time::now();
    img=cv_bridge::toCvShare(img_in,"bgr8")->image;
 //   std::cout<<curTime.toSec()<<endl;
    cv::imshow("img",img);
    ros::Time curTime=ros::Time::now();

//save image and make the timeStamp as the name of images
    double timeStamp=curTime.toSec()-baseTime.toSec();
    std::string timeStampStr = boost::lexical_cast<std::string>(timeStamp);
    timeStampStr.replace(timeStampStr.find("."),1,"_");
   // std::cout<<timeStampStr<<endl;
    //使用测向GPS产生的偏航角，不再使用IMU产生的地磁偏航
    //file<<timeStampStr<<"  "<<"rtk_gps:"<<setprecision(13)<<rtk_latitude<<"  "<<rtk_longtitude<<",cexiang_gps:"<<cexiang_latitude<<" "<<cexiang_longtitude<<"; yaw:"<<direction_cexiang<<"\n";
    gps_file<<setprecision(13)<<timeStamp<<" "<<rtk_latitude<<" "<<rtk_longtitude<<" "<<rtk_altitude<<" "<<cexiang_latitude<<" "<<cexiang_longtitude<<" "<<cexiang_altitude<<" "<<garmin_latitude<<" "<<garmin_longtitude<<" "<<garmin_altitude<<" "<<filtered_gps_latitude<<" "<<filtered_gps_longtitude<<"\n";
    imu_file<<setprecision(13)<<timeStamp<<" "<<roll<<" "<<pitch<<" "<<yaw<<" "<<direction_cexiang<<" "<<filtered_yaw<<"\n";
    cv::imwrite(timeStampStr+".jpg",img);
    cv:waitKey(5);
}

  void SensorData::rtk_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &gps_in){
      rtk_latitude = gps_in->latitude;
      rtk_longtitude = gps_in->longitude;
      rtk_altitude=gps_in->altitude;
  }


  void SensorData::filtered_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &gps_in){
      filtered_gps_latitude = gps_in->latitude;
      filtered_gps_longtitude = gps_in->longitude;
  }


  void SensorData::cexiang_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &gps_in){
      cexiang_latitude = gps_in->latitude;
      cexiang_longtitude = gps_in->longitude;
      cexiang_altitude=gps_in->altitude;
  }

  void SensorData::garmin_gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &gps_in){
      garmin_latitude = gps_in->latitude;
      garmin_longtitude = gps_in->longitude;
      garmin_altitude=gps_in->altitude;
  }


void SensorData::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_in){
    tf::Quaternion q;
    tf::quaternionMsgToTF(imu_in->orientation, q);
    tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
}
