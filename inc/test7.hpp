#ifndef TEST7_H_
#define TEST7_H_

struct Position_{
    int x;
    int y;
};
typedef struct Position_ Position;

void test7();

double Sobel(unsigned char *src,unsigned char *dst,double *edgedriction,int width,int height,int sobel_size);

void getEdgeAngle(unsigned char *src_x,unsigned char *src_y,double *edgeAngle,int width,int height);

void RotateRealMatrix(double *matrix,double *dst,int width,int height);

void RealConvolution(unsigned char *src,unsigned char *dst,double *mask,
                     int width,int height,int m_width,int m_height);


double findMatrixMax(unsigned char *src,int width,int height,Position *max_position);




#endif
