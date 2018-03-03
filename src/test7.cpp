#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdlib.h"
#include "test7.hpp"
#include "base.hpp"
#include "smooth.hpp"

using namespace cv;

void test7()
{
	Mat src = imread("7.png", 2);

	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);

	imshow("src",src);
	waitKey(0);

	return ;
}

