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
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);

	
	Sobel(src.data,dst1.data, NULL, src.cols,src.rows,3);


	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sobel1",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("sobel1",100,100);

	//imshow("src",src);
	imshow("sobel1",dst1);


	waitKey(0);

	return ;
}

double Sobel(unsigned char *src,unsigned char *dst,double *edgedriction,int width,int height,int sobel_size)
{
    //double SobelMask_x[3]={-1,-2,-1,0,0,0,1,2,1};
    unsigned char *dst_x=(unsigned char *)malloc(sizeof(unsigned char)*width*height);
    unsigned char *dst_y=(unsigned char *)malloc(sizeof(unsigned char)*width*height);
    if(sobel_size==3){
        double SobelMask1[3]={0.25,0.5,0.25};
        double SobelMask2[3]={1,0,-1};
        RealConvolution(src, dst_x, SobelMask1, width, height, 1, 3);
        RealConvolution(dst_x, dst_x, SobelMask2, width, height, 3, 1);

        RealConvolution(src, dst_y, SobelMask2, width, height, 1, 3);
        RealConvolution(dst_y, dst_y, SobelMask1, width, height, 3, 1);
    }else if(sobel_size==5){
        double SobelMask1[5]={0.0625,0.25,0.375,0.25,0.0625};
        double SobelMask2[5]={1/3.0,2/3.0,0,-2/3.0,-1/3.0};
        RealConvolution(src, dst_x, SobelMask1, width, height, 1, 5);
        RealConvolution(dst_x, dst_x, SobelMask2, width, height, 5, 1);

        RealConvolution(src, dst_y, SobelMask2, width, height, 1, 5);
        RealConvolution(dst_y, dst_y, SobelMask1, width, height, 5, 1);

    }else if(sobel_size==7){
        double SobelMask1[7]={0.015625,0.09375,0.234375,0.3125,0.234375,0.09375,0.015625};
        double SobelMask2[7]={0.1,0.4,0.5,0,-0.5,-0.4,-0.1};
        RealConvolution(src, dst_x, SobelMask1, width, height, 1, 7);
        RealConvolution(dst_x, dst_x, SobelMask2, width, height, 7, 1);

        RealConvolution(src, dst_y, SobelMask2, width, height, 1, 7);
        RealConvolution(dst_y, dst_y, SobelMask1, width, height, 7, 1);

    }
    if(edgedriction!=NULL)
        getEdgeAngle(dst_x, dst_y, edgedriction, width, height);
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            dst[j*width+i]=abs(dst_x[j*width+i])+abs(dst_y[j*width+i]);
        }
    free(dst_x);
    free(dst_y);
    return findMatrixMax(dst,width,height,NULL);
}


double findMatrixMax(unsigned char *src,int width,int height,Position *max_position)
{
    double max=-1.0;
    double value=0.0;
    int x,y;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
	{
            value=src[j*width+i];
            if(value>max){
                value=max;
                x=i;
                y=j;
            } 
        }
    if(max_position!=NULL){
        max_position->x=x;
        max_position->y=y;
    }
    return max;
}

void getEdgeAngle(unsigned char *src_x,unsigned char *src_y,double *edgeAngle,int width,int height)
{
    double x;
    double y;
    for(int i=0;i<width*height;i++){
        x=src_x[i];
        y=src_y[i];
        if(!(x==0.0&&y==0.0)){
            double v=atan2(y, x)*180.0/M_PI;
            if(v<0.0)
                v+=360.0;
            edgeAngle[i]=v;
        }else
            edgeAngle[i]=-1.0;
    }
}


void RealConvolution(unsigned char *src,unsigned char *dst,double *mask,
                     int width,int height,int m_width,int m_height)
{
    double *temp=(double *)malloc(sizeof(double)*width*height);
    RotateRealMatrix(mask,temp,m_width,m_height);
    RealRelevant(src, dst, temp, width, height, m_width, m_height);
}

void RotateRealMatrix(double *matrix,double *dst,int width,int height)
{
    double *temp=(double*)malloc(sizeof(double)*width*height);
    if(temp==NULL){
        printf("malloc wrong!\n");
        exit(0);
    }
    for(int i=0;i<width*height;i++){
        temp[width*height-1-i]=matrix[i];
    }
    for(int i=0;i<width*height;i++){
        dst[i]=temp[i];
    }
    free(temp);
}

