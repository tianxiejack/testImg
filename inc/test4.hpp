#ifndef TEST4_H_
#define TEST4_H_

struct Complex_{
    double real;
    double imagin;
};
typedef struct Complex_ Complex;


int test4();
void DFT(double * src,Complex * dst,int size);
void IDFT(Complex *src,Complex *dst,int size);










#endif
