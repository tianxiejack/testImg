//
//  main.c
//  Fourer1D
//
//  Created by Tony on 14/11/16.
//  Copyright (c) 2014Äê Tony. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "test4.hpp"

#define SIZE 4


void DFT(double * src,Complex * dst,int size)
{
    clock_t start,end;
    start=clock();
    printf("size=  %d\n",size);
    for(int m=0;m<size;m++)
    {
        double real=0.0;
        double imagin=0.0;
        for(int n=0;n<size;n++)
        {
            double x=M_PI*2*m*n;
            real+=src[n]*cos(x/size);
            imagin+=src[n]*(-sin(x/size));
        }
        dst[m].imagin=imagin;
        dst[m].real=real;

		#if 0
			if(imagin>=0.0)
				printf("%lf+%lfj\n",real,imagin);
			else
				printf("%lf%lfj\n",real,imagin);
		#endif
    }
    end=clock();
    printf("DFT use time :%lf for Datasize of:%d\n",(double)(end-start)/CLOCKS_PER_SEC,size);

}

void IDFT(Complex *src,Complex *dst,int size)
{
    //Complex temp[SIZE];
    clock_t start,end;
    start=clock();
    for(int m=0;m<size;m++){
        double real=0.0;
        double imagin=0.0;
        for(int n=0;n<size;n++)
        {
            double x=M_PI*2*m*n/size;
            real+=src[n].real*cos(x)-src[n].imagin*sin(x);
            imagin+=src[n].real*sin(x)+src[n].imagin*cos(x);

        }
        real/=SIZE;
        imagin/=SIZE;
        if(dst!=NULL){
            dst[m].real=real;
            dst[m].imagin=imagin;
        }
        if(imagin>=0.0)
            printf("%lf+%lfj\n",real,imagin);
        else
            printf("%lf%lfj\n",real,imagin);
    }
    end=clock();
    printf("IDFT use time :%lfs for Datasize of:%d\n",(double)(end-start)/CLOCKS_PER_SEC,size);
}

int test4()
{
    double input[SIZE];
    Complex dst[SIZE];

    input[0] = 1;
    input[1] = 2;
    input[2] = 4;
    input[3] = 4;

    printf("\n\n");
    DFT(input, dst, SIZE);
    printf("\n\n");
    IDFT(dst, NULL, SIZE);

}
