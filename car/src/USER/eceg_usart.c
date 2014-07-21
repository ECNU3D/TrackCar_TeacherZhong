/******************** (C) COPYRIGHT  ***************************
 * 文件名  ：eceg_usart.c
 * 描述    ：
 *           
 * 硬件平台：
 * 硬件连接：
 *         
 *           
 * 库版本  ：ST3.5.0
 * 作者    ：
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
 * 函数名：DMA_Config
 * 描述  ：DMA 串口的初始化配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void Usart_DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);	//开启DMA2时钟
	Usart_NVIC_Config();	   														//配置DMA中断


 	// 设置USART1 发送DMA
	/*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	   

	/*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart1_RingBuf.pucBuf;
	
	/*方向：从内存到外设*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART1_DMA_TX_RINGBUF_SIZE;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*优先级：中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	
	
	
	/*配置DMA1的4通道*/		   
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel4,ENABLE);								 //使能DMA
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
	

	// 设置USART1 接收DMA
	// DMA1通道5配置   
	DMA_DeInit(DMA1_Channel5);  

	// 外设地址   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
	
	//内存地址   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart1_entity.u8RX_Buffer;

	// dma传输方向单向   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// 设置DMA在传输时缓冲区的长度   
	DMA_InitStructure.DMA_BufferSize = USART1_DMA_RX_BUFF_SIZE;  
	
	// 设置DMA的外设递增模式，一个外设   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// 设置DMA的内存递增模式   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// 外设数据字长   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// 内存数据字长   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// 设置DMA的传输模式，环形循环模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// 设置DMA的优先级别   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel5,ENABLE);
	
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC | DMA_IT_HT,ENABLE);  //配置DMA接收完成和半满后产生中断




 	// 设置USART3 发送DMA
	/*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	   

	/*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart3_RingBuf.pucBuf;
	
	/*方向：从内存到外设*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART3_DMA_TX_RINGBUF_SIZE;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*优先级：中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*配置DMA1的2通道*/		   
    DMA_Init(DMA1_Channel2, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel2,ENABLE);								 //使能DMA
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断


	// 设置USART3 接收DMA
	// DMA1通道3配置   
	DMA_DeInit(DMA1_Channel3);  

	// 外设地址   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
	
	//内存地址   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart3_entity.u8RX_Buffer;

	// dma传输方向单向   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// 设置DMA在传输时缓冲区的长度   
	DMA_InitStructure.DMA_BufferSize = USART3_DMA_RX_BUFF_SIZE;  
	
	// 设置DMA的外设递增模式，一个外设   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// 设置DMA的内存递增模式   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// 外设数据字长   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// 内存数据字长   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// 设置DMA的传输模式，环形循环模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// 设置DMA的优先级别   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel3,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	DMA_ITConfig(DMA1_Channel3,DMA_IT_TC | DMA_IT_HT,ENABLE);  //配置DMA接收完成和半满后产生中断




 	// 设置USART2 发送DMA
	/*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);	   

	/*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart2_RingBuf.pucBuf;
	
	/*方向：从内存到外设*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = USART2_DMA_TX_RINGBUF_SIZE;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*优先级：中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*配置DMA1的7通道*/		   
    DMA_Init(DMA1_Channel7, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel7,ENABLE);								 //使能DMA
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断


	// 设置USART2 接收DMA
	// DMA1通道6配置   
	DMA_DeInit(DMA1_Channel6);  

	// 外设地址   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
	
	//内存地址   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUsart2_entity.u8RX_Buffer;

	// dma传输方向单向   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// 设置DMA在传输时缓冲区的长度   
	DMA_InitStructure.DMA_BufferSize = USART2_DMA_RX_BUFF_SIZE;  
	
	// 设置DMA的外设递增模式，一个外设   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// 设置DMA的内存递增模式   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// 外设数据字长   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// 内存数据字长   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// 设置DMA的传输模式，环形循环模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// 设置DMA的优先级别   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA1_Channel6,&DMA_InitStructure);  
	
	DMA_Cmd(DMA1_Channel6,ENABLE);
	
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC | DMA_IT_HT,ENABLE);  //配置DMA接收完成和半满后产生中断





 // 设置UART4 发送DMA
	/*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);	   

	/*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUart4_RingBuf.pucBuf;
	
	/*方向：从内存到外设*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = UART4_DMA_TX_RINGBUF_SIZE;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*优先级：中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	



	/*配置DMA2的5通道*/		   
    DMA_Init(DMA2_Channel5, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA2_Channel5,ENABLE);								 //使能DMA
	DMA_ITConfig(DMA2_Channel5,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断


	// 设置UART4 接收DMA
	// DMA2通道3配置   
	DMA_DeInit(DMA2_Channel3);  

	// 外设地址   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);  
	
	//内存地址   
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sUart4_entity.u8RX_Buffer;

	// dma传输方向单向   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  

	// 设置DMA在传输时缓冲区的长度   
	DMA_InitStructure.DMA_BufferSize = UART4_DMA_RX_BUFF_SIZE;  
	
	// 设置DMA的外设递增模式，一个外设   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	
	// 设置DMA的内存递增模式   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	
	// 外设数据字长   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  

	// 内存数据字长   
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  

	// 设置DMA的传输模式，环形循环模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  

	// 设置DMA的优先级别   
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  

	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA2_Channel3,&DMA_InitStructure);  
	
	DMA_Cmd(DMA2_Channel3,ENABLE);
	
	DMA_ITConfig(DMA2_Channel3,DMA_IT_TC | DMA_IT_HT,ENABLE);  //配置DMA接收完成和半满后产生中断




}


/*
 * 函数名：NVIC_Config
 * 描述  ：DMA 中断配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void Usart_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
	// 接收DMA中断优先级相对发送DMA和IDLE中断要高
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	配置UART1中断     
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口1中断  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	// 接收DMA中断优先级相对发送DMA和IDLE中断要高 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	配置UART3中断     
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //通道设置为串口3中断  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	

		// 接收DMA中断优先级相对发送DMA和IDLE中断要高
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	配置UART2中断     
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //通道设置为串口2中断  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
			// 接收DMA中断优先级相对发送DMA和IDLE中断要高
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel3_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

//   /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel4_5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//	配置UART4中断     
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;               //通道设置为串口4中断  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 12;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}





/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
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
 * 函数名：USART1_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口1，即USART1
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART1_printf( USART1, "\r\n this is a demo \r\n" );
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
	
	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
	{									  
	switch ( *++Data )
	{
		case 'r':							          //回车符
			USART_SendData(USARTx, 0x0d);
			Data ++;
		break;
		
		case 'n':							          //换行符
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
		case 's':										  //字符串
			s = va_arg(ap, const char *);
	for ( ; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;
	
	case 'd':										//十进制
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

