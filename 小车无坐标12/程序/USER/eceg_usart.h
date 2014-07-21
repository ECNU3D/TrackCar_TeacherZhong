#ifndef __ECEG_USART_H
#define	__ECEG_USART_H

#include "stm32f10x.h"
#include <stdio.h>


typedef struct{
		uint8_t		u8RxFlag;
		uint8_t		u8TxFlag;
		uint8_t		u8Reserved1;
		uint8_t		u8Reserved2;
		uint16_t	u16RxCounter;
		uint16_t	u16TxCounter;
		uint16_t	u16RxTotalNum;
		uint16_t	u16TxTotalNum;
		uint8_t		*u8RX_Buffer;
		uint8_t		*u8TX_Buffer;
}tsUSART_entity;


void Usart_DMA_Config(void);

void Usart_NVIC_Config(void);

// void USART_SEND(uint8_t *u8Buf, uint32_t u32Len);

#endif /* __ECEG_USART_H */
