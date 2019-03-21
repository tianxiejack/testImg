
#include <opencv2/opencv.hpp>
using namespace cv;

int test1_5()
{
   cv::Mat srcImage =  imread("../image/dadou.tif",0);
    if( !srcImage.data )
      return 1;
   cv::Mat srcGray;
   cv::imshow("srcImage", srcImage);

   cv::Mat heqResult;
   cv::equalizeHist(srcImage, heqResult);
   cv::imshow("heqResult", heqResult);
   cv::waitKey(0);
   return 0;
}
