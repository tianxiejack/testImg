#include "test5.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdio.h"


//using namespace cv;

void test5()
{

	cv::Mat src = cv::imread("5.png", 2);


	if (src.empty()){
		printf("imread failed \n");
		return ;
	}

	int width=ChangtoPower2(src.cols);
	int height=ChangtoPower2(src.rows);

	cv::Mat dst1 = cv::Mat(height,width,CV_8UC1);
	cv::Mat dst2 = cv::Mat(src.rows,src.cols,CV_8UC1);
	cv::Mat dst3 = cv::Mat(src.rows,src.cols,CV_8UC1);
	cv::Mat dst4 = cv::Mat(src.rows,src.cols,CV_8UC1);


	FrequencyFiltering(src.data,dst1.data,src.cols,src.rows,20);



	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("d",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("e",CV_WINDOW_AUTOSIZE);

	cvMoveWindow("src",100,100);
	cvMoveWindow("b",200,100);
	cvMoveWindow("c",300,100);
	cvMoveWindow("d",400,100);
	cvMoveWindow("e",500,100);

	cv::imshow("src",src);
	cv::imshow("b",dst1);

	cv::waitKey(0);

	return ;
}


void FrequencyFiltering(unsigned char* src1,unsigned char* dst,int width,int height,double param)
{
	double *temp=NULL;
	//unsigned char *rectmp = (unsigned char*)malloc(1*width*height);
	//Resize_xt(src1,rectmp,width,height);
	

	double* src =  (double*)malloc(sizeof(double)*width*height);
	double* dst1 = (double*)malloc(sizeof(double)*width*height);

	for(int ll = 0; ll < height - 1; ll++)
		for(int kk = 0; kk < width -1 ; kk++)
		{
			src[ll*width + kk] = (double)src1[ll*width + kk];
			//printf("src[%d*width + %d] = %f\n",ll,kk,src[ll*width + kk]);
		}

//////////111111111111		
	/*
	int fft_width  = width*2;
	int fft_height = height*2;
	double *filter=(double *)malloc(sizeof(double)*fft_height*fft_width);
	if(filter==NULL)
	{
		printf("frequency filter malloc faile");
		exit(0);
	}
	FFT_Shift(src,width, height);
	Complex *getap = (Complex *)malloc(sizeof(Complex)*width*height);;
	DFT(src,getap,width*height);
	GaussianLPFilter(filter, fft_width, fft_height, param);
	*/

//////////222222222222

		
	ResizeMatrix4FFT(src, &temp, width, height);
	width = ChangtoPower2(width);
	height = ChangtoPower2(height);


 	int fft_width  = 2*width;
    int fft_height = 2*height;

	double *filter=(double *)malloc(sizeof(double)*fft_height*fft_width);
	if(filter==NULL)
	{
	    printf("frequency filter malloc faile");
	    exit(0);
	}

	Complex *temp_complex=(Complex*)malloc(sizeof(Complex)*fft_height*fft_width);
	if(temp_complex==NULL)
	{
		printf("temp_complex==NULL\n");
		exit(0);
	}

	/*
	unsigned char* iii = (unsigned char*)malloc(fft_width*fft_height);
    	for(int ll = 0; ll < fft_height - 1; ll++)
		for(int kk = 0; kk < fft_width -1 ; kk++)
			iii[ll*fft_width + kk] = (unsigned char)temp[ll*fft_width + kk];
	cv::Mat qqq = cv::Mat(fft_height,fft_width,CV_8UC1,iii);
	cv::imshow("123",qqq);
	cv::waitKey(0);
	*/
	GaussianHPFilter(filter,fft_width,fft_height,50);

	//GaussianLPFilter(filter, fft_width, fft_height, param);
	
	ImageFFT(temp, temp_complex,fft_width,fft_height);
	MatrixMulti_R_C(filter,temp_complex,temp_complex,fft_width*fft_height);

	#if 1
	    for(int ll = 0; ll < fft_width - 1; ll++)
	    		for(int kk = 0; kk < fft_width -1 ; kk++)
	    			printf("filter[%d*fft_width + %d] = %f\n",ll,kk,filter[ll*fft_width + kk]);
	#endif
	
	ImageIFFT(temp_complex, temp, fft_width, fft_height);
       double *result2=(double *)malloc(sizeof(double)*fft_width/2*fft_height/2);
	   
       CutImage421(temp,fft_width,fft_height,result2,fft_width/2,fft_height/2);
       matrixCopy(result2, dst1, fft_width/2, fft_height/2);

	for(int ll = 0; ll < 512 - 1; ll++)
		for(int kk = 0; kk < 512 -1 ; kk++)
			dst[ll*512 + kk] = (unsigned char)temp[ll*512 + kk];


   // free(result2);
  //  free(filter);
   // free(temp_complex);
    //free(rectmp);
    return;
}

void Resize_xt(unsigned char* src,unsigned char* dst,int width,int height)
{
	int i,j;
	for(j=0;j<2*height-1;j++)
		for(i=0;i<2*width-1;i++)
		{
			if(j<height-1 && i<width-1)
				dst[j*width+i] = src[j*width+i];
			else
				dst[j*width+i] = 0;
		}
	return ;
}

void matrixCopy_x(double *src,double *dst,int width,int height)
{
	#if 0
   	for(int i=0;i<width*height;i++)
      	 	dst[i]=src[i];
	#else
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
			dst[j*2*width + i] = src[j*width + i];
	#endif
	return ;
}

void ResizeMatrix4FFT(double *src,double **dst,int width,int height)
{
    int re_width=ChangtoPower2(width);
    int re_height=ChangtoPower2(height);
    double *temp=(double *)malloc(sizeof(double)*re_width*re_height);
    Resize(src, width, height, temp, re_width, re_height);
    *dst=(double *)malloc(sizeof(double)*re_width*re_height*4);
    Zero(*dst, re_width*2, re_height*2);
    matrixCopy_x(temp, *dst, re_width, re_height);

    /*
    double * ddd = *dst;    
    unsigned char* haha = (unsigned char*)malloc(1*4*re_width*re_height);
    for(int ll = 0; ll <2* re_height - 1; ll++)
    		for(int kk = 0; kk < 2* re_width -1 ; kk++)
    			haha[ll* 2*re_width + kk] = (unsigned char)ddd[ll* 2*re_width + kk];


   cv::Mat iii = cv::Mat( 2*re_height, 2*re_width,CV_8UC1,haha);
   cv::imshow("iii",iii);
   cv::waitKey(0);
   return ;
   */
	
   free(temp);
}

void Resize(double *src,int s_width,int s_height,double *dst,int d_width,int d_height)
{
    double r_width=(double)s_width/(double)d_width;
    double r_height=(double)s_height/(double)d_height;
    double x,y;
    double v11,v12,v21,v22;
    double value;
    for(int j=0;j<d_height;j++){
        y=(double)j*r_height;
        for(int i=0;i<d_width;i++){
            x=(double)i*r_width;
            if((int)x==s_width-1&&(int)y<s_height-1){
                v11=src[(int)y*s_width+(int)x];
                v21=src[((int)y+1)*s_width+(int)x];
                double d_y=y-(double)((int)y);
                value=d_y*v21+(1-d_y)*v11;
            }
            else if((int)x<s_width-1&&(int)y==s_height-1){
                v11=src[(int)y*s_width+(int)x];
                v12=src[(int)y*s_width+(int)x+1];
                double d_x=x-(double)((int)x);
                value=d_x*v12+(1-d_x)*v11;
            }
            else if((int)x==s_width-1&&(int)y==s_height-1){
                value=src[(int)y*s_width+(int)x];
            }
            else{
                v11=src[(int)y*s_width+(int)x];
                v12=src[(int)y*s_width+(int)x+1];
                v21=src[((int)y+1)*s_width+(int)x];
                v22=src[((int)y+1)*s_width+(int)x+1];
                double d_x=x-(double)((int)x);
                double d_y=y-(double)((int)y);
                value=(v22*d_x+(1-d_x)*v21)*d_y+(1-d_y)*(v12*d_x+(1-d_x)*v11);
            }
            dst[j*d_width+i]=value;
        }
    }
}


int ChangtoPower2(int size)
{
    size--;
    int i=0;
    while ((size/=2)>0)
    {
        i++;
    }
    return 2<<i;
}


void Zero(double *src,int width,int height){
    for(int i=0;i<width*height;i++)
        src[i]=0.0;
}

double Distance(double x,double y,double c_x,double c_y)
{

    return sqrt((x-c_x)*(x-c_x)+(y-c_y)*(y-c_y));
}

void GaussianLPFilter(double *Filter,int width,int height,double cut_off_frequency)
{
    int center_x=width/2;
    int center_y=height/2;

	cut_off_frequency  =60;
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            double value=Distance((double)i, (double)j, center_x, center_y);
            Filter[j*width+i]=exp(-value*value/(2*cut_off_frequency*cut_off_frequency));

		//printf("value = %f\n",value);
		//printf("exp(value)/(2) = %f\n",exp(value*value/(2*60*60)));
		Filter[j*width+i]  = 1.0/exp(value*value/(2*100*100));
		//printf(" Filter[j*width+i]=%10.20f\n", Filter[j*width+i]);
		//putchar(10);
		//putchar(10);
        }
}

void CutImage421(double *src,int s_width,int s_height,double *dst,int d_width,int d_height)
{
    Position p;
    p.x=0;
    p.y=0;
    matrixCopyLocal(src, dst, s_width, s_height, d_width, d_height, &p);
}

int matrixCopyLocal(double *src,double *dst,int width,int height,int w_width,int w_height,Position *lefttoppoint)
{
    if(lefttoppoint->x+w_width<width&&lefttoppoint->y+w_height<height)
    {
        for(int j=0;j<w_height;j++)
            for(int i=0;i<w_width;i++){
                dst[j*w_width+i]=src[(j+lefttoppoint->y)*width+i+lefttoppoint->x];
            }
        return 1;
    }
    else
        return 0;
}



void MatrixMulti_R_C(double *src1,Complex *src2,Complex *dst,int size)
{
    for(int i=0;i<size;i++)
    {
    		printf("real = %f\n",dst[i].real);
	    printf("imagin = %f\n",dst[i].imagin);

        dst[i].real=src2[i].real*src1[i];
        dst[i].imagin=src2[i].imagin*src1[i];


	printf("111real = %f\n",dst[i].real);
	    printf("111imagin = %f\n",dst[i].imagin);
    }
}

void ImageIFFT(Complex *src,double *dst,int size_w,int size_h)
{
    Complex *temp_c=(Complex*)malloc(sizeof(Complex)*size_w*size_h);
    if(temp_c==NULL)
        exit(0);
    for(int i=0;i<size_w*size_h;i++)
        Copy_Complex(&src[i],&temp_c[i]);
    Complex *temp=(Complex*)malloc(sizeof(Complex)*size_w*size_h);
    if(temp==NULL)
        exit(0);
    double *temp_d=(double *)malloc(sizeof(double)*size_w*size_h);
    if(temp_d==NULL)
        exit(0);
    IFFT2D(temp_c,temp,size_w,size_h);
    for(int j=0;j<size_h;j++)
        for(int i=0;i<size_w;i++){
            temp_d[j*size_w+i]=temp[j*size_w+i].real;
        }
    FFT_Shift(temp_d, size_w, size_h);
    matrixCopy(temp_d, dst, size_w, size_h);
    free(temp);
    free(temp_c);
    free(temp_d);
    return ;
}

double getPower(Complex *src,int totalsize)
{
    double power=0.0;
    double real;
    double imagin;
    for(int i=0;i<totalsize;i++)
    {
        real=src[i].real;
        imagin=src[i].imagin;
        power+=real*real+imagin*imagin;
    }
    return power;
}


void ImageFFT(double * src,Complex * dst,int width,int height)
{
    double *image_data=(double*)malloc(sizeof(double)*width*height);

    matrixCopy(src, image_data, width, height);
    FFT_Shift(image_data,width, height);
    FFT2D(image_data, dst, width, height);
    //DFT(image_data, dst,width*height);

#if 0
    for(int ll = 0; ll < height - 1; ll++)
    		for(int kk = 0; kk < width -1 ; kk++)
    			printf("dst[%d*width + %d] = %f\n",ll,kk,dst[ll*width + kk]);

	unsigned char* iii = (unsigned char*)malloc(width*height);
	for(int ll = 0; ll < height - 1; ll++)
		for(int kk = 0; kk < width -1 ; kk++)
			iii[ll*width + kk] = (unsigned char)image_data[ll*width + kk];
		
	cv::Mat qqq = cv::Mat(height,width,CV_8UC1,iii);
	cv::imshow("222",qqq);
	cv::waitKey(0);
#endif
	
	free(image_data);
    return ;
}

void FFT_Shift(double * src,int size_w,int size_h)
{
    for(int j=0;j<size_h;j++)
        for(int i=0;i<size_w;i++)
        {
            if((i+j)%2)
                src[j*size_w+i]=-src[j*size_w+i];
        }
}

void matrixCopy(double *src,double *dst,int width,int height)
{
	#if 1
   	for(int i=0;i<width*height;i++)
      	 	dst[i]=src[i];
	#else
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
			dst[j*2*width + i] = src[j*width + i];
	#endif
	return ;
}

int FFT2D(double *src,Complex *dst,int size_w,int size_h)
{
    if(isBase2(size_w)==-1||isBase2(size_h)==-1)
    {
       printf("not match 1<<k \n");
       exit(0);
    }

    Complex *temp=(Complex *)malloc(sizeof(Complex)*size_h*size_w);
    if(temp==NULL)
        return -1;
    for(int i=0;i<size_h;i++)
    {
        RealFFT(&src[size_w*i], &temp[size_w*i], size_w);
    }

    Complex *Column=(Complex *)malloc(sizeof(Complex)*size_h);
    if(Column==NULL)
        return -1;
    for(int i=0;i<size_w;i++)
    {
        ColumnVector(&temp[i], Column, size_w, size_h);
        FFT(Column, Column, size_h);
        IColumnVector(Column, &temp[i], size_w, size_h);
    }

    for(int i=0;i<size_h*size_w;i++)
        Copy_Complex(&temp[i], &dst[i]);
	
    free(temp);
    free(Column);
    return 0;
}

void ColumnVector(Complex * src,Complex * dst,int size_w,int size_h)
{
    for(int i=0;i<size_h;i++)
        Copy_Complex(&src[size_w*i], &dst[i]);

}


void Copy_Complex(Complex * src,Complex *dst)
{
    dst->real=src->real;
    dst->imagin=src->imagin;
}

void IColumnVector(Complex * src,Complex * dst,int size_w,int size_h)
{
    for(int i=0;i<size_h;i++)
        Copy_Complex(&src[i],&dst[size_w*i]);

}

void FFT(Complex * src,Complex * dst,int size_n)
{

    int k=size_n;
    int z=0;
    while (k/=2) {
        z++;
    }
    k=z;
    if(size_n!=(1<<k))
        exit(0);
    Complex * src_com=(Complex*)malloc(sizeof(Complex)*size_n);
    if(src_com==NULL)
        exit(0);
    for(int i=0;i<size_n;i++)
    {
        Copy_Complex(&src[i], &src_com[i]);
    }
    FFTComplex_remap(src_com, size_n);
    for(int i=0;i<k;i++){
        z=0;
        for(int j=0;j<size_n;j++)
	 {
            if((j/(1<<i))%2==1)
	     {
                Complex wn;
                getWN(z, size_n, &wn);
                Multy_Complex(&src_com[j], &wn,&src_com[j]);
                z+=1<<(k-i-1);
                Complex temp;
                int neighbour=j-(1<<(i));
                temp.real=src_com[neighbour].real;
                temp.imagin=src_com[neighbour].imagin;
                Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
                Sub_Complex(&temp, &src_com[j], &src_com[j]);
            }
            else
                z=0;
        }

    }


    for(int i=0;i<size_n;i++){
        Copy_Complex(&src_com[i], &dst[i]);
    }
    free(src_com);


}

void getWN(double n,double size_n,Complex * dst){
    double x=2.0*M_PI*n/size_n;
    dst->imagin=-sin(x);
    dst->real=cos(x);
}

void Sub_Complex(Complex * src1,Complex *src2,Complex *dst){
    dst->imagin=src1->imagin-src2->imagin;
    dst->real=src1->real-src2->real;
}

void Add_Complex(Complex * src1,Complex *src2,Complex *dst){
    dst->imagin=src1->imagin+src2->imagin;
    dst->real=src1->real+src2->real;
}

void Multy_Complex(Complex * src1,Complex *src2,Complex *dst){
    double r1=0.0,r2=0.0;
    double i1=0.0,i2=0.0;
    r1=src1->real;
    r2=src2->real;
    i1=src1->imagin;
    i2=src2->imagin;
    dst->imagin=r1*i2+r2*i1;
    dst->real=r1*r2-i1*i2;
}


int FFTComplex_remap(Complex * src,int size_n)
{
    if(size_n==1)
        return 0;
    Complex * temp=(Complex *)malloc(sizeof(Complex)*size_n);
    for(int i=0;i<size_n;i++)
        if(i%2==0)
            Copy_Complex(&src[i],&(temp[i/2]));
        else
            Copy_Complex(&(src[i]),&(temp[(size_n+i)/2]));
		
    for(int i=0;i<size_n;i++)
        Copy_Complex(&(temp[i]),&(src[i]));
    free(temp);
    FFTComplex_remap(src, size_n/2);
    FFTComplex_remap(src+size_n/2, size_n/2);
    return 1;


}

int IFFT2D(Complex *src,Complex *dst,int size_w,int size_h)
{

    if(isBase2(size_w)==-1||isBase2(size_h)==-1)
        exit(0);

    Complex *temp=(Complex *)malloc(sizeof(Complex)*size_h*size_w);
    if(temp==NULL)
        return -1;
    Complex *Column=(Complex *)malloc(sizeof(Complex)*size_h);
    if(Column==NULL)
        return -1;

    for(int i=0;i<size_w;i++){
        ColumnVector(&src[i], Column, size_w, size_h);
        IFFT(Column, Column, size_h);
        IColumnVector(Column, &src[i], size_w, size_h);

    }
    for(int i=0;i<size_w*size_h;i++)
        src[i].imagin=-src[i].imagin;
    for(int i=0;i<size_h;i++){
        IFFT(&src[size_w*i], &temp[size_w*i], size_w);

    }


    for(int i=0;i<size_h*size_w;i++)
        Copy_Complex(&temp[i], &dst[i]);
    free(temp);
    free(Column);
    return 0;

}

void IFFT(Complex * src,Complex * dst,int size_n)
{
    for(int i=0;i<size_n;i++)
        src[i].imagin=-src[i].imagin;
    FFTComplex_remap(src, size_n);
    int z,k;
    if((z=isBase2(size_n))!=-1)
        k=isBase2(size_n);
    else
        exit(0);
    for(int i=0;i<k;i++){
        z=0;
        for(int j=0;j<size_n;j++){
            if((j/(1<<i))%2==1){
                Complex wn;
                getWN(z, size_n, &wn);
                Multy_Complex(&src[j], &wn,&src[j]);
                z+=1<<(k-i-1);
                Complex temp;
                int neighbour=j-(1<<(i));
                Copy_Complex(&src[neighbour], &temp);
                Add_Complex(&temp, &src[j], &src[neighbour]);
                Sub_Complex(&temp, &src[j], &src[j]);
            }
            else
                z=0;
        }

    }
    for(int i=0;i<size_n;i++){
            dst[i].imagin=(1./size_n)*src[i].imagin;
            dst[i].real=(1./size_n)*src[i].real;
        }

}

int isBase2(int size_n)
{
    int k=size_n;
    int z=0;
    while (k/=2)
        z++;

    k = z;
    if(size_n!=(1<<k))
        return -1;
    else
        return k;
}

void RealFFT(double * src,Complex * dst,int size_n)
{

    int k=size_n;
    int z=0;
	
    while (k/=2) 
    {
        z++;
    }
    k=z;
    if(size_n!=(1<<k))
    {
    	printf("RealFFT size_n error \n");
        exit(0);
    }
	
    Complex * src_com=(Complex*)malloc(sizeof(Complex)*size_n);
    if(src_com==NULL)
        exit(0);
    for(int i=0;i<size_n;i++)
   {
        src_com[i].real=src[i];
        src_com[i].imagin=0;
    }
	
    FFTComplex_remap(src_com, size_n);
	
    for(int i=0;i<k;i++)
    {
        z=0;
        for(int j=0;j<size_n;j++)
	{
            if((j/(1<<i))%2==1)
	    {
                Complex wn;
                getWN(z, size_n, &wn);
                Multy_Complex(&src_com[j], &wn,&src_com[j]);
                z+=1<<(k-i-1);
                Complex temp;
                int neighbour=j-(1<<(i));
                temp.real=src_com[neighbour].real;
                temp.imagin=src_com[neighbour].imagin;
                Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
                Sub_Complex(&temp, &src_com[j], &src_com[j]);
            }
            else
                z=0;
        }

    }


    for(int i=0;i<size_n;i++){
        Copy_Complex(&src_com[i], &dst[i]);
    }
    free(src_com);

}


void GaussianHPFilter(double *Filter,int width,int height,double cut_off_frequency)
{  
    int center_x=width/2;  
    int center_y=height/2;  
    for(int i=0;i<width;i++)  
        for(int j=0;j<height;j++){  
            double value=Distance(i, j, center_x, center_y);  
            Filter[j*width+i]=1.0-exp(-value*value/(2*cut_off_frequency*cut_off_frequency));  

		//printf("value = %f\n",value);
		//printf("exp(value)/(2) = %f\n",exp(value*value/(2*60*60)))
		printf(" Filter[j*width+i]=%f\n", Filter[j*width+i]);

	}  
    Filter[width*(height+1)/2]+=1.0;  

	
}  

