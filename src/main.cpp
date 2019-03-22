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


#include "test1_1.hpp"

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


	//test1_1();
	//test1_2();			//logtrans
	//test1_3();			//liner
	//test1_4();			//gamma
	//test1_5();			//zhifangtu
	//test1_6();			//mediumlvbo
	//test1_7();			//junzhilb
	//test1_8();				//laplace



	//test3();	//kuluAssemble
	//test7(); 			//by

	//test_triangle();

	//test2();
	//test6();


	//test5();
	//test8();

	return 0;
}
