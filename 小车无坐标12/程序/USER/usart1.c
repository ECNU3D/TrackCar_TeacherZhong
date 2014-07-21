/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��usart1.c
 * ����    ��
 *           
 * Ӳ��ƽ̨��
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ��
**********************************************************************************/
#include "usart1.h"
#include <stdarg.h>

#include "stm32f10x_dma.h"
#include "stdint.h"





uint8_t u8Usart1_SendBuff[USART1_SENDBUFF_SIZE];
uint8_t	u8Usart1_User_RX_Buffer[USART1_DMA_RX_BUFF_SIZE*2];

uint8_t	u8Usart1_TX_Buffer[USART1_DMA_TX_RINGBUF_SIZE];
uint8_t	u8Usart1_RX_Buffer[USART1_DMA_RX_BUFF_SIZE];




tsUSART_entity sUsart1_entity = {	0,
																	0,
																  0,
																	0,
																	
																	0,
																	0,
	
																	0,
																	0,
																	
																	u8Usart1_RX_Buffer,
																	u8Usart1_TX_Buffer
															 };


static uint8_t u8Usart1_Halffull = 1;					// 0������ǰ������������ˣ�1�����Ǻ�������������




void DMA1_Channel5_IRQ(void)
{
		uint32_t i;
	
 		if (DMA1->ISR & DMA1_IT_HT5)										// ͨ��5�봫���¼����
 		{ 

			 DMA1->IFCR |= DMA1_FLAG_HT5;									// ���ͨ��5�봫����ɱ�־
			 u8Usart1_Halffull = 0;												// ǰ�����������
			 
			 for (i = 0; i < (USART1_DMA_RX_BUFF_SIZE_HALF); i++)
			 {
					 // һ�������жϲ�������ѳ���������һ�����������������
					 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[i];		
				 
					 sUsart1_entity.u16RxCounter++;						//����ָ��ָ����һ����Ԫ

			 }
			 // ���ǰ��������������ܸ�����(USART_DMA_RX_BUFF_SIZE_HALF)
			 sUsart1_entity.u16RxTotalNum += (USART1_DMA_RX_BUFF_SIZE_HALF);			

		}// End if (DMA1->ISR & DMA1_IT_HT5)
		else if (DMA1->ISR & DMA1_IT_TC5)								// ͨ��5�����¼����
 		{ 
						u8Usart1_Halffull = 1;									// ������������
 						DMA1->IFCR |= DMA1_FLAG_TC5;						// ���ͨ��5������ɱ�־
							
						for (i = 0; i < (USART1_DMA_RX_BUFF_SIZE_HALF); i++)
						{
								u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[USART1_DMA_RX_BUFF_SIZE_HALF + i];
								
								sUsart1_entity.u16RxCounter++;				//����ָ��ָ����һ����Ԫ

						}
						
						// ���ǰ��������������ܸ�����(USART_DMA_RX_BUFF_SIZE_HALF)
						sUsart1_entity.u16RxTotalNum += (USART1_DMA_RX_BUFF_SIZE_HALF);			
		}// End else if (DMA1->ISR & DMA1_IT_TC5)	
	
}

void DMA1_Channel5_IRQHandler(void)
{
		DMA1_Channel5_IRQ();
}


// #define		TX_RINGBUF_SIZE		128
tRingBufObject sUsart1_RingBuf = {
																	USART1_DMA_TX_RINGBUF_SIZE,
																	0,
																	0,
																	u8Usart1_TX_Buffer
																 };

void DMA1_Channel4_IRQ(void)
{
		 uint32_t u32Tail;
		 uint32_t u32Head;
	
		 //�ж��Ƿ�ΪDMA��������ж�
		 if (DMA1->ISR & DMA1_FLAG_TC4) 
		 {  
				DMA1->IFCR = DMA1_FLAG_TC4;					// ���־

			  // �ж϶����Ƿ�ǿգ�
			  // ������зǿգ���ζ�Ž�������DMA�������񡣶��ڻ��ζ��зǿգ������������
			  // һ����βָ��tail>��ָ��head�������ζ���δ�����ؾ���ʱ����ֱ������DMA���͡�
			  // ��һ��βָ��tail<��ָ��head�������ζ��з����˻ؾ���ʱDMA���ͽ��ֳ�������
			  // ��һ������ָ��head�������ڴ��ַβ������һ��DMA�������С�
			  // ���úø�DMA�������к������ָ��head��������Ȼ���뵽�ڶ�����
			  // �ڶ��������������ַ��ַ��βָ��tail������һDMA�������С�
			  // ��������գ���ʲô����Ҳ���ɡ�
			 
				// �����Ƿ�ǿգ�			 
			  //
				// Copy the Read/Write indices for calculation.
				//
				u32Tail = sUsart1_RingBuf.ulWriteIndex;
				u32Head = sUsart1_RingBuf.ulReadIndex;
			  
			  if (u32Tail != u32Head)
				{
					 // ���зǿ�
					 if (u32Tail > u32Head)
					 {
							// ringbufδ�ؾ�
						  
						  // ��ֹDMA1_Channel4
							DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
						  // ���÷���DMA��memory��base��ַ
						  DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];
						 
						  // ���÷���DMA�ĳ���
							DMA1_Channel4->CNDTR = u32Tail - u32Head;
						 
							// ����ʹ��DMA1_Channel4
							DMA1_Channel4->CCR |= DMA_CCR1_EN;

							// ����ringbuf��ָ��(�ٽ����)
							sUsart1_RingBuf.ulReadIndex = sUsart1_RingBuf.ulWriteIndex;					 
						 						 
					 }
					 else
					 {
							// ringbuf�ؾ�

							// ��ֹDMA1_Channel4
							DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
						  // ���÷���DMA��memory��base��ַ
						  DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];
						 
						  // ���÷���DMA�ĳ���
							DMA1_Channel4->CNDTR = sUsart1_RingBuf.ulSize - u32Head;
						 
							// ����ʹ��DMA1_Channel4
							DMA1_Channel4->CCR |= DMA_CCR1_EN;			
						 
						  // ����ringbuf��ָ��(�ٽ����)
							sUsart1_RingBuf.ulReadIndex = 0;
						 
					 }
					 
				}
				else
				{
					 // ���п�
				}
			 
		 }		
		 
}


void DMA1_Channel4_IRQHandler(void)
{	
		 DMA1_Channel4_IRQ();
}



void USART1_IRQ(void)
{
	uint32_t res, u32Temp, dmabuflen;
	//static u16 j=0;	 
	uint32_t i;

					
	if (USART1->SR & USART_FLAG_IDLE)									//�����⵽����λ
	{
			u32Temp = USART1->SR;  
      u32Temp = USART1->DR; 												//��USART_IT_IDLE��־   

			if (u8Usart1_Halffull == 0)										//���ǰ�����������
			{
				 dmabuflen = (USART1_DMA_RX_BUFF_SIZE_HALF) - DMA1_Channel5->CNDTR;			//ȡ������һ�������˶��ٸ�����
			}
			else if (u8Usart1_Halffull == 1)							//������������
			{
				 dmabuflen = USART1_DMA_RX_BUFF_SIZE - DMA1_Channel5->CNDTR;
			}

					
			for	(i = 0; i < dmabuflen; i++)
			{
					if (u8Usart1_Halffull == 0)								//ǰ�����������
					{
						 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[USART1_DMA_RX_BUFF_SIZE_HALF + i];
						
						 sUsart1_entity.u16RxCounter++;					//����ָ��ָ����һ����Ԫ
					}
					else if (u8Usart1_Halffull == 1)					//���������������
					{
							 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[i];
						
							 sUsart1_entity.u16RxCounter++;				//����ָ��ָ����һ����Ԫ

					}

			}// End for
			
			sUsart1_entity.u16RxTotalNum += dmabuflen;			//������У����϶�������ݸ���
			
			// һ�����������ݱ��������
			sUsart1_entity.u8RxFlag = 1;
			
			// ��ֹDMA1_Channel5
			DMA1_Channel5->CCR &= (uint16_t)(~DMA_CCR1_EN);
			
			// ��������DMA1_Channel5��ָ��
			DMA1_Channel5->CNDTR = USART1_DMA_RX_BUFF_SIZE;
			
			// ����ʹ��DMA1_Channel5
			DMA1_Channel5->CCR |= DMA_CCR1_EN;
					
			// ���ڽ��ռ�����0
			sUsart1_entity.u16RxCounter = 0;
			
			// �ָ�u8Usart1_HalffullΪ��ʼֵ
			u8Usart1_Halffull = 1;

  }// End if (USART1->SR & USART_FLAG_IDLE)	

}

void USART1_IRQHandler(void)
{

		 USART1_IRQ();
}



void Usart1_Send(uint8_t *u8Buf, uint32_t u32Len)
{
	int32_t i;
	int32_t result;
	uint32_t u32Tail, u32Head;
	
	if (u32Len == 0)
	{
			return;
	}
		
	//
	// Copy the Read/Write indices for calculation.
	//
	u32Tail = sUsart1_RingBuf.ulWriteIndex;
	u32Head = sUsart1_RingBuf.ulReadIndex;
	
	// �����Ƿ�ǿգ�
	if (u32Tail == u32Head)
	{
			// ���п�
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUsart1_RingBuf, u8Buf[i]);					// ����Ҫ����Ҫ�����������뻷�ζ���
				
					// ��������Ӧ��ʩ��
					
			}// End for
				
			// DMA����
			// ��ֹDMA1_Channel4
			DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
			// ���÷���DMA��memory��base��ַ
			DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];

			// �ն�ringbufһ���ֽڣ���Ϊ����һ���ֽڣ�
			result = RingBufReadOne(&sUsart1_RingBuf);
			
			// ���÷���DMA�ĳ���
			DMA1_Channel4->CNDTR = 1;
						 
			// ����ʹ��DMA1_Channel4
			DMA1_Channel4->CCR |= DMA_CCR1_EN;

			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	
			
	}
	else
	{
			// ���зǿ�
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUsart1_RingBuf, u8Buf[i]);					// ����Ҫ����Ҫ�����������뻷�ζ���
				
					// ��������Ӧ��ʩ��
					
			}// End for
			
	}
	
		
}


/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	
	
	// ����DMA��ʽ����   
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  

	// �ж�����   
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);   

	// ��������
	USART_Cmd(USART1, ENABLE); 

}







// /*
//  * ��������DMA_Config
//  * ����  ��DMA ���ڵĳ�ʼ������
//  * ����  ����
//  * ���  : ��
//  * ����  ���ⲿ����
//  */
// void DMA_Config(void)
// {
//   DMA_InitTypeDef DMA_InitStructure;

// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��
// 	NVIC_Config();	   																	//����DMA�ж�

//  	// ����USART1 ����DMA
// 	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
//     DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	   

// 	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
//     DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tRingBuf.pucBuf;
// 	
// 	/*���򣺴��ڴ浽����*/		
//     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
// 	
// 	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
//     DMA_InitStructure.DMA_BufferSize = USART1_SENDBUFF_SIZE;
// 	
// 	/*�����ַ����*/	    
//     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
// 	
// 	/*�ڴ��ַ����*/
//     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
// 	
// 	/*�������ݵ�λ*/	
//     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
// 	
// 	/*�ڴ����ݵ�λ 8bit*/
//     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
// 	
// 	/*DMAģʽ��һ�δ��䣬ѭ��*/
//     DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
// 	
// 	/*���ȼ�����*/	
//     DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
// 	
// 	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
//     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
// 	
// 	/*����DMA1��4ͨ��*/		   
//     DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
// 	
// 	DMA_Cmd (DMA1_Channel4,ENABLE);					//ʹ��DMA
// 	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
// 	

// 	// ����USART1 ����DMA
// 	// DMA1ͨ��5����   
// 	DMA_DeInit(DMA1_Channel5);  

// 	// �����ַ   
// 	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
// 	
// 	//�ڴ��ַ   
//   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUSART_entity.u8RX_Buffer;

// 	// dma���䷽����   
// 	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

// 	// ����DMA�ڴ���ʱ�������ĳ���   
// 	DMA_InitStructure.DMA_BufferSize = USART1_DMA_RX_BUFF_SIZE;  
// 	
// 	// ����DMA���������ģʽ��һ������   
// 	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
// 	
// 	// ����DMA���ڴ����ģʽ   
// 	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
// 	
// 	// ���������ֳ�   
// 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

// 	// �ڴ������ֳ�   
// 	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

// 	// ����DMA�Ĵ���ģʽ������ѭ��ģʽ
// 	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

// 	// ����DMA�����ȼ���   
// 	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

// 	// ��ֹ�ڴ浽�ڴ�Ĵ���
// 	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

// 	DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
// 	
// 	DMA_Cmd(DMA1_Channel5,ENABLE);
// 	
// 	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC | DMA_IT_HT,ENABLE);  //����DMA������ɺͰ���������ж�

// }
// /*
//  * ��������NVIC_Config
//  * ����  ��DMA �ж�����
//  * ����  ����
//  * ���  : ��
//  * ����  ���ⲿ����
//  */
// static void NVIC_Config(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
//   
//   /* Configure one bit for preemption priority */
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//   
// 	// 
// 	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

//   /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
//   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// 	//	����UART1�ж�     
// 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //ͨ������Ϊ����1�ж�  
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// }





/******************* (C) COPYRIGHT *****END OF FILE************/

