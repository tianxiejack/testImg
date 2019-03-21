
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;


cv::Mat linearTransform(cv::Mat srcImage, float a, int b)
{
    if(srcImage.empty()){
        std::cout<< "No data!" <<std::endl;
    }
    const int nRows = srcImage.rows;
    const int nCols = srcImage.cols;
    cv::Mat resultImage =
        cv::Mat::zeros(srcImage.size(), srcImage.type());

    for( int i = 0; i < nRows; i++ )
    {
        for( int j = 0; j < nCols; j++ )
        {
                resultImage.at<uchar>(i,j) = saturate_cast<uchar>(a *(srcImage.at<uchar>(i,j)) + b);
        }
    }
    return resultImage;
}
int test1_3()
{
    cv::Mat srcImage = cv::imread("../image/lakeWater.jpg",0);
    if(!srcImage.data)
       return -1;
    cv::imshow("srcImage", srcImage);
    //  cv::waitKey(0);
    // 线性变换
    float a = 1.2;
    int b = 50;
    cv::Mat new_image  = linearTransform(srcImage, a, b);
    cv::imshow("dst", new_image);
    cv::waitKey(0);
    return 0;
}
