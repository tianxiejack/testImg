#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"
#include "test3.hpp"
#include "base.hpp"
#include "unsmooth.hpp"
#include "smooth.hpp"
#include "test7.hpp"

using namespace cv;

void test3()
{

	Mat src = imread("3.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst2 = Mat(src.rows,src.cols,CV_8UC1);

	if (src.empty()){
		printf("imread failed \n");
		return ;
	}
	
	//Laplace(src.data,dst1.data,src.cols,src.rows);
	Laplace(src.data,dst1.data,src.cols,src.rows);

	MatrixSub(src.data,dst2.data,src.cols,src.rows);

	cvNamedWindow("a",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("a",100,100);
	cvMoveWindow("b",200,100);
	cvMoveWindow("c",300,100);

	imshow("a",src);
	imshow("b",dst1);
	imshow("c",dst2);

	waitKey(0);




	return ;
}

void Laplace(unsigned char *src,unsigned char *dst,int width,int height)
{
   	char LaplaceMask[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};
   	int* tmp = (int *)malloc(sizeof(int)*width*height);
   	int min = 255,max = 0;
   	int i,j;
	for(j = 1;j<height-1;j++)
		for(i = 1;i<width -1 ;i++)
		{
			tmp[j*width + i] =
				LaplaceMask[0]*src[(j-1)*width + i-1] + LaplaceMask[1]*src[(j-1)*width + i] + LaplaceMask[2]*src[(j-1)*width + i]
			+	LaplaceMask[3]*src[j*width + i-1] 	  + LaplaceMask[4]*src[j*width + i]     + LaplaceMask[5]*src[j*width + i]
			+	LaplaceMask[6]*src[(j+1)*width + i-1] + LaplaceMask[7]*src[(j+1)*width + i] + LaplaceMask[8]*src[(j+1)*width + i];

			if(tmp[j*width + i] < min)
				min = tmp[j*width + i];

		}


		min = min* -1;
		for(j = 0;j<=height-1;j++)
			for(i = 0;i<=width -1 ;i++)
			{
				tmp[j*width + i] += min;
			}

		for(j = 0;j<=height-1;j++)
			for(i = 0;i<=width -1 ;i++)
			{
				if(tmp[j*width + i] > max)
					max = tmp[j*width + i];
			}

		for(j = 0;j<=height-1;j++)
			for(i = 0;i<=width -1 ;i++)
			{
				tmp[j*width + i] = (tmp[j*width + i]*255/max);
			}


	for(j = 0;j<=height-1;j++)
		for(i = 0;i<=width -1 ;i++)
		{
			dst[j*width + i] = (unsigned char)tmp[j*width + i];
			//printf("j = %d,i = %d,pixel = %d\n",j,i,tmp[j*width + i]);
		}

	free(tmp);
	return ;
}

void MatrixSub(unsigned char *src,unsigned char *dst,int width,int height)
{
	int i,j;
	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);

	char LaplaceMask[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};
	int min =255;
	for(j = 1;j<height-1;j++)
		for(i = 1;i<width -1 ;i++)
		{
			tmp[j*width + i] =
				LaplaceMask[0]*src[(j-1)*width + i-1] + LaplaceMask[1]*src[(j-1)*width + i] + LaplaceMask[2]*src[(j-1)*width + i]
			+	LaplaceMask[3]*src[j*width + i-1] 	  + LaplaceMask[4]*src[j*width + i]     + LaplaceMask[5]*src[j*width + i]
			+	LaplaceMask[6]*src[(j+1)*width + i-1] + LaplaceMask[7]*src[(j+1)*width + i] + LaplaceMask[8]*src[(j+1)*width + i];

		}


	for(j = 0;j<height - 1;j++)
		for(i = 0;i<width -1 ;i++)
		{
			tmp[j*width + i] = (src[j*width + i] + tmp[j*width + i]);//(unsigned char)
			//dst[j*width + i] = tmp[j*width + i];
			if(tmp[j*width + i] < 0)
				dst[j*width + i] = 0;
			else if(tmp[j*width + i] >  255)
				dst[j*width + i] = 255;
			else
				dst[j*width + i] = tmp[j*width + i];
			//printf("j = %d,i = %d,pixel = %d\n",j,i,tmp[j*width + i]);
		}


	//dst[j+width + i] = (src1[j*width + i] - src2[j+width + i]);
	return ;
}




