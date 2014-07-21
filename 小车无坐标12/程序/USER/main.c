/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：将c库中的printf()函数实现到串口1(USART1)。这样我们就可以用printf()将
 *           调试信息通过串口打印到电脑上。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "usart3.h"
#include "usart2.h"
#include "uart4.h"
#include "led.h"
#include "variables.h"
#include "timer.h"
#include "polygon.h"
#include "ringFifo.h"
#include <math.h>
#include <resolve.h>
#include "adc.h"
#include "eceg_usart.h"
#include "protocol.h"
#include "core_cm3.h"
#include <string.h>
#include "stdint.h"

void DK_NVIC_Init(unsigned char Group);
extern uint8_t SendBuff[USART1_SENDBUFF_SIZE];


#pragma push
#pragma O0

void delay_ms(uint32_t u32_ms)
{
	uint32_t u32_len;
    
	for (;u32_ms > 0; u32_ms --)
	{
		for (u32_len = 0; u32_len < 8000; u32_len++ );
	}

}


u16 find_str(char *str1,char *str2)
{
	u16 i,j,k;
	u16 index;
	k = strlen(str2);
	for(i = 0 ;*(str1 + i) != '\0';i ++)
	{
		if ( *(str1 + i) == *str2)
		{
			for(j = 0;j < k;j ++)
			{
				if(*(str1 + i +j ) != *(str2 + j))
					break;
			}
			if (j == k)
				index=i;
// 				printf("str2 first display at%d\n",i);
			else 
				index=NULL;
		}
	}
	return index;
}


#define VS 60000
#define V1f 10000
#define V2f 20000
#define V3f 30000
#define V4f 45000
#define V5f 50000
#define VT1 50000
#define VT2 43000


void order(void)//该函数用于判断串口4接收到了什么指令
{
	char *order1="1fast";//加速命令
	char *order2="2fast";//减速命令
	char *order3="3fast";//加速命令
	char *order4="4fast";//减速命令
	char *order5="5fast";//加速命令
	char *stop="stop";//停止命令
	char *right="right";//右转命令
	char *left="left";//左转命令
	char *orgright="orgright";//原地右转
	char *orgleft="orgleft";//原地左转
	char *back="back";//后退命令
	char *emergency="instanthalt";
	char *remote="ARQ";
	char *path="P";
	
	
	if((strstr(sUart4_entity.u8RX_Buffer,stop)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,order5)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,left)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,right)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,back)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,emergency)==NULL))
	{//如果没有接收到指令的话
		package[60]=0;
	}
// 					if((memcmp(sUart4_entity.u8RX_Buffer,order1,sizeof(sUart4_entity.u8RX_Buffer)))==0)
// 					{
// 						Uart4_Send(sendbuff, u32RxLen);//从机如果收到数据，可以返回一个标志代表收到
// 						LED0_PWM_VAL1=V1f;
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=V1f;
// 						LED0_PWM_VAL4=VS;
// 					}//直行速度1
// 					
// 					else if((memcmp(sUart4_entity.u8RX_Buffer,order2,sizeof(sUart4_entity.u8RX_Buffer)))==0)
// 					{
// 						Uart4_Send(sendbuff, u32RxLen);//从机如果收到数据，可以返回一个标志代表收到
// 						LED0_PWM_VAL1=V2f;
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=V2f;
// 						LED0_PWM_VAL4=VS;
// 					}//直行速度2
					
	if(strstr(sUart4_entity.u8RX_Buffer,order3)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=V3f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V3f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//直行速度3
					
	if(strstr(sUart4_entity.u8RX_Buffer,order4)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=V4f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V4f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//直行速度4
// 					
	if(strstr(sUart4_entity.u8RX_Buffer,order5)!=NULL)
	{
		package[60]='Y';//回送握手信号
						//一旦收到就开始执行
		LED0_PWM_VAL1=V5f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V5f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//直行速度5
					
	if(strstr(sUart4_entity.u8RX_Buffer,stop)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//停止命令
					
	if(strstr(sUart4_entity.u8RX_Buffer,emergency)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VS;
						
		pathok=0;//不能再进行路径解析了

// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//强制停止命令
					
	if(strstr(sUart4_entity.u8RX_Buffer,right)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VS;//右转大调
		LED0_PWM_VAL2=VT1;
		LED0_PWM_VAL3=VT2;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
// 						LED0_PWM_VAL1=VT1;//微调右转
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=VT2;
// 						LED0_PWM_VAL4=VS;
	}//右转 

	if(strstr(sUart4_entity.u8RX_Buffer,left)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VT2;//左转大调
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VT1;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
// 						LED0_PWM_VAL1=VT2;//微调左转
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=VT1;
// 						LED0_PWM_VAL4=VS;
	}//左转		

	if(strstr(sUart4_entity.u8RX_Buffer,orgright)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VT1;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VT1;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//原地右转 

	if(strstr(sUart4_entity.u8RX_Buffer,orgleft)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VT1;
		LED0_PWM_VAL3=VT1;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//原地左转				
	if(strstr(sUart4_entity.u8RX_Buffer,back)!=NULL)
	{
		package[60]='Y';//回送握手信号
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=V4f;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=V4f;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//清空串口4接收缓冲区
	}//后退	
	if(strstr(sUart4_entity.u8RX_Buffer,remote)!=NULL)
	{
		beat++;
		heartok=1;//串口通信恢复正常
		//如果收到读取路径信息的命令
		if((strchr(sUart4_entity.u8RX_Buffer,'B')!=NULL)&&(strchr(sUart4_entity.u8RX_Buffer,'P')!=NULL))
		{
			memcpy(pathrecord,sUart4_entity.u8RX_Buffer,strlen(sUart4_entity.u8RX_Buffer));
			package[59]='M';//回送握手信号
			pathen++;
			if(pathen==1)
				pathresolve(pathrecord);
			else
				pathen=2;
// 			memset(sUart4_entity.u8RX_Buffer,0,100);//清空串口4接收缓冲区
		}	
	}//心跳数据		
}


void hearttest(void)//检测心跳是否正常函数
{
// 	{//上位机每隔1.5秒发出ARQ心跳检测信号
		if(beat==0)
		{//如果没有心跳，则制动，心跳标志位清零
			heartok=0;
			LED0_PWM_VAL1=VS;
			LED0_PWM_VAL2=VS;
			LED0_PWM_VAL3=VS;
			LED0_PWM_VAL4=VS;
		}
		else if(beat!=0)
		{//如果有心跳，那么又可以继续刚才的路径走下去
			heartok=1;
			beat=0;
		}
}

#pragma pop	





/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{
	
	uint32_t i, u32RxLen;
	
 	u16 led0pwmval1=59999;
	u16 led0pwmval2=59999;
	u16 led0pwmval3=59999;
	u16 led0pwmval4=59999;
	u16 adcx;

	float temp;
	double x1,y1,x2,y2,fai;
	
	u8 LAT1,LNG1;//定义两个指针指向存放经纬度的内存地址

	u8 processok=0;//所有数据每20ms处理一次
	double lat,lng;
	double speed2;
// 	double seitatest=0;
	static u8 heartbeat=0;
	
	const u8 at[] = {"receiveok"};
	u8 reply[6]={0x01,0x04,0x01};
	u8 gpsdata[100]={0};//存放待处理的GPS数组
	u8 reply1[3];//准备存放回应的数据	
	u8 reply2[3];//存放左右倾角，滚转角
	u8 reply3[3];//存放前后倾角，俯仰角
	u8 package1[10];//存放纬度
	u8 package2[10];//存放经度
	u8 package3[10];//存放方位角
	u8 package4[10];//存放滚转角
	u8 package5[10];//存放前后倾角
	u8 package6[4];//存放速度
	u8 package7[4];//存放剩余电量
	
	uint8_t source=0x01;//源地址
	uint8_t destination=0x02;//目的地址
	tsPacketOfAppInfo truesendout;//给这个类型定义一个名字
	uint8_t len=61;
	
// 	u8 gpgga[]={"$GPGGA,061021.05,3102.02726033,N,12126.86794498,E,2,12,0.9,25.022,M,8.127,M,1.0,0000*46\r\n"};
  uint8_t sendbuff[]="receiveok";
	u32RxLen=sizeof(at);
	
	ptuoqiu->latitude=&latitude3;
	ptuoqiu->longitude=&longitude3;
	
	gaosi->gaosix =&gaosix3;
	gaosi->gaosiy =&gaosiy3;
	gaosi->gaosix1 =&gaosix4;
	gaosi->gaosiy1 =&gaosiy4;

	DK_NVIC_Init(4);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//设置systick的时钟是AHB不分频的
	SysTick_Config(7200000);//设置两次中断的时间间隔为100ms

/* USART1,2,3 ,UART4 config 115200 8-N-1 */
	USART1_Config();
	USART2_Config();
	USART3_Config();
	UART4_Config();
	
	Usart_DMA_Config();
	LED_GPIO_Config();
	
	delay_ms(1000);
	
	PWM_Initch1(60000,0);	 //不分频。PWM频率=72000000/60000=1.2Khz
	PWM_Initch2(60000,0);
	PWM_Initch3(60000,0);
	PWM_Initch4(60000,0);

	TIM3->CR1|=0x01;    //使能定时器3 

	LED0_PWM_VAL1=led0pwmval1;
	LED0_PWM_VAL2=led0pwmval2;
	LED0_PWM_VAL3=led0pwmval3;
	LED0_PWM_VAL4=led0pwmval4;

//这个是测试用的数据	
  /*填充将要发送的数据*/	
// 	for (i = 0; i < sizeof(at); i++)
//   {
// 			SendBuff[i]	 = at[i];
//   }

// 	USART_SEND(SendBuff, sizeof(at)-1);

// 	delay_ms(1000);
	
	
  /*填充将要发送的数据*/
// 	for (i = 0; i < SENDBUFF_SIZE; i++)
//   {
// 			SendBuff[i]	 = 0x31;
//   }

// 	USART_SEND(SendBuff, 30);
// //测试数据结束	
//  /*串口向 DMA发出请求 */
//  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	

  /*在DMA尚未传送完成时，cpu继续执行main函数中的代码*/
  /*点亮了LED灯*/
/*而同时DMA在向串口运送数据，当DMA发送完成时，在中断函数关闭LED灯 */

	Adc_Init();//ADC转换是分频为12MHz

	
	//order_sendinit();
	while(1)
	{
// 	  gpggaresolve(gpgga);
		//Usart1_Send(command1, sizeof(comd1));
		//delay_ms(500);
// 		static u8 pathen=0;
		
				if (sUsart2_entity.u8RxFlag == 1)
				{//如果收到罗盘返回的数据
					sUsart2_entity.u8RxFlag = 0;
					u32RxLen = sUsart2_entity.u16RxTotalNum;
					sUsart2_entity.u16RxTotalNum = 0;	
					processok=1;//50ms到，可以开始处理数据
					if(sUsart2_entity.u8RX_Buffer[1]==0x0d)//如果传回的数据是角度
					{
						for(i=0;i<3;i++)
						{
							reply1[i]=sUsart2_entity.u8RX_Buffer[10+i];//取出方向角
							reply2[i]=sUsart2_entity.u8RX_Buffer[4+i];//取出左右倾角，滚转角
							reply3[i]=sUsart2_entity.u8RX_Buffer[7+i];//取出前后倾角，俯仰角
						}
					}
					memset(sUsart2_entity.u8RX_Buffer,0,15);
				}
	
				if(sUsart3_entity.u8RxFlag==1)
				{//如果收到GPS传回的数据
					sUsart3_entity.u8RxFlag = 0;
					u32RxLen = sUsart3_entity.u16RxTotalNum;
					sUsart3_entity.u16RxTotalNum = 0;	
					
// 					processok=1;//20ms到，可以开始处理数据
					
					for(i=0;i<sizeof(sUsart3_entity.u8RX_Buffer);i++)
					{
						sUsart3_entity.u8RX_Buffer[i]=gpsdata[i];
					}
					memset(sUsart3_entity.u8RX_Buffer,0,150);
// 					gpggaresolve(sUsart3_entity.u8RX_Buffer);		
				}
				
				if (sUart4_entity.u8RxFlag == 1)
				{//如果收到指令
					sUart4_entity.u8RxFlag = 0;
					u32RxLen = sUart4_entity.u16RxTotalNum;
					sUart4_entity.u16RxTotalNum = 0;			
				}
				
				if(speeden==1)//如果2秒到了的话，测速一次，检测剩余电量一次
				{
					speeden=0;
					heartbeat++;
					memset(package6,0,4);//速度和电量的数组先清掉再赋新的值
					memset(package7,0,4);
					speed2=getspeed((*(gaosi->gaosix1)),(*(gaosi->gaosiy1)));//1秒测速一次
// 					speed2=10.6;
// 					seita=getheading(0.5,-1,1,-2);//检测方位角函数是否正常
// 					gettoorbit(200,330);//检测大调整函数
// 					changedirections(1,4,0.5,-1,1,-2);//检测微调是否正常
					if(heartbeat==7)//每隔14s检测一次心跳是否正常
					{
						heartbeat=0;
						hearttest();//检测心跳是否正常函数
					}
// 					(*(gaosi->gaosix1))+=0.05;
// 					(*(gaosi->gaosiy1))+=0.05;//测试速度
// 					if((*(gaosi->gaosix1))>=5)
// 						*(gaosi->gaosix1)=0;
// 					if((*(gaosi->gaosiy1))>=5)
// 						*(gaosi->gaosiy1)=0;
// 					GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);
// 					speed2=getspeed((*(gaosi->gaosix1)),(*(gaosi->gaosiy1)));//1秒测速一次
					
					sprintf(package6,"%4.1f",speed2);
				
					for(i=50;i<=53;i++)
					{
						package[i]=package6[i-50];//速度数组赋值，准备打包
					}
					temp=powadc();//1秒转换电压一次
					
					sprintf(package7,"%4.1lf",temp);
					for (i=54;i<=57;i++)
					{
						package[i]=package7[i-54];//将电压值赋值到数组的后面
					}
				}
		
				if(processok==1)//如果50ms到了的话，那么所有数据进行处理
				{
					memset(package1,0,10);//数据域经纬度，方位角，前后倾角，左右滚转角数组清零
					memset(package2,0,10);
					memset(package3,0,10);
					memset(package4,0,10);
					memset(package5,0,10);
// 					memset(package6,0,4);//速度和电量的数组先清掉再赋新的值
// 					memset(package7,0,4);
					processok=0;//清零50ms标记

					
					head2=hextodex(reply1);//将角度转换为十进制
					roll2=rolltodec(reply2);
					pitch2=pitchtodec(reply3);
	
					
					gpggaresolve(sUsart3_entity.u8RX_Buffer,&LAT1,&LNG1);//处理GPS的数据
					
					lat=longtodouble(ptuoqiu->LAT);
					lng=longtodouble(ptuoqiu->LNG);
					
					changeformat(lng,lat,ptuoqiu->latitude,ptuoqiu->longitude);//将GPS数据解析成经纬度
					
					order();//判断串口4是否接收到什么指令了
					
					if((pathok==1)&&(heartok==1))//如果允许路径转换的话
					{
						move();//路径转换,大约耗时4ms左右
					}
					
					sprintf(package1,"%10.6lf",*(ptuoqiu->latitude));
					sprintf(package2,"%10.6lf",*(ptuoqiu->longitude));
					sprintf(package3,"%10.6lf",head2);
					sprintf(package4,"%10.6lf",roll2);
					sprintf(package5,"%10.6lf",pitch2);
					
// 					GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);//将小车当前的坐标转换为平面坐标
	
					for(i=0;i<=9;i++)//纬度赋值到数据域
					{
						package[i]=package1[i];
					}
					for(i=10;i<=19;i++)//经度赋值到数据域
					{
						package[i]=package2[i-10];
					}
					
					for(i=20;i<=29;i++)//将方位角赋值到数据域中
					{
						package[i]=package3[i-20];
					}
					
					for(i=30;i<=39;i++)//将左右倾角赋值到数据域中
					{
						package[i]=package4[i-30];
					}

					for(i=40;i<=49;i++)//将前后倾角赋值到数据域中
					{
						package[i]=package5[i-40];
					}
						
					
					
					memset(sUart4_entity.u8RX_Buffer,0,150);
		
					count=SendData_thisprotocol(truesendout,source,destination,len);//所有要打包的数据准备到一个数组里	
	//返回打包后的数据个数,函数很好，但是用于VB非常麻烦，太麻烦了简直，所以不用了,解析的时候实在是崩溃了
					head2=0;
					roll2=0;
					pitch2=0;
					memset(reply1,0,10);//三个角度数组都清零
					memset(reply2,0,10);
					memset(reply3,0,10);
// 					memset(package1,0,10);
// 					memset(package2,0,10);
// 					memset(package3,0,10);
// 					memset(package4,0,10);
// 					memset(package5,0,10);
// 					memset(package6,0,4);
// 					memset(package7,0,4);
			
				}
	}
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/



void DK_NVIC_Init(unsigned char Group)
{
	#if defined (VECT_TAB_RAM)
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#elif defined(VECT_TAB_FLASH_IAP)
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif 
	switch(Group)
	{
		case 0:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		break;
		case 1:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		break;
		case 2:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		break;
		case 3:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
		break;
		case 4:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		break;
	}
}