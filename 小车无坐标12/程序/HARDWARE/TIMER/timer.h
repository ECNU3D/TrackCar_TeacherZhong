#ifndef __TIMER_H
#define __TIMER_H
//#include "sys.h"
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
#include "stm32f10x.h"

//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
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























