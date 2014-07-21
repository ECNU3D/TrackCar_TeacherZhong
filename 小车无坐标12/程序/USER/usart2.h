#ifndef __USART2_H
#define	__USART2_H

#include "stm32f10x.h"
#include <stdio.h>

#include "eceg_usart.h"
#include "ringbuf.h"



#define	USART2_DMA_RX_BUFF_SIZE					(512)
#define	USART2_DMA_RX_BUFF_SIZE_HALF		(USART2_DMA_RX_BUFF_SIZE/2)
#define	USART2_DMA_TX_RINGBUF_SIZE			(2048)

// #define USART2_DR_Base  								0x40013804
#define USART2_SENDBUFF_SIZE 						(2048)

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

extern uint8_t u8Usart2_SendBuff[USART2_SENDBUFF_SIZE];
extern uint8_t	u8Usart2_User_RX_Buffer[USART2_DMA_RX_BUFF_SIZE*4];

extern uint8_t	u8Usart2_TX_Buffer[USART2_DMA_TX_RINGBUF_SIZE];
extern uint8_t	u8Usart2_RX_Buffer[USART2_DMA_RX_BUFF_SIZE];

extern tsUSART_entity sUsart2_entity;
extern tRingBufObject sUsart2_RingBuf;


void USART2_Config(void);
// int fputc(int ch, FILE *f);
// void USART3_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
// void DMA_Config(void);
// static void NVIC_Config(void);

void Usart2_Send(uint8_t *u8Buf, uint32_t u32Len);

#endif /* __USART2_H */