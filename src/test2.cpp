#include "smooth.hpp"
#include "unsmooth.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"


using namespace cv;

void test2()
{

	Mat src = imread("1.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst2 = Mat(src.rows,src.cols,CV_8UC1);
	if (src.empty()){
		printf("imread failed \n");
		return ;
	}

	printf("channel = %d\n",src.channels());

	GaussianFilter(src.data,dst1.data,src.cols,src.rows,src.cols/25,src.rows/25,1);
	UnsharpMasking(src.data,dst2.data,src.cols,src.rows,3,src.cols/25,src.rows/25,0.5,1);

	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("GaussianFilter",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("UnsharpMasking",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("GaussianFilter",300,100);
	cvMoveWindow("UnsharpMasking",500,100);

	imshow("src",src);
	imshow("GaussianFilter",dst1);
	imshow("UnsharpMasking",dst2);

	waitKey(0);
	return ;
}
