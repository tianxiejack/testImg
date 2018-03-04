#include "unsmooth.hpp"
#include "smooth.hpp"

void UnsharpMasking(unsigned char *src,unsigned char *dst,int width,int height,int smooth_type,
		int smooth_mask_width,int smooth_mask_height,double gaussian_deta,double k)
{
    switch (smooth_type) {
        case SMOOTH_GAUSSIAN:
            GaussianFilter(src, dst,width,height, smooth_mask_width, smooth_mask_height,gaussian_deta);
            break;
        case SMOOTH_MEAN:
            MeanFilter(src, dst,width,height, smooth_mask_width, smooth_mask_height);
            break;
        default:
            break;
    }
    matrixSub(src, dst, dst, width, height);
    matrixMultreal(dst, dst, k, width, height);
    matrixAdd(src, dst, dst, width, height);
}

void matrixSub(unsigned char *src1,unsigned char *src2,unsigned char *dst,int width,int height)
{
    for(int i=0;i<width*height;i++)
        dst[i]=src1[i]-src2[i];
}

void matrixMultreal(unsigned char *src,unsigned char *dst,double k,int width,int height)
{
    for(int i=0;i<width*height;i++)
        dst[i]=src[i]*k;
}

void matrixAdd(unsigned char *src1,unsigned char *src2,unsigned char *dst,int width,int height)
{
    for(int i=0;i<width*height;i++)
        dst[i]=src1[i]+src2[i];
}

void matrixCopy(unsigned char *src,unsigned char *dst,int width,int height)
{
    for(int i=0;i<width*height;i++)
        dst[i]=src[i];
}

