#ifndef TEST3_H_
#define TEST3_H_


void test3();

void Laplace(unsigned char *src,unsigned char *dst,int width,int height);
void MatrixAdd(unsigned char *src,unsigned char *dst,int width,int height);
void sobel_td(unsigned char* src,unsigned char *dst,int width,int height);
void sobel5x5(unsigned char* src,unsigned char* dst,int width,int height);
void getPicF(unsigned char* src,unsigned char* dst,int width,int height);
void getPicG(unsigned char* src,unsigned char * dst,int width,int height);
void getPicLast(unsigned char* src,unsigned char * dst,int width,int height,double gama,double c);

#endif
