#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "cv.h"
#include "highgui.h"
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
        Mat src = imread("palm_hw2.bmp");
        Mat dst;
        cv::imshow("normal", src) ;
        //输入图像
        //输出图像
        //单元大小，这里是5*5的8位单元
        //腐蚀位置，为负值取核中心
        //腐蚀次数两次
        erode(src,dst,Mat(3,3,CV_8U),Point(0,0),1);
        cv::imshow("erode", dst) ;

        //输入图像
        //输出图像
        //单元大小，这里是5*5的8位单元
        //膨胀位置，为负值取核中心
        //膨胀次数两次
		dilate(src,dst,Mat());
		dilate(src,dst,Mat());
		dilate(src,dst,Mat());
		dilate(src,dst,Mat());
		dilate(src,dst,Mat());
        dilate(src,dst,Mat(3,3,CV_8U),Point(0,0),1);
        cv::imshow("dilate", dst) ;

        //输入图像
        //输出图像
        //定义操作：MORPH_OPEN为开操作，MORPH_CLOSE为闭操作
        //单元大小，这里是3*3的8位单元
        //开闭操作位置
        //开闭操作次数
        morphologyEx(src,dst,MORPH_OPEN,Mat(3,3,CV_8U),Point(0,0),1);
        cv::imshow("OPEN", dst) ;

        morphologyEx(src,dst,MORPH_CLOSE,Mat(3,3,CV_8U),Point(0,0),1);
        cv::imshow("CLOSE", dst) ;

        //imshow("dst",dst);
        waitKey();

        return 0;
}








//void dilate(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
//{
//	int num = 0;
//	vector<int> position;
//	outputImage.release();
//	//Mat ker = kernel.getMat();
//	Mat ker = kernel.getMat();
//	Size ksize = ker.data ? ker.size():Size(3,3);
//	if (iterations == 0 || ((ker.size().height) * (ker.size().width) ==1))
//	{
//		cout<<"there"<<endl;
//		//把矩阵复制到另一个矩阵中
//		inputImage.copyTo(outputImage);
//		outputImage.convertTo(outputImage, CV_32SC1) ; 
//	}
//	else
//	{
//		//第一次循环
//		inputImage.convertTo(outputImage, CV_32SC1) ; 
//		int row = outputImage.rows;
//		int col = outputImage.cols;
//		for (int i = 1; i < row; i++)
//		{
//	        int* data_curRow = outputImage.ptr<int>(i) ;  
//			for (int j = 1; j < col; j++)
//			{
//				if (data_curRow[j] >= 1)  
//	            {			
//					position.push_back(i);
//					position.push_back(j);
//					num++;
//				}
//			}
//		}
//		//第二次循环
//		for (int c = 0; c <= position.size()-2; c = c + 2)
//		{
//			//cout<<"second time"<<endl;
//			int rows = position[c];
//			int cols = position[c+1];
//			outputImage.at<int>(rows,cols+1) = 1;
//			outputImage.at<int>(rows,cols-1) = 1;
//			outputImage.at<int>(rows,cols) = 1;
//			outputImage.at<int>(rows-1,cols+1) = 1;
//			outputImage.at<int>(rows-1,cols-1) = 1;
//			outputImage.at<int>(rows-1,cols) = 1;
//			outputImage.at<int>(rows+1,cols+1) = 1;
//			outputImage.at<int>(rows+1,cols-1) = 1;
//			outputImage.at<int>(rows+1,cols) = 1;
//		}
//	}
//	cout<<"the total num:  ";
//	cout<<num<<endl;
//	cout<<endl<<endl;
//}
//
//void erode(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
//{
//	int num = 0;
//	int sum = 0;
//	vector<int> position;
//	outputImage.release();
//	//Mat ker = kernel.getMat();
//	Mat erode_ker = kernel.getMat();
//	Size ksize = erode_ker.data ? erode_ker.size():Size(3,3);
//	if (iterations == 0 || ((erode_ker.size().height) * (erode_ker.size().width) ==1))
//	{
//		cout<<"there_erode"<<endl;
//		//把矩阵复制到另一个矩阵中
//		inputImage.copyTo(outputImage);
//		outputImage.convertTo(outputImage, CV_32SC1) ; 
//		cout<<"hello";
//	}
//	else
//	{
//		
//		inputImage.convertTo(outputImage, CV_32SC1) ; 
//		int row = outputImage.rows;
//		int col = outputImage.cols;
//		for (int i = 2; i < row - 1; i++)
//		{
//			int* data_preRow = outputImage.ptr<int>(i-1) ;
//	        int* data_curRow = outputImage.ptr<int>(i) ;  
//			int* data_nxtRow = outputImage.ptr<int>(i+1) ;
//			for (int j = 2; j < col - 1; j++)
//			{
//				if (data_curRow[j] >=1)
//				{
//					
//					int upleft = data_preRow[j - 1];
//					int up = data_preRow[j];
//					int upright = data_preRow[j + 1];
//					int left = data_curRow[j - 1];
//					int middle = data_curRow[j];
//					int right = data_curRow[j + 1];
//					int downleft = data_nxtRow[j - 1];
//					int down = data_nxtRow[j ];
//					int downright = data_nxtRow[j + 1];
//					//cout<<upleft;
//					//cout<<up;
//					//cout<<upright;
//					//cout<<left;
//					//cout<<middle;
//					//cout<<right;
//					//cout<<downleft;
//					//cout<<down;
//					//cout<<downright;
//					sum++;
//					if ((upleft >= 1) && (up >= 1) && (upright >= 1) && (left >= 1) && (middle >= 1) && (right >= 1) && (downleft >= 1) && (down >= 1) && (downright >= 1))  
//					{			
//						position.push_back(i);
//						position.push_back(j);
//						//cout<<i;
//						//cout<<j;
//						num++;
//					}
//				}
//				//data_curRow[j] = 0;
//			}
//		}
//		cout<<"sum:   ";
//		cout<<sum<<endl;
//		cout<<"here111"<<endl;
//		cout<<position.size()<<endl;
//		outputImage.convertTo(outputImage, CV_8UC1);
//		threshold(outputImage, outputImage, 0, 0, CV_THRESH_BINARY);
//		outputImage.convertTo(outputImage, CV_32SC1);
//		//outputImage.release();
//		//outputImage.create( inputImage.size(), inputImage.type() );
//		if (position.size() == 0)
//		{
//			cout<<"error";
//		}
//		else
//		{
//
//		for (int c = 0; c <= position.size()-2; c = c + 2)
//		{
//			//cout<<"second time"<<endl;
//			int rows = position[c];
//			int cols = position[c+1];
//			outputImage.at<int>(rows,cols+1) = 0;
//			outputImage.at<int>(rows,cols-1) = 0;
//			outputImage.at<int>(rows,cols) = 1;
//			outputImage.at<int>(rows-1,cols+1) = 0;
//			outputImage.at<int>(rows-1,cols-1) = 0;
//			outputImage.at<int>(rows-1,cols) = 0;
//			outputImage.at<int>(rows+1,cols+1) = 0;
//			outputImage.at<int>(rows+1,cols-1) = 0;
//			outputImage.at<int>(rows+1,cols) = 0;
//		}
//		}
//	}
//	cout<<"the total num:  ";
//	cout<<num<<endl;
//	cout<<endl<<endl;
//}
//
//void opening(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
//{
//	outputImage.release();
//	Mat element = kernel.getMat();
//	int times = iterations;
//	if (times == 0)
//	{
//		cout<<"there_opening";
//		erode(inputImage, outputImage, element, Point(0,0), 0);
//		outputImage.convertTo(inputImage, CV_8UC1);
//		dilate(inputImage, outputImage, element, Point(0,0), 0);
//		cout<<"exit";
//	}
//	else
//	{
//		cout<<"here";
//		for (int i = 1; i <= times; i++)
//		{
//			erode(inputImage, outputImage, element, Point(0,0), 1);
//			outputImage.convertTo(inputImage, CV_8UC1);
//			dilate(inputImage, outputImage, element, Point(0,0), 1);
//		}
//	}
//}
//
//void closing(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
//{
//	outputImage.release();
//	Mat element = kernel.getMat();
//	int times = iterations;
//	if (times == 0)
//	{
//		dilate(inputImage, outputImage, element, Point(0,0), 0);
//		outputImage.convertTo(inputImage, CV_8UC1) ;
//		erode(inputImage, outputImage, element, Point(0,0), 0);
//	}
//	else
//	{
//		for (int i = 1; i <= times; i++)
//		{
//			dilate(inputImage, outputImage, element, Point(0,0), 1);
//			outputImage.convertTo(inputImage, CV_8UC1) ;
//			erode(inputImage, outputImage, element, Point(0,0), 1);
//		}
//	}
//}
//
//
//
//int main(int argc, char* argv[])
//{
//	//Mat grayImage = imread("gun_hw2.bmp", 0);
//	Mat grayImage = imread("palm_hw2.bmp", 0);
//	imshow("grayImage", grayImage);
//
//	Mat binImage;
//	threshold(grayImage, binImage, 50, 1, CV_THRESH_BINARY);
//
//	Mat dilateImage;
//	dilate(binImage, dilateImage, Mat(3,3,CV_8U), Point(0,0), 1);
//	dilateImage.convertTo(dilateImage, CV_8UC1);
//	threshold(dilateImage, dilateImage, 0, 255, CV_THRESH_BINARY_INV);
//	imshow("dilateImage", dilateImage);
//
//	Mat erodeImage;
//	erode(binImage, erodeImage, Mat(3,3,CV_8U), Point(0,0), 1);
//	erodeImage.convertTo(erodeImage, CV_8UC1) ;
//	threshold(erodeImage, erodeImage, 0, 255, CV_THRESH_BINARY_INV);
//	imshow("erodeImage", erodeImage);
//
//	Mat openImage;
//	opening(binImage, openImage, Mat(3,3,CV_8U), Point(0,0), 1);
//	openImage.convertTo(openImage, CV_8UC1) ;
//	threshold(openImage, openImage, 0, 255, CV_THRESH_BINARY_INV);
//	imshow("openImage", openImage);
//
//	Mat colseImage;
//	closing(binImage, colseImage, Mat(3,3,CV_8U), Point(0,0), 1);
//	colseImage.convertTo(colseImage, CV_8UC1) ;
//	threshold(colseImage, colseImage, 0, 255, CV_THRESH_BINARY_INV);
//	imshow("colseImage", colseImage);
//	//system("pause");
//	waitKey();
//	return 0;
//}