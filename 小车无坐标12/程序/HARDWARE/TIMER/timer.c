#include "timer.h"
#include "led.h"
#include "variables.h"
#include "stm32f10x.h"
#include "stdint.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
// 		LED1=!LED1;			    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void Timerx_Init(uint16_t arr,uint16_t psc)
{
// 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�
		  							    
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3		


}

//TIM3 PWM����
//����ԭ��@ALIENTEK
//2010/6/2	 

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��


void PWM_Initch1(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    
	  	
	GPIOA->CRL&=0XF0FFFFFF;//PA6���
	GPIOA->CRL|=0X0B000000;//���ù������ 	  
	GPIOA->ODR|=1<<6;//PA6����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=7<<4;  //CH1 PWM2ģʽ		 
	TIM3->CCMR1|=1<<3; //CH1Ԥװ��ʹ��	   

	TIM3->CCER|=1<<0;   //OC1 ���ʹ��	   

	TIM3->CR1=0x8000;   //ARPEʹ�� 
// 	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
	
} 


void PWM_Initch2(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	//RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    

	GPIOA->CRL&=0X0FFFFFFF;//PA7���
	GPIOA->CRL|=0XB0000000;//���ù������ 	  
	GPIOA->ODR|=1<<7;//PA7����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=7<<12;  //CH2 PWM2ģʽ		 
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   

	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	   

	//TIM3->CR1=0x8000;   //ARPEʹ�� 
// 	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
}  	 



void PWM_Initch3(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	//RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    
	  	
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	
	
	GPIOB->CRL&=0xfffffff0;
	GPIOB->CRL|=0x0000000a;
	
	GPIOB->ODR&=~1<<0;//����TIM3��PB0Ϊ�Ƚ����		

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR2|=7<<4;  //CH3 PWM2ģʽ		 
	TIM3->CCMR2|=1<<3; //CH3Ԥװ��ʹ��	   

	TIM3->CCER|=1<<8;   //OC3 ���ʹ��	   

	//TIM3->CR1=0x8000;   //ARPEʹ�� 
// 	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
} 

void PWM_Initch4(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	//RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    

	GPIOB->CRL&=0xffffff0f;
	GPIOB->CRL|=0x000000b0;
	
	GPIOB->ODR&=~1<<1;//����TIM3��PB1Ϊ�Ƚ����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	                                                                                                             
	TIM3->CCMR2|=7<<12;  //CH4 PWM2ģʽ		 
	TIM3->CCMR2|=1<<11; //CH4Ԥװ��ʹ��	   

	TIM3->CCER|=1<<12;   //OC4 ���ʹ��	   

	//TIM3->CR1=0x8000;   //ARPEʹ�� 
// 	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
}





