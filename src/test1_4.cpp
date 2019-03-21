
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// Gamma变换函数实现
cv::Mat gammaTransform(cv::Mat& srcImage, float kFactor)
{
	unsigned char LUT[256];
	for( int i = 0; i < 256; i++ )
	{
		LUT[i] = saturate_cast<uchar>(pow( ( float)(
               i / 255.0 ), kFactor ) * 255.0f );
	}
	cv::Mat resultImage = srcImage.clone();

	if(srcImage.channels() == 1)
	{
		cv::MatIterator_<uchar> iterator =
                 resultImage.begin<uchar>();
		cv::MatIterator_<uchar> iteratorEnd =
                 resultImage.end<uchar>();
		for( ; iterator != iteratorEnd; iterator ++ )
			*iterator = LUT[(*iterator)];
	}else
	{
        cv::MatIterator_<cv::Vec3b> iterator =
               resultImage.begin<Vec3b>();
        cv::MatIterator_<cv::Vec3b> iteratorEnd =
               resultImage.end<Vec3b>();
		for( ; iterator != iteratorEnd; iterator++ )
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}
	return resultImage;
}


int test1_4()
{
     cv::Mat srcImage =  imread("../image/lakeWater.jpg",0);
	 //cv::Mat srcImage =  imread("../image/road.tif",0);

     if( !srcImage.data )
	      return -1;

     float kFactor1 =  0.3;
     float kFactor2 =  3.0;
     float kFactor3 =  4.0;
     float kFactor4 =  5.0;

	 cv::Mat result1 = gammaTransform(srcImage, kFactor1);
	 cv::Mat result2 = gammaTransform(srcImage, kFactor2);
	 cv::Mat result3 = gammaTransform(srcImage, kFactor3);
	 cv::Mat result4 = gammaTransform(srcImage, kFactor4);

     cv::imshow("srcImage", srcImage);
     cv::imshow("result1", result1);
     cv::imshow("result2", result2);
     //cv::imshow("result3", result3);
     //cv::imshow("result4", result4);

     cv::waitKey(0);
	 return 0;
}
