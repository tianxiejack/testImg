#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "test2.hpp"
#include "test3.hpp"
#include "test5.hpp"
#include "test6.hpp"
#include "test7.hpp"
#include "test8.hpp"
#include "test_delaunay.hpp"

using namespace std;
using namespace cv;



float hex2float(int num)
{
	return (*(float*)&num);
}

int float2hex(float num)
{
	return (*(int*)&num);
}

int main(int argc , char** argv)
{


	//test_triangle();

	//test2();
	//test3();
	//test6();
	//test7();

	//test5();
	//test8();

	return 0;
}
