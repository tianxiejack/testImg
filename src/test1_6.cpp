
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

void myMedianBlur(Mat& src, Mat& dst,const int kSize)
{
  dst = src.clone();
  std::vector<uchar> vList;
  const int nPix = (kSize*2+1) * (kSize*2+1);
  // 图像源遍历
  for( int i = kSize; i < dst.rows-kSize; ++i )
  {
      for ( int j = kSize; j < dst.cols-kSize; ++j )
      {
          for( int pi = i-kSize; pi <= i+kSize; pi++ )
          {
              for( int pj = j-kSize; pj <= j+kSize; pj++ )
              {
                vList.push_back(src.at<uchar>(pi,pj));
              }
          }
          sort(vList.begin(),vList.end());
          // 提取中间元素作为当前元素
          dst.at<uchar>(i,j) = vList[nPix/2];
          vList.clear();
      }
  }
}
int test1_6( )
{
  cv::Mat image = imread("../image/flower3.jpg",0);
  if(!image.data)
      return -1;
  cv::imshow("image", image);
  cv::Mat dst;
  myMedianBlur(image, dst, 3);
  cv::imshow("out_image", dst);
  cv::waitKey(0);
  return 0;
}

