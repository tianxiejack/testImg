#ifndef TEST2_H_
#define TEST2_H_


void test2();
void generateGaussianTemplate(double *GaussMask, int ksize, double sigma);
void GaussFilter(unsigned char* src,unsigned char* dst ,int width ,int height);
void getPicC(unsigned char *src,unsigned char* dst,int width ,int height);
void getPicD(unsigned char *src,unsigned char* dst,int width ,int height,double k);


#endif
