/*
 * test1_8.cpp
 *
 *  Created on: 2019年3月22日
 *      Author: jet
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

int test1_8()
{
  cv::Mat srcImage = cv::imread("../image/7.png", 0);
  if (!srcImage.data)
    return -1;
  GaussianBlur(srcImage, srcImage, cv::Size(3, 3),
    0, 0, cv::BORDER_DEFAULT);
  cv::Mat dstImage;
  Laplacian(srcImage, dstImage, CV_16S, 3);
  convertScaleAbs(dstImage, dstImage);
  cv::imshow("srcImage", srcImage);
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
}


