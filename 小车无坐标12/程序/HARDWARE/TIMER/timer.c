#include "timer.h"
#include "led.h"
#include "variables.h"
#include "stm32f10x.h"
#include "stdint.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
// 		LED1=!LED1;			    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void Timerx_Init(uint16_t arr,uint16_t psc)
{
// 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC->APB1ENR|=1<<1;//TIM3时钟使能    
 	TIM3->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东东要同时设置才可以使用中断
	TIM3->DIER|=1<<0;   //允许更新中断				
	TIM3->DIER|=1<<6;   //允许触发中断
		  							    
	TIM3->CR1|=0x01;    //使能定时器3		


}

//TIM3 PWM部分
//正点原子@ALIENTEK
//2010/6/2	 

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数


void PWM_Initch1(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能    
	  	
	GPIOA->CRL&=0XF0FFFFFF;//PA6输出
	GPIOA->CRL|=0X0B000000;//复用功能输出 	  
	GPIOA->ODR|=1<<6;//PA6上拉	

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR1|=7<<4;  //CH1 PWM2模式		 
	TIM3->CCMR1|=1<<3; //CH1预装载使能	   

	TIM3->CCER|=1<<0;   //OC1 输出使能	   

	TIM3->CR1=0x8000;   //ARPE使能 
// 	TIM3->CR1|=0x01;    //使能定时器3 
	
} 


void PWM_Initch2(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	//RCC->APB1ENR|=1<<1;       //TIM3时钟使能    

	GPIOA->CRL&=0X0FFFFFFF;//PA7输出
	GPIOA->CRL|=0XB0000000;//复用功能输出 	  
	GPIOA->ODR|=1<<7;//PA7上拉	

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR1|=7<<12;  //CH2 PWM2模式		 
	TIM3->CCMR1|=1<<11; //CH2预装载使能	   

	TIM3->CCER|=1<<4;   //OC2 输出使能	   

	//TIM3->CR1=0x8000;   //ARPE使能 
// 	TIM3->CR1|=0x01;    //使能定时器3 
}  	 



void PWM_Initch3(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	//RCC->APB1ENR|=1<<1;       //TIM3时钟使能    
	  	
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	
	
	GPIOB->CRL&=0xfffffff0;
	GPIOB->CRL|=0x0000000a;
	
	GPIOB->ODR&=~1<<0;//配置TIM3的PB0为比较输出		

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR2|=7<<4;  //CH3 PWM2模式		 
	TIM3->CCMR2|=1<<3; //CH3预装载使能	   

	TIM3->CCER|=1<<8;   //OC3 输出使能	   

	//TIM3->CR1=0x8000;   //ARPE使能 
// 	TIM3->CR1|=0x01;    //使能定时器3 
} 

void PWM_Initch4(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	//RCC->APB1ENR|=1<<1;       //TIM3时钟使能    

	GPIOB->CRL&=0xffffff0f;
	GPIOB->CRL|=0x000000b0;
	
	GPIOB->ODR&=~1<<1;//配置TIM3的PB1为比较输出	

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	                                                                                                             
	TIM3->CCMR2|=7<<12;  //CH4 PWM2模式		 
	TIM3->CCMR2|=1<<11; //CH4预装载使能	   

	TIM3->CCER|=1<<12;   //OC4 输出使能	   

	//TIM3->CR1=0x8000;   //ARPE使能 
// 	TIM3->CR1|=0x01;    //使能定时器3 
}





