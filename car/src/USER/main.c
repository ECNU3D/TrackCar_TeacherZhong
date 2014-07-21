/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ����c���е�printf()����ʵ�ֵ�����1(USART1)���������ǾͿ�����printf()��
 *           ������Ϣͨ�����ڴ�ӡ�������ϡ�         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
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


void order(void)//�ú��������жϴ���4���յ���ʲôָ��
{
	char *order1="1fast";//��������
	char *order2="2fast";//��������
	char *order3="3fast";//��������
	char *order4="4fast";//��������
	char *order5="5fast";//��������
	char *stop="stop";//ֹͣ����
	char *right="right";//��ת����
	char *left="left";//��ת����
	char *orgright="orgright";//ԭ����ת
	char *orgleft="orgleft";//ԭ����ת
	char *back="back";//��������
	char *emergency="instanthalt";
	char *remote="ARQ";
	char *path="P";
	
	
	if((strstr(sUart4_entity.u8RX_Buffer,stop)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,order5)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,left)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,right)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,back)==NULL)&&(strstr(sUart4_entity.u8RX_Buffer,emergency)==NULL))
	{//���û�н��յ�ָ��Ļ�
		package[60]=0;
	}
// 					if((memcmp(sUart4_entity.u8RX_Buffer,order1,sizeof(sUart4_entity.u8RX_Buffer)))==0)
// 					{
// 						Uart4_Send(sendbuff, u32RxLen);//�ӻ�����յ����ݣ����Է���һ����־�����յ�
// 						LED0_PWM_VAL1=V1f;
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=V1f;
// 						LED0_PWM_VAL4=VS;
// 					}//ֱ���ٶ�1
// 					
// 					else if((memcmp(sUart4_entity.u8RX_Buffer,order2,sizeof(sUart4_entity.u8RX_Buffer)))==0)
// 					{
// 						Uart4_Send(sendbuff, u32RxLen);//�ӻ�����յ����ݣ����Է���һ����־�����յ�
// 						LED0_PWM_VAL1=V2f;
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=V2f;
// 						LED0_PWM_VAL4=VS;
// 					}//ֱ���ٶ�2
					
	if(strstr(sUart4_entity.u8RX_Buffer,order3)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=V3f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V3f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ֱ���ٶ�3
					
	if(strstr(sUart4_entity.u8RX_Buffer,order4)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=V4f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V4f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ֱ���ٶ�4
// 					
	if(strstr(sUart4_entity.u8RX_Buffer,order5)!=NULL)
	{
		package[60]='Y';//���������ź�
						//һ���յ��Ϳ�ʼִ��
		LED0_PWM_VAL1=V5f;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=V5f;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ֱ���ٶ�5
					
	if(strstr(sUart4_entity.u8RX_Buffer,stop)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ֹͣ����
					
	if(strstr(sUart4_entity.u8RX_Buffer,emergency)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VS;
						
		pathok=0;//�����ٽ���·��������

// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ǿ��ֹͣ����
					
	if(strstr(sUart4_entity.u8RX_Buffer,right)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VS;//��ת���
		LED0_PWM_VAL2=VT1;
		LED0_PWM_VAL3=VT2;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
// 						LED0_PWM_VAL1=VT1;//΢����ת
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=VT2;
// 						LED0_PWM_VAL4=VS;
	}//��ת 

	if(strstr(sUart4_entity.u8RX_Buffer,left)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VT2;//��ת���
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VT1;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
// 						LED0_PWM_VAL1=VT2;//΢����ת
// 						LED0_PWM_VAL2=VS;
// 						LED0_PWM_VAL3=VT1;
// 						LED0_PWM_VAL4=VS;
	}//��ת		

	if(strstr(sUart4_entity.u8RX_Buffer,orgright)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VT1;
		LED0_PWM_VAL2=VS;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=VT1;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ԭ����ת 

	if(strstr(sUart4_entity.u8RX_Buffer,orgleft)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=VT1;
		LED0_PWM_VAL3=VT1;
		LED0_PWM_VAL4=VS;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//ԭ����ת				
	if(strstr(sUart4_entity.u8RX_Buffer,back)!=NULL)
	{
		package[60]='Y';//���������ź�
		LED0_PWM_VAL1=VS;
		LED0_PWM_VAL2=V4f;
		LED0_PWM_VAL3=VS;
		LED0_PWM_VAL4=V4f;
// 		memset(sUart4_entity.u8RX_Buffer,0,10);//��մ���4���ջ�����
	}//����	
	if(strstr(sUart4_entity.u8RX_Buffer,remote)!=NULL)
	{
		beat++;
		heartok=1;//����ͨ�Żָ�����
		//����յ���ȡ·����Ϣ������
		if((strchr(sUart4_entity.u8RX_Buffer,'B')!=NULL)&&(strchr(sUart4_entity.u8RX_Buffer,'P')!=NULL))
		{
			memcpy(pathrecord,sUart4_entity.u8RX_Buffer,strlen(sUart4_entity.u8RX_Buffer));
			package[59]='M';//���������ź�
			pathen++;
			if(pathen==1)
				pathresolve(pathrecord);
			else
				pathen=2;
// 			memset(sUart4_entity.u8RX_Buffer,0,100);//��մ���4���ջ�����
		}	
	}//��������		
}


void hearttest(void)//��������Ƿ���������
{
// 	{//��λ��ÿ��1.5�뷢��ARQ��������ź�
		if(beat==0)
		{//���û�����������ƶ���������־λ����
			heartok=0;
			LED0_PWM_VAL1=VS;
			LED0_PWM_VAL2=VS;
			LED0_PWM_VAL3=VS;
			LED0_PWM_VAL4=VS;
		}
		else if(beat!=0)
		{//�������������ô�ֿ��Լ����ղŵ�·������ȥ
			heartok=1;
			beat=0;
		}
}

#pragma pop	





/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
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
	
	u8 LAT1,LNG1;//��������ָ��ָ���ž�γ�ȵ��ڴ��ַ

	u8 processok=0;//��������ÿ20ms����һ��
	double lat,lng;
	double speed2;
// 	double seitatest=0;
	static u8 heartbeat=0;
	
	const u8 at[] = {"receiveok"};
	u8 reply[6]={0x01,0x04,0x01};
	u8 gpsdata[100]={0};//��Ŵ������GPS����
	u8 reply1[3];//׼����Ż�Ӧ������	
	u8 reply2[3];//���������ǣ���ת��
	u8 reply3[3];//���ǰ����ǣ�������
	u8 package1[10];//���γ��
	u8 package2[10];//��ž���
	u8 package3[10];//��ŷ�λ��
	u8 package4[10];//��Ź�ת��
	u8 package5[10];//���ǰ�����
	u8 package6[4];//����ٶ�
	u8 package7[4];//���ʣ�����
	
	uint8_t source=0x01;//Դ��ַ
	uint8_t destination=0x02;//Ŀ�ĵ�ַ
	tsPacketOfAppInfo truesendout;//��������Ͷ���һ������
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
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//����systick��ʱ����AHB����Ƶ��
	SysTick_Config(7200000);//���������жϵ�ʱ����Ϊ100ms

/* USART1,2,3 ,UART4 config 115200 8-N-1 */
	USART1_Config();
	USART2_Config();
	USART3_Config();
	UART4_Config();
	
	Usart_DMA_Config();
	LED_GPIO_Config();
	
	delay_ms(1000);
	
	PWM_Initch1(60000,0);	 //����Ƶ��PWMƵ��=72000000/60000=1.2Khz
	PWM_Initch2(60000,0);
	PWM_Initch3(60000,0);
	PWM_Initch4(60000,0);

	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 

	LED0_PWM_VAL1=led0pwmval1;
	LED0_PWM_VAL2=led0pwmval2;
	LED0_PWM_VAL3=led0pwmval3;
	LED0_PWM_VAL4=led0pwmval4;

//����ǲ����õ�����	
  /*��佫Ҫ���͵�����*/	
// 	for (i = 0; i < sizeof(at); i++)
//   {
// 			SendBuff[i]	 = at[i];
//   }

// 	USART_SEND(SendBuff, sizeof(at)-1);

// 	delay_ms(1000);
	
	
  /*��佫Ҫ���͵�����*/
// 	for (i = 0; i < SENDBUFF_SIZE; i++)
//   {
// 			SendBuff[i]	 = 0x31;
//   }

// 	USART_SEND(SendBuff, 30);
// //�������ݽ���	
//  /*������ DMA�������� */
//  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	

  /*��DMA��δ�������ʱ��cpu����ִ��main�����еĴ���*/
  /*������LED��*/
/*��ͬʱDMA���򴮿��������ݣ���DMA�������ʱ�����жϺ����ر�LED�� */

	Adc_Init();//ADCת���Ƿ�ƵΪ12MHz

	
	//order_sendinit();
	while(1)
	{
// 	  gpggaresolve(gpgga);
		//Usart1_Send(command1, sizeof(comd1));
		//delay_ms(500);
// 		static u8 pathen=0;
		
				if (sUsart2_entity.u8RxFlag == 1)
				{//����յ����̷��ص�����
					sUsart2_entity.u8RxFlag = 0;
					u32RxLen = sUsart2_entity.u16RxTotalNum;
					sUsart2_entity.u16RxTotalNum = 0;	
					processok=1;//50ms�������Կ�ʼ��������
					if(sUsart2_entity.u8RX_Buffer[1]==0x0d)//������ص������ǽǶ�
					{
						for(i=0;i<3;i++)
						{
							reply1[i]=sUsart2_entity.u8RX_Buffer[10+i];//ȡ�������
							reply2[i]=sUsart2_entity.u8RX_Buffer[4+i];//ȡ��������ǣ���ת��
							reply3[i]=sUsart2_entity.u8RX_Buffer[7+i];//ȡ��ǰ����ǣ�������
						}
					}
					memset(sUsart2_entity.u8RX_Buffer,0,15);
				}
	
				if(sUsart3_entity.u8RxFlag==1)
				{//����յ�GPS���ص�����
					sUsart3_entity.u8RxFlag = 0;
					u32RxLen = sUsart3_entity.u16RxTotalNum;
					sUsart3_entity.u16RxTotalNum = 0;	
					
// 					processok=1;//20ms�������Կ�ʼ��������
					
					for(i=0;i<sizeof(sUsart3_entity.u8RX_Buffer);i++)
					{
						sUsart3_entity.u8RX_Buffer[i]=gpsdata[i];
					}
					memset(sUsart3_entity.u8RX_Buffer,0,150);
// 					gpggaresolve(sUsart3_entity.u8RX_Buffer);		
				}
				
				if (sUart4_entity.u8RxFlag == 1)
				{//����յ�ָ��
					sUart4_entity.u8RxFlag = 0;
					u32RxLen = sUart4_entity.u16RxTotalNum;
					sUart4_entity.u16RxTotalNum = 0;			
				}
				
				if(speeden==1)//���2�뵽�˵Ļ�������һ�Σ����ʣ�����һ��
				{
					speeden=0;
					heartbeat++;
					memset(package6,0,4);//�ٶȺ͵���������������ٸ��µ�ֵ
					memset(package7,0,4);
					speed2=getspeed((*(gaosi->gaosix1)),(*(gaosi->gaosiy1)));//1�����һ��
// 					speed2=10.6;
// 					seita=getheading(0.5,-1,1,-2);//��ⷽλ�Ǻ����Ƿ�����
// 					gettoorbit(200,330);//�����������
// 					changedirections(1,4,0.5,-1,1,-2);//���΢���Ƿ�����
					if(heartbeat==7)//ÿ��14s���һ�������Ƿ�����
					{
						heartbeat=0;
						hearttest();//��������Ƿ���������
					}
// 					(*(gaosi->gaosix1))+=0.05;
// 					(*(gaosi->gaosiy1))+=0.05;//�����ٶ�
// 					if((*(gaosi->gaosix1))>=5)
// 						*(gaosi->gaosix1)=0;
// 					if((*(gaosi->gaosiy1))>=5)
// 						*(gaosi->gaosiy1)=0;
// 					GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);
// 					speed2=getspeed((*(gaosi->gaosix1)),(*(gaosi->gaosiy1)));//1�����һ��
					
					sprintf(package6,"%4.1f",speed2);
				
					for(i=50;i<=53;i++)
					{
						package[i]=package6[i-50];//�ٶ����鸳ֵ��׼�����
					}
					temp=powadc();//1��ת����ѹһ��
					
					sprintf(package7,"%4.1lf",temp);
					for (i=54;i<=57;i++)
					{
						package[i]=package7[i-54];//����ѹֵ��ֵ������ĺ���
					}
				}
		
				if(processok==1)//���50ms���˵Ļ�����ô�������ݽ��д���
				{
					memset(package1,0,10);//������γ�ȣ���λ�ǣ�ǰ����ǣ����ҹ�ת����������
					memset(package2,0,10);
					memset(package3,0,10);
					memset(package4,0,10);
					memset(package5,0,10);
// 					memset(package6,0,4);//�ٶȺ͵���������������ٸ��µ�ֵ
// 					memset(package7,0,4);
					processok=0;//����50ms���

					
					head2=hextodex(reply1);//���Ƕ�ת��Ϊʮ����
					roll2=rolltodec(reply2);
					pitch2=pitchtodec(reply3);
	
					
					gpggaresolve(sUsart3_entity.u8RX_Buffer,&LAT1,&LNG1);//����GPS������
					
					lat=longtodouble(ptuoqiu->LAT);
					lng=longtodouble(ptuoqiu->LNG);
					
					changeformat(lng,lat,ptuoqiu->latitude,ptuoqiu->longitude);//��GPS���ݽ����ɾ�γ��
					
					order();//�жϴ���4�Ƿ���յ�ʲôָ����
					
					if((pathok==1)&&(heartok==1))//�������·��ת���Ļ�
					{
						move();//·��ת��,��Լ��ʱ4ms����
					}
					
					sprintf(package1,"%10.6lf",*(ptuoqiu->latitude));
					sprintf(package2,"%10.6lf",*(ptuoqiu->longitude));
					sprintf(package3,"%10.6lf",head2);
					sprintf(package4,"%10.6lf",roll2);
					sprintf(package5,"%10.6lf",pitch2);
					
// 					GaussProjCal(*(ptuoqiu->longitude),*(ptuoqiu->latitude),gaosi->gaosix,gaosi->gaosiy);//��С����ǰ������ת��Ϊƽ������
	
					for(i=0;i<=9;i++)//γ�ȸ�ֵ��������
					{
						package[i]=package1[i];
					}
					for(i=10;i<=19;i++)//���ȸ�ֵ��������
					{
						package[i]=package2[i-10];
					}
					
					for(i=20;i<=29;i++)//����λ�Ǹ�ֵ����������
					{
						package[i]=package3[i-20];
					}
					
					for(i=30;i<=39;i++)//��������Ǹ�ֵ����������
					{
						package[i]=package4[i-30];
					}

					for(i=40;i<=49;i++)//��ǰ����Ǹ�ֵ����������
					{
						package[i]=package5[i-40];
					}
						
					
					
					memset(sUart4_entity.u8RX_Buffer,0,150);
		
					count=SendData_thisprotocol(truesendout,source,destination,len);//����Ҫ���������׼����һ��������	
	//���ش��������ݸ���,�����ܺã���������VB�ǳ��鷳��̫�鷳�˼�ֱ�����Բ�����,������ʱ��ʵ���Ǳ�����
					head2=0;
					roll2=0;
					pitch2=0;
					memset(reply1,0,10);//�����Ƕ����鶼����
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