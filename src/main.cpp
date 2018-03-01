#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "smooth.hpp"

using namespace std;
using namespace cv;



int main()
{
	Mat src = imread("1.png", 2);
	Mat dst = Mat(src.rows,src.cols,CV_8UC1);
	if (src.empty()){
		printf("imread failed \n");
		return -1;
	}
	imshow("src",src);
	printf("channel = %d\n",src.channels());

	GaussianFilter(src.data,dst.data,src.cols,src.rows,src.cols/25,src.rows/25,1);

	imshow("GaussianFilter",dst);

	waitKey(0);


	return 0;
}
