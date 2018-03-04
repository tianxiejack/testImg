#include "smooth.hpp"
#include "base.hpp"

void GaussianMask(double *mask,int width,int height,double deta)
{
    double deta_2=deta*deta;
    double center_x=(double)width/2.0-0.5;
    double center_y=(double)height/2.0-0.5;
    double param=1.0/(2*M_PI*deta_2);
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++){
            double distance=Distance(j, i, center_x, center_y);
            mask[i*width+j]=param*exp(-(distance*distance)/(2*deta_2));

    }
    double sum=0.0;
    for(int i=0;i<width*height;i++)
        sum+=mask[i];
    for(int i=0;i<width*height;i++)
        mask[i]/=sum;
}


void GaussianFilter(unsigned char *src,unsigned char *dst,int width,int height,int m_width,int m_height,double deta)
{
	double * mask=(double *)malloc(sizeof(double)*m_width*m_height);
    GaussianMask(mask, m_width, m_height, deta);
    RealRelevant(src,dst,mask,width,height,m_width,m_height);
    free(mask);
}

void RealRelevant(unsigned char *src,unsigned char *dst,double *mask,
                  int width,int height,int m_width,int m_height)
{
    unsigned char *temp=(unsigned char *)malloc(sizeof(unsigned char)*width*height);
    if(temp==NULL)
   {
        printf("realrelecant:malloc wrong\n");
        exit(0);
    }
    int mask_center_x=m_width/2;
    int mask_center_y=m_height/2;

    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
	{
        	unsigned char value=0.0;
              for(int n=0;n<m_height;n++)
                for(int m=0;m<m_width;m++)
		  {
                    if((i+m-mask_center_x)<width&&(j+n-mask_center_y)<height&&
                       (i+m-mask_center_x)>=0&&(j+n-mask_center_y)>=0)
                   {
                        value+=src[(j+n-mask_center_y)*width+(i+m-mask_center_x)]*mask[n*m_width+m];
                    }
                }
            temp[j*width+i]=value;
       }
    for(int i=0;i<width*height;i++)
        dst[i]=temp[i];
    free(temp);
}

double Distance(double x,double y,double c_x,double c_y){

    return sqrt((x-c_x)*(x-c_x)+(y-c_y)*(y-c_y));
}


void MeanMask(double *mask,int width,int height)
{
    double w=width;
    double h=height;
    double meanvalue=1.0/(w*h);
    for(int i=0;i<width*height;i++)
        mask[i]=meanvalue;
}


void MeanFilter(unsigned char *src,unsigned char *dst,int width,int height,int m_width,int m_height)
{
	double * mask=(double *)malloc(sizeof(double)*m_width*m_height);

    MeanMask(mask, m_width, m_height);
    RealRelevant(src,dst,mask,width,height,m_width,m_height);

    free(mask);
}


