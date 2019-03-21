
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

cv::Mat logTransform(Mat srcImage, float c)
{
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;
    cv::Mat resultImage =
      cv::Mat::zeros(srcImage.size(), srcImage.type());
    srcImage.convertTo(resultImage,CV_32F);
    resultImage = resultImage + 1;
    cv::log(resultImage,resultImage);
    resultImage = c * resultImage;
    cv::normalize(resultImage,resultImage,0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage,resultImage);
    return resultImage;
}


int test1_2()
{
    cv::Mat srcImage = cv::imread("../image/lakeWater.jpg",0);
    if(!srcImage.data)
        return -1;
    // 验证三种不同方式的对数变换速度
    cv::imshow("srcImage", srcImage);
    float c = 1.0;
    cv::Mat resultImage;

    resultImage = logTransform(srcImage, c);

    cv::imshow("resultImage", resultImage);
    cv::waitKey(0);
    return 0;
}




