#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
#include "variables.h"
#include "timer.h"
#include "polygon.h"
#include "ringFifo.h"
#include "math.h"
#include "resolve.h"
#include "usart3.h"
#include "eceg_usart.h"
#include "usart1.h"
#include "usart2.h"
#include "string.h"
#include "protocol.h"
#include "stdint.h"

#define		ABS(A)			(((A) > 0)?(A):(-(A)))

// extern double head2;

#define gpsstate0 0
#define gpsstate1 1
#define gpsstate2 2
#define gpsstate3 3
#define gpsstate4 4
#define gpsstate5 5


//�������������
void order_sendinit()
{
	u8 reply[10];//׼����Ż�Ӧ������	
	u8 i;
	uint32_t u32RxLen;

	Usart2_Send(command2, sizeof(comd2));//��У׼
	while (sUsart2_entity.u8RxFlag == 1)
	{//������յ����̵ķ�������
		sUsart2_entity.u8RxFlag = 0;
		u32RxLen = sUsart2_entity.u16RxTotalNum;
		sUsart2_entity.u16RxTotalNum = 0;			
					
		reply[0]=sUsart2_entity.u8RX_Buffer[4];//ȡ���ж�λ
		if(reply[0]==0xff)
			Usart2_Send(command2, sizeof(comd2));//��У׼һ��
		else//У׼�ɹ�
		{
			Usart2_Send(command5, sizeof(comd5));//�ٷ�����Ϊ�Զ�Ӧ��ģʽ
			while (sUsart2_entity.u8RxFlag == 1)
			{//������յ����̵ķ�������
				sUsart2_entity.u8RxFlag = 0;
				u32RxLen = sUsart2_entity.u16RxTotalNum;
				sUsart2_entity.u16RxTotalNum = 0;			
					
				reply[0]=sUsart2_entity.u8RX_Buffer[4];//ȡ���ж�λ
				if(reply[0]==0xff)
					Usart2_Send(command5, sizeof(comd5));//�ٷ�һ��
				else//�����Զ�Ӧ��ģʽ�ɹ�
				{
					if (sUsart2_entity.u8RxFlag == 1)
					{//����յ����̷��ص�����
						sUsart2_entity.u8RxFlag = 0;
						u32RxLen = sUsart2_entity.u16RxTotalNum;
						sUsart2_entity.u16RxTotalNum = 0;
					}
					for(i=0;i<3;i++)
						reply[i]=sUsart2_entity.u8RX_Buffer[10+i];//ȡ�������
					hextodex(reply);//���Ƕ�ת��Ϊʮ����
					i=0;//����ָ������
				}
			}						

		}
		for(i=0;i<=9;i++)
		reply[i]=0;//������������
	}
}

	


//�ú�������ȡ����ʮ�����Ƶ�����ת����ʮ���ƵĽǶ�ֵ
double hextodex(u8 reply[])
{
	u8 changeresult[6];
	u8 package3[10];
	u8 din[12];
// 	u8 buffertosend[32];
	u8 i;
	static double headtemp=0;
	static u8 headcount=0;
	double heading=0;
	

	
	for(i=0;i<=2;i++)
	{
		changeresult[2*i]=reply[i]/16;//ȡ��ʮ�����Ƹ�λ
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//ȡ��ʮ�����Ƶ�λ
	}
	heading+=changeresult[0];
	for(i=1;i<=5;i++)
		heading=heading*10+changeresult[i];
	heading=(double)heading;//ǿ������ת��Ϊdouble��
	heading=heading/100.0;
	headcount++;
	
	if(headcount>1)//������ǵ�һ�εĻ�
	{
		headcount=2;
		if((ABS(heading-headtemp)>15)&&(ABS(heading-headtemp)<200))//����Ƕȴ�������ֵͻ��Ļ�
		{//�����ͻ���ֵ����
			heading=headtemp;
		}
	}
	
	headtemp=heading;
// 	headtemp=heading;
	heading=0;
	return headtemp;
}


//�ú��������������ת����ʮ���ƵĽǶ�
double rolltodec(u8 reply[])
{
	u8 changeresult[6];
	u8 package4[10];
	u8 din[12];
// 	u8 buffertosend[32];
	u8 i;
	static double rolltemp=0;
	static u8 rollcount=0;
	double roll=0;
	

	
	for(i=0;i<=2;i++)
	{
		changeresult[2*i]=reply[i]/16;//ȡ��ʮ�����Ƹ�λ
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//ȡ��ʮ�����Ƶ�λ
	}
	roll+=changeresult[2];
	for(i=3;i<=5;i++)
		roll=roll*10+changeresult[i];
	roll=(double)roll;//ǿ������ת��Ϊdouble��
	if((changeresult[0]==0)&&(changeresult[1]==0))
		roll=roll/100.0;
	else
		roll=-roll/100.0;
	rollcount++;
	
	if(rollcount>1)//������ǵ�һ�εĻ�
	{
		rollcount=2;
		if((ABS(roll-rolltemp)>5)&&(ABS(roll-rolltemp)<80))//����Ƕȴ�������ֵͻ��Ļ�
		{//�����ͻ���ֵ����
			roll=rolltemp;
		}
	}
	
	rolltemp=roll;
	
	roll=0;
	
	return rolltemp;
}



//�ú�������ǰ�����ת����ʮ���ƵĽǶ�
double pitchtodec(u8 reply[])
{
	u8 changeresult[6];
	u8 package5[10];
	u8 din[12];
// 	u8 buffertosend[32];
	u8 i;
	double pitch=0;
	
	static u8 pitchcount=0;
	static double pitchtemp=0;
	
	for(i=0;i<=2;i++)
	{
		changeresult[2*i]=reply[i]/16;//ȡ��ʮ�����Ƹ�λ
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//ȡ��ʮ�����Ƶ�λ
	}
	pitch+=changeresult[2];
	for(i=3;i<=5;i++)
		pitch=pitch*10+changeresult[i];
	pitch=(double)pitch;//ǿ������ת��Ϊdouble��
	if((changeresult[0]==0)&&(changeresult[1]==0))
		pitch=pitch/100.0;
	else
		pitch=-pitch/100.0;
	
	pitchcount++;
	
	if(pitchcount>1)//������ǵ�һ�εĻ�
	{
		pitchcount=2;
		if((ABS(pitch-pitchtemp)>5)&&(ABS(pitch-pitchtemp)<80))//����Ƕȴ�������ֵͻ��Ļ�
		{//�����ͻ���ֵ����
			pitch=pitchtemp;
		}
	}
	
	pitchtemp=pitch;	
	pitch=0;	
	return pitchtemp;
}


double getspeed(double sx,double sy)
{//�ú�����Լ1s����һ��
	static u8 speedcount=0;
	static u8 speedtempc=0;
	static double pxtemp,pytemp,speedtemp;
	static double speed;
// 	u8 package6[4];
	u8 i;
		//��ʼ���㵱ǰ�ٶ�
	//���Ե�ʱ��ע�����ܵ�ʱ��ų���
				if((sx>3000000)&&(sy>300000))//ֻȡ����Ч����
				{//����ط�ҲҪ���ɵ��ص�ƽ������Ĵ��·�Χ
						speedcount++;
// 						speedtempc=2;
						//���µ������ȥ֮ǰ�����꣬���С����˲ʱ�ٶȣ��ü���ÿ1s����һ�Σ��õ�С����˲ʱ�ٶ�
						if(speedcount>1)
						{
							speed=100*sqrt((sx-pxtemp)*(sx-pxtemp)+(sy-pytemp)*(sy-pytemp))/2;
							//��λ��cm/s	
							speedcount=2;
						}
						pxtemp=sx;//һ����ƽ������ת���������͸�ֵ����������
						pytemp=sy;
				}
				return speed;
}



//�ú������𽫶�ȡ����·����Ϣת��double�͵������
void pathresolve(u8 pathrecord[])
{
	volatile u16 i,j,k,m,index,pathstate;
	u16 index1,index2;
// 	u8 index2,index4,index5;
	u8 *path=pathrecord;
	u8 pathr[20];
	u16 pathindex[200];
	volatile double pathx;
	volatile double pathy;

	volatile u16 indexb;
	volatile u16 indexp;
	
	i=0;
	j=0;
	k=0;
	m=0;
	index=0;
	pathstate=0;
	
	indexb=find_str(pathrecord,"B");
	indexp=find_str(pathrecord,"P");
	//��ʼ��������
	index1=0;
	index2=indexb;
	
	for(i=index2;i<=indexp;i++)
	{
		if(pathrecord[i]==',')//�ҵ�����
		{
			pathindex[j]=i;//���ڴ�Ŷ����±������
			j++;//��¼���ŵĸ���
		}
	}
	for(k=0;k<=j-2;k++)
	{
		index1=pathindex[k];//ȡ�����������м�Ĳ���
		index2=pathindex[k+1];
		for(i=index1+1;i<index2;i++)
		{
			if(pathrecord[i]!=0x2e)//�������С����
				pathr[i-index1-1]=pathrecord[i]-0x30;//����30h���õ�����
			else
				pathr[i-index1-1]=pathrecord[i];//�����С���㣬�Ͳ���
		}
		pathr[13]='\r';
		if(k%2==0)//��������������ţ���Ϊ������
		{
			pathx=pathstopathx(pathr);//�ִ�ת��double����
			pathrecord1[index]=pathx;
			index++;
			pathlen++;//������Ķ���
		}
		else if(k%2==1)//�����ż�������ţ���Ϊ������
		{
			pathy=pathstopathy(pathr);//�ִ�ת��double����
			pathrecord1[index]=pathy;
			index++;
			pathlen++;
			m++;//��ĸ���
			if(m==2)
			{//ÿ�õ�������ͼ���һ�η�λ��
				m=0;
			}
		}
	}
// 	package[35]='0';
	pathok=1;
	memset(pathrecord,0,1024);
	//���Է�λ��
// 	changedirections(px,py,3435820.34,-351793.568,3435823.7295,-351797.626);
	
}
	
	
double pathstopathx(u8 pathr[])
{
	u8 i;
	long long data1=0;
	double pathx;
	
	data1=pathr[0];
	i = 1;
	for(i=1;pathr[i]!='\r';i++)
	{
		if(pathr[i]!=0x2e)//�������С����
		{
			data1=data1*10+pathr[i];//������ת���ɳ�����
		}
	}
	pathx=(double) data1/100000;
	return pathx;
}
	

double pathstopathy(u8 pathr[])
{
	u8 i;
	long long data1=0;
	double pathy;
	
	data1=pathr[0];
	i = 1;
	for(i=1;pathr[i]!='\r';i++)
	{
		if(pathr[i]!=0x2e)//�������С����
		{
			data1=data1*10+pathr[i];//������ת���ɳ�����
		}
	}
	pathy=(double) data1/1000000;
	return pathy;
}


void move(void)
{
	static u16 jp=0;
// 	volatile double pa0,pa1,pa2,pa3;
	u16 jp1;
	static u8 seitaok=0;//�Ƿ�ʼ����·����λ�ǵı�־
// 	static u8 seita;//����·���ķ�λ��
	static u8 gausscount=0;

	//���Ե�ʱ��ע�͵��������ԵĻ�����ע�ͣ�����һ��Ҫ�ų���
	if((*(ptuoqiu->longitude)>115)&&(*(ptuoqiu->longitude)<130)&&(*(ptuoqiu->latitude)>25)&&(*(ptuoqiu->latitude)<35))
	{//����ط�Ҫ���ɵ��صľ�γ�ȵĴ��·�Χ��ƽ������
		GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);//��С����ǰ������ת��Ϊƽ������
		
		if(gausscount>0)//������ǵ�һ��ת��ƽ������
		{ //�����ǲ�������ģ�������������������50cm�Ļ�����һ��������㣬����������
			if((ABS(*(gaosi->gaosix)-*(gaosi->gaosix1))<0.5)&&(ABS(*(gaosi->gaosiy)-*(gaosi->gaosiy1))<0.5))
			{
				*(gaosi->gaosix1)=*(gaosi->gaosix);
				*(gaosi->gaosiy1)=*(gaosi->gaosiy);//���ݷ��뻺����
			}
		}

		else if(gausscount==0)
		{
			*(gaosi->gaosix1)=*(gaosi->gaosix);
			*(gaosi->gaosiy1)=*(gaosi->gaosiy);//����ǵ�һ�εĻ������ݷ��뻺����
			gausscount=1;
		}
		//�����ã��յ�ʱ��ע����һ��Ҫע��
// 		px= 3435823.7112;
//  
// 		py=351797.611133333;

			if(seitaok==0)//ֻ�е�·���ϵ�����ı�ʱ�����¼���·��������ķ�λ��
			{	//����·����������������ߵķ�λ��
				seita=getheading(pathrecord1[jp],pathrecord1[jp+1],pathrecord1[jp+2],pathrecord1[jp+3]);
				seitaok=1;//��Ҫ�����������
			}
			if(rotateok==0)//���С���ķ�λ�Ǻ�·���ĽǶȲ���һ�µĻ�����һֱת��
			{
// 				anglewide=10;//���С����λ�Ǻ�·��ƫ����10�����ҵĻ�����Ϊ�Ѿ���ֱ��ƽ��
				gettoorbit(head2,seita);//��С����ת����·����λ��һ�µĽǶ���ȥ
			}
			//�ٵ������Թ滮��С�����е���
			if(rotateok==1)
			{//����Ѿ�ת���˺�·����λ�Ƕ�һ�µ�λ�õĻ�
// 				anglewide=10;//��ƫ��ʱ����Ϊ�������ǶȺ�ֱ�ߵ�ƫ����10�����ҵ�ʱ����Ѿ��ǱȽ����ص�ƫ����
				changedirections(*(gaosi->gaosix1),*(gaosi->gaosiy1),pathrecord1[jp],pathrecord1[jp+1],pathrecord1[jp+2],pathrecord1[jp+3]);
// 		//������С�����һ���͵ڶ���������߿���
			}
			if((jp+2)<(pathlen-2))
			{
				if((ABS(*(gaosi->gaosix1)-pathrecord1[jp+2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[jp+3])<=0.25))//���С���ߵ�·���ϵĵڶ�����
				{
					jp=jp+2;//ָ����һ����
					seitaok=0;//���¿�ʼ����·����������ķ�λ��
					rotateok=0;//׼�����¿�ʼ��С��ת��һ���ĽǶ�ȥ
				}
			}
			
			else if((jp+2)==(pathlen-2))
			{
				if((ABS(*(gaosi->gaosix1)-pathrecord1[jp+2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[jp+3])<=0.25))//���С���ߵ�·���ϵĵڶ�����
				{
					//����õ�����յ�Ļ�
					pathok=0;
// 					speeden=1;//׼����ʼ��һ�ֵ��ٶȼ���
					pathlen=0;
					jp=0;
// 					gausscount=0;
					seitaok=0;
					rotateok=0;
					rotateok1=0;
					LED0_PWM_VAL1=60000;//ֹͣ
					LED0_PWM_VAL2=60000;
					LED0_PWM_VAL3=60000;
					LED0_PWM_VAL4=60000;
					pathen=0;//�����������ٴν�������
					memset(pathrecord1,0,1024);
				}
			}
			//�����Ƿ�jp��ֵ�ı䣬ֻҪ�����յ㣬��Ҫ�ƶ�����
			if((ABS(*(gaosi->gaosix1)-pathrecord1[pathlen-2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[pathlen-1])<=0.25))//���С���ߵ�·���ϵĵڶ�����
			{
					pathok=0;

					pathlen=0;
					jp=0;

					seitaok=0;
					rotateok=0;
					rotateok1=0;
					LED0_PWM_VAL1=60000;//ֹͣ
					LED0_PWM_VAL2=60000;
					LED0_PWM_VAL3=60000;
					LED0_PWM_VAL4=60000;
					pathen=0;//�����������ٴν�������
					memset(pathrecord1,0,1024);
			}
	}
}



void gpggaresolve(u8 gpgga[],u8 *LAT,u8 *LNG)
{
	u8 i,j,k,index,gpsstate;
	u8 index2,index4,index5;
	u8 *gps=gpgga;
	double *x2,*y2;
	u8 latitude[14];//���γ�ȣ����һ�����\0
	u8 longitude[15];//��ž��ȣ����һ�����\0
	
	volatile double lat,lng;
	
	i=0;
	j=0;
	k=0;
	gpsstate=0;
	
	
	switch(gpsstate)
	{
		case 0:
		{
			gps=(u8 *)strstr((char *)gpgga,"$GPGGA");
			if(gps!=NULL)//����ҵ�GPGGA�������״̬1
				gpsstate=1;
			else//���û�У�������switch
			{
				gpsstate=0;
				break;
			}
		}
		case 1:
		{
			gps=(u8 *)strstr((char *)gpgga,"\r\n");
			if(gps!=NULL)//����ҵ��������������״̬2
				gpsstate=2;
			else
			{
				gpsstate=0;
				break;
			}
		}
		case 2:
		{
			for(i=0;gpgga[i]!='\r';i++)
			{
				if(gpgga[i]==0x2c)//����ҵ����ŵĻ�
				{
					j++;
					if(j==2)
						index2=i;
					else if(j==4)
						index4=i;
					else if(j==5)
					{
						gpsstate=3;//ֻ�е��ҵ�5�����ŵ�ʱ��Ž��м���
						break;//����forѭ��
					}
				}
			}
			if(j!=5)//���û���ҵ�5������
			{
				gpsstate=0;
				break;
			}
		}
		case 3:
		{
				index2=index2+1;//��ǰ�����±�
				for(k=0;k<13;k++)
				{
					if(gpgga[index2+k]!=0x2e)//�������С����
						*(ptuoqiu->LAT+k)=gpgga[index2+k]-0x30;//����30h���õ�����
					else
						*(ptuoqiu->LAT+k)=gpgga[index2+k];//�����С���㣬�Ͳ���
				}
				*(ptuoqiu->LAT+13)='\r';
				
				
				index4=index4+1;
				for(k=0;k<14;k++)
				{
					if(gpgga[index4+k]!=0x2e)//�������С����
						*(ptuoqiu->LNG+k)=gpgga[index4+k]-0x30;//����30H,�õ�����
					else
						*(ptuoqiu->LNG+k)=gpgga[index4+k];
				}
				*(ptuoqiu->LNG+14)='\r';
				

		}
		break;
	}
	
	//�����Ϊû����������
	if(gpsstate!=3)
	{
		*(ptuoqiu->LAT+13)='\r';
		*(ptuoqiu->LNG+14)='\r';

		memset(longitude,0,15);
		memset(latitude,0,14);

		gpsstate=0;//״̬����
	}
	else if(gpsstate==3)//����������������Ļ�
		gpsstate=0;//״̬����

}



double longtodouble(u8 data[])
{
	u8 i;
	long long data1=0;
	double laln;
	
	data1=data[0];
	i = 1;
	for(i=1;data[i]!='\r';i++)
	{
		if(data[i]!=0x2e)//�������С����
		{
			data1=data1*10+data[i];//������ת���ɳ�����
		}
	}
	laln=(double) data1/100000000;	
	return laln;
}


