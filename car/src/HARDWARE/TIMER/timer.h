#ifndef __TIMER_H
#define __TIMER_H
//#include "sys.h"
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
#include "stm32f10x.h"

//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL1 TIM3->CCR1 
#define LED0_PWM_VAL2 TIM3->CCR2
#define LED0_PWM_VAL3 TIM3->CCR3 
#define LED0_PWM_VAL4 TIM3->CCR4 


void Timerx_Init(uint16_t arr,uint16_t psc);
void PWM_Initch1(u16 arr,u16 psc);
void PWM_Initch2(u16 arr,u16 psc);
void PWM_Initch3(u16 arr,u16 psc);
void PWM_Initch4(u16 arr,u16 psc);
#endif























