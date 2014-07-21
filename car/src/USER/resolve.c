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


//发送命令给罗盘
void order_sendinit()
{
	u8 reply[10];//准备存放回应的数据	
	u8 i;
	uint32_t u32RxLen;

	Usart2_Send(command2, sizeof(comd2));//先校准
	while (sUsart2_entity.u8RxFlag == 1)
	{//如果接收到罗盘的返回数据
		sUsart2_entity.u8RxFlag = 0;
		u32RxLen = sUsart2_entity.u16RxTotalNum;
		sUsart2_entity.u16RxTotalNum = 0;			
					
		reply[0]=sUsart2_entity.u8RX_Buffer[4];//取出判断位
		if(reply[0]==0xff)
			Usart2_Send(command2, sizeof(comd2));//再校准一遍
		else//校准成功
		{
			Usart2_Send(command5, sizeof(comd5));//再发设置为自动应答模式
			while (sUsart2_entity.u8RxFlag == 1)
			{//如果接收到罗盘的返回数据
				sUsart2_entity.u8RxFlag = 0;
				u32RxLen = sUsart2_entity.u16RxTotalNum;
				sUsart2_entity.u16RxTotalNum = 0;			
					
				reply[0]=sUsart2_entity.u8RX_Buffer[4];//取出判断位
				if(reply[0]==0xff)
					Usart2_Send(command5, sizeof(comd5));//再发一遍
				else//设置自动应答模式成功
				{
					if (sUsart2_entity.u8RxFlag == 1)
					{//如果收到罗盘返回的数据
						sUsart2_entity.u8RxFlag = 0;
						u32RxLen = sUsart2_entity.u16RxTotalNum;
						sUsart2_entity.u16RxTotalNum = 0;
					}
					for(i=0;i<3;i++)
						reply[i]=sUsart2_entity.u8RX_Buffer[10+i];//取出方向角
					hextodex(reply);//将角度转换为十进制
					i=0;//数组指针清零
				}
			}						

		}
		for(i=0;i<=9;i++)
		reply[i]=0;//数组重新清零
	}
}

	


//该函数负责将取出的十六进制的数据转换成十进制的角度值
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
		changeresult[2*i]=reply[i]/16;//取出十六进制高位
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//取出十六进制低位
	}
	heading+=changeresult[0];
	for(i=1;i<=5;i++)
		heading=heading*10+changeresult[i];
	heading=(double)heading;//强制类型转换为double型
	heading=heading/100.0;
	headcount++;
	
	if(headcount>1)//如果不是第一次的话
	{
		headcount=2;
		if((ABS(heading-headtemp)>15)&&(ABS(heading-headtemp)<200))//如果角度传感器的值突变的话
		{//则将这个突变的值丢弃
			heading=headtemp;
		}
	}
	
	headtemp=heading;
// 	headtemp=heading;
	heading=0;
	return headtemp;
}


//该函数负责将左右倾角转换成十进制的角度
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
		changeresult[2*i]=reply[i]/16;//取出十六进制高位
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//取出十六进制低位
	}
	roll+=changeresult[2];
	for(i=3;i<=5;i++)
		roll=roll*10+changeresult[i];
	roll=(double)roll;//强制类型转换为double型
	if((changeresult[0]==0)&&(changeresult[1]==0))
		roll=roll/100.0;
	else
		roll=-roll/100.0;
	rollcount++;
	
	if(rollcount>1)//如果不是第一次的话
	{
		rollcount=2;
		if((ABS(roll-rolltemp)>5)&&(ABS(roll-rolltemp)<80))//如果角度传感器的值突变的话
		{//则将这个突变的值丢弃
			roll=rolltemp;
		}
	}
	
	rolltemp=roll;
	
	roll=0;
	
	return rolltemp;
}



//该函数负责将前后倾角转换成十进制的角度
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
		changeresult[2*i]=reply[i]/16;//取出十六进制高位
	}
	for(i=0;i<=2;i++)
	{
		changeresult[2*i+1]=reply[i]%16;//取出十六进制低位
	}
	pitch+=changeresult[2];
	for(i=3;i<=5;i++)
		pitch=pitch*10+changeresult[i];
	pitch=(double)pitch;//强制类型转换为double型
	if((changeresult[0]==0)&&(changeresult[1]==0))
		pitch=pitch/100.0;
	else
		pitch=-pitch/100.0;
	
	pitchcount++;
	
	if(pitchcount>1)//如果不是第一次的话
	{
		pitchcount=2;
		if((ABS(pitch-pitchtemp)>5)&&(ABS(pitch-pitchtemp)<80))//如果角度传感器的值突变的话
		{//则将这个突变的值丢弃
			pitch=pitchtemp;
		}
	}
	
	pitchtemp=pitch;	
	pitch=0;	
	return pitchtemp;
}


double getspeed(double sx,double sy)
{//该函数大约1s调用一次
	static u8 speedcount=0;
	static u8 speedtempc=0;
	static double pxtemp,pytemp,speedtemp;
	static double speed;
// 	u8 package6[4];
	u8 i;
		//开始计算当前速度
	//调试的时候注掉，跑的时候放出来
				if((sx>3000000)&&(sy>300000))//只取出有效坐标
				{//这个地方也要换成当地的平面坐标的大致范围
						speedcount++;
// 						speedtempc=2;
						//用新的坐标减去之前的坐标，求出小车的瞬时速度，该计算每1s计算一次，得到小车的瞬时速度
						if(speedcount>1)
						{
							speed=100*sqrt((sx-pxtemp)*(sx-pxtemp)+(sy-pytemp)*(sy-pytemp))/2;
							//单位是cm/s	
							speedcount=2;
						}
						pxtemp=sx;//一旦有平面坐标转换出来，就赋值到缓冲区中
						pytemp=sy;
				}
				return speed;
}



//该函数负责将读取到的路径信息转成double型的坐标点
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
	//开始遍历数组
	index1=0;
	index2=indexb;
	
	for(i=index2;i<=indexp;i++)
	{
		if(pathrecord[i]==',')//找到逗号
		{
			pathindex[j]=i;//用于存放逗号下标的数组
			j++;//记录逗号的个数
		}
	}
	for(k=0;k<=j-2;k++)
	{
		index1=pathindex[k];//取出两个逗号中间的部分
		index2=pathindex[k+1];
		for(i=index1+1;i<index2;i++)
		{
			if(pathrecord[i]!=0x2e)//如果不是小数点
				pathr[i-index1-1]=pathrecord[i]-0x30;//减掉30h，得到数字
			else
				pathr[i-index1-1]=pathrecord[i];//如果是小数点，就不减
		}
		pathr[13]='\r';
		if(k%2==0)//如果是奇数个逗号，则为横坐标
		{
			pathx=pathstopathx(pathr);//字串转成double变量
			pathrecord1[index]=pathx;
			index++;
			pathlen++;//点个数的二倍
		}
		else if(k%2==1)//如果是偶数个逗号，则为纵坐标
		{
			pathy=pathstopathy(pathr);//字串转成double变量
			pathrecord1[index]=pathy;
			index++;
			pathlen++;
			m++;//点的个数
			if(m==2)
			{//每拿到两个点就计算一次方位角
				m=0;
			}
		}
	}
// 	package[35]='0';
	pathok=1;
	memset(pathrecord,0,1024);
	//测试方位角
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
		if(pathr[i]!=0x2e)//如果不是小数点
		{
			data1=data1*10+pathr[i];//将数组转换成长整形
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
		if(pathr[i]!=0x2e)//如果不是小数点
		{
			data1=data1*10+pathr[i];//将数组转换成长整形
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
	static u8 seitaok=0;//是否开始计算路径方位角的标志
// 	static u8 seita;//保存路径的方位角
	static u8 gausscount=0;

	//调试的时候注释掉，不调试的话不用注释，而且一定要放出来
	if((*(ptuoqiu->longitude)>115)&&(*(ptuoqiu->longitude)<130)&&(*(ptuoqiu->latitude)>25)&&(*(ptuoqiu->latitude)<35))
	{//这个地方要换成当地的经纬度的大致范围，平滑坐标
		GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);//将小车当前的坐标转换为平面坐标
		
		if(gausscount>0)//如果不是第一次转换平面坐标
		{ //坐标是不能跳变的，如果横纵坐标跳变大于50cm的话，那一定是奇异点，丢掉不处理
			if((ABS(*(gaosi->gaosix)-*(gaosi->gaosix1))<0.5)&&(ABS(*(gaosi->gaosiy)-*(gaosi->gaosiy1))<0.5))
			{
				*(gaosi->gaosix1)=*(gaosi->gaosix);
				*(gaosi->gaosiy1)=*(gaosi->gaosiy);//数据放入缓冲区
			}
		}

		else if(gausscount==0)
		{
			*(gaosi->gaosix1)=*(gaosi->gaosix);
			*(gaosi->gaosiy1)=*(gaosi->gaosiy);//如果是第一次的话，数据放入缓冲区
			gausscount=1;
		}
		//调试用，烧的时候注掉，一定要注掉
// 		px= 3435823.7112;
//  
// 		py=351797.611133333;

			if(seitaok==0)//只有当路径上的坐标改变时才重新计算路径上两点的方位角
			{	//计算路径上面连个点的连线的方位角
				seita=getheading(pathrecord1[jp],pathrecord1[jp+1],pathrecord1[jp+2],pathrecord1[jp+3]);
				seitaok=1;//不要进行这个计算
			}
			if(rotateok==0)//如果小车的方位角和路径的角度不是一致的话，就一直转着
			{
// 				anglewide=10;//如果小车方位角和路径偏差在10度左右的话，认为已经和直线平行
				gettoorbit(head2,seita);//让小车先转到和路径方位角一致的角度上去
			}
			//再调用线性规划对小车进行调整
			if(rotateok==1)
			{//如果已经转到了和路径方位角度一致的位置的话
// 				anglewide=10;//纠偏的时候认为如果方向角度和直线的偏差在10度左右的时候就已经是比较严重的偏差了
				changedirections(*(gaosi->gaosix1),*(gaosi->gaosiy1),pathrecord1[jp],pathrecord1[jp+1],pathrecord1[jp+2],pathrecord1[jp+3]);
// 		//首先让小车向第一个和第二个点的连线靠近
			}
			if((jp+2)<(pathlen-2))
			{
				if((ABS(*(gaosi->gaosix1)-pathrecord1[jp+2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[jp+3])<=0.25))//如果小车走到路径上的第二个点
				{
					jp=jp+2;//指向下一个点
					seitaok=0;//重新开始计算路径上两个点的方位角
					rotateok=0;//准备重新开始把小车转到一定的角度去
				}
			}
			
			else if((jp+2)==(pathlen-2))
			{
				if((ABS(*(gaosi->gaosix1)-pathrecord1[jp+2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[jp+3])<=0.25))//如果小车走到路径上的第二个点
				{
					//如果该点就是终点的话
					pathok=0;
// 					speeden=1;//准备开始新一轮的速度计算
					pathlen=0;
					jp=0;
// 					gausscount=0;
					seitaok=0;
					rotateok=0;
					rotateok1=0;
					LED0_PWM_VAL1=60000;//停止
					LED0_PWM_VAL2=60000;
					LED0_PWM_VAL3=60000;
					LED0_PWM_VAL4=60000;
					pathen=0;//主函数允许再次接收数据
					memset(pathrecord1,0,1024);
				}
			}
			//不论是否jp的值改变，只要靠近终点，都要制动下来
			if((ABS(*(gaosi->gaosix1)-pathrecord1[pathlen-2])<=0.25)&&(ABS(*(gaosi->gaosiy1)-pathrecord1[pathlen-1])<=0.25))//如果小车走到路径上的第二个点
			{
					pathok=0;

					pathlen=0;
					jp=0;

					seitaok=0;
					rotateok=0;
					rotateok1=0;
					LED0_PWM_VAL1=60000;//停止
					LED0_PWM_VAL2=60000;
					LED0_PWM_VAL3=60000;
					LED0_PWM_VAL4=60000;
					pathen=0;//主函数允许再次接收数据
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
	u8 latitude[14];//存放纬度，最后一个添加\0
	u8 longitude[15];//存放经度，最后一个添加\0
	
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
			if(gps!=NULL)//如果找到GPGGA，则进入状态1
				gpsstate=1;
			else//如果没有，则跳出switch
			{
				gpsstate=0;
				break;
			}
		}
		case 1:
		{
			gps=(u8 *)strstr((char *)gpgga,"\r\n");
			if(gps!=NULL)//如果找到结束符，则进入状态2
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
				if(gpgga[i]==0x2c)//如果找到逗号的话
				{
					j++;
					if(j==2)
						index2=i;
					else if(j==4)
						index4=i;
					else if(j==5)
					{
						gpsstate=3;//只有当找到5个逗号的时候才进行计算
						break;//跳出for循环
					}
				}
			}
			if(j!=5)//如果没有找到5个逗号
			{
				gpsstate=0;
				break;
			}
		}
		case 3:
		{
				index2=index2+1;//当前数组下标
				for(k=0;k<13;k++)
				{
					if(gpgga[index2+k]!=0x2e)//如果不是小数点
						*(ptuoqiu->LAT+k)=gpgga[index2+k]-0x30;//减掉30h，得到数字
					else
						*(ptuoqiu->LAT+k)=gpgga[index2+k];//如果是小数点，就不减
				}
				*(ptuoqiu->LAT+13)='\r';
				
				
				index4=index4+1;
				for(k=0;k<14;k++)
				{
					if(gpgga[index4+k]!=0x2e)//如果不是小数点
						*(ptuoqiu->LNG+k)=gpgga[index4+k]-0x30;//减掉30H,得到数字
					else
						*(ptuoqiu->LNG+k)=gpgga[index4+k];
				}
				*(ptuoqiu->LNG+14)='\r';
				

		}
		break;
	}
	
	//如果因为没有正常解析
	if(gpsstate!=3)
	{
		*(ptuoqiu->LAT+13)='\r';
		*(ptuoqiu->LNG+14)='\r';

		memset(longitude,0,15);
		memset(latitude,0,14);

		gpsstate=0;//状态清零
	}
	else if(gpsstate==3)//如果数据正常解析的话
		gpsstate=0;//状态清零

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
		if(data[i]!=0x2e)//如果不是小数点
		{
			data1=data1*10+data[i];//将数组转换成长整形
		}
	}
	laln=(double) data1/100000000;	
	return laln;
}


