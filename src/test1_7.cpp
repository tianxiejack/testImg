
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

int test1_7()
{
    //cv::Mat srcImage = cv::imread("../image/flower3.jpg",0);
    cv::Mat srcImage = cv::imread("../image/alfa.tif",0);

     if(srcImage.empty())
          return-1;
    cv::imshow("srcImage",srcImage);
    cv::Mat resBlurMat;
    // 均值滤波
    blur(srcImage, resBlurMat, cv::Size(35, 35));
    cv::imshow("resBlurMat", resBlurMat);

    cv::waitKey(0);
}


