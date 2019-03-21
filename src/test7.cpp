#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdlib.h"
#include "test7.hpp"
#include "base.hpp"


using namespace cv;

void test7()
{
	Mat src = imread("7.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst2 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst3 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst4 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst5 = Mat(src.rows,src.cols,CV_8UC1);

	//printf("src.channel = %d\n",src.channels());
	
	getPic(src.data,dst1.data,src.cols,src.rows,1);	//x
	getPic(src.data,dst2.data,src.cols,src.rows,2);	//y
	getPic(src.data,dst3.data,src.cols,src.rows,0);	//x & y

	getPicX(src.data,dst4.data,src.cols,src.rows,1);	//45
	getPicX(src.data,dst5.data,src.cols,src.rows,2);	//f45
	
	
	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("d",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("e",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("f",CV_WINDOW_AUTOSIZE);

	
	cvMoveWindow("src",100,100);
	cvMoveWindow("b",100,100);
	cvMoveWindow("c",100,100);
	cvMoveWindow("d",100,100);
	cvMoveWindow("e",100,100);
	cvMoveWindow("f",100,100);



	imshow("src",src);
	imshow("b",dst1);
	imshow("c",dst2);
	imshow("d",dst3);
	imshow("e",dst4);
	imshow("f",dst5);

	waitKey(0);

	return ;
}



void getPic(const unsigned char* in, unsigned char* out,short cols, short rows,unsigned char xoy)
{
		char sobel_x[9] = {-1,-2,-1,0,0,0,1,2,1};
		char sobel_y[9] = {-1,0,1,-2,0,2,-1,0,1};		
		
              int xy;
         	for(xy = 0;xy<cols*(rows-2)-2;xy++)
              {
			int H;    
            	  	int V;    
             	 	int O;   
			int i00, i01, i02;
			int i10, i11, i12;
			int i20, i21, i22;
	  
			i00 = in[xy];	i01 = in[xy + 1];	i02 = in[xy + 2];
		 	i10 = in[cols + xy];		i12 = in[cols + 2 + xy];
			i20 = in[2*cols + xy];	i21 = in[2*cols + 1 + xy];	i22 = in[2*cols + 2 + xy];
			i11 = 0;


			H = 		sobel_x[0]*i00 + sobel_x[1]*i01 + sobel_x[2]*i02
				+	sobel_x[3]*i10 + sobel_x[4]*i11 + sobel_x[5]*i12
				+	sobel_x[6]*i20 + sobel_x[7]*i21 + sobel_x[8]*i22;

		       V = 		sobel_y[0]*i00 + sobel_y[1]*i01 + sobel_y[2]*i02
				+	sobel_y[3]*i10 + sobel_y[4]*i11 + sobel_y[5]*i12
				+	sobel_y[6]*i20 + sobel_y[7]*i21 + sobel_y[8]*i22;



		    if(xoy == 1)
                 	 O = abs(H);
		    else if(xoy == 2)
				O = abs(V);
		    else
				O = abs(H) + abs(V);

                  if (O > 255) 
				O = 255;

                  out[xy+1] = O;
              }
 }

void getPicX(const unsigned char* in, unsigned char* out,short cols, short rows,unsigned char xoy)
{
		char sobel_45[9] = {0,1,1,-1,0,1,-1-1,0};
		char sobel_f45[9]  = {-1,-1,0,-1,0,1,0,1,1};
		
		
              int xy;
         	for(xy = 0;xy<cols*(rows-2)-2;xy++)
              {
			int Z;    
            	  	int F;    
             	 	int O;   
			int i00, i01, i02;
			int i10, i11, i12;
			int i20, i21, i22;
	  
			i00 = in[xy];	i01 = in[xy + 1];	i02 = in[xy + 2];
		 	i10 = in[cols + xy];		i12 = in[cols + 2 + xy];
			i20 = in[2*cols + xy];	i21 = in[2*cols + 1 + xy];	i22 = in[2*cols + 2 + xy];
			i11 = 0;


			Z = 		sobel_45[0]*i00 + sobel_45[1]*i01 + sobel_45[2]*i02
				+	sobel_45[3]*i10 + sobel_45[4]*i11 + sobel_45[5]*i12
				+	sobel_45[6]*i20 + sobel_45[7]*i21 + sobel_45[8]*i22;

		       F = 		sobel_f45[0]*i00 + sobel_f45[1]*i01 + sobel_f45[2]*i02
				+	sobel_f45[3]*i10 + sobel_f45[4]*i11 + sobel_f45[5]*i12
				+	sobel_f45[6]*i20 + sobel_f45[7]*i21 + sobel_f45[8]*i22;


		    if(xoy == 1)
                 	 O = abs(Z);
		    else if(xoy == 2)
				O = abs(F);
		    else
				O = abs(Z) + abs(F);

                  if (O > 255) 
				O = 255;

                  out[xy+1] = O;
              }
 }

