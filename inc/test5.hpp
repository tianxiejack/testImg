#ifndef TEST5_H_
#define TEST5_H_


#include "test4.hpp"


struct Position_{
    int x;
    int y;
};
typedef struct Position_ Position;


void test5();
void FrequencyFiltering(unsigned char* src1,unsigned char* dst,int width,int height,double param);
void Resize_xt(unsigned char* src,unsigned char* dst,int width,int height);
void Resize(double *src,int s_width,int s_height,double *dst,int d_width,int d_height);
void ResizeMatrix4FFT(double *src,double **dst,int width,int height);


double Distance(double x,double y,double c_x,double c_y);
void GaussianLPFilter(double *Filter,int width,int height,double cut_off_frequency);

void Zero(double *src,int width,int height);

int ChangtoPower2(int size);

void CutImage421(double *src,int s_width,int s_height,double *dst,int d_width,int d_height);
int matrixCopyLocal(double *src,double *dst,int width,int height,int w_width,int w_height,Position *lefttoppoint);
void MatrixMulti_R_C(double *src1,Complex *src2,Complex *dst,int size);
void ImageIFFT(Complex *src,double *dst,int size_w,int size_h);
double getPower(Complex *src,int totalsize);
void ImageFFT(double * src,Complex * dst,int width,int height);
void FFT_Shift(double * src,int size_w,int size_h);
void matrixCopy(double *src,double *dst,int width,int height);

int FFT2D(double *src,Complex *dst,int size_w,int size_h);
void Copy_Complex(Complex * src,Complex *dst);
void IColumnVector(Complex * src,Complex * dst,int size_w,int size_h);
void FFT(Complex * src,Complex * dst,int size_n);
void Sub_Complex(Complex * src1,Complex *src2,Complex *dst);
void Add_Complex(Complex * src1,Complex *src2,Complex *dst);
void Multy_Complex(Complex * src1,Complex *src2,Complex *dst);

void getWN(double n,double size_n,Complex * dst);
int FFTComplex_remap(Complex * src,int size_n);
void ColumnVector(Complex * src,Complex * dst,int size_w,int size_h);
int IFFT2D(Complex *src,Complex *dst,int size_w,int size_h);
void IFFT(Complex * src,Complex * dst,int size_n);
int isBase2(int size_n);
void RealFFT(double * src,Complex * dst,int size_n);



#endif
