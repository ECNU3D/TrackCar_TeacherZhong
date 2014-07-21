
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

// extern double head2;//����main�еĴ����������ڸ�.c�п���

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
//��GPS���ݸ�ʽ����ת����ȫ��ת��Ϊ�Զ�Ϊ��λ,������GPS���ݣ�����Ǿ��Ⱥ�γ��
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
		longitudea= (int)flongitude/100;//����
		latitudea=(int)flatitude/100;//���ȶ���
		longitudeb=(flongitude-longitudea*100)/(double) 60;//���ȷ���ת����
		latitudeb=(flatitude-latitudea*100)/(double) 60;//γ�ȷ���ת����
	}
	
	*(ptuoqiu->longitude)=longitudea+longitudeb;//����
	*(ptuoqiu->latitude)=latitudea+latitudeb;//γ��
	
}



//ע�������´���ĺ��ˣ�����ʵ�ָ�˹����ת����ƽ�����꣬��������֤
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
//Ŀǰ�ú�����VB��λ���е��ã�����������ã�̫��ʱ����
//��˹����ת����ƽ������
//�����Ǿ�γ�ȣ������ƽ������
void GaussProjCal(double longitude, double latitude, double *X, double *Y)
{
	
  double a, e2,e1, A , Bc, C, D, N , x, dl, n, t, n2, pi,xval,yval;
  int m , L0;
  double N1, M1, n1, t1, BB, B0, B1, B2, B4, B6, r;
	
  pi= 4*atan (1.0) ; //3.14=4*pi/4  
	m = ( int) longitude/6+ 1;//21��
  L0= 6*m - 3;   //���������߾���Ϊ123�ȶ���
	dl= longitude- L0;//���ؾ��Ⱥ����������߲�
  dl= dl*pi/180;   //����ת�ɻ���
	latitude=latitude*pi/180;//γ��ת�ɻ���
  a= 6378245.0;   //����뾶
	e1=0.006738525415;//�ڶ�������ƽ��
	e2= 0.006693421623; //��һ������ƽ��
  A = 1.0050517739;  //�ؼ�ϵ��
  Bc= 0.00506237764; //�ؼ�ϵ��  
	C= 0.00001062451;  //�ؼ�ϵ��
	D= 0.00000002081;  //�ؼ�ϵ��
  N = a/sqrt (1- e2*sin (latitude) *sin (latitude) ) ;  //î��Ȧ���ʰ뾶 
	t= tan (latitude) ;
  n= 0.006738525415*cos (latitude) *cos (latitude) ;//
  x= a* (1- e2) * (A * latitude- Bc/2 * sin (2* latitude) + C/4 *sin (4* latitude) - D/6* sin (6* latitude) ) ;
	xval= x+ dl* dl/2* N * sin (latitude) * cos (latitude) * (1+ dl* dl* cos (latitude) * cos (latitude) /12 *(5- t* t+ 9* n+ 4* n* n)
    + dl* dl* dl* dl* cos (latitude) * cos (latitude) * cos (latitude) * cos (latitude)
    /360* (61- 58* t* t+ t* t* t* t) ) ;
	yval= dl* N * cos (latitude) * (1+ dl* dl* cos (latitude) * cos (latitude) /6* (1- t* t+ n)
    + dl* dl* dl* dl* cos (latitude) * cos (latitude) * cos (latitude) * cos (latitude) /120
    * (5- 18* t* t+ t* t* t* t+ 14* n- 58* n* t* t) ) ;
// 	yval= yval+ 500000+ m * 1000000;//��������������21�Ŵ���һ�����������ǲ��������һ���
	yval=yval+500000;
	//����ƽ������
	//px=xval;
	//py=yval;

	*X=xval;
	*Y=yval;
  }

//�������Ѿ�ת���û��õ������ƽ�����꣬������������ߵķ�λ��
double getheading(double x1,double y1,double x2,double y2)
{
	double fai1;
	double dy,dx,pi,k,b;
	double seita1;
	
	pi= 4*atan (1.0) ; //3.14=4*pi/4 
	dy=y2-y1;//�ֱ�ȡ��ƽ�������Ӧ������
	dx=x2-x1;
	
	if((dx!=0)&&(dy!=0))
	{//������������ֵ����Ϊ0�Ļ�
		fai1=ABS(atan(dy/dx));
		fai1=fai1*180/pi;//����ת�ɶ���
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
	LED0_PWM_VAL1=V1;//΢����ת
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V2;
	LED0_PWM_VAL4=V;	
}

void lleft(void)
{
	LED0_PWM_VAL1=V2;//΢����ת
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V1;
	LED0_PWM_VAL4=V;	
}

void ldr(void)
{
	LED0_PWM_VAL1=V3;//����ֱ��
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V3;
	LED0_PWM_VAL4=V;	
}
	
//������Ҫ�жϵĵ��ƽ�����꼴С����������꣬��֪���ߵķ�λ�Ǻ�б�ʣ��������ת������ת������
void changedirections(double x3,double y3,double x1,double y1,double x2,double y2)
{//Ҳ����˵Ŀǰ����������Դ����Ǹ���λ�ǵĺ���
	volatile double dy,dx,pi,k,b;

	pi= 4*atan (1.0) ; //3.14=4*pi/4 
	dy=y2-y1;//�ֱ�ȡ��ƽ�������Ӧ������
	dx=x2-x1;
	
	if((dx!=0)&&(dy!=0))
	{
		k=tan(seita*pi/180);
		b=y1-(k*x1);
	}
	
	if((dx==0)&&(dy>0))
	{
		if((x3-x1)>dpath)//��ֱ���ϣ���ת
		{
			//΢����ת
			lright();	
		}
		if((x1-x3)>dpath)//��ֱ���£���ת
		{
			//΢����ת		
			lleft();
		}
		if((ABS(x1-x3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	else if((dx==0)&&(dy<0))
	{
		if((x3-x1)>dpath)//��ֱ���ϣ���ת
		{
			//΢����ת		
			lleft();
		
		}
		if((x1-x3)>dpath)//��ֱ���£���ת
		{
			//΢����ת
			lright();				
		}
		if((ABS(x1-x3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	else if((dy==0)&&(dx>0))
	{
		if((y3-y1)>dpath)//��ֱ���ң���ת
		{
			//΢����ת		
			lleft();
		
		}
		if((y1-y3)>dpath)//��ֱ������ת
		{
			//΢����ת
			lright();				
		}
		if((ABS(y1-y3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	else if((dy==0)&&(dx<0))
	{
		if((y3-y1)>dpath)//��ֱ���ң���ת
		{
			//΢����ת
			lright();	
		}
		if((y1-y3)>dpath)//��ֱ������ת
		{
			//΢����ת		
			lleft();				
		}
		if((ABS(y1-y3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}

	
	else if((dx!=0)&&(dy!=0)&&(seita>=0)&&(seita<=90))//��һ���޷�λ��
	{
// 		if((k*x3+b)<y3)//����ֱ���·�
		if((y3-(k*x3+b))>dpath)//�����ƫ����ֱ���·�����20cm
		{
			//΢����ת		
			lleft();
		}
// 		else if((k*x3+b)>y3)//����ֱ���Ϸ�
		if(((k*x3+b)-y3)>dpath)//����ֱ���Ϸ�����20cm
		{
			//΢����ת
			lright();	

		}
// 		else if((k*x3+b)==y3)//����ֱ����
		if((ABS(k*x3+b-y3))<=dpath)//ƫ��С��20cm����Ϊ����ֱ����
		{
						//���С���Ѿ���ֱ���ϣ��򾡿��������ֱ��һ�µ�ָ����ȥ
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>270)&&(seita<=360))//�ڶ����޷�λ��
	{
// 		if((k*x3+b)<y3)//����ֱ���Ϸ�
		if((y3-(k*x3+b))>dpath)
		{
			//΢����ת		
			lleft();
		}
// 		else if((k*x3+b)>y3)//����ֱ���·�
		if((k*x3+b-y3)>dpath)
		{
			//΢����ת
			lright();
		}
// 		else if((k*x3+b)==y3)//����ֱ����
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>180)&&(seita<=270))//�������޷�λ��
	{
// 		if((k*x3+b)<y3)//����ֱ���·�
		if((y3-(k*x3+b))>dpath)
		{
			//΢����ת
			lright();
		}
// 		else if((k*x3+b)>y3)//����ֱ���Ϸ�
		if((k*x3+b-y3)>dpath)
		{
			//΢����ת		
			lleft();
		}
// 		else if((k*x3+b)==y3)//����ֱ����
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
	
	else if((dx!=0)&&(dy!=0)&&(seita>90)&&(seita<=180))//�������޷�λ��
	{
// 		if((k*x3+b)<y3)//����ֱ���Ϸ�
		if((y3-(k*x3+b))>dpath)
		{
			//΢����ת
			lright();
		}
// 		else if((k*x3+b)>y3)//����ֱ���·�
		if((k*x3+b-y3)>dpath)
		{
			//΢����ת		
			lleft();
		}
// 		else if((k*x3+b)==y3)//����ֱ����
		if((ABS(k*x3+b-y3))<=dpath)
		{
			gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			if(rotateok1==1)
			{
				ldr();//����ֱ��
			}
		}
	}
	
}
	

void bright(void)
{
	LED0_PWM_VAL1=V;//��ת���
	LED0_PWM_VAL2=BV2;
	LED0_PWM_VAL3=BV1;
	LED0_PWM_VAL4=V;	
}


void bleft(void)
{
	LED0_PWM_VAL1=BV1;//��ת���
	LED0_PWM_VAL2=V;
	LED0_PWM_VAL3=V;
	LED0_PWM_VAL4=BV2;
}


//ǰ����С���Ѿ��ڹ���Ĳ��ֵ�������,���������С����ǰ���ڵصķ�λ�Ǻ͹켣�ķ���ǣ��������Ӧ����ת��ʲô�̶ȵ�����
void gettoorbit(double fai,double fai1)
{//�ú���������С���ص���㣬�൱��С�����������������㣬����ǹ켣�ϵ�һ����
	if((fai1>=0)&&(fai1<=90))//���·����λ���ڵ�һ������
	{
		if(((fai1-fai)>=anglewide)||(fai>=(180+fai1)))//���С������·�������
		{
			rotateok1=0;
			bright();//��ת���		
		}
		else if(((fai-fai1)>=anglewide)&&(fai<(fai1+180)))
		{
			rotateok1=0;
			bleft();//��ת���
		}
	}
	
	
	else if((fai1>90)&&(fai1<=180))//���·����λ���ڵڶ�������
	{
		if(((fai1-fai)>=anglewide)||(fai>=(180+fai1)))//���С������·�������
		{
			rotateok1=0;
			bright();//��ת���				
		}
		else if(((fai-fai1)>=anglewide)&&(fai<(fai1+180)))
		{
			rotateok1=0;
			bleft();//��ת���
		}
	}
	
	
	else if((fai1>180)&&(fai1<=270))//���·����λ���ڵ���������
	{
		if(((fai1-fai)>=anglewide)&&(fai>=(fai1-180)))//���С������·�������
		{
			rotateok1=0;
			bright();//��ת���			
		}
		else if(((fai-fai1)>=anglewide)||(fai<(fai1-180)))
		{
			rotateok1=0;
			bleft();//��ת���
		}
	}
	
	
	else if((fai1>270)&&(fai1<=360))//���·����λ���ڵ���������
	{
		if(((fai1-fai)>=anglewide)&&(fai>=(fai1-180)))//���С������·�������
		{
			rotateok1=0;
			bright();//��ת���			
		}
		else if(((fai-fai1)>=anglewide)||(fai<(fai1-180)))
		{
			rotateok1=0;
			bleft();//��ת���
		}
	}
	if((ABS(fai-fai1))<=anglewide)//���ת����һ����Χ�ڵĽǶȣ���ֱ��
	{
		ldr();//����ֱ��
		
		rotateok=1;//�Ѿ�ת����·���ϵĵ���Ӧ�ķ�λ�Ƕ���
		rotateok1=1;//ת����·���ϵĵ���Ӧ�ķ�λ�Ƕ�	
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
				// ��� y=p.y �� p1p2 �Ľ��� 
				x = ABS(p2.y - p1.y);
				if ( x < 0.0001 ) // p1p2 �� y=p0.yƽ�� 
				continue; 
				if ( pMapNode->y < MIN(p1.y, p2.y) ) // ������p1p2�ӳ����� 
				continue; 
				if ( pMapNode->y >= MAX(p1.y, p2.y) ) // ������p1p2�ӳ����� 
				continue; 
				// �󽻵�� X ���� -------------------------------------------------------------- 
				x = (double)(pMapNode->y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x; 
				if ( x > pMapNode->x ) 
				nCross++; // ֻͳ�Ƶ��߽��� 
		} 
		// ���߽���Ϊż�������ڶ����֮�� --- 
		return (nCross % 2 == 1); 

}  


