#ifndef UNSMOOTH_H_
#define UNSMOOTH_H_


#define SMOOTH_GAUSSIAN 0
#define SMOOTH_MEDIAN 1
#define SMOOTH_BILATERAL 2
#define SMOOTH_MEAN 3


void UnsharpMasking(unsigned char *src,unsigned char *dst,int width,int height,int smooth_type,
		int smooth_mask_width,int smooth_mask_height,double gaussian_deta,double k);

void matrixSub(unsigned char *src1,unsigned char *src2,unsigned char *dst,int width,int height);
void matrixMultreal(unsigned char *src,unsigned char *dst,double k,int width,int height);
void matrixAdd(unsigned char *src1,unsigned char *src2,unsigned char *dst,int width,int height);

#endif
