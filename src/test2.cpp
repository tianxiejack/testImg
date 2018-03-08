#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"
#include "test2.hpp"


using namespace cv;

void test2()
{

	Mat src = imread("1.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst2 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst3 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst4 = Mat(src.rows,src.cols,CV_8UC1);

	if (src.empty()){
		printf("imread failed \n");
		return ;
	}

	//printf("channel = %d\n",src.channels());

	GaussFilter(src.data,dst1.data ,src.cols ,src.rows);
	getPicC(src.data,dst2.data,src.cols ,src.rows);
	getPicD(src.data,dst3.data,src.cols ,src.rows,1.0);
	getPicD(src.data,dst4.data,src.cols ,src.rows,3.0);

	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("GaussianFilter",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("UnsharpMasking",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("d",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("e",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("GaussianFilter",200,100);
	cvMoveWindow("UnsharpMasking",300,100);
	cvMoveWindow("d",400,100);
	cvMoveWindow("e",500,100);

	imshow("src",src);
	imshow("GaussianFilter",dst1);
	imshow("UnsharpMasking",dst2);
	imshow("d",dst3);
	imshow("e",dst4);

	waitKey(0);
	return ;
}


void generateGaussianTemplate(double *GaussMask, int ksize, double Sigmma)
{
	#define SIZE 3
	#define PI 3.1415926

	double weight;
	double sum = 0;
	//double Sigmma = 1;

	double Gaussian_Temp[SIZE][SIZE] = {0};
	int i,j;

	weight = 2*PI*Sigmma*Sigmma;
	for(i =0;i <SIZE;i++)
	{
	 for(j = 0;j < SIZE;j++)
	 {
		 Gaussian_Temp[i][j] =weight* exp(-((i-SIZE/2)*(i-SIZE/2)+(j-SIZE/2)*(j-SIZE/2))/(2.0*Sigmma*Sigmma));
		 sum += Gaussian_Temp[i][j];
	 }
	}

	for(i = 0; i < SIZE;i++)
	{
		 for(j = 0;j < SIZE;j++)
	 {
		 GaussMask[i*SIZE + j] = Gaussian_Temp[i][j]/sum;
		 //printf("%f ",GaussMask[i*SIZE + i]);
	 }
		 //printf("\n");
	}

}

void GaussFilter(unsigned char* src,unsigned char* dst ,int width ,int height)
{
	double GaussMask[3*3] = {0};
	generateGaussianTemplate(GaussMask,3,1);

	int *tmp = (int*)malloc(sizeof(int)*width*height);
	memset(tmp,0,sizeof(int)*width*height);
	int i,j;
	for(j=1;j<height-2;j++)
		for(i=1;i<width-2;i++)
		{
			tmp[j*width + i] =
					GaussMask[0]*src[(j-1)*width + i-1] + GaussMask[1]*src[(j-1)*width + i] + GaussMask[2]*src[(j-1)*width + i+1]
				+   GaussMask[3]*src[(j)*width + i-1] 	+ GaussMask[4]*src[(j)*width + i] 	+ GaussMask[5]*src[(j)*width + i+1]
				+   GaussMask[6]*src[(j+1)*width + i-1] + GaussMask[7]*src[(j+1)*width + i] + GaussMask[8]*src[(j+1)*width + i+1];

			if(tmp[j*width + i] < 0)
				dst[j*width + i] = 0;
			else if(tmp[j*width + i] > 255)
				dst[j*width + i] = 255;
			else
				dst[j*width + i] = tmp[j*width + i];
			//printf("j =%d ,i=%d , %f\n",j,i,tmp[j*width + i]);
		}

	/*
	for(j=0;j<height-1;j++)
		for(i=0;i<width-1;i++)
		{
			if(i == 0 || j == 0 ||
					i == width -1 || j == height -1 )
				dst[j*width + i] = 0;
		}
	*/


	free(tmp);
	return ;
}

void getPicC(unsigned char *src,unsigned char* dst,int width ,int height)
{
	unsigned char*dst1 = (unsigned char*)malloc(1*width*height);
	memset(dst1,0,width*height);
	int *tmp = (int *)malloc(4*width*height);
	memset(tmp,0,4*width*height);

	int i,j;
	GaussFilter(src ,dst1 ,width,height);
	int min = 255,max = 0;
	for(j = 0 ;j<height-1;j++)
		for(i = 0;i<width - 1;i++)
		{
			tmp[j*width + i] = src[j*width + i] - dst1[j*width + i];

			if(tmp[j*width + i] < min)
					min = tmp[j*width + i];
			#if 0
			if(tmp[j*width + i] < 0)
				tmp[j*width + i]  = 0;
			else if(tmp[j*width + i] > 255)
				tmp[j*width + i]  = 255;
			else
				dst[j*width + i] = tmp[j*width + i] ;
			#endif
		}

#if 1
	min = min*(-1);
	for(j = 0 ;j<height-1;j++)
		for(i = 0;i<width - 1;i++)
		{
			tmp[j*width + i] += min ;
			if(tmp[j*width + i] > max)
					max = tmp[j*width + i];
		}

	for(j = 0 ;j<height-1;j++)
		for(i = 0;i<width - 1;i++)
		{
			dst[j*width + i] = tmp[j*width + i]*255/max;
		}

#endif
	free(dst1);
	free(tmp);
	return ;
}

void getPicD(unsigned char *src,unsigned char* dst,int width ,int height,double k)
{
	unsigned char* dst1 = (unsigned char*)malloc(1*width*height);
	memset(dst1,0,width*height);
	int tmp;

	getPicC(src,dst1,width ,height);

	int i,j;
	for(j = 0 ;j<height-1;j++)
		for(i = 0;i<width - 1;i++)
		{
			tmp = src[j*width + i] + k*dst1[j*width + i];
			if(tmp > 255)
				dst[j*width + i] = 255;
			else if(tmp < 0)
				dst[j*width + i] = 0;
			else
				dst[j*width + i] = tmp;
		}


	free(dst1);
	return ;
}
