#ifndef TEST6_HPP_
#define TEST6_HPP_

#include "test5.hpp"


typedef struct Position_ MoveDirection;

void test6();

void erosion(uchar* data,uchar* out,int width, int height);
void dilation(uchar* data,uchar* out, int width, int height);
void close(uchar* data,uchar* out, int width, int height);
void open(uchar* data,uchar* out, int width, int height);

void Zoom(double *src,int s_width,int s_height,double *dst,int d_width,int d_height);
void Erode(unsigned char *src1,int s_width,int s_height,unsigned char *dst1,int d_width,int d_height,double *se,int se_width,int se_height,Position *center);
void Translation(double *src,double *dst,int width,int height,MoveDirection *direction);
void And(double *src0,double *src1,double *dst,int width,int height);



#endif
