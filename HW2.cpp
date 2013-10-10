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

//int main(int argc, char* argv[])
//{
//        Mat src = imread("gun_hw2.bmp");
//        Mat dst;
//        cv::imshow("normal", src) ;
//        //����ͼ��
//        //���ͼ��
//        //��Ԫ��С��������5*5��8λ��Ԫ
//        //��ʴλ�ã�Ϊ��ֵȡ������
//        //��ʴ��������
//        erode(src,dst,Mat(3,3,CV_8U),Point(0,0),1);
//        cv::imshow("erode", dst) ;
//
//        //����ͼ��
//        //���ͼ��
//        //��Ԫ��С��������5*5��8λ��Ԫ
//        //����λ�ã�Ϊ��ֵȡ������
//        //���ʹ�������
//		dilate(src,dst,Mat());
//		dilate(src,dst,Mat());
//		dilate(src,dst,Mat());
//		dilate(src,dst,Mat());
//		dilate(src,dst,Mat());
//        //dilate(src,dst,Mat(3,3,CV_8U),Point(0,0),1);
//        cv::imshow("dilate", dst) ;
//
//        //����ͼ��
//        //���ͼ��
//        //���������MORPH_OPENΪ��������MORPH_CLOSEΪ�ղ���
//        //��Ԫ��С��������3*3��8λ��Ԫ
//        //���ղ���λ��
//        //���ղ�������
//        morphologyEx(src,dst,MORPH_OPEN,Mat(3,3,CV_8U),Point(0,0),3);
//        cv::imshow("MORPH_OPEN", dst) ;
//
//        morphologyEx(src,dst,MORPH_CLOSE,Mat(3,3,CV_8U),Point(0,0),5);
//        cv::imshow("MORPH_CLOSE", dst) ;
//
//        //imshow("dst",dst);
//        waitKey();
//
//        return 0;
//}

void dilate(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
{
	int num = 0;
	vector<int> position;
	outputImage.release();
	//Mat ker = kernel.getMat();
	Mat ker = kernel.getMat();
	Size ksize = ker.data ? ker.size():Size(3,3);
	if (iterations == 0 || ((ker.size().height) * (ker.size().width) ==1))
	{
		cout<<"there"<<endl;
		//�Ѿ����Ƶ���һ��������
		inputImage.copyTo(outputImage);
		outputImage.convertTo(outputImage, CV_32SC1) ; 
	}
	else
	{
		//��һ��ѭ��
		inputImage.convertTo(outputImage, CV_32SC1) ; 
		int row = outputImage.rows;
		int col = outputImage.cols;
		for (int i = 1; i < row; i++)
		{
	        int* data_curRow = outputImage.ptr<int>(i) ;  
			for (int j = 1; j < col; j++)
			{
				if (data_curRow[j] >= 1)  
	            {			
					position.push_back(i);
					position.push_back(j);
					num++;
				}
			}
		}
		//�ڶ���ѭ��
		for (int c = 0; c <= position.size()-2; c = c + 2)
		{
			//cout<<"second time"<<endl;
			int rows = position[c];
			int cols = position[c+1];
			outputImage.at<int>(rows,cols+1) = 1;
			outputImage.at<int>(rows,cols-1) = 1;
			outputImage.at<int>(rows,cols) = 1;
			outputImage.at<int>(rows-1,cols+1) = 1;
			outputImage.at<int>(rows-1,cols-1) = 1;
			outputImage.at<int>(rows-1,cols) = 1;
			outputImage.at<int>(rows+1,cols+1) = 1;
			outputImage.at<int>(rows+1,cols-1) = 1;
			outputImage.at<int>(rows+1,cols) = 1;
		}
	}
	cout<<"the total num:  ";
	cout<<num<<endl;
	cout<<endl<<endl;
}

void erode(Mat& inputImage, Mat& outputImage, InputArray kernel, Point anchor, int iterations)
{
	int num = 0;
	vector<int> position;
	outputImage.release();
	//Mat ker = kernel.getMat();
	Mat ker = kernel.getMat();
	Size ksize = ker.data ? ker.size():Size(3,3);
	if (iterations == 0 || ((ker.size().height) * (ker.size().width) ==1))
	{
		cout<<"there"<<endl;
		//�Ѿ����Ƶ���һ��������
		inputImage.copyTo(outputImage);
		outputImage.convertTo(outputImage, CV_32SC1) ; 
	}
	else
	{
		inputImage.convertTo(outputImage, CV_32SC1) ; 
		int row = outputImage.rows;
		int col = outputImage.cols;
		for (int i = 1; i < row; i++)
		{
			int* data_preRow = outputImage.ptr<int>(i-1) ;
	        int* data_curRow = outputImage.ptr<int>(i) ;  
			int* data_nxtRow = outputImage.ptr<int>(i+1) ;
			for (int j = 1; j < col; j++)
			{
				int upleft = data_preRow[j - 1];
				int up = data_preRow[j];
				int upright = data_preRow[j + 1];
				int left = data_curRow[j - 1];
				int middle = data_curRow[j];
				int right = data_curRow[j + 1];
				int downleft = data_nxtRow[j - 1];
				int down = data_nxtRow[j ];
				int downright = data_nxtRow[j + 1];
				if (upleft == 1 && up == 1 && upright == 1 && left == 1 && middle == 1 && right == 1 && downleft == 1 && down == 1 && downright == 1)  
	            {			
					position.push_back(i);
					position.push_back(j);
					num++;
				}
			}
		}
		outputImage.convertTo(outputImage, CV_8UC1);
		threshold(outputImage, outputImage, 0, 0, CV_THRESH_BINARY);
		outputImage.convertTo(outputImage, CV_32SC1);
		for (int c = 0; c <= position.size()-2; c = c + 2)
		{
			//cout<<"second time"<<endl;
			int rows = position[c];
			int cols = position[c+1];
		//	outputImage.at<int>(rows,cols+1) = 1;
		//	outputImage.at<int>(rows,cols-1) = 1;
			outputImage.at<int>(rows,cols) = 1;
		//	outputImage.at<int>(rows-1,cols+1) = 1;
		//	outputImage.at<int>(rows-1,cols-1) = 1;
		//	outputImage.at<int>(rows-1,cols) = 1;
		//	outputImage.at<int>(rows+1,cols+1) = 1;
		//	outputImage.at<int>(rows+1,cols-1) = 1;
		//	outputImage.at<int>(rows+1,cols) = 1;
		}
	}
	cout<<"the total num:  ";
	cout<<num<<endl;
	cout<<endl<<endl;
}




int main(int argc, char* argv[])
{
	Mat grayImage = imread("gun_hw2.bmp", 0);
	imshow("grayImage", grayImage);

	Mat binImage;
	threshold(grayImage, binImage, 50, 1, CV_THRESH_BINARY);

	Mat dilateImage;
	dilate(binImage, dilateImage, Mat(3,3,CV_8U), Point(0,0), 2);
	dilateImage.convertTo(dilateImage, CV_8UC1);
	threshold(dilateImage, dilateImage, 0, 255, CV_THRESH_BINARY_INV);
	imshow("dilateImage", dilateImage);

	Mat erodeImage;
	erode(binImage, erodeImage, Mat(3,3,CV_8U), Point(0,0), 0);
	erodeImage.convertTo(erodeImage, CV_8UC1) ;
	threshold(erodeImage, erodeImage, 0, 255, CV_THRESH_BINARY_INV);
	imshow("erodeImage", erodeImage);

	//system("pause");
	waitKey();
	return 0;
}