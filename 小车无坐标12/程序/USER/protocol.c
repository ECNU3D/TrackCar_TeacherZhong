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
//两种包，一种是链路层的，datalink,一种是应用层的，appinfo，每种包分为两部分，一个是收，一个是发，所以有四个结构体
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

uint8_t outputdata[512];//接收已经拆包过后的数据

																			 
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
{//只是将数据打包，并不加上STX和ETX，返回所有数据的字节总数，不是返回包数
	//功能就是把所有的数据打包，已经包括STX和ETX了，不需要再加什么进去了
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
	
	  u32Block = u32Len >> 3;//数据一共可以分成几包						// u32Block = u32Len / 8
		u32Remainder = u32Len & (8-1);//可能会有不满8个数据的一包，最后剩下的不满8个的数据		// u32Remainder = u32Len % 8
	
		for( u32I = 0; u32I < u32Block; u32I++ )
		{
				 for( u32J = 0; u32J < 8; u32J++ )
				 {
						    if( u32J >= 7 )
							{
									continue; //说明到了下一包数据要处理了，这个是跳出for循环，但是以一个新的变量u32J自加后再次进入for循环
									//如果是break的话，跳出去就不再回来，这个是跳出去还可以回来的
							}
							if( (u8InputData[(u32I<<3) + 0]) & (0x01 << u32J) )
							{//依次从最低位取出头部字节的bit，如果是1的话
									u8OutputData[u32DataIndex] = u8InputData[(u32I<<3) + u32J + 1] | 0x80;//从第二个字节开始恢复原数据，把人家的最高位还给人家
							}
							else
							{
									u8OutputData[u32DataIndex] = u8InputData[(u32I<<3) + u32J + 1];//如果不是1的话，那么就不用管了，直接拿出来即可
							}
							u32DataIndex++;//输出数据下标自加
				 }
		}
		
		if( u32Remainder == 0 )
		{  //如果没有不满8和数据的包，那么直接返回
				return ;
		}
		
		for( u32J = 0; u32J <= (u32Remainder - 1); u32J++ )
		{//如果有不满8个数据的一包
				 if( (u8InputData[(u32Block<<3) + 0]) & (0x01 << (u32J+8-u32Remainder)))//!!!!!!!!!There is a big BUG!!!!!!!!!
				 {//同上，拆分最后一包数据，只不过后面与上的东西不一样，但也是从最低位开始把头部字节拆掉还给人家原数据
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
{//该函数的功能是拆包，将链路层的包拆掉STX和ETX
	//功能就是拆成一个一个的字符，然后再怎么样就是另外函数的事了
		uint32_t u32DataIndex = 0, u32Len;
		tsPacketOfAppInfo *psTmpPacketOfAppInfo;
	
		DownLinkTransform( u8InputData, u8DataPool, u32DataLen );//将输入的数组拆包拆成一字节一字节的放入u8DataPool中
	
		u32Len = sizeof(psPacketOfDataLinkRec->u8RecAddr) + sizeof(psPacketOfDataLinkRec->u8SendAddr);
		memcpy( (uint8_t *)psPacketOfDataLinkRec, 
						&u8DataPool[u32DataIndex], 
						u32Len
					);//把u8DataPool的地址赋给指针，让指针指向那个拆包过后的数组
		
		u32DataIndex += u32Len;//数组下标移动
	
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
{//该函数的功能是将数据包加上STX和ETX组成一个链路层的包
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
	// 计算checksum, 重新赋值
	
	
	// 转换至到链路数据层
	u32DataIndex = UpLinkTransform( u8DataPool, u8OutDataBufToSend + 1, u32DataIndex );
	//这里已经将所有数据打好包了，不用再去写了，他自己在函数内部做掉了，同时也将数据放入了
	//u8OutDataBufToSend中去

	u8OutDataBufToSend[0] = STX;

	u8OutDataBufToSend[1 + u32DataIndex] = ETX;
	
	//ParseProtocol(u8OutDataBufToSend, count+18);//解析协议，其中包括拆掉STX和ETX，也包括拆包
	
	return u32DataIndex + 1 + 1;//所以现在整个从STX到ETX的数组就是u8OutDataBufToSend这个数组

	
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

		su32Len = su32Len % u32MaxLen;//要赋值的数组的下标 
		su32Index = su32Index % u32MaxLen;//收到数据的下标
		su32LenToBeRec = u32MaxLen;//totalnum;//UART_Receiving(su32Index);//收到的数据的长度
	
	  	if( su32LenToBeRec == 0 )
		{
				return;
		}
		memcpy( u8RecBuffer+su32Len,u8RecData+su32Index, su32LenToBeRec);
		//将收到的数据赋值给自己定义的数组
		su32Len+=su32LenToBeRec;//总长度定好
		su32Index+=su32LenToBeRec;
// 		u8RecData[su32Len++] = 0xbb;
// 		u32Tmp = LoadDataToDataLink(&sPacketOfDataLinkUp, u8SendBuffer);
// 		memcpy( u8RecData + su32Len, u8SendBuffer, u32Tmp);
// 		su32Len += u32Tmp;
// 		u8RecData[su32Len++] = 0xcc;
		
		switch(su32ParseStatus)
		{
				case 0:
						// 在u8RecData中搜索STX字符，搜索长度为目前接收到的字节总数su32Len
						pu8Tmp = memstr( u8RecBuffer, su32Len, NULL, STX );
						//返回值是搜索到以后在较长数组中指针的位置
						if( pu8Tmp != NULL )
						{
								su32Pos1 = pu8Tmp - u8RecBuffer;//当前指针减去首地址得到长数组失败匹配字节数 
								su32ParseStatus = 1;
							
								// 在搜索到STX的后续位置(su32Pos1 + 1)继续搜索ETX，
								// 搜索长度为目前接收到的字节总数su32Len - (su32Pos1 + 1)
								// 此处的1一般一般情况是sizeof(needle string)
								pu8Tmp = memstr( u8RecBuffer + (su32Pos1 + 1), 
																 su32Len - (su32Pos1 + 1), NULL, ETX );
								//从当前位置开始往后寻找ETX  
								if( pu8Tmp != NULL )
								{
										// 匹配到ETX, su32Pos2相对于u8RecBuffer首地址的位置
										su32Pos2 = pu8Tmp - u8RecBuffer; 
										//su32ParseStatus = 2;
										
										UnloadDataToDataLink( u8RecBuffer + (su32Pos1 + 1),
																					&sPacketOfDataLinkDown,
																					su32Pos2 - su32Pos1 - 1
																				);
										//开始解析这两个之间的数据
										//将已经解析的部分清空
									  for(su32I=su32Pos1;su32I<=su32Pos2;su32I++)
									{
										u8RecBuffer[su32I]=0;
									}
										// 计算ETX后接收字节
										u32Tmp = su32Len - (su32Pos2 + 1);//ETX后面如果还有数据的话
										memmove( u8RecBuffer + su32Pos1, 
														 u8RecBuffer + su32Pos2 + 1,
														 u32Tmp
													 );//把后面的数据抓到前面来
										su32Len -= (su32Pos2 - su32Pos1 + 1);	
										//总长度还是STX和ETX之间的
										// 处理用户层
										//AppProcess( sPacketOfDataLinkDown.pPacketOfAppInfo );
										//用已经解析好的数据做什么做什么。。。
										su32ParseStatus = 0;
								}// End if
								else
								{
										// su32ParseStatus仍然为1
								}
						}
						else
						{
						}
				break;
				case 1:
						// 在搜索到STX的后续位置(su32Pos1 + 1)继续搜索ETX，
						// 搜索长度为目前接收到的字节总数su32Len - (su32Pos1 + 1)
						// 此处的1一般一般情况是sizeof(needle string)
						pu8Tmp = memstr( u8RecBuffer + (su32Pos1 + 1), 
														 su32Len - (su32Pos1 + 1), NULL, ETX );  
						if( pu8Tmp != NULL )
						{
								// 匹配到ETX
								//su32Pos2 = pu8Tmp - (u8RecData + (su32Pos1 + 1)) + (su32Pos1 + 1)); 
								su32Pos2 = pu8Tmp - u8RecBuffer; 
								su32ParseStatus = 2;
							
								UnloadDataToDataLink( u8RecBuffer + (su32Pos1 + 1),
																			&sPacketOfDataLinkDown,
																			su32Pos2 - su32Pos1 - 1
																		);
								
								//将已经解析的部分清空
								for(su32I=su32Pos1;su32I<=su32Pos2;su32I++)
								{
									u8RecBuffer[su32I]=0;
								}
								// 计算ETX后接收字节
								u32Tmp = su32Len - (su32Pos2 + 1);
								memmove( u8RecBuffer + su32Pos1, 
												 u8RecBuffer + su32Pos2 + 1,
												 u32Tmp
											 );
								su32Len -= (su32Pos2 - su32Pos1 + 1);	
									
								// 处理用户层
								//AppProcess( sPacketOfDataLinkDown.pPacketOfAppInfo );
								
								su32ParseStatus = 0;
						}
						else
						{
								// su32ParseStatus仍然为1
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
	
	tsPacketOfAppInfo *apppoint=sPacketOfDataLinkUp.pPacketOfAppInfo;//让这个空类型指针指向应用层结构体
	for(i=0;i<=len-1;i++)
	{
		u8AppSendData[i]=package[i];
	}
	
	sPacketOfAppInfoSend = sendout;//给这个结构起一个新名字叫sendout
	sPacketOfDataLinkUp.u8RecAddr=destination;//给收地址赋值
	sPacketOfDataLinkUp.u8SendAddr=source;//给发地址赋值
	sPacketOfDataLinkUp.u8Checksum=0x01;//校验位
	//sPacketOfDataLinkUp.*pPacketOfAppInfo=sPacketOfAppInfoSend;//空类型指针指向应用层的数据
	//除掉收发地址和校验位之后的所有数据

	apppoint->u8PacketNO=0x01;//包的No
	apppoint->u8CMD=0x01;//命令值
	apppoint->u16LEN=len;//数组长度
	(uint8_t *)apppoint->pData=u8AppSendData;//实际要传输的数据
												//u8Checksum has not defined
	count=LoadDataToDataLink(&sPacketOfDataLinkUp,u8SendBuffer);//将数据整理打包加上STX和ETX
//	for(i=0;i<count;i++)
//	{
//		printf("%c",u8SendBuffer[i]);//检测数据是否正确
//	}
	return count;
}





//该函数用于规定要打包的数据是些什么，包括收发地址，也包括包的编号，命令，数据长度，真正要传的数据，校验位，其中规定，RecAddr=0x02,SendAddr=0x01
//也就是在打包过程中的形参，InputData[]
//规定命令都为0x01,以后再慢慢改
//规定包的No为0x01,作为输入变量，以后需要的时候再来改
//规定收地址为0x02
//规定发地址为0x01
//规定校验位为0x01
void AppProcesspacket( void *pPacketOfAppInfo ,uint8_t u8RealData[],uint8_t len,uint8_t packetno,uint8_t cmd,uint8_t Data[])
{
		static uint8_t i=0;
		uint8_t j=0;
		//uint8_t Data[1000];//待送入打包的数组
		tsPacketOfDataLink *pTmpsPacketOfDataLinkUp = pPacketOfAppInfo;
	
		pTmpsPacketOfDataLinkUp->u8RecAddr=0x02;//收地址为0x02
		Data[i]=pTmpsPacketOfDataLinkUp->u8RecAddr;//第一个数据为收地址
		i++;
	
		pTmpsPacketOfDataLinkUp->u8SendAddr=0x01;//发地址为0x01
		Data[i]=pTmpsPacketOfDataLinkUp->u8SendAddr;//第一个数据为发地址
		i++;
		
		Data[i]=packetno;//第三个数据为包的编号，由用户自己设定
		i++;
	
		Data[i]=cmd;//第四个数据为命令
		i++;
	
		Data[i]=len;
		i=i+2;//第五个数据为真正要传的数据的字节长度,这个变量时2个字节
	
		for(j=0 ;j<len;j++)
		{
				Data[i]=u8RealData[j];//后面的是真正要传的数据
				i++;
		}
		
		pTmpsPacketOfDataLinkUp->u8Checksum=0x01;//校验位
		Data[i]=0x01;//校验位
		//到这里就把出了STX和ETX的所有数据都赋值到要打包的数组里了

}


