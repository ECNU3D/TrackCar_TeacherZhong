#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>

#include "eceg_usart.h"
#include "ringbuf.h"



#define	USART3_DMA_RX_BUFF_SIZE					(512)
#define	USART3_DMA_RX_BUFF_SIZE_HALF		(USART3_DMA_RX_BUFF_SIZE/2)
#define	USART3_DMA_TX_RINGBUF_SIZE			(2048)

// #define USART3_DR_Base  								0x40013804
#define USART3_SENDBUFF_SIZE 						(2048)

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

extern uint8_t u8Usart3_SendBuff[USART3_SENDBUFF_SIZE];
extern uint8_t	u8Usart3_User_RX_Buffer[USART3_DMA_RX_BUFF_SIZE*4];

extern uint8_t	u8Usart3_TX_Buffer[USART3_DMA_TX_RINGBUF_SIZE];
extern uint8_t	u8Usart3_RX_Buffer[USART3_DMA_RX_BUFF_SIZE];

extern tsUSART_entity sUsart3_entity;
extern tRingBufObject sUsart3_RingBuf;


void USART3_Config(void);
// int fputc(int ch, FILE *f);
// void USART3_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
// void DMA_Config(void);
// static void NVIC_Config(void);

void Usart3_Send(uint8_t *u8Buf, uint32_t u32Len);

#endif /* __USART3_H */
