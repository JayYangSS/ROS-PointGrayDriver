/****
*This file is not used in the ROS node, it is just a demo in VS2013, and this ROS node is reconstruct from this demo
*/
#include "Drogonfly_ImgRead.h"
//#include <stdlib.h>
//#include <time.h>

int main()
{
	CvVideoWriter *writer=NULL;
	bool saveFlag=true;
	Drogonfly_ImgRead p;
	IplImage *src_img;
	IplImage *img=NULL;

	p.Camera_Intial();

	while(1)
	{
		src_img=p.Camera2IplImage();
		if(saveFlag)
		{
			img=cvCreateImage(Size(800,600),src_img->depth,3);
			//char *videoPath = new char[100];// "D:/123.dat";
			//SYSTEMTIME stTime;
			//GetLocalTime(&stTime);
			//sprintf(videoPath, "Video_%04d%02d%02d%02d%02d%02d.avi", stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
						
			writer = cvCreateVideoWriter("test.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, cvGetSize(img), 1);
			//writer = cvCreateVideoWriter("cameraCapture2.avi",CV_FOURCC('X','V','I','D'),20,cvGetSize(img),1);
			saveFlag=false;

		sensor_msgs::ImagePtr img_msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", img).toImageMsg();
		pub_img.publish(img_msg);
		}

		cvResize(src_img,img); 

		cvWriteFrame(writer,img); 
		cout<<"read success"<<endl;   
		cvWaitKey(10);
		cvShowImage("src1",img);
		
		int c=cvWaitKey(20);

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

