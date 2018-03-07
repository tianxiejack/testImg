#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdlib.h"
#include "test8.hpp"

using namespace cv;

void test8()
{
	Mat src = imread("8.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);


	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);


	imshow("src",src);
	waitKey(0);

	return ;
}


