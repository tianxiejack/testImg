#ifndef TEST6_HPP_
#define TEST6_HPP_

#include "test5.hpp"


typedef struct Position_ MoveDirection;

void test6();

void erosion(uchar* data,uchar* out,int width, int height);
void dilation(uchar* data,uchar* out, int width, int height);
void close(uchar* data,uchar* out, int width, int height);
void open(uchar* data,uchar* out, int width, int height);

#endif
