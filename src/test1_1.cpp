/*
 * test1-1.cpp
 *
 *  Created on: 2019年3月21日
 *      Author: jet
 */


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"
#include "test2.hpp"

#include <stdio.h>

using namespace cv;

void test1_1()
{

	Mat src = imread("../image/lena.bmp", 0);
	Mat dst;
	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvMoveWindow("src",100,100);
	imshow("src",src);


	//resize(src, dst, cv::Size(512, 512),CV_INTER_NN);
	//imshow("dst",dst);

	Point2f center = Point2f(src.cols/2.0, src.rows/2.0);
	int degree = 0;
	int scale = 1;

	    // 获取变换矩阵
	Mat  rot = getRotationMatrix2D(center,degree,scale);

for(int j=0 ; j< rot.rows; j++ )
	for(int i =0 ; i< rot.cols; i++)
		printf("rot(%d) = %f \n",j*rot.cols + i , rot.at<float>(j, i)  );


	warpAffine(src, dst, rot, dst.size());
	imshow("dst",dst);

	waitKey(0);
	return ;
}
