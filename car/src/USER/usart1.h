#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#include "eceg_usart.h"
#include "ringbuf.h"



#define	USART1_DMA_RX_BUFF_SIZE					(512)
#define	USART1_DMA_RX_BUFF_SIZE_HALF		(USART1_DMA_RX_BUFF_SIZE/2)
#define	USART1_DMA_TX_RINGBUF_SIZE			(128)

#define USART1_DR_Base  								0x40013804
#define USART1_SENDBUFF_SIZE 						50

// typedef struct{
// 		uint8_t		u8RxFlag;
// 		uint8_t		u8TxFlag;
// 		uint8_t		u8Reserved1;
// 		uint8_t		u8Reserved2;
// 		uint16_t	u16RxCounter;
// 		uint16_t	u16TxCounter;
// 		uint16_t	u16RxTotalNum;
// 		uint16_t	u16TxTotalNum;
// 		uint8_t		*u8RX_Buffer;
// 		uint8_t		*u8TX_Buffer;
// }tsUSART_entity;

extern uint8_t u8Usart1_SendBuff[USART1_SENDBUFF_SIZE];
extern uint8_t	u8Usart1_User_RX_Buffer[USART1_DMA_RX_BUFF_SIZE*2];

extern uint8_t	u8Usart1_TX_Buffer[USART1_DMA_TX_RINGBUF_SIZE];
extern uint8_t	u8Usart1_RX_Buffer[USART1_DMA_RX_BUFF_SIZE];

extern tsUSART_entity sUsart1_entity;
extern tRingBufObject sUsart1_RingBuf;


void USART1_Config(void);
// int fputc(int ch, FILE *f);
// void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
// void DMA_Config(void);
// static void NVIC_Config(void);

void Usart1_Send(uint8_t *u8Buf, uint32_t u32Len);

#endif /* __USART1_H */
