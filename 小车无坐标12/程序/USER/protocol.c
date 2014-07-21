#include "protocol.h"
#include <string.h>
#include <stdint.h>
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "variables.h"
#include "polygon.h"
#include "stdint.h"

//#include "Uart_Application.h"
//���ְ���һ������·��ģ�datalink,һ����Ӧ�ò�ģ�appinfo��ÿ�ְ���Ϊ�����֣�һ�����գ�һ���Ƿ����������ĸ��ṹ��
tsPacketOfDataLink sPacketOfDataLinkDown = 
																			 {
																					0x00,													// u8RecAddr
																					0x00,													// u8SendAddr
																					(void *)&sPacketOfAppInfoRec,	// *pPacketOfAppInfo
																					0x00													// u8Checksum
																			 };

tsPacketOfAppInfo sPacketOfAppInfoRec = 	 
																			 {
																					0x00,										// u8PacketNO
																					0x00,										// u8CMD
																					0,											// u16LEN
																					(void *)u8AppRecData		//*pData
																			 };
																			 
tsPacketOfDataLink sPacketOfDataLinkUp = 
																			 {
																					0x00,													// u8RecAddr
																					IP_address,										// u8SendAddr
																					(void *)&sPacketOfAppInfoSend,// *pPacketOfAppInfo
																					0x00													// u8Checksum
																			 };

tsPacketOfAppInfo sPacketOfAppInfoSend = 	 
																			 {
																					0x00,										// u8PacketNO
																					0x00,										// u8CMD
																					0,											// u16LEN
																					(void *)u8AppSendData		//*pData
																			 };
																			 
uint8_t u8AppRecData[APP_DATA_LEN];										//the actual data of receiving
uint8_t u8AppSendData[APP_DATA_LEN];				//the actual data of sending

uint8_t u8RecBuffer[REC_BUG_LENGTH];
uint8_t u8SendBuffer[REC_BUG_LENGTH]; 

uint8_t u8DataPool[APP_DATA_LEN]; 

uint8_t outputdata[512];//�����Ѿ�������������

																			 
uint8_t i;

	
									
/*****************************************
 * Function Name:memstr
 * Discription  :seek a string from another string.
 * Function input:*haystack: 	the string to be seek;
									size: 			the size of the seeked string;
									*needl: 		the seeking data;
									needlesize	the seeking data size;
 * Function output:	if find,return the pointer of the seeked string where they are found
										else    return NULL
 * special usage	: if the seeking string is only a byte,we can value *needl=NULL and needlesize = seeking-char
******************************************/
uint8_t * memstr(uint8_t *haystack, uint32_t size, uint8_t *needle, uint32_t needlesize)
{
	uint8_t *p, u8Single[1];

	if( needle == NULL )
	{
			u8Single[0] = needlesize;
			needle = u8Single;
			needlesize = 1;
	}
	for (p = haystack; p <= (haystack-needlesize+size); p++)
	{
		if( memcmp(p, needle, needlesize) == 0 )
		{
				return p; /* found */
		}
	}
	return NULL;
}
/*****************************************
 * Function Name:UpLinkTransform
 * Discription  :Package the input data,rules below:
								1.Package every 7 Bytes in sequence.Creat a package header before them.So every normal package is made up of 
									8 Bytes with a header at the first position.
								2.The header's bit-7 to bit-1 is made up of the bit-8 of every Packed data.The bit-7 of header eaquals the 
									last data of this package.And the header's bit-8 of header is always low.
								3.Each packaed data=data&0x7f.
								4.In this way,each data's bit-8 is always low.if we recieve a high-bit-8 data but it's not the STX or ETX.
									It's must be a wrong data.
								5.if the number of a package's data is below 7,It's also ok to package.
 * Function input:u8InputData[]: 	the unpacked input data;
									u32Len: 				the length of unpacked data;
									u8OutputData[]: the packed output data;				 
 * Function output:								the length of packed data;
******************************************/
uint32_t UpLinkTransform( uint8_t u8InputData[], uint8_t u8OutputData[], uint32_t u32Len )
{//ֻ�ǽ����ݴ������������STX��ETX�������������ݵ��ֽ����������Ƿ��ذ���
	//���ܾ��ǰ����е����ݴ�����Ѿ�����STX��ETX�ˣ�����Ҫ�ټ�ʲô��ȥ��
		 uint32_t u32I = 0, u32J = 0;
		 uint32_t u32DataIndex = 0, u32Tmp  = 0;
	
		 for( ; u32DataIndex < u32Len; u32DataIndex++ )
		 {
										
					if( u32I++ > 6 )
					{
							u32I = 0;
							u8OutputData[u32J << 3] = u32Tmp;
							u32J++;
							u32Tmp = 0;
						
							u32DataIndex--;
					}
					else
					{
							u32Tmp = (u32Tmp >> 1);
							if( u8InputData[u32DataIndex] & 0x80 )
							{
									u32Tmp = (u32Tmp ) | 0x40;
							}
							else
							{
							}
							u8OutputData[(u32J << 3) + u32I ] = u8InputData[u32DataIndex] & 0x7f;
					}
					
		 }// End for

					
		 if( u32I != 0 )
		 {
				 u8OutputData[u32J << 3] = u32Tmp;
		 }
		 
		 return (u32J << 3) + u32I + 1;
}
/*****************************************
 * Function Name:DownLinkTransform
 * Discription  :unPackage the input data
 * Function input:u8InputData[]: 	the packed input data;
									u32Len: 				the length of packed data;
									u8OutputData[]: the unpacked output data;				 
 * Function output:
******************************************/
void DownLinkTransform( uint8_t u8InputData[], uint8_t u8OutputData[], uint32_t u32Len )
{
		uint32_t u32I, u32J, u32Block, u32Remainder;
		uint32_t u32DataIndex = 0;
	
	  u32Block = u32Len >> 3;//����һ�����Էֳɼ���						// u32Block = u32Len / 8
		u32Remainder = u32Len & (8-1);//���ܻ��в���8�����ݵ�һ�������ʣ�µĲ���8��������		// u32Remainder = u32Len % 8
	
		for( u32I = 0; u32I < u32Block; u32I++ )
		{
				 for( u32J = 0; u32J < 8; u32J++ )
				 {
						    if( u32J >= 7 )
							{
									continue; //˵��������һ������Ҫ�����ˣ����������forѭ����������һ���µı���u32J�ԼӺ��ٴν���forѭ��
									//�����break�Ļ�������ȥ�Ͳ��ٻ��������������ȥ�����Ի�����
							}
							if( (u8InputData[(u32I<<3) + 0]) & (0x01 << u32J) )
							{//���δ����λȡ��ͷ���ֽڵ�bit�������1�Ļ�
									u8OutputData[u32DataIndex] = u8InputData[(u32I<<3) + u32J + 1] | 0x80;//�ӵڶ����ֽڿ�ʼ�ָ�ԭ���ݣ����˼ҵ����λ�����˼�
							}
							else
							{
									u8OutputData[u32DataIndex] = u8InputData[(u32I<<3) + u32J + 1];//�������1�Ļ�����ô�Ͳ��ù��ˣ�ֱ���ó�������
							}
							u32DataIndex++;//��������±��Լ�
				 }
		}
		
		if( u32Remainder == 0 )
		{  //���û�в���8�����ݵİ�����ôֱ�ӷ���
				return ;
		}
		
		for( u32J = 0; u32J <= (u32Remainder - 1); u32J++ )
		{//����в���8�����ݵ�һ��
				 if( (u8InputData[(u32Block<<3) + 0]) & (0x01 << (u32J+8-u32Remainder)))//!!!!!!!!!There is a big BUG!!!!!!!!!
				 {//ͬ�ϣ�������һ�����ݣ�ֻ�����������ϵĶ�����һ������Ҳ�Ǵ����λ��ʼ��ͷ���ֽڲ�������˼�ԭ����
						 u8OutputData[u32DataIndex] = u8InputData[(u32Block<<3) + u32J + 1] | 0x80;
				 }
				 else
				 {
						 u8OutputData[u32DataIndex] = u8InputData[(u32Block<<3) + u32J + 1];
				 }			
				 u32DataIndex++;
		}// End for
		
		return;
}
/*****************************************
 * Function Name:UnloadDataToDataLink
 * Discription  :transfer the data from receive(already remove the STX and ETX) to link layer
 * Function input:u8InputData[]: 					the receive data
									*psPacketOfDataLinkRec:	the Link layer struct pointer
									u32DataLen:							the length of the receive data;
 * Function output:
******************************************/
void UnloadDataToDataLink(uint8_t u8InputData[], tsPacketOfDataLink *psPacketOfDataLinkRec, uint32_t u32DataLen)
{//�ú����Ĺ����ǲ��������·��İ����STX��ETX
	//���ܾ��ǲ��һ��һ�����ַ���Ȼ������ô���������⺯��������
		uint32_t u32DataIndex = 0, u32Len;
		tsPacketOfAppInfo *psTmpPacketOfAppInfo;
	
		DownLinkTransform( u8InputData, u8DataPool, u32DataLen );//����������������һ�ֽ�һ�ֽڵķ���u8DataPool��
	
		u32Len = sizeof(psPacketOfDataLinkRec->u8RecAddr) + sizeof(psPacketOfDataLinkRec->u8SendAddr);
		memcpy( (uint8_t *)psPacketOfDataLinkRec, 
						&u8DataPool[u32DataIndex], 
						u32Len
					);//��u8DataPool�ĵ�ַ����ָ�룬��ָ��ָ���Ǹ�������������
		
		u32DataIndex += u32Len;//�����±��ƶ�
	
		u32Len = sizeof(tsPacketOfAppInfo) - sizeof(void*);
		memcpy( (uint8_t *)psPacketOfDataLinkRec->pPacketOfAppInfo, 
						&u8DataPool[u32DataIndex], 
						u32Len
					);
		
		u32DataIndex += u32Len;
	
		psTmpPacketOfAppInfo = psPacketOfDataLinkRec->pPacketOfAppInfo;
		u32Len = psTmpPacketOfAppInfo->u16LEN;
		memcpy( (uint8_t *)psTmpPacketOfAppInfo->pData, 
						&u8DataPool[u32DataIndex],
						u32Len
					);
		ps=(uint8_t *)psTmpPacketOfAppInfo->pData;		
		u32DataIndex += u32Len;
		
		psPacketOfDataLinkRec->u8Checksum = u8DataPool[u32DataIndex++];
		
}
/*****************************************
 * Function Name:LoadDataToDataLink
 * Discription  :transfer the data from Link layer to send data
 * Function input:*psPacketOfDataLinkUp: 	the Link layer struct pointer
									u8OutDataBufToSend[]:	the transform result			 
 * Function output:											the length of the result data;
******************************************/
uint32_t LoadDataToDataLink(tsPacketOfDataLink *psPacketOfDataLinkUp, uint8_t u8OutDataBufToSend[])
{//�ú����Ĺ����ǽ����ݰ�����STX��ETX���һ����·��İ�
	uint32_t u32I, u32DataIndex = 0, u32Len;
	tsPacketOfAppInfo *psTmpPacketOfAppInfo;
	
	
	u32Len = sizeof(psPacketOfDataLinkUp->u8RecAddr) + sizeof(psPacketOfDataLinkUp->u8SendAddr);
	memcpy( &u8DataPool[u32DataIndex], 
					(uint8_t *)psPacketOfDataLinkUp, 
					u32Len
				);
	
	u32DataIndex += u32Len;
	
	u32Len = sizeof(tsPacketOfAppInfo) - sizeof(void*);
	memcpy( &u8DataPool[u32DataIndex], 
					(uint8_t *)psPacketOfDataLinkUp->pPacketOfAppInfo, 
					u32Len
				);
	
	u32DataIndex += u32Len;
	
	psTmpPacketOfAppInfo = psPacketOfDataLinkUp->pPacketOfAppInfo;
	u32Len = psTmpPacketOfAppInfo->u16LEN;
	memcpy( &u8DataPool[u32DataIndex], 
					(uint8_t *)psTmpPacketOfAppInfo->pData,
					u32Len
				);
				
	u32DataIndex += u32Len;
	
	u8DataPool[u32DataIndex++] = psPacketOfDataLinkUp->u8Checksum;
	// ����checksum, ���¸�ֵ
	
	
	// ת��������·���ݲ�
	u32DataIndex = UpLinkTransform( u8DataPool, u8OutDataBufToSend + 1, u32DataIndex );
	//�����Ѿ����������ݴ�ð��ˣ�������ȥд�ˣ����Լ��ں����ڲ������ˣ�ͬʱҲ�����ݷ�����
	//u8OutDataBufToSend��ȥ

	u8OutDataBufToSend[0] = STX;

	u8OutDataBufToSend[1 + u32DataIndex] = ETX;
	
	//ParseProtocol(u8OutDataBufToSend, count+18);//����Э�飬���а������STX��ETX��Ҳ�������
	
	return u32DataIndex + 1 + 1;//��������������STX��ETX���������u8OutDataBufToSend�������

	
}
/*****************************************
 * Function Name:ParseProtocol
 * Discription  :Parse the protocol from the receiving memory buffer.If received the right thing ,do AppProcess() defined at 
								 Uart_Application.h
 * Function input:u8RecData[]:It must be the receiving memory buffer.For example:
															If we use the DMA mode to transfer data,we should let the u8RecData=DMA buffer;
									u32MaxLen:	The max lentgh of the memory buffer			 
 * Function output:
******************************************/
void ParseProtocol(uint8_t u8RecData[], uint32_t u32MaxLen)
{
		static uint32_t su32ParseStatus, su32Pos1, su32Pos2;
	
		static uint32_t	su32Len = 0, su32Index = 0;
	
		uint32_t su32I, su32LenToBeRec = 0;
	
		uint8_t *pu8Tmp;
		uint32_t u32Tmp;

		su32Len = su32Len % u32MaxLen;//Ҫ��ֵ��������±� 
		su32Index = su32Index % u32MaxLen;//�յ����ݵ��±�
		su32LenToBeRec = u32MaxLen;//totalnum;//UART_Receiving(su32Index);//�յ������ݵĳ���
	
	  	if( su32LenToBeRec == 0 )
		{
				return;
		}
		memcpy( u8RecBuffer+su32Len,u8RecData+su32Index, su32LenToBeRec);
		//���յ������ݸ�ֵ���Լ����������
		su32Len+=su32LenToBeRec;//�ܳ��ȶ���
		su32Index+=su32LenToBeRec;
// 		u8RecData[su32Len++] = 0xbb;
// 		u32Tmp = LoadDataToDataLink(&sPacketOfDataLinkUp, u8SendBuffer);
// 		memcpy( u8RecData + su32Len, u8SendBuffer, u32Tmp);
// 		su32Len += u32Tmp;
// 		u8RecData[su32Len++] = 0xcc;
		
		switch(su32ParseStatus)
		{
				case 0:
						// ��u8RecData������STX�ַ�����������ΪĿǰ���յ����ֽ�����su32Len
						pu8Tmp = memstr( u8RecBuffer, su32Len, NULL, STX );
						//����ֵ���������Ժ��ڽϳ�������ָ���λ��
						if( pu8Tmp != NULL )
						{
								su32Pos1 = pu8Tmp - u8RecBuffer;//��ǰָ���ȥ�׵�ַ�õ�������ʧ��ƥ���ֽ��� 
								su32ParseStatus = 1;
							
								// ��������STX�ĺ���λ��(su32Pos1 + 1)��������ETX��
								// ��������ΪĿǰ���յ����ֽ�����su32Len - (su32Pos1 + 1)
								// �˴���1һ��һ�������sizeof(needle string)
								pu8Tmp = memstr( u8RecBuffer + (su32Pos1 + 1), 
																 su32Len - (su32Pos1 + 1), NULL, ETX );
								//�ӵ�ǰλ�ÿ�ʼ����Ѱ��ETX  
								if( pu8Tmp != NULL )
								{
										// ƥ�䵽ETX, su32Pos2�����u8RecBuffer�׵�ַ��λ��
										su32Pos2 = pu8Tmp - u8RecBuffer; 
										//su32ParseStatus = 2;
										
										UnloadDataToDataLink( u8RecBuffer + (su32Pos1 + 1),
																					&sPacketOfDataLinkDown,
																					su32Pos2 - su32Pos1 - 1
																				);
										//��ʼ����������֮�������
										//���Ѿ������Ĳ������
									  for(su32I=su32Pos1;su32I<=su32Pos2;su32I++)
									{
										u8RecBuffer[su32I]=0;
									}
										// ����ETX������ֽ�
										u32Tmp = su32Len - (su32Pos2 + 1);//ETX��������������ݵĻ�
										memmove( u8RecBuffer + su32Pos1, 
														 u8RecBuffer + su32Pos2 + 1,
														 u32Tmp
													 );//�Ѻ��������ץ��ǰ����
										su32Len -= (su32Pos2 - su32Pos1 + 1);	
										//�ܳ��Ȼ���STX��ETX֮���
										// �����û���
										//AppProcess( sPacketOfDataLinkDown.pPacketOfAppInfo );
										//���Ѿ������õ�������ʲô��ʲô������
										su32ParseStatus = 0;
								}// End if
								else
								{
										// su32ParseStatus��ȻΪ1
								}
						}
						else
						{
						}
				break;
				case 1:
						// ��������STX�ĺ���λ��(su32Pos1 + 1)��������ETX��
						// ��������ΪĿǰ���յ����ֽ�����su32Len - (su32Pos1 + 1)
						// �˴���1һ��һ�������sizeof(needle string)
						pu8Tmp = memstr( u8RecBuffer + (su32Pos1 + 1), 
														 su32Len - (su32Pos1 + 1), NULL, ETX );  
						if( pu8Tmp != NULL )
						{
								// ƥ�䵽ETX
								//su32Pos2 = pu8Tmp - (u8RecData + (su32Pos1 + 1)) + (su32Pos1 + 1)); 
								su32Pos2 = pu8Tmp - u8RecBuffer; 
								su32ParseStatus = 2;
							
								UnloadDataToDataLink( u8RecBuffer + (su32Pos1 + 1),
																			&sPacketOfDataLinkDown,
																			su32Pos2 - su32Pos1 - 1
																		);
								
								//���Ѿ������Ĳ������
								for(su32I=su32Pos1;su32I<=su32Pos2;su32I++)
								{
									u8RecBuffer[su32I]=0;
								}
								// ����ETX������ֽ�
								u32Tmp = su32Len - (su32Pos2 + 1);
								memmove( u8RecBuffer + su32Pos1, 
												 u8RecBuffer + su32Pos2 + 1,
												 u32Tmp
											 );
								su32Len -= (su32Pos2 - su32Pos1 + 1);	
									
								// �����û���
								//AppProcess( sPacketOfDataLinkDown.pPacketOfAppInfo );
								
								su32ParseStatus = 0;
						}
						else
						{
								// su32ParseStatus��ȻΪ1
						}
				break;
				case 2:
				break;
				default:
				break;
		}
}
/*****************************************
 * Function Name:SendData_thisprotocol
 * Discription  :Send the Data in this protocol
 * Function input:tsPacketOfAppInfo			 
 * Function output:
******************************************/
uint32_t SendData_thisprotocol(tsPacketOfAppInfo sendout,uint8_t source,uint8_t destination,uint8_t len)
{
	uint32_t i;
	
	tsPacketOfAppInfo *apppoint=sPacketOfDataLinkUp.pPacketOfAppInfo;//�����������ָ��ָ��Ӧ�ò�ṹ��
	for(i=0;i<=len-1;i++)
	{
		u8AppSendData[i]=package[i];
	}
	
	sPacketOfAppInfoSend = sendout;//������ṹ��һ�������ֽ�sendout
	sPacketOfDataLinkUp.u8RecAddr=destination;//���յ�ַ��ֵ
	sPacketOfDataLinkUp.u8SendAddr=source;//������ַ��ֵ
	sPacketOfDataLinkUp.u8Checksum=0x01;//У��λ
	//sPacketOfDataLinkUp.*pPacketOfAppInfo=sPacketOfAppInfoSend;//������ָ��ָ��Ӧ�ò������
	//�����շ���ַ��У��λ֮�����������

	apppoint->u8PacketNO=0x01;//����No
	apppoint->u8CMD=0x01;//����ֵ
	apppoint->u16LEN=len;//���鳤��
	(uint8_t *)apppoint->pData=u8AppSendData;//ʵ��Ҫ���������
												//u8Checksum has not defined
	count=LoadDataToDataLink(&sPacketOfDataLinkUp,u8SendBuffer);//����������������STX��ETX
//	for(i=0;i<count;i++)
//	{
//		printf("%c",u8SendBuffer[i]);//��������Ƿ���ȷ
//	}
	return count;
}





//�ú������ڹ涨Ҫ�����������Щʲô�������շ���ַ��Ҳ�������ı�ţ�������ݳ��ȣ�����Ҫ�������ݣ�У��λ�����й涨��RecAddr=0x02,SendAddr=0x01
//Ҳ�����ڴ�������е��βΣ�InputData[]
//�涨���Ϊ0x01,�Ժ���������
//�涨����NoΪ0x01,��Ϊ����������Ժ���Ҫ��ʱ��������
//�涨�յ�ַΪ0x02
//�涨����ַΪ0x01
//�涨У��λΪ0x01
void AppProcesspacket( void *pPacketOfAppInfo ,uint8_t u8RealData[],uint8_t len,uint8_t packetno,uint8_t cmd,uint8_t Data[])
{
		static uint8_t i=0;
		uint8_t j=0;
		//uint8_t Data[1000];//��������������
		tsPacketOfDataLink *pTmpsPacketOfDataLinkUp = pPacketOfAppInfo;
	
		pTmpsPacketOfDataLinkUp->u8RecAddr=0x02;//�յ�ַΪ0x02
		Data[i]=pTmpsPacketOfDataLinkUp->u8RecAddr;//��һ������Ϊ�յ�ַ
		i++;
	
		pTmpsPacketOfDataLinkUp->u8SendAddr=0x01;//����ַΪ0x01
		Data[i]=pTmpsPacketOfDataLinkUp->u8SendAddr;//��һ������Ϊ����ַ
		i++;
		
		Data[i]=packetno;//����������Ϊ���ı�ţ����û��Լ��趨
		i++;
	
		Data[i]=cmd;//���ĸ�����Ϊ����
		i++;
	
		Data[i]=len;
		i=i+2;//���������Ϊ����Ҫ�������ݵ��ֽڳ���,�������ʱ2���ֽ�
	
		for(j=0 ;j<len;j++)
		{
				Data[i]=u8RealData[j];//�����������Ҫ��������
				i++;
		}
		
		pTmpsPacketOfDataLinkUp->u8Checksum=0x01;//У��λ
		Data[i]=0x01;//У��λ
		//������Ͱѳ���STX��ETX���������ݶ���ֵ��Ҫ�������������

}


