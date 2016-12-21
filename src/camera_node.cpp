#include "ros/ros.h"
#include "std_msgs/String.h"

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Drogonfly_ImgRead.h"



int main(int argc, char **argv)
{
	ros::init(argc, argv, "camera");

	CvVideoWriter *writer=NULL;
    bool saveFlag=false;
	Drogonfly_ImgRead p;
	IplImage *src_img;
	IplImage *img=NULL;
	
	ros::NodeHandle nh;
	image_transport::Publisher  pub_img;
	image_transport::ImageTransport it(nh);
    	pub_img = it.advertise("img", 2);  

	p.Camera_Intial();

	if(saveFlag)
	{
			
			//char *videoPath = new char[100];// "D:/123.dat";
			//SYSTEMTIME stTime;
			//GetLocalTime(&stTime);
			//sprintf(videoPath, "Video_%04d%02d%02d%02d%02d%02d.avi", stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
						
		writer = cvCreateVideoWriter("test.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, Size(800,600), 1);
		//writer = cvCreateVideoWriter("cameraCapture2.avi",CV_FOURCC('X','V','I','D'),20,cvGetSize(img),1);
	}


    img=cvCreateImage(Size(800,600),IPL_DEPTH_8U,3);
	while(ros::ok())
	{
		src_img=p.Camera2IplImage();
		//cvShowImage("src_img",src_img);
		
	
		cvResize(src_img,img); 

		cv::Mat test_Mat_image(img);
			// cv_bridge::CvImagePtr cv_ptr(new cv_bridge::CvImage);
			// cv_ptr->image = test_Mat_image;
   //      		cv_ptr->encoding = "bgr8";
			// pub_img.publish(cv_ptr->toImageMsg());
		cv::imshow("test_Mat_image",test_Mat_image);
        sensor_msgs::ImagePtr img_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",test_Mat_image).toImageMsg();
		pub_img.publish(img_msg);		
		if(saveFlag)
			{
				cvWriteFrame(writer,img); 
				cout<<"read success"<<endl;   
			}
		
		//cvShowImage("resizeImg",img);
		int c=cvWaitKey(5);

		//按ESC键退出采集，否则下次无法正常采集
		if (c==27)
		{
			p.ClearBuffer();
			cvReleaseImage(&img);
			cvReleaseVideoWriter(&writer); 
			break;
		}
	}

	return 0;
}
