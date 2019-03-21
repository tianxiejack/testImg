

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"
#include "test6.hpp"


void test6()
{

	cv::Mat src = cv::imread("6.png", 2);


	if (src.empty()){
		printf("imread failed \n");
		return ;
	}


	cv::Mat dst1 = cv::Mat(src.rows,src.cols,CV_8UC1);
	cv::Mat dst2 = cv::Mat(src.rows,src.cols,CV_8UC1);
	cv::Mat dst3 = cv::Mat(src.rows,src.cols,CV_8UC1);
	cv::Mat dst4 = cv::Mat(src.rows,src.cols,CV_8UC1);

	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("d",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("e",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("b",200,100);
	cvMoveWindow("c",300,100);
	cvMoveWindow("d",400,100);
	cvMoveWindow("e",500,100);

	erosion(src.data,dst1.data,src.cols,src.rows);
	open(src.data,dst2.data,src.cols,src.rows);
	dilation(dst2.data,dst3.data,src.cols,src.rows);
	close(dst2.data,dst4.data,src.cols,src.rows);

	cv::imshow("src",src);
	cv::imshow("b",dst1);
	cv::imshow("c",dst2);
	cv::imshow("d",dst3);
	cv::imshow("e",dst4);

	cv::waitKey(0);

	return ;
}


void erosion(uchar* data,uchar* out,int width, int height)
{
    int i, j, index, sum, flag;
    sum = height * width * sizeof(uchar);
    uchar *tmpdata = (uchar*)malloc(sum);
    memcpy((char*)tmpdata, (char*)data, sum);
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            flag = 1;
            for(int m = i - 1;m < i + 2;m++)
            {
                for(int n = j - 1; n < j + 2;n++)
                {
                    //自身及领域中若有一个为0
                    //则将该点设为0
                    if(tmpdata[i * width + j] == 0 || tmpdata[m * width + n] == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                out[i * width + j] = 0;
            }
            else
            {
                out[i * width + j] = 255;
            }
        }
    }
    free(tmpdata);
}

void dilation(uchar* data,uchar* out, int width, int height)
{
    int i, j, index, sum, flag;
    sum = height * width * sizeof(uchar);
    uchar *tmpdata = (uchar*)malloc(sum);
    memcpy((char*)tmpdata, (char*)data, sum);
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            flag = 1;
            for(int m = i - 1;m < i + 2;m++)
            {
                for(int n = j - 1; n < j + 2;n++)
                {
                    //自身及领域中若有一个为255
                    //则将该点设为255
                    if(tmpdata[i * width + j] == 255 || tmpdata[m * width + n] == 255)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                out[i * width + j] = 255;
            }
            else
            {
                out[i * width + j] = 0;
            }
        }
    }
    free(tmpdata);
}

void open(uchar* data,uchar* out, int width, int height)
{
	uchar * tmp = (uchar*)malloc(width*height);
	erosion(data,tmp, width, height);
	dilation(tmp,out, width, height);
	return ;
}

void close(uchar* data,uchar* out, int width, int height)
{
	uchar * tmp = (uchar*)malloc(width*height);
	dilation(data,tmp, width, height);
	erosion(tmp,out, width, height);
	return ;
}

