/******************** (C) COPYRIGHT  ***************************
 * 文件名  ：usart1.c
 * 描述    ：
 *           
 * 硬件平台：
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.5.0
 * 作者    ：
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


static uint8_t u8Usart1_Halffull = 1;					// 0代表是前半个缓冲区满了，1代表是后半个缓冲区满了




void DMA1_Channel5_IRQ(void)
{
		uint32_t i;
	
 		if (DMA1->ISR & DMA1_IT_HT5)										// 通道5半传输事件完成
 		{ 

			 DMA1->IFCR |= DMA1_FLAG_HT5;									// 清除通道5半传输完成标志
			 u8Usart1_Halffull = 0;												// 前半个缓冲区满
			 
			 for (i = 0; i < (USART1_DMA_RX_BUFF_SIZE_HALF); i++)
			 {
					 // 一旦半满中断产生，则把充满缓冲区一半的数据立即读出来
					 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[i];		
				 
					 sUsart1_entity.u16RxCounter++;						//数组指针指向下一个单元

			 }
			 // 如果前半个缓冲区满，总个数加(USART_DMA_RX_BUFF_SIZE_HALF)
			 sUsart1_entity.u16RxTotalNum += (USART1_DMA_RX_BUFF_SIZE_HALF);			

		}// End if (DMA1->ISR & DMA1_IT_HT5)
		else if (DMA1->ISR & DMA1_IT_TC5)								// 通道5传输事件完成
 		{ 
						u8Usart1_Halffull = 1;									// 后半个缓冲区满
 						DMA1->IFCR |= DMA1_FLAG_TC5;						// 清除通道5传输完成标志
							
						for (i = 0; i < (USART1_DMA_RX_BUFF_SIZE_HALF); i++)
						{
								u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[USART1_DMA_RX_BUFF_SIZE_HALF + i];
								
								sUsart1_entity.u16RxCounter++;				//数组指针指向下一个单元

						}
						
						// 如果前半个缓冲区满，总个数加(USART_DMA_RX_BUFF_SIZE_HALF)
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
	
		 //判断是否为DMA发送完成中断
		 if (DMA1->ISR & DMA1_FLAG_TC4) 
		 {  
				DMA1->IFCR = DMA1_FLAG_TC4;					// 清标志

			  // 判断队列是否非空？
			  // 如果队列非空，意味着接下来有DMA发送任务。对于环形队列非空，有两种情况：
			  // 一种是尾指针tail>首指针head，即环形队列未发生回卷，此时可以直接设置DMA发送。
			  // 另一种尾指针tail<首指针head，即环形队列发生了回卷，此时DMA发送将分成两步：
			  // 第一步：首指针head到队列内存地址尾部构成一个DMA发送序列。
			  // 设置好该DMA发送序列后更新首指针head，这样自然进入到第二步。
			  // 第二步：队列物理地址首址到尾指针tail构成另一DMA发送序列。
			  // 队列如果空，则什么事情也不干。
			 
				// 队列是否非空？			 
			  //
				// Copy the Read/Write indices for calculation.
				//
				u32Tail = sUsart1_RingBuf.ulWriteIndex;
				u32Head = sUsart1_RingBuf.ulReadIndex;
			  
			  if (u32Tail != u32Head)
				{
					 // 队列非空
					 if (u32Tail > u32Head)
					 {
							// ringbuf未回卷
						  
						  // 禁止DMA1_Channel4
							DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
						  // 设置发送DMA的memory的base地址
						  DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];
						 
						  // 设置发送DMA的长度
							DMA1_Channel4->CNDTR = u32Tail - u32Head;
						 
							// 重新使能DMA1_Channel4
							DMA1_Channel4->CCR |= DMA_CCR1_EN;

							// 更新ringbuf首指针(临界代码)
							sUsart1_RingBuf.ulReadIndex = sUsart1_RingBuf.ulWriteIndex;					 
						 						 
					 }
					 else
					 {
							// ringbuf回卷

							// 禁止DMA1_Channel4
							DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
						  // 设置发送DMA的memory的base地址
						  DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];
						 
						  // 设置发送DMA的长度
							DMA1_Channel4->CNDTR = sUsart1_RingBuf.ulSize - u32Head;
						 
							// 重新使能DMA1_Channel4
							DMA1_Channel4->CCR |= DMA_CCR1_EN;			
						 
						  // 更新ringbuf首指针(临界代码)
							sUsart1_RingBuf.ulReadIndex = 0;
						 
					 }
					 
				}
				else
				{
					 // 队列空
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

					
	if (USART1->SR & USART_FLAG_IDLE)									//如果检测到空闲位
	{
			u32Temp = USART1->SR;  
      u32Temp = USART1->DR; 												//清USART_IT_IDLE标志   

			if (u8Usart1_Halffull == 0)										//如果前半个缓冲区满
			{
				 dmabuflen = (USART1_DMA_RX_BUFF_SIZE_HALF) - DMA1_Channel5->CNDTR;			//取得现在一共传输了多少个数据
			}
			else if (u8Usart1_Halffull == 1)							//后半个缓冲区满
			{
				 dmabuflen = USART1_DMA_RX_BUFF_SIZE - DMA1_Channel5->CNDTR;
			}

					
			for	(i = 0; i < dmabuflen; i++)
			{
					if (u8Usart1_Halffull == 0)								//前半个缓冲区满
					{
						 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[USART1_DMA_RX_BUFF_SIZE_HALF + i];
						
						 sUsart1_entity.u16RxCounter++;					//数组指针指向下一个单元
					}
					else if (u8Usart1_Halffull == 1)					//如果后半个缓冲区满
					{
							 u8Usart1_User_RX_Buffer[sUsart1_entity.u16RxCounter] = sUsart1_entity.u8RX_Buffer[i];
						
							 sUsart1_entity.u16RxCounter++;				//数组指针指向下一个单元

					}

			}// End for
			
			sUsart1_entity.u16RxTotalNum += dmabuflen;			//如果空闲，加上多余的数据个数
			
			// 一连续串口数据报接收完成
			sUsart1_entity.u8RxFlag = 1;
			
			// 禁止DMA1_Channel5
			DMA1_Channel5->CCR &= (uint16_t)(~DMA_CCR1_EN);
			
			// 重新设置DMA1_Channel5的指针
			DMA1_Channel5->CNDTR = USART1_DMA_RX_BUFF_SIZE;
			
			// 重新使能DMA1_Channel5
			DMA1_Channel5->CCR |= DMA_CCR1_EN;
					
			// 串口接收计数清0
			sUsart1_entity.u16RxCounter = 0;
			
			// 恢复u8Usart1_Halffull为初始值
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
	
	// 队列是否非空？
	if (u32Tail == u32Head)
	{
			// 队列空
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUsart1_RingBuf, u8Buf[i]);					// 将需要的需要的数据量存入环形队列
				
					// 队列满相应措施？
					
			}// End for
				
			// DMA操作
			// 禁止DMA1_Channel4
			DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
						  
			// 设置发送DMA的memory的base地址
			DMA1_Channel4->CMAR = (uint32_t)&sUsart1_RingBuf.pucBuf[u32Head];

			// 空读ringbuf一个字节（因为发了一个字节）
			result = RingBufReadOne(&sUsart1_RingBuf);
			
			// 设置发送DMA的长度
			DMA1_Channel4->CNDTR = 1;
						 
			// 重新使能DMA1_Channel4
			DMA1_Channel4->CCR |= DMA_CCR1_EN;

			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	
			
	}
	else
	{
			// 队列非空
			for (i = 0; i < u32Len; i++)
			{
					RingBufWriteOne(&sUsart1_RingBuf, u8Buf[i]);					// 将需要的需要的数据量存入环形队列
				
					// 队列满相应措施？
					
			}// End for
			
	}
	
		
}


/*
 * 函数名：USART1_Config
 * 描述  ：USART1 GPIO 配置,工作模式配置。115200 8-N-1
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
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
	
	
	// 采用DMA方式接收   
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  

	// 中断配置   
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);   

	// 启动串口
	USART_Cmd(USART1, ENABLE); 

}







// /*
//  * 函数名：DMA_Config
//  * 描述  ：DMA 串口的初始化配置
//  * 输入  ：无
//  * 输出  : 无
//  * 调用  ：外部调用
//  */
// void DMA_Config(void)
// {
//   DMA_InitTypeDef DMA_InitStructure;

// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
// 	NVIC_Config();	   																	//配置DMA中断

//  	// 设置USART1 发送DMA
// 	/*设置DMA源：内存地址&串口数据寄存器地址*/
//     DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	   

// 	/*内存地址(要传输的变量的指针)*/
//     DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tRingBuf.pucBuf;
// 	
// 	/*方向：从内存到外设*/		
//     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
// 	
// 	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
//     DMA_InitStructure.DMA_BufferSize = USART1_SENDBUFF_SIZE;
// 	
// 	/*外设地址不增*/	    
//     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
// 	
// 	/*内存地址自增*/
//     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
// 	
// 	/*外设数据单位*/	
//     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
// 	
// 	/*内存数据单位 8bit*/
//     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
// 	
// 	/*DMA模式：一次传输，循环*/
//     DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
// 	
// 	/*优先级：中*/	
//     DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
// 	
// 	/*禁止内存到内存的传输	*/
//     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
// 	
// 	/*配置DMA1的4通道*/		   
//     DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
// 	
// 	DMA_Cmd (DMA1_Channel4,ENABLE);					//使能DMA
// 	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
// 	

// 	// 设置USART1 接收DMA
// 	// DMA1通道5配置   
// 	DMA_DeInit(DMA1_Channel5);  

// 	// 外设地址   
// 	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
// 	
// 	//内存地址   
//   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUSART_entity.u8RX_Buffer;

// 	// dma传输方向单向   
// 	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

// 	// 设置DMA在传输时缓冲区的长度   
// 	DMA_InitStructure.DMA_BufferSize = USART1_DMA_RX_BUFF_SIZE;  
// 	
// 	// 设置DMA的外设递增模式，一个外设   
// 	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
// 	
// 	// 设置DMA的内存递增模式   
// 	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
// 	
// 	// 外设数据字长   
// 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

// 	// 内存数据字长   
// 	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

// 	// 设置DMA的传输模式，环形循环模式
// 	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

// 	// 设置DMA的优先级别   
// 	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

// 	// 禁止内存到内存的传输
// 	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

// 	DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
// 	
// 	DMA_Cmd(DMA1_Channel5,ENABLE);
// 	
// 	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC | DMA_IT_HT,ENABLE);  //配置DMA接收完成和半满后产生中断

// }
// /*
//  * 函数名：NVIC_Config
//  * 描述  ：DMA 中断配置
//  * 输入  ：无
//  * 输出  : 无
//  * 调用  ：外部调用
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

//   /* 配置P[A|B|C|D|E]0为中断源 */
//   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// 	//	配置UART1中断     
// 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口1中断  
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// }





/******************* (C) COPYRIGHT *****END OF FILE************/

