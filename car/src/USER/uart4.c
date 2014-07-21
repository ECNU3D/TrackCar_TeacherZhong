/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��uart4.c
 * ����    ��
 *           
 * Ӳ��ƽ̨��
 * Ӳ�����ӣ�------------------------
 *          | PC10  - UART4(Tx)      |
 *          | PC11 - UART4(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ��
**********************************************************************************/
#include "uart4.h"
#include <stdarg.h>

#include "stm32f10x_dma.h"
#include "stdint.h"
#include "stdint.h"



uint8_t u8Uart4_SendBuff[UART4_SENDBUFF_SIZE];
uint8_t	u8Uart4_User_RX_Buffer[UART4_DMA_RX_BUFF_SIZE*4];

uint8_t	u8Uart4_TX_Buffer[UART4_DMA_TX_RINGBUF_SIZE];
uint8_t	u8Uart4_RX_Buffer[UART4_DMA_RX_BUFF_SIZE];




tsUSART_entity sUart4_entity = {	0,
																	0,
																  0,
																	0,
																	
																	0,
																	0,
	
																	0,
																	0,
																	
																	u8Uart4_RX_Buffer,
																	u8Uart4_TX_Buffer
															 };



static uint8_t u8Uart4_Halffull = 1;					// 0������ǰ������������ˣ�1�����Ǻ�������������




void DMA2_Channel3_IRQ(void)
{
		uint32_t i;
	
 		if (DMA2->ISR & DMA2_IT_HT3)										// ͨ��3�봫���¼����
 		{ 

			 DMA2->IFCR |= DMA2_FLAG_HT3;									// ���ͨ��3�봫����ɱ�־
			 u8Uart4_Halffull = 0;												// ǰ�����������
			 
			 for (i = 0; i < (UART4_DMA_RX_BUFF_SIZE_HALF); i++)
			 {
					 // һ�������жϲ�������ѳ���������һ�����������������
					 u8Uart4_User_RX_Buffer[sUart4_entity.u16RxCounter] = sUart4_entity.u8RX_Buffer[i];		
				 
					 sUart4_entity.u16RxCounter++;						//����ָ��ָ����һ����Ԫ

			 }
			 // ���ǰ��������������ܸ�����(UART_DMA_RX_BUFF_SIZE_HALF)
			 sUart4_entity.u16RxTotalNum += (UART4_DMA_RX_BUFF_SIZE_HALF);			

		}// End if (DMA2->ISR & DMA2_IT_HT3)
		else if (DMA2->ISR & DMA2_IT_TC3)								// ͨ��3�����¼����
 		{ 
						u8Uart4_Halffull = 1;									// ������������
 						DMA2->IFCR |= DMA2_FLAG_TC3;						// ���ͨ��3������ɱ�־
							
						for (i = 0; i < (UART4_DMA_RX_BUFF_SIZE_HALF); i++)
						{
								u8Uart4_User_RX_Buffer[sUart4_entity.u16RxCounter] = sUart4_entity.u8RX_Buffer[UART4_DMA_RX_BUFF_SIZE_HALF + i];
								
								sUart4_entity.u16RxCounter++;				//����ָ��ָ����һ����Ԫ

						}
						
						// ���ǰ��������������ܸ�����(UART_DMA_RX_BUFF_SIZE_HALF)
						sUart4_entity.u16RxTotalNum += (UART4_DMA_RX_BUFF_SIZE_HALF);			
		}// End else if (DMA2->ISR & DMA1_IT_TC3)	
	
}

void DMA2_Channel3_IRQHandler(void)
{
		DMA2_Channel3_IRQ();
}


// #define		TX_RINGBUF_SIZE		128
tRingBufObject sUart4_RingBuf = {
																	UART4_DMA_TX_RINGBUF_SIZE,
																	0,
																	0,
																	u8Uart4_TX_Buffer
																 };

void DMA2_Channel5_IRQ(void)
{
		 uint32_t u32Tail;
		 uint32_t u32Head;
	
		 //�ж��Ƿ�ΪDMA��������ж�
		 if (DMA2->ISR & DMA2_FLAG_TC5) 
		 {  
				DMA2->IFCR = DMA2_FLAG_TC5;					// ���־

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
				u32Tail = sUart4_RingBuf.ulWriteIndex;
				u32Head = sUart4_RingBuf.ulReadIndex;
			  
			  if (u32Tail != u32Head)
				{
					 // ���зǿ�
					 if (u32Tail > u32Head)
					 {
							// ringbufδ�ؾ�
						  
						  // ��ֹDMA2_Channel5
							DMA2_Channel5->CCR &= (uint16_t)(~DMA_CCR5_EN);
						  
						  // ���÷���DMA��memory��base��ַ
						  DMA2_Channel5->CMAR = (uint32_t)&sUart4_RingBuf.pucBuf[u32Head];
						 
						  // ���÷���DMA�ĳ���
							DMA2_Channel5->CNDTR = u32Tail - u32Head;
						 
							// ����ʹ��DMA2_Channel5
							DMA2_Channel5->CCR |= DMA_CCR5_EN;

							// ����ringbuf��ָ��(�ٽ����)
							sUart4_RingBuf.ulReadIndex = sUart4_RingBuf.ulWriteIndex;					 
						 						 
					 }
					 else
					 {
							// ringbuf�ؾ�

							// ��ֹDMA2_Channel5
							DMA2_Channel5->CCR &= (uint16_t)(~DMA_CCR5_EN);
						  
						  // ���÷���DMA��memory��base��ַ
						  DMA2_Channel5->CMAR = (uint32_t)&sUart4_RingBuf.pucBuf[u32Head];
						 
						  // ���÷���DMA�ĳ���
							DMA2_Channel5->CNDTR = sUart4_RingBuf.ulSize - u32Head;
						 
							// ����ʹ��DMA2_Channel5
							DMA2_Channel5->CCR |= DMA_CCR5_EN;			
						 
						  // ����ringbuf��ָ��(�ٽ����)
							sUart4_RingBuf.ulReadIndex = 0;
						 
					 }
					 
				}
				else
				{
					 // ���п�
				}
			 
		 }		
		 
}


void DMA2_Channel4_5_IRQHandler(void)
{	
		 DMA2_Channel5_IRQ();
}



void UART4_IRQ(void)
{
	uint32_t res, u32Temp, dmabuflen;
	//static u16 j=0;	 
	uint32_t i;

					
	if (UART4->SR & USART_FLAG_IDLE)									//�����⵽����λ
	{
			u32Temp = UART4->SR;  
      u32Temp = UART4->DR; 												//��USART_IT_IDLE��־   

			if (u8Uart4_Halffull == 0)										//���ǰ�����������
			{
				 dmabuflen = (UART4_DMA_RX_BUFF_SIZE_HALF) - DMA2_Channel3->CNDTR;			//ȡ������һ�������˶��ٸ�����
			}
			else if (u8Uart4_Halffull == 1)							//������������
			{
				 dmabuflen = UART4_DMA_RX_BUFF_SIZE - DMA2_Channel3->CNDTR;
			}

					
			for	(i = 0; i < dmabuflen; i++)
			{
					if (u8Uart4_Halffull == 0)								//ǰ�����������
					{
						 u8Uart4_User_RX_Buffer[sUart4_entity.u16RxCounter] = sUart4_entity.u8RX_Buffer[UART4_DMA_RX_BUFF_SIZE_HALF + i];
						
						 sUart4_entity.u16RxCounter++;					//����ָ��ָ����һ����Ԫ
					}
					else if (u8Uart4_Halffull == 1)					//���������������
					{
							 u8Uart4_User_RX_Buffer[sUart4_entity.u16RxCounter] = sUart4_entity.u8RX_Buffer[i];
						
							 sUart4_entity.u16RxCounter++;				//����ָ��ָ����һ����Ԫ

					}

			}// End for
			
			sUart4_entity.u16RxTotalNum += dmabuflen;			//������У����϶�������ݸ���
			
			// һ�����������ݱ��������
			sUart4_entity.u8RxFlag = 1;
			
			// ��ֹDMA2_Channel3
			DMA2_Channel3->CCR &= (uint16_t)(~DMA_CCR3_EN);
			
			// ��������DMA2_Channel3��ָ��
			DMA2_Channel3->CNDTR = UART4_DMA_RX_BUFF_SIZE;
			
			// ����ʹ��DMA2_Channel3
			DMA2_Channel3->CCR |= DMA_CCR3_EN;
					
			// ���ڽ��ռ�����0
			sUart4_entity.u16RxCounter = 0;
			
			// �ָ�u8Uart4_HalffullΪ��ʼֵ
			u8Uart4_Halffull = 1;

  }// End if (UART4->SR & UART_FLAG_IDLE)	

}

void UART4_IRQHandler(void)
{

		 UART4_IRQ();
}



void Uart4_Send(uint8_t *u8Buf, uint32_t u32Len)
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
	u32Tail = sUart4_RingBuf.ulWriteIndex;
	u32Head = sUart4_RingBuf.ulReadIndex;
	
	// �����Ƿ�ǿգ�
	if (u32Tail == u32Head)
	{
			// ���п�
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUart4_RingBuf, u8Buf[i]);					// ����Ҫ����Ҫ�����������뻷�ζ���
				
					// ��������Ӧ��ʩ��
					
			}// End for
				
			// DMA����
			// ��ֹDMA2_Channel5
			DMA2_Channel5->CCR &= (uint16_t)(~DMA_CCR5_EN);
						  
			// ���÷���DMA��memory��base��ַ
			DMA2_Channel5->CMAR = (uint32_t)&sUart4_RingBuf.pucBuf[u32Head];

			// �ն�ringbufһ���ֽڣ���Ϊ����һ���ֽڣ�
			result = RingBufReadOne(&sUart4_RingBuf);
			
			// ���÷���DMA�ĳ���
			DMA2_Channel5->CNDTR = 1;
						 
			// ����ʹ��DMA2_Channel5
			DMA2_Channel5->CCR |= DMA_CCR5_EN;

			USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);	
			
	}
	else
	{
			// ���зǿ�
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUart4_RingBuf, u8Buf[i]);					// ����Ҫ����Ҫ�����������뻷�ζ���
				
					// ��������Ӧ��ʩ��
					
			}// End for
			
	}
	
		
}


/*
 * ��������UART4_Config
 * ����  ��UART4 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void UART4_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config UART4 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* UART4 GPIO config */
	/* Configure UART4 Tx (PC.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);    
	/* Configure UART4 Rx (PC.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	  
	/* UART4 mode config */
	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure); 
	
	
	// ����DMA��ʽ����   
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);  

	// �ж�����   
	USART_ITConfig(UART4,USART_IT_TC,DISABLE);  
	USART_ITConfig(UART4,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);   

	// ��������
	USART_Cmd(UART4, ENABLE); 

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

