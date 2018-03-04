#ifndef SMOOTH_H_
#define SMOOTH_H_

void GaussianFilter(unsigned char *src,unsigned char *dst,int width,int height,
		int m_width,int m_height,double deta);

void GaussianMask(double *mask,int width,int height,double deta);


void RealRelevant(unsigned char *src,unsigned char *dst,double *mask,int width,
		int height,int m_width,int m_height);

double Distance(double x,double y,double c_x,double c_y);
void MeanFilter(unsigned char *src,unsigned char *dst,int width,int height,int m_width,int m_height);
void MeanMask(double *mask,int width,int height);



#endif
