
//#include "lpc17xx_adc.h"
//#include "lpc17xx_libcfg.h"
//#include "lpc17xx_pinsel.h"

#include "ringFifo.h"

#include "polygon.h"
#include "protocol.h"

#include <math.h>
#include "variables.h"
#include "stm32f10x.h"
#include "usart1.h"

#include "usart1.h"
#include <stdarg.h>
#include "ringbuf.h"
#include "stm32f10x_dma.h"
#include "timer.h"
#include "math.h"
#include "stdint.h"

#ifndef		MIN
//#define
#define 	MIN(A, B)		(((A) > (B))?(B):(A))
#endif
#ifndef		MAX
#define 	MAX(A, B)		(((A) > (B))?(A):(B))
#endif
#define		ABS(A)			(((A) > 0)?(A):(-(A)))

#define anglewide 10

// extern double head2;//声明main中的传感器变量在该.c中可用

#define V1 50000
#define V2 38000
#define V3 47000
#define V 60000
#define dpath 0.05

#define BV1 46000
#define BV2 50000

tRingFIFO_Object	InsRingFIFO_AREA;

tsContentOfCmdA_A7 sContentOfCmdA_A7;


void changeformat(double flongitude,double flatitude,double *longitude,double *latitude)
//将GPS数据格式进行转换，全部转换为以度为单位,参数是GPS数据，输出是经度和纬度
{
	
	static double longitudeb=0;
	static double latitudeb=0;
	static int longitudea=0;
	static int latitudea=0;
// 	static u8 latlngcount=0;
// 	u8 package1[10];
// 	u8 package2[10];
// 	u8 i;
	
	if((flongitude!=0)&&(flatitude!=0))
	{
		longitudea= (int)flongitude/100;//度数
		latitudea=(int)flatitude/100;//经度度数
		longitudeb=(flongitude-longitudea*100)/(double) 60;//精度分数转度数
		latitudeb=(flatitude-latitudea*100)/(double) 60;//纬度分数转度数
	}
	
	*(ptuoqiu->longitude)=longitudea+longitudeb;//精度
	*(ptuoqiu->latitude)=latitudea+latitudeb;//纬度
	
}



//注明：以下代码改好了，可以实现高斯坐标转换成平面坐标，本人已验证
// void GaussProjCal(double longitude, double latitude, double *X, double *Y)
// {
// int ProjNo=0; int ZoneWide; ////??
// double longitude1,latitude1, longitude0,latitude0, X0,Y0, xval,yval;
// double a,f, e2,ee, NN, T,C,A, M, iPI;
// iPI = 0.0174532925199433; ////3.1415926535898/180.0;
// ZoneWide = 6; ////6 ???
// a=6378245.0; f=1.0/298.3; //54 ????????
// ////a=6378140.0; f=1/298.257; //80 ????????
// ProjNo = (int)(longitude / ZoneWide) ;
// longitude0 = ProjNo * ZoneWide + ZoneWide / 2;
// longitude0 = longitude0 * iPI ;
// latitude0=0;
// longitude1 = longitude * iPI ; //???????
// latitude1 = latitude * iPI ; //???????
// e2=2*f-f*f;
// ee=e2*(1.0-e2);
// NN=a/sqrt(1.0-e2*sin(latitude1)*sin(latitude1));
// T=tan(latitude1)*tan(latitude1);
// C=ee*cos(latitude1)*cos(latitude1);
// A=(longitude1-longitude0)*cos(latitude1);
// M=a*((1-e2/4-3*e2*e2/64-5*e2*e2*e2/256)*latitude1-(3*e2/8+3*e2*e2/32+45*e2*e2
// *e2/1024)*sin(2*latitude1)+(15*e2*e2/256+45*e2*e2*e2/1024)*sin(4*latitude1)-(35
// *e2*e2*e2/3072)*sin(6*latitude1));
// yval = NN*(A+(1-T+C)*A*A*A/6+(5-18*T+T*T+72*C-58*ee)*A*A*A*A*A/120);
// xval = M+NN*tan(latitude1)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
// +(61-58*T+T*T+600*C-330*ee)*A*A*A*A*A*A/720);
// X0 = 0;
// Y0 = 1000000L*(ProjNo+1)+500000L;
// xval = xval+X0; yval = yval+Y0;
// *X = xval;
// *Y = yval;
// }
//目前该函数在VB上位机中调用，不在这里调用，太费时间了
//高斯坐标转换成平面坐标
//输入是经纬度，输出是平面坐标
void GaussProjCal(double longitude, double latitude, double *X, double *Y)
{
	
  double a, e2,e1, A , Bc, C, D, N , x, dl, n, t, n2, pi,xval,yval;
  int m , L0;
  double N1, M1, n1, t1, BB, B0, B1, B2, B4, B6, r;
	
  pi= 4*atan (1.0) ; //3.14=4*pi/4  
	m = ( int) longitude/6+ 1;//21带
  L0= 6*m - 3;   //中央子午线经度为123度东经
	dl= longitude- L0;//当地经度和中央子午线差
  dl= dl*pi/180;   //经度转成弧度
	latitude=latitude*pi/180;//纬度转成弧度
  a= 6378245.0;   //地球半径
	e1=0.006738525415;//第二离心率平方
	e2= 0.006693421623; //第一离心率平方
  A = 1.0050517739;  //关键系数
  Bc= 0.00506237764; //关键系数  
	C= 0.00001062451;  //关键系数
	D= 0.00000002081;  //关键系数
  N = a/sqrt (1- e2*sin (latitude) *sin (latitude) ) ;  //卯酉圈曲率半径 
	t= tan (latitude) ;
  n= 0.006738525415*cos (latitude) *cos (latitude) ;//
  x= a* (1- e2) * (A * latitude- Bc/2 * sin (2* latitude) + C/4 *sin (4* latitude) - D/6* sin (6* latitude) ) ;
	xval= x+ dl* dl/2* N * sin (latitude) * cos (latitude) * (1+ dl* dl* cos (latitude) * cos (latitude) /12 *(5- t* t+ 9* n+ 4* n* n)
    + dl* dl* dl* dl* cos (latitude) * cos (latitude) * cos (latitude) * cos (latitude)
    /360* (61- 58* t* t+ t* t* t* t) ) ;
	yval= dl* N * cos (latitude) * (1+ dl* dl* cos (latitude) * cos (latitude) /6* (1- t* t+ n)
    + dl* dl* dl* dl* cos (latitude) * cos (latitude) * cos (latitude) * cos (latitude) /120
    * (5- 18* t* t+ t* t* t* t+ 14* n- 58* n* t* t) ) ;
// 	yval= yval+ 500000+ m * 1000000;//这里的坐标加上了21号带，一般的软件里面是不会加上这一项的
	yval=yval+500000;
	//计算平面坐标
	//px=xval;
	//py=yval;

	*X=xval;
	*Y=yval;
  }

//输入是已经转换好或测得的两点的平面坐标，输出是他们连线的方位角
double getheading(double x1,double y1,double x2,double y2)
{
	double fai1;
	double dy,dx,pi,k,b;
	double seita1;
	
	pi= 4*atan (1.0) ; //3.14=4*pi/4 
	dy=y2-y1;//分别取到平面坐标对应的增量
	dx=x2-x1;
	
	if((dx!=0)&&(dy!=0))
	{//如果横纵坐标差值均不为0的话
		fai1=ABS(atan(dy/dx));
		fai1=fai1*180/pi;//弧度转成度数
	}
	
	
	if((dx==0)&&(dy>0))
		seita1=90;
	else if((dx==0)&&(dy<0))
		seita1=270;
	else if((dy==0)&&(dx>0))
		seita1=0;
	else if((dy==0)&&(dx<0))
		seita1=180;
	
	
	else if ((dy>0)&&(dx>0))
		seita1=fai1;
	else if((dy<0)&&(dx<0))
		seita1=180+fai1;
	else if((dy<0)&&(dx>0))
		seita1=360-fai1;
	else if((dy>0)&&(dx<0))
		seita1=180-fai1;
	return seita1;
}

void lright(void)
{
	LED0_PWM_VAL1=V1;//微调右转
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V2;
	LED0_PWM_VAL4=V;	
}

void lleft(void)
{
	LED0_PWM_VAL1=V2;//微调左转
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V1;
	LED0_PWM_VAL4=V;	
}

void ldr(void)
{
	LED0_PWM_VAL1=V3;//慢速直行
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V3;
	LED0_PWM_VAL4=V;	
}
	
//输入是要判断的点的平面坐标即小车本身的坐标，已知连线的方位角和斜率，输出是左转或者右转的命令
void changedirections(double x3,double y3,double x1,double y1,double x2,double y2)
{//也就是说目前这个函数可以代替那个求方位角的函数
	volatile double dy,dx,pi,k,b;

	pi= 4*atan (1.0) ; //3.14=4*pi/4 
	dy=y2-y1;//分别取到平面坐标对应的增量
	dx=x2-x1;
	
	if((dx!=0)&&(dy!=0))
	{
		k=tan(seita*pi/180);
		b=y1-(k*x1);
	}
	
	if((dx==0)&&(dy>0))
	{
		if((x3-x1)>dpath)//在直线上，右转
		{
			//微调右转
			lright();	
		}
		if((x1-x3)>dpath)//在直线下，左转
		{
			//微调左转		
			lleft();
		}
		if((ABS(x1-x3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	else if((dx==0)&&(dy<0))
	{
		if((x3-x1)>dpath)//在直线上，左转
		{
			//微调左转		
			lleft();
		
		}
		if((x1-x3)>dpath)//在直线下，右转
		{
			//微调右转
			lright();				
		}
		if((ABS(x1-x3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	else if((dy==0)&&(dx>0))
	{
		if((y3-y1)>dpath)//在直线右，左转
		{
			//微调左转		
			lleft();
		
		}
		if((y1-y3)>dpath)//在直线左，右转
		{
			//微调右转
			lright();				
		}
		if((ABS(y1-y3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	else if((dy==0)&&(dx<0))
	{
		if((y3-y1)>dpath)//在直线右，右转
		{
			//微调右转
			lright();	
		}
		if((y1-y3)>dpath)//在直线左，左转
		{
			//微调左转		
			lleft();				
		}
		if((ABS(y1-y3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}

	
	else if((dx!=0)&&(dy!=0)&&(seita>=0)&&(seita<=90))//第一象限方位角
	{
// 		if((k*x3+b)<y3)//点在直线下方
		if((y3-(k*x3+b))>dpath)//如果点偏差在直线下方大于20cm
		{
			//微调左转		
			lleft();
		}
// 		else if((k*x3+b)>y3)//点在直线上方
		if(((k*x3+b)-y3)>dpath)//点在直线上方大于20cm
		{
			//微调右转
			lright();	

		}
// 		else if((k*x3+b)==y3)//点在直线上
		if((ABS(k*x3+b-y3))<=dpath)//偏差小于20cm，认为点在直线上
		{
						//如果小车已经在直线上，则尽快调整到和直线一致的指向上去
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>270)&&(seita<=360))//第二象限方位角
	{
// 		if((k*x3+b)<y3)//点在直线上方
		if((y3-(k*x3+b))>dpath)
		{
			//微调左转		
			lleft();
		}
// 		else if((k*x3+b)>y3)//点在直线下方
		if((k*x3+b-y3)>dpath)
		{
			//微调右转
			lright();
		}
// 		else if((k*x3+b)==y3)//点在直线上
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>180)&&(seita<=270))//第三象限方位角
	{
// 		if((k*x3+b)<y3)//点在直线下方
		if((y3-(k*x3+b))>dpath)
		{
			//微调右转
			lright();
		}
// 		else if((k*x3+b)>y3)//点在直线上方
		if((k*x3+b-y3)>dpath)
		{
			//微调左转		
			lleft();
		}
// 		else if((k*x3+b)==y3)//点在直线上
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>90)&&(seita<=180))//第四象限方位角
	{
// 		if((k*x3+b)<y3)//点在直线上方
		if((y3-(k*x3+b))>dpath)
		{
			//微调右转
			lright();
		}
// 		else if((k*x3+b)>y3)//点在直线下方
		if((k*x3+b-y3)>dpath)
		{
			//微调左转		
			lleft();
		}
// 		else if((k*x3+b)==y3)//点在直线上
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			if(rotateok1==1)
			{
				ldr();//慢速直行
			}
		}
	}
	
}
	

void bright(void)
{
	LED0_PWM_VAL1=V;//右转大调
	LED0_PWM_VAL2=BV2;
	LED0_PWM_VAL3=BV1;
	LED0_PWM_VAL4=V;	
}


void bleft(void)
{
	LED0_PWM_VAL1=BV1;//左转大调
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V;
	LED0_PWM_VAL4=BV2;
}


//前提是小车已经在轨道的部分点上面了,输入参数是小车当前所在地的方位角和轨迹的方向角，输出是他应该旋转到什么程度的命令
void gettoorbit(double fai,double fai1)
{//该函数可以让小车回到起点，相当于小车本身的坐标是新起点，起点是轨迹上的一个点
	if((fai1>=0)&&(fai1<=90))//如果路径方位角在第一象限内
	{
		if(((fai1-fai)>=anglewide)||(fai>=(180+fai1)))//如果小车朝向路径的左侧
		{
			rotateok1=0;
			bright();//右转大调		
		}
		else if(((fai-fai1)>=anglewide)&&(fai<(fai1+180)))
		{
			rotateok1=0;
			bleft();//左转大调
		}
	}
	
	
	else if((fai1>90)&&(fai1<=180))//如果路径方位角在第二象限内
	{
		if(((fai1-fai)>=anglewide)||(fai>=(180+fai1)))//如果小车朝向路径的左侧
		{
			rotateok1=0;
			bright();//右转大调				
		}
		else if(((fai-fai1)>=anglewide)&&(fai<(fai1+180)))
		{
			rotateok1=0;
			bleft();//左转大调
		}
	}
	
	
	else if((fai1>180)&&(fai1<=270))//如果路径方位角在第三象限内
	{
		if(((fai1-fai)>=anglewide)&&(fai>=(fai1-180)))//如果小车朝向路径的左侧
		{
			rotateok1=0;
			bright();//右转大调			
		}
		else if(((fai-fai1)>=anglewide)||(fai<(fai1-180)))
		{
			rotateok1=0;
			bleft();//左转大调
		}
	}
	
	
	else if((fai1>270)&&(fai1<=360))//如果路径方位角在第四象限内
	{
		if(((fai1-fai)>=anglewide)&&(fai>=(fai1-180)))//如果小车朝向路径的左侧
		{
			rotateok1=0;
			bright();//右转大调			
		}
		else if(((fai-fai1)>=anglewide)||(fai<(fai1-180)))
		{
			rotateok1=0;
			bleft();//左转大调
		}
	}
	if((ABS(fai-fai1))<=anglewide)//如果转到了一定范围内的角度，则直行
	{
		ldr();//慢速直行
		
		rotateok=1;//已经转到和路径上的点相应的方位角度了
		rotateok1=1;//转到和路径上的点相应的方位角度	
	}
}
	

MakestrMapNode ptPolygon[16] = {
																	{0.0, 0.0},
																	{1.0, 0.0},
																	{1.0, 1.0},
																	{0.75, 0.5},
																	{0.65, 1.0},
																	{0.35, 1.0},
																	{0.25, 0.5},
																	{0.0, 1.0}
															 };

void TranslateLTude(tsContentOfCmdC_C4 *psContentOfCmdC_C4, uint32_t u32Count)
{
		uint32_t u32I;
		int32_t i32Tmp;
		double dfTmpLatiude, dfTmpLongtitude;
	
	  for( u32I = 0; u32I < u32Count; u32I++ )
		{
				 i32Tmp = psContentOfCmdC_C4->sVertex[u32I].u8Latitude[0];
				 i32Tmp = i32Tmp << 8;
				 i32Tmp += psContentOfCmdC_C4->sVertex[u32I].u8Latitude[1];
				 i32Tmp = i32Tmp << 8;
				 i32Tmp += psContentOfCmdC_C4->sVertex[u32I].u8Latitude[2];
				 if( (i32Tmp/10000000) == 1 )
				 {
							i32Tmp = -i32Tmp;
				 }
				 dfTmpLatiude = (double)i32Tmp/10000;
				 
				 i32Tmp = psContentOfCmdC_C4->sVertex[u32I].u8Longitude[0];
				 i32Tmp = i32Tmp << 8;
				 i32Tmp += psContentOfCmdC_C4->sVertex[u32I].u8Longitude[1];
				 i32Tmp = i32Tmp << 8;
				 i32Tmp += psContentOfCmdC_C4->sVertex[u32I].u8Longitude[2];
				 if( (i32Tmp/10000000) == 1 )
				 {
							i32Tmp = -i32Tmp;
				 }
				 dfTmpLongtitude = (double)i32Tmp/10000;
				 
				 GaussProjCal(dfTmpLongtitude, dfTmpLatiude, &ptPolygon[u32I].x, &ptPolygon[u32I].y);  
				 
		}// End for
		
}

char PtInPolygon (MakestrMapNode *pMapNode, int nCount) 
{ 
		int nCross = 0, i;
		MakestrMapNode p1;
		MakestrMapNode p2;
		double x;

		for (i = 0; i < nCount; i++) 
		{ 
				p1.x = ptPolygon[i].x; p1.y = ptPolygon[i].y; 
				p2.x = ptPolygon[(i + 1) % nCount].x; p2.y = ptPolygon[(i + 1) % nCount].y; 
				// 求解 y=p.y 与 p1p2 的交点 
				x = ABS(p2.y - p1.y);
				if ( x < 0.0001 ) // p1p2 与 y=p0.y平行 
				continue; 
				if ( pMapNode->y < MIN(p1.y, p2.y) ) // 交点在p1p2延长线上 
				continue; 
				if ( pMapNode->y >= MAX(p1.y, p2.y) ) // 交点在p1p2延长线上 
				continue; 
				// 求交点的 X 坐标 -------------------------------------------------------------- 
				x = (double)(pMapNode->y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x; 
				if ( x > pMapNode->x ) 
				nCross++; // 只统计单边交点 
		} 
		// 单边交点为偶数，点在多边形之外 --- 
		return (nCross % 2 == 1); 

}  


