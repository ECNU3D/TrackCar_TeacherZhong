/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��eceg_usart.c
 * ����    ��
 *           
 * Ӳ��ƽ̨��
 * Ӳ�����ӣ�
 *         
 *           
 * ��汾  ��ST3.5.0
 * ����    ��
**********************************************************************************/
#include "eceg_usart.h"
#include <stdarg.h>

#include "stm32f10x_dma.h"
#include "stm32f10x.h"

#include "usart1.h"
#include "usart3.h"
#include "usart2.h"
#include "uart4.h"

#include "ringbuf.h"
#include "stdint.h"


/*
 * ��������DMA_Config
 * ����  ��DMA ���ڵĳ�ʼ������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void Usart_DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMA1ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);	//����DMA2ʱ��
	Usart_NVIC_Config();	   														//����DMA�ж�


 	// ����USART1 ����DMA
	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	   

	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart1_RingBuf.pucBuf;
	
	/*���򣺴��ڴ浽����*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART1_DMA_TX_RINGBUF_SIZE;
	
	/*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*���ȼ�����*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	
	
	
	/*����DMA1��4ͨ��*/		   
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel4,ENABLE);								 //ʹ��DMA
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
	

	// ����USART1 ����DMA
	// DMA1ͨ��5����   
	DMA_DeInit(DMA1_Channel5);  

	// �����ַ   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
	
	//�ڴ��ַ   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart1_entity.u8RX_Buffer;

	// dma���䷽����   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// ����DMA�ڴ���ʱ�������ĳ���   
	DMA_InitStructure.DMA_BufferSize = USART1_DMA_RX_BUFF_SIZE;  
	
	// ����DMA���������ģʽ��һ������   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// ����DMA���ڴ����ģʽ   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// ���������ֳ�   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// �ڴ������ֳ�   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// ����DMA�Ĵ���ģʽ������ѭ��ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// ����DMA�����ȼ���   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel5,ENABLE);
	
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC | DMA_IT_HT,ENABLE);  //����DMA������ɺͰ���������ж�




 	// ����USART3 ����DMA
	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	   

	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart3_RingBuf.pucBuf;
	
	/*���򣺴��ڴ浽����*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART3_DMA_TX_RINGBUF_SIZE;
	
	/*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*���ȼ�����*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*����DMA1��2ͨ��*/		   
    DMA_Init(DMA1_Channel2, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel2,ENABLE);								 //ʹ��DMA
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�


	// ����USART3 ����DMA
	// DMA1ͨ��3����   
	DMA_DeInit(DMA1_Channel3);  

	// �����ַ   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
	
	//�ڴ��ַ   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart3_entity.u8RX_Buffer;

	// dma���䷽����   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// ����DMA�ڴ���ʱ�������ĳ���   
	DMA_InitStructure.DMA_BufferSize = USART3_DMA_RX_BUFF_SIZE;  
	
	// ����DMA���������ģʽ��һ������   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// ����DMA���ڴ����ģʽ   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// ���������ֳ�   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// �ڴ������ֳ�   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// ����DMA�Ĵ���ģʽ������ѭ��ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// ����DMA�����ȼ���   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel3,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	DMA_ITConfig(DMA1_Channel3,DMA_IT_TC | DMA_IT_HT,ENABLE);  //����DMA������ɺͰ���������ж�




 	// ����USART2 ����DMA
	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);	   

	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart2_RingBuf.pucBuf;
	
	/*���򣺴��ڴ浽����*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART2_DMA_TX_RINGBUF_SIZE;
	
	/*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*���ȼ�����*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*����DMA1��7ͨ��*/		   
    DMA_Init(DMA1_Channel7, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel7,ENABLE);								 //ʹ��DMA
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�


	// ����USART2 ����DMA
	// DMA1ͨ��6����   
	DMA_DeInit(DMA1_Channel6);  

	// �����ַ   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
	
	//�ڴ��ַ   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart2_entity.u8RX_Buffer;

	// dma���䷽����   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// ����DMA�ڴ���ʱ�������ĳ���   
	DMA_InitStructure.DMA_BufferSize = USART2_DMA_RX_BUFF_SIZE;  
	
	// ����DMA���������ģʽ��һ������   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// ����DMA���ڴ����ģʽ   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// ���������ֳ�   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// �ڴ������ֳ�   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// ����DMA�Ĵ���ģʽ������ѭ��ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// ����DMA�����ȼ���   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel6,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel6,ENABLE);
	
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC | DMA_IT_HT,ENABLE);  //����DMA������ɺͰ���������ж�





 // ����UART4 ����DMA
	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);	   

	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUart4_RingBuf.pucBuf;
	
	/*���򣺴��ڴ浽����*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = UART4_DMA_TX_RINGBUF_SIZE;
	
	/*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*���ȼ�����*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*����DMA2��5ͨ��*/		   
    DMA_Init(DMA2_Channel5, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA2_Channel5,ENABLE);								 //ʹ��DMA
	DMA_ITConfig(DMA2_Channel5,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�


	// ����UART4 ����DMA
	// DMA2ͨ��3����   
	DMA_DeInit(DMA2_Channel3);  

	// �����ַ   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);  
	
	//�ڴ��ַ   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUart4_entity.u8RX_Buffer;

	// dma���䷽����   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// ����DMA�ڴ���ʱ�������ĳ���   
	DMA_InitStructure.DMA_BufferSize = UART4_DMA_RX_BUFF_SIZE;  
	
	// ����DMA���������ģʽ��һ������   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// ����DMA���ڴ����ģʽ   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// ���������ֳ�   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// �ڴ������ֳ�   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// ����DMA�Ĵ���ģʽ������ѭ��ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// ����DMA�����ȼ���   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA2_Channel3,&DMA_InitStructure);  
	
	DMA_Cmd(DMA2_Channel3,ENABLE);
	
	DMA_ITConfig(DMA2_Channel3,DMA_IT_TC | DMA_IT_HT,ENABLE);  //����DMA������ɺͰ���������ж�




}


/*
 * ��������NVIC_Config
 * ����  ��DMA �ж�����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void Usart_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
	// ����DMA�ж����ȼ���Է���DMA��IDLE�ж�Ҫ��
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	����UART1�ж�     
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //ͨ������Ϊ����1�ж�  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	// ����DMA�ж����ȼ���Է���DMA��IDLE�ж�Ҫ�� 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	����UART3�ж�     
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //ͨ������Ϊ����3�ж�  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	

		// ����DMA�ж����ȼ���Է���DMA��IDLE�ж�Ҫ��
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	����UART2�ж�     
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //ͨ������Ϊ����2�ж�  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
			// ����DMA�ж����ȼ���Է���DMA��IDLE�ж�Ҫ��
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel3_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

//   /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel4_5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	����UART4�ж�     
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;               //ͨ������Ϊ����4�ж�  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 12;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}





/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
	/* ��Printf���ݷ������� */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	
	    /* Make the value positive. */
	    value *= -1;
	}
	
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;
	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;

} /* NCL_Itoa */

/*
 * ��������USART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���1����USART1
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
	{									  
	switch ( *++Data )
	{
		case 'r':							          //�س���
			USART_SendData(USARTx, 0x0d);
			Data ++;
		break;
		
		case 'n':							          //���з�
			USART_SendData(USARTx, 0x0a);	
			Data ++;
		break;
		
		default:
			Data ++;
		break;
	}			 
	}
	else if ( *Data == '%')
	{									  //
	switch ( *++Data )
	{				
		case 's':										  //�ַ���
			s = va_arg(ap, const char *);
	for ( ; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;
	
	case 'd':										//ʮ����
	d = va_arg(ap, int);
	itoa(d, buf, 10);
	for (s = buf; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
	Data++;
	break;
		 default:
				Data++;
		    break;
	}		 
	} /* end of else if */
	else USART_SendData(USARTx, *Data++);
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/******************* (C) COPYRIGHT *****END OF FILE************/

