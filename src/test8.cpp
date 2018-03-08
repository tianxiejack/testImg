#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "stdlib.h"
#include "stdio.h"
#include "test8.hpp"
#include "test5.hpp"



using namespace cv;

void test8()
{
	Mat src = imread("houfutest.png", 2);
	Mat dst1 = Mat(src.rows,src.cols,CV_8UC1);
	Mat dst2 = Mat(src.rows,src.cols,CV_8UC1);


	cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("b",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("c",CV_WINDOW_AUTOSIZE);
	
	cvMoveWindow("src",100,100);
	cvMoveWindow("b",200,100);
	cvMoveWindow("c",300,100);
	
	//HoughLine(src.data,dst1.data,src.cols,src.rows,20);

	//MeanThreshold(src.data,dst1.data,src.cols,src.rows,3);
	HoughLine(src.data,dst2.data,src.cols,src.rows,100);
	

	imshow("src",src);
	imshow("b",dst1);
	imshow("c",dst2);
	waitKey(0);

	return ;
}

void InitHistogram(int *hist)
{
    for(int i=0;i<GRAY_LEVEL;i++)
        hist[i]=0;
}

void setHistogram(unsigned char *src,int *hist,int width,int height)
{
    InitHistogram(hist);
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int tempv=src[j*width+i];
            hist[tempv]++;
        }
}

void Threshold(unsigned char *src,unsigned char *dst,int width,int height,double threshold,int type)
{
    if(type==THRESHOLD_TYPE1){
        for(int i=0;i<width*height;i++)
            dst[i]=src[i]>threshold?src[i]:MIN_VALUE;
    }else if(type==THRESHOLD_TYPE2){
        for(int i=0;i<width*height;i++)
            dst[i]=src[i]>threshold?MAX_VALUE:src[i];
    }else if(type==THRESHOLD_TYPE3){
        for(int i=0;i<width*height;i++)
            dst[i]=src[i]>threshold?MAX_VALUE:MIN_VALUE;
    }else if(type==THRESHOLD_TYPE4){
        for(int i=0;i<width*height;i++)
            dst[i]=src[i]>threshold?MIN_VALUE:MAX_VALUE;
    }
    
}

void MeanThreshold(unsigned char *src,unsigned char *dst,int width,int height,int type)
{
    int hist[GRAY_LEVEL];
    double threshold_value=0.0;
    InitHistogram(hist);
    setHistogram(src, hist, width,height);    
    threshold_value=getMeaninHist(0, GRAY_LEVEL, hist);
    Threshold(src,dst, width, height, threshold_value,type);
}

double getMeaninHist(int start,int end,int *hist)
{
    int hist_count=0;
    double hist_value=0;
    for(int i=start;i<end;i++){
        hist_count+=hist[i];
        hist_value+=(double)hist[i]*i;
    }
    return hist_value/(double)hist_count;
}



void SHT(int x,int y,int zero,double * polar)
{
    double angle_step=PI/POLARWIDTH;
    double angle= -PI/2;
    for(int i=0;i<POLARWIDTH;i++)
   {

        int p_y=(int)((sin(angle)*y+cos(angle)*x))+zero;
	
   
        polar[p_y*POLARWIDTH+i]++;
	//if(p_y >= 754)
		//printf(" polar[%d*POLARWIDTH+%d] = %f\n", p_y,i,polar[p_y*POLARWIDTH+i]);
        angle+=angle_step;
    }
	
   return ;
}

void DrawLine(unsigned char *image,int width,int height,double theta,int r)
{
    if(theta==PI/2||theta==-PI/2)
    {
        for(int j=0;j<height;j++)
	 {
            if(r<height&&r>=0)
                image[j*width+r]=255;
        }
    }
    else
    {
        double tan_theta=tan(theta);
        for(int i=0;i<width;i++)
	 {
            int j=(int)(tan_theta*i+r);
            if(j<height&&j>=0)
                image[j*width+i]=255;
        }
    }
}

void HoughLine(unsigned char *src,unsigned char *dst,int width,int height,int lineLength)
{
    int polar_height =2*(int)(sqrt(width*width+height*height)+1);
    int polar_width = POLARWIDTH;
    double *polar=(double *)malloc(sizeof(double)*polar_height*polar_width);
    Zero(polar,polar_width,polar_height);
	
    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
	 {
            if(src[j*width+i]==255)
                SHT(i, j,polar_height/2,polar);	
        }
    }

	#if 0
		for(int ll = 754;ll<1000 ;ll++)
		for(int kk=0;kk<POLARWIDTH - 1;kk++)
		{
			if(polar[ll*POLARWIDTH+kk])
				printf(" 11111111polar[%d*POLARWIDTH+%d] = %f\n", ll,kk,polar[ll*POLARWIDTH+kk]);
		}
	#endif	
	
    for(int j=0; j<polar_height;j++)
        for(int i=0;i<polar_width;i++)
	 {
            if(polar[j*polar_width+i]>lineLength)
	     {
                double theta=i*POLARSTEP;
                if(theta == PI/2 || theta == -PI/2)
                    DrawLine(dst, width, height, theta, abs(j-polar_height/2));
                else if (theta==0)
                    DrawLine(dst, width, height, theta, abs(j-polar_height/2));
                else
                    DrawLine(dst, width, height, theta, -(int)((j-polar_height/2)/cos(i*POLARSTEP)));
            }
        }
    free(polar);
}


void HoughLine_x(unsigned char *src,unsigned char *dst,int width,int height,int nLineRet)
{
	int i,j;
	int nMaxDist=(int)(sqrt(width*width+height*height)+1);
   	int nMaxAngle=90;
	memset(dst,0,width*height);
	
	SMaxValue* pInfoRet = new SMaxValue[nLineRet];
	memset(pInfoRet,0,sizeof(SMaxValue)*nLineRet);

	int nAreaNum = nMaxAngle*nMaxDist;
	int *pTransArea = new int[nAreaNum];
	memset(pTransArea ,0,nAreaNum*sizeof(int));

	unsigned char bt;
	int nAngle,nDist;
	double fRadian;
	for(j = 0;j<height-1;i++)
		for(i=0;i<width -1 ;j++)
		{
			bt = 1;//bt = src[j*width + i];
			if(bt == 255)
			{
				for(nAngle=0;nAngle<nMaxAngle;nAngle++)
				{
					fRadian = nAngle*2*PI/180.0;
					nDist = (i*cos(fRadian) + j*sin(fRadian));
					if(nDist >= 0)
						pTransArea[nDist*nMaxAngle + nAngle]++;
					else
					{
						nDist = fabs(nDist);
						//pTransArea[nMaxAngle*nMaxDist + nDist*nMaxAngle + nAngle]++;
					}
					
				}
			}
		}
	return ;
	SMaxValue MaxValue1;
	int nMaxDisAllow = 20;
	int nMaxAngleAllow = 5;


	for(int nLine=0; nLine<nLineRet; nLine++) 
	{	
		MaxValue1.nValue = 0;
		for(i=0; i<nAreaNum; i++)
		{
			if(pTransArea[i] > MaxValue1.nValue)
			{
				MaxValue1.nValue = pTransArea[i];
				MaxValue1.nAngle = i;
			}
		}
		
		if(MaxValue1.nValue == 0) 
		{
			return;
		}
		
		if(MaxValue1.nAngle < nMaxAngle * nMaxDist)
		{
			MaxValue1.nDist = MaxValue1.nAngle/nMaxAngle;
			MaxValue1.nAngle = MaxValue1.nAngle%nMaxAngle;
		}
		else
		{
			MaxValue1.nAngle -= nMaxAngle * nMaxDist;
			
			MaxValue1.nDist = MaxValue1.nAngle/nMaxAngle;
			MaxValue1.nDist *= -1;
			
			
			MaxValue1.nAngle = MaxValue1.nAngle%nMaxAngle;
		}
		

		pInfoRet[nLine].nAngle = MaxValue1.nAngle*2;
		pInfoRet[nLine].nDist = MaxValue1.nDist;
		pInfoRet[nLine].nPixels = MaxValue1.nValue;	
		
		if(pInfoRet[nLine].nDist < 0)
		{
			pInfoRet[nLine].nAngle = pInfoRet[nLine].nAngle - 180;
			pInfoRet[nLine].nDist = pInfoRet[nLine].nDist*(-1);
			
		}
		

		for(nDist = (-1)*nMaxDisAllow; nDist <= nMaxDisAllow; nDist ++)
		{
			for(nAngle = (-1)*nMaxAngleAllow; nAngle <= nMaxAngleAllow; nAngle ++)
			{
				int nThisDist = MaxValue1.nDist + nDist;
				int nThisAngle = MaxValue1.nAngle + nAngle;
				
				
				
				nThisAngle *= 2;
				
				if(nThisAngle < 0 && nThisAngle >= -180)
				{
					nThisAngle += 180;
					nThisDist *= -1;
				}
				if(nThisAngle >= 180 && nThisAngle < 360)
				{
					nThisAngle -= 180; 
					nThisDist *= -1;
				}
				
				
				
				if(fabs(nThisDist) <= nMaxDist
					&& nThisAngle >= 0 && nThisAngle <= nMaxAngle*2)
				{
					nThisAngle /= 2;
					if(nThisDist >= 0)
					{
						pTransArea[nThisDist*nMaxAngle + nThisAngle] = 0;
					}
					else
					{
						nThisDist = fabs(nThisDist);
						pTransArea[nMaxDist*nMaxAngle + nThisDist*nMaxAngle + nThisAngle] = 0;
					}
				}
			}//for nAngle
		}//for nDist
	}


	for (int k = 0; k<nLineRet; k++)
	{
		for(int i = 0; i <height-1; i++)
		{
			for(int j = 0;j <width -1; j++)
			{	
				int mDist;
				
				mDist = (int) (j*cos(pInfoRet[k].nAngle*PI/180.0) + \
							i*sin(pInfoRet[k].nAngle*PI/180.0));
	
				if (mDist == pInfoRet[k].nDist) 
					dst[i*width+j] = 255;
			}//for j
		}//for i
	}//for k


		
	delete []pTransArea;

	return ;
}


    void Hough(unsigned char *src,int width,int height, int *pR, int *pTh, int iThreshold)  
    {  
        int *pArray;  
        int iRMax = (int)sqrt(width * width + height * height) + 1;  
        int iThMax = 361;  
        int iTh = 0;  
        int iR;  
        int iMax = -1;  
        int iThMaxIndex = -1;  
        int iRMaxIndex = -1;  
      
        pArray = new int[iRMax * iThMax];  
        memset(pArray, 0, sizeof(int) * iRMax * iThMax);  
      
        float fRate = (float)(PI/180);  
      
        for (int y = 0; y < height; y++)  
        {  
            for (int x = 0; x < width; x++)  
            {  
                if(*src == 255)  
                {  
                    for(iTh = 0; iTh < iThMax; iTh += 1)  
                    {  
                        iR = (int)(x * cos(iTh * fRate) + y * sin(iTh * fRate));  
      
                        if(iR > 0)  
                        {  
                            pArray[iR/1 * iThMax + iTh]++;  
                        }  
                    }  
                }  
      
                src++;  
            } // x  
        } // y  
      
        for(iR = 0; iR < iRMax; iR++)  
        {  
            for(iTh = 0; iTh < iThMax; iTh++)  
            {  
                int iCount = pArray[iR * iThMax + iTh];  
                if(iCount > iMax)  
                {  
                    iMax = iCount;  
                    iRMaxIndex = iR;  
                    iThMaxIndex = iTh;  
                }  
            }  
        }  
      
        if(iMax >= iThreshold)  
        {  
            *pR = iRMaxIndex;  
            *pTh = iThMaxIndex;  
        }  
      
        delete []pArray;  
      
        return;  
    } // end of Hough  
