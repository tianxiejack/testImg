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
	Mat dst3 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst4 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst5 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst6 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst7 = Mat(src.rows,src.cols,CV_8UC1);


	if (src.empty()){
		printf("imread failed \n");
		return ;
	}
	

	Laplace(src.data,dst1.data,src.cols,src.rows);
	MatrixAdd(src.data,dst2.data,src.cols,src.rows);
	sobel_td(src.data,dst3.data,src.cols,src.rows);
	sobel5x5(dst3.data,dst4.data,src.cols,src.rows);
	getPicF(src.data,dst5.data,src.cols,src.rows);
	getPicG(src.data,dst6.data,src.cols,src.rows);
	getPicLast(src.data,dst7.data,src.cols,src.rows,0.5,1);


	cvNamedWindow("a",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("d",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("e",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("f",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("g",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("h",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("a",100,100);
	cvMoveWindow("b",200,100);
	cvMoveWindow("c",300,100);
	cvMoveWindow("d",400,100);
	cvMoveWindow("e",500,100);
	cvMoveWindow("f",600,100);
	cvMoveWindow("g",600,100);
	cvMoveWindow("h",600,100);

	imshow("a",src);
	imshow("b",dst1);
	imshow("c",dst2);
	imshow("d",dst3);
	imshow("e",dst4);
	imshow("f",dst5);
	imshow("g",dst6);
	imshow("h",dst7);

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


		min = min* (-1);
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

void MatrixAdd(unsigned char *src,unsigned char *dst,int width,int height)
{
	int i,j;
	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);

	char LaplaceMask[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};

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
	free(tmp);
	return ;
}

void sobel_td(unsigned char* src,unsigned char *dst,int width,int height)
{
	int i,j;
	char sobel_x[9]={-1,-2,-1,0,0,0,1,2,1};
	char sobel_y[9]={-1,0,1,-2,0,2,-1,0,1};

	int * tmp_x = (int *)malloc(sizeof(int)*width*height);
	int * tmp_y = (int *)malloc(sizeof(int)*width*height);
	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);
	memset(tmp_x,0,sizeof(int)*width*height);
	memset(tmp_y,0,sizeof(int)*width*height);

	for(j = 1;j<height-1;j++)
		for(i = 1;i<width -1 ;i++)
		{
			tmp_x[j*width + i] =
				sobel_x[0]*src[(j-1)*width + i-1] + sobel_x[1]*src[(j-1)*width + i] + sobel_x[2]*src[(j-1)*width + i]
			+	sobel_x[3]*src[j*width + i-1] 	  + sobel_x[4]*src[j*width + i]     + sobel_x[5]*src[j*width + i]
			+	sobel_x[6]*src[(j+1)*width + i-1] + sobel_x[7]*src[(j+1)*width + i] + sobel_x[8]*src[(j+1)*width + i];

			tmp_y[j*width + i] =
				sobel_y[0]*src[(j-1)*width + i-1] + sobel_y[1]*src[(j-1)*width + i] + sobel_y[2]*src[(j-1)*width + i]
			+	sobel_y[3]*src[j*width + i-1] 	  + sobel_y[4]*src[j*width + i]     + sobel_y[5]*src[j*width + i]
			+	sobel_y[6]*src[(j+1)*width + i-1] + sobel_y[7]*src[(j+1)*width + i] + sobel_y[8]*src[(j+1)*width + i];

			tmp[j*width + i] = abs(tmp_x[j*width + i]) + abs(tmp_y[j*width + i]);
			if(tmp[j*width + i] < 0)
				tmp[j*width + i] = 0;
			else if(tmp[j*width + i] > 255)
				tmp[j*width + i] = 255;

			dst[j*width + i] = tmp[j*width + i];
		}
	free(tmp);
	free(tmp_x);
	free(tmp_y);
	return ;
}

void sobel5x5(unsigned char* src,unsigned char* dst,int width,int height)
{
	int i,j;
	char sobel[25]={0};
	memset(sobel,1,25);

	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);

	for(j = 2;j<height-2;j++)
		for(i = 2;i<width -2 ;i++)
		{
			tmp[j*width + i] =
					sobel[0]*src[(j-2)*width + i-2]  + sobel[1]*src[(j-2)*width + i-1] + sobel[2]*src[(j-2)*width + i] +sobel[3]*src[(j-2)*width + i+1] +sobel[4]*src[(j-2)*width + i+2]
				+	sobel[5]*src[(j-1)*width + i-2]  + sobel[6]*src[(j-1)*width + i-1] + sobel[7]*src[(j-1)*width + i] +sobel[8]*src[(j-1)*width + i+1] +sobel[9]*src[(j-1)*width + i+2]
				+	sobel[10]*src[(j)*width + i-2]   + sobel[11]*src[(j)*width + i-1] + sobel[12]*src[(j-1)*width + i] +sobel[13]*src[(j-1)*width + i+1] +sobel[14]*src[(j-1)*width + i+2]
				+	sobel[15]*src[(j+1)*width + i-2] + sobel[16]*src[(j+1)*width + i-1] + sobel[17]*src[(j+1)*width + i] +sobel[18]*src[(j+1)*width + i+1] +sobel[19]*src[(j+1)*width + i+2]
				+	sobel[20]*src[(j+2)*width + i-2] + sobel[21]*src[(j+2)*width + i-1] + sobel[22]*src[(j+2)*width + i] +sobel[23]*src[(j+2)*width + i+1] +sobel[24]*src[(j+2)*width + i+2];


		    tmp[j*width + i] = tmp[j*width + i]/25;
			if(tmp[j*width + i] < 0)
				tmp[j*width + i] = 0;
			else if(tmp[j*width + i] > 255)
				tmp[j*width + i] = 255;

			dst[j*width + i] = tmp[j*width + i];
		}
	free(tmp);
	return ;
}

void getPicF(unsigned char* src,unsigned char* dst,int width,int height)
{
	int i,j;
	int min = 255,max = 0;
	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);

	unsigned char * dst1 = (unsigned char *)malloc(sizeof(1)*width*height);
	memset(dst1,0,sizeof(1)*width*height);
	unsigned char * dst2 = (unsigned char *)malloc(sizeof(1)*width*height);
	memset(dst1,0,sizeof(1)*width*height);
	unsigned char * dst3 = (unsigned char *)malloc(sizeof(1)*width*height);
	memset(dst1,0,sizeof(1)*width*height);

	MatrixAdd(src,dst1,width,height);

	sobel_td(src,dst2,width,height);
	sobel5x5(dst2,dst3,width,height);

	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			tmp[j*width + i] = dst1[j*width + i] * dst3[j*width + i];
			if(tmp[j*width + i] < min)
				min = tmp[j*width + i];
		}

	min = (-1)*min;
	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			tmp[j*width + i] += min;
			if(tmp[j*width + i] > max)
				max = tmp[j*width + i];
		}

	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			dst[j*width + i] = (unsigned char)(tmp[j*width + i]*255/max);
		}

	free(tmp);
	free(dst1);
	free(dst2);
	free(dst3);
	return ;
}

void getPicG(unsigned char* src,unsigned char * dst,int width,int height)
{
	unsigned char * dst1 = (unsigned char *)malloc(sizeof(1)*width*height);
	memset(dst1,0,sizeof(1)*width*height);
	int * tmp = (int *)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);
	int min = 255,max = 0;
	int i,j;
	getPicF(src,dst1,width,height);

	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			tmp[j*width + i] = src[j*width + i] + dst1[j*width + i];
			if(tmp[j*width + i] < min)
				min = tmp[j*width + i];
		}

	min = (-1)*min;
	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			tmp[j*width + i] += min;
			if(tmp[j*width + i] > max)
				max = tmp[j*width + i];
		}

	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			dst[j*width + i] = (unsigned char)(tmp[j*width + i]*255/max);
		}

	return;
}

void getPicLast(unsigned char* src,unsigned char * dst,int width,int height,double gama,double c)
{
	int i,j;
	unsigned char gray;
	int target;
	double tmp[256] = {0};
	unsigned char *dst1 = (unsigned char *)malloc(1*width*height);
	memset(dst1,0,1*width*height);


	getPicG(src,dst1,width,height);


	for(j = 0;j<height-1;j++)
		for(i = 0;i<width -1;i++)
		{
			gray = dst1[j*width + i];
			target = pow(gray/255.0,gama)*255;

			if(target < 0)
				target = 0;
			else if(target > 255)
				target = 255;

			dst[j*width + i] = target;
		}


	return ;
}
