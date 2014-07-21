#ifndef		_PROTOCOL_H_
#define		_PROTOCOL_H_

#include "stdint.h"
#define STX     0x73//这里原来是0x82,0x83,还不都是为了该死的VB，我不得不换成s,e的ascii码
#define ETX     0x65

#define IP_address 0x00

#define		REC_BUG_LENGTH			512
#define		APP_DATA_LEN				512

typedef __packed struct{
			   uint8_t	u8PacketNO;
			   uint8_t	u8CMD;
				 uint16_t u16LEN;
			   void 		*pData;
			   }tsPacketOfAppInfo;

typedef __packed struct{
			   uint8_t	u8RecAddr;
			   uint8_t	u8SendAddr;
			   void  *pPacketOfAppInfo;
			   uint8_t 	u8Checksum;
			  }tsPacketOfDataLink;





extern	tsPacketOfDataLink sPacketOfDataLinkDown;
extern	tsPacketOfAppInfo sPacketOfAppInfoRec;
extern	tsPacketOfDataLink sPacketOfDataLinkUp;
extern	tsPacketOfAppInfo sPacketOfAppInfoSend;


extern uint8_t u8RecBuffer[REC_BUG_LENGTH];
extern uint8_t u8SendBuffer[REC_BUG_LENGTH];

extern	uint8_t u8AppRecData[APP_DATA_LEN];
extern	uint8_t u8AppSendData[APP_DATA_LEN];

extern	uint8_t u8DataPool[APP_DATA_LEN];

uint32_t UpLinkTransform( uint8_t u8InputData[], uint8_t u8OutputData[], uint32_t u32Len );

void DownLinkTransform( uint8_t u8InputData[], uint8_t u8OutputData[], uint32_t u32Len );

void UnloadDataToDataLink(uint8_t u8InputData[], tsPacketOfDataLink *psPacketOfDataLinkRec, uint32_t u32Len);

uint32_t LoadDataToDataLink(tsPacketOfDataLink *psPacketOfDataLinkUp, uint8_t u8OutDataBufToSend[]);
				 
void ParseProtocol(uint8_t u8RecData[], uint32_t u32MaxLen);

uint32_t SendData_thisprotocol(tsPacketOfAppInfo sendout,uint8_t source,uint8_t destination,uint8_t len);

void AppProcesspacket( void *pPacketOfAppInfo ,uint8_t u8RealData[],uint8_t len,uint8_t packetno,uint8_t cmd,uint8_t Data[]);

void AppProcessunpacket(uint8_t u8RealData[],uint8_t len,uint8_t Data[]);
#endif
