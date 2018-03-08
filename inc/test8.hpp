#ifndef TEST8_H_
#define TEST8_H_

#define PI 3.1415926
#define POLARWIDTH 180
#define POLARSTEP (PI/POLARWIDTH)

#define TRUE 1
#define GRAY_LEVEL 256

#define MAX_VALUE 255.0
#define MIN_VALUE 0.0
#define THRESHOLD_TYPE1 1
#define THRESHOLD_TYPE2 2
#define THRESHOLD_TYPE3 3
#define THRESHOLD_TYPE4 4


struct SMaxValue
{
	int nValue;
	int nDist;
	int nAngle;
	int nPixels;
};

void test8();

void HoughLine(unsigned char *src,unsigned char *dst,int width,int height,int lineLength);
void HoughLine_x(unsigned char *src,unsigned char *dst,int width,int height,int nLineRet);
void DrawLine(unsigned char *image,int width,int height,double theta,int r);
void SHT(int x,int y,int zero,double * polar);

void MeanThreshold(unsigned char *src,unsigned char *dst,int width,int height,int type);
double getMeaninHist(int start,int end,int *hist);
void Threshold(unsigned char *src,unsigned char *dst,int width,int height,double threshold,int type);
void setHistogram(unsigned char *src,int *hist,int width,int height);
void InitHistogram(int *hist);

#endif
