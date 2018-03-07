#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdlib.h"
#include "test7.hpp"
#include "base.hpp"


using namespace cv;

void test7()
{
	Mat src = imread("7.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);

	
	getPicB(src.data,dst1.data,src.cols,src.rows);


	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("b",100,100);

	imshow("src",src);
	imshow("b",dst1);


	waitKey(0);

	return ;
}

void getPicB(unsigned char* src,unsigned char *dst,int width ,int height)
{
	unsigned char sobel_x[9] = {-1,-2,-1,0,0,0,1,2,1};
	unsigned char sobel_y[9] = {-1,0,1,-2,0,2,-1,0,1};

	int *tmp = (int *)malloc(4*width*height);
	memset(tmp,0,4*width*height);

	int min=255,max = 0;
	int i,j;

	for(j=1;j<height-1;j++)
		for(i=1;i<width-1;i++)
		{
			tmp[j*width + i] =
				sobel_x[0]*src[(j-1)*width + i-1] + sobel_x[1]*src[(j-1)*width + i] + sobel_x[2]*src[(j-1)*width + i+1]
			+	sobel_x[3]*src[(j)*width + i-1] + sobel_x[4]*src[(j)*width + i] + sobel_x[5]*src[(j)*width + i+1]
			+	sobel_x[6]*src[(j+1)*width + i-1] + sobel_x[7]*src[(j+1)*width + i] + sobel_x[8]*src[(j+1)*width + i+1];

			tmp[j*width + i] = abs(tmp[j*width + i]);
			if(tmp[j*width + i] < min)
				min = (tmp[j*width + i]);
		}

	min = -1*min;
	for(j=1;j<height-1;j++)
		for(i=1;i<width-1;i++)
		{
			tmp[j*width + i] += min;
			if(tmp[j*width + i] > max)
				max = tmp[j*width + i];
		}

	for(j=1;j<height-1;j++)
		for(i=1;i<width-1;i++)
		{
			dst[j*width + i] = tmp[j*width + i]*255/max;
		}




	free(tmp);
	return ;
}
