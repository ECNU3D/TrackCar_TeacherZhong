
#include <string.h>

#include "LPC17xx.h"

#include "lpc17xx_uart.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_systick.h"

#include "GPS.h"
#include "GPRS.h"

#include "ringFifo.h"
#include "rtc.h"

#include "system.h"



#define		GPS_STATUS_INITSTAGE1				0
#define		GPS_STATUS_INITSTAGE2				1

#define		GPS_STATUS_PROCESSING1				10
#define		GPS_STATUS_PROCESSING1_REP			11
#define		GPS_STATUS_PROCESSING2				15
#define		GPS_STATUS_PROCESSING2_REP			16

#define		GPS_STATUS_RECEIVE					200

#define		GPS_STATUS_DELAY					255


#define		GPS_SIGNAL_AVAIL_LOW_SPEED			30
#define		GPS_SIGNAL_AVAIL_NORMAL_SPEED		31
#define		GPS_SIGNAL_AVAIL_EMERGENCY			32
#define		GPS_SIGNAL_INVALID_EMERGENCY		33
#define		GPS_SIGNAL_INVALID					34



uint32_t	u32GPS_GPRMC_RecStatus = 0;
tsPacketOfGPS  sPacketOfGPS;
tsPacketOfGPS	 sPacketOfGPS_ToPolygonArea = {0};
const uint8_t u8DaysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const uint8_t u8DaysOfMonthLeap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// InsRingFIFO_GPS作为GPS具体数据的FIFO
tRingFIFO_Object	InsRingFIFO_GPS;

/*************************************************************************
GPS数据的FIFO与文件存储处理策略：
GPS数据的报送优先级条件有5类：
1．GPS信号正常且车低速（车速<=v）,GPS_AvailLowSpeed。
2．GPS信号正常且车速大于V，GPS_AvailNormalSpeed。
3．GPS信号正常且有报警事件，GPS_AvailEmergency。
4．GPS信号不正常且有报警事件，GPS_InvaidEmergency。
5．GPS信号不正常且没有报警事件，GPS_Invaid。
其中，第5类任何情况下不在SD卡上存储GPS数据。
当GPRS不在线，即终端和服务器通信中断后，GPS数据按一定规则存储在SD卡中。
SD卡上GPS的相关文件根据报送优先级分4类：
1．GPS信号正常且车低速（车速<=v）,GPS_AvailLowSpeed.dat。对应记录文件GPS_ALS_Index.txt。
2．GPS信号正常且车速大于V，GPS_AvailNormalSpeed.dat。对应记录文件GPS_ANS_Index.txt。
3．GPS信号正常且有报警事件，GPS_AvailEmergency.dat。对应记录文件GPS_AE_Index.txt。
4．GPS信号不正常且有报警事件，GPS_InvaidEmergency.dat。对应记录文件GPS_IE_Index.txt。
记录文件格式：采用ASC格式记录总记录数和已报送记录数，如下：
				Total record：xxxx(9999max)
				Record uploaded:xxxx(9999max)
写文件策略：
RAM设4类优先级对应的缓冲数据区，每个容量为8个tsPacketOfGPS大小，GPRS通信中断的情况下，
每填满缓冲数据区就执行一次写文件（append）操作。当GPRS通信恢复后，不管缓冲数据区是否
被填满，均执行一次写文件（append）操作。每次写文件操作指得是写GPS数据以及更新记录文件。
GPRS通信恢复后的报送策略：
报送当前GPS数据为高优先级，间歇时间补发打包的GPS数据，按优先级分别发送4个文件中的数据，
并更新相关记录文件。
**************************************************************************/
const uint8_t		cu8FileNameGPS_AvailLowSpeed[] = "GPS_AvailLowSpeed.dat";
const uint8_t		cu8FileNameGPS_ALS_Index[] = "GPS_ALS_Index.txt";
const uint8_t		cu8FileNameGPS_AvailNormalSpeed[] = "GPS_AvailNormalSpeed.dat";
const uint8_t		cu8FileNameGPS_ANS_Index[] = "GPS_ANS_Index.txt";
const uint8_t		cu8FileNameGPS_AvailEmergency[] = "GPS_AvailEmergency.dat";
const uint8_t		cu8FileNameGPS_AE_Index[] = "GPS_AE_Index.txt";
const uint8_t		cu8FileNameGPS_InvaidEmergency[] = "GPS_InvaidEmergency.dat";
const uint8_t		cu8FileNameGPS_IE_Index[] = "GPS_IE_Index.txt";
uint32_t			u32GPS_UploadCondition; 
tsPacketOfGPS		sPacketGPS_AvailLowSpeed[8];	
tsPacketOfGPS		sPacketGPS_AvailNormalSpeed[8];	
tsPacketOfGPS		sPacketGPS_AvailEmergency[8];	
tsPacketOfGPS		sPacketGPS_InvaidEmergency[8];	
tsIndexOfGPS_Record sGPS_ALS_Index = {0};
tsIndexOfGPS_Record sGPS_ANS_Index = {0};
tsIndexOfGPS_Record sGPS_AE_Index = {0};
tsIndexOfGPS_Record sGPS_IE_Index = {0};
uint16_t			u16GPS_UploadPeriod = 15;
// 以下5个值可由服务器远程更新设置
uint16_t			u16GPS_UploadT0 = 15;
uint16_t			u16GPS_UploadT1 = 90;
uint16_t			u16GPS_UploadT2 = 120;
uint16_t			u16GPS_UploadT3 = 5;
// 采用Q8格式，意味着判断时GPS原始数据需乘以2^8=256。
uint32_t			uq8GPS_LowSpeedLimitMknot = 6904;				// 5 * (1 / 0.1854) * 2^8;
////////////////////////////////////////

uint8_t GPS_RecBuffer[1024];

tsAggregateOfGPS	sAggregateOfGPS = {
																			{0},
																			0,						// Index
																			0,
																			0
																		};



uint32_t AscToNumX10000( uint8_t pStrTmp[] )
{
	uint32_t i, u32Result = 0, u32Tmp = 0, u32PosDot = 0;
	float fTmp;
	
	while( pStrTmp[u32PosDot] != '.' )
	{
		u32PosDot++;
	}
	
	// Modified 20130413!
	for( i = 0; i < u32PosDot - 2; i++ )
	{
			u32Result = u32Result*10 + ((pStrTmp[i] - '0'));
	}
	
	for( i = 0; i < 7; i++ )
	{
			if( i == 2 )
			{
					// Skip '.'
					continue;
			}
			u32Tmp = u32Tmp*10 + ((pStrTmp[i + u32PosDot - 2] - '0'));
	}
	fTmp = (float)u32Tmp / 60;
	u32Tmp = (uint32_t)fTmp;
	
	u32Result = u32Result * 10000 + u32Tmp;
	// End modification 20130413!
	
    return u32Result;
}

uint32_t AscToNumX10( uint8_t pStrTmp[] )
{
	uint32_t i = 0, u32Result = 0;

	while( pStrTmp[i] != '.' )
	{
		u32Result = u32Result*10 + ((pStrTmp[i] - '0'));
		i++;
	}
	u32Result = u32Result * 10 + ((pStrTmp[++i] - '0'));

    return u32Result;
}

void GPS_Machine(void)
{
	static uint32_t u32GPS_Status = GPS_STATUS_PROCESSING1;
	static uint32_t u32GPS_NextStatus = 0;
	static uint32_t u32GPS_TimeToDelay = 0;
	static uint32_t	u32Len = 0;
	static uint8_t *pStr;
	static uint32_t su32StrToMatchIndex = 0;
	uint32_t u32BoolEnableReception = 0;
	uint8_t *pStrTmp;
	uint32_t i = 0, u32Index = 0, u32ParseState = 0, u32REVtmp;

//	uint8_t StrTmp[16];


	u32Len += UART0Receive((LPC_UART_TypeDef *)LPC_UART0, GPS_RecBuffer + u32Len, sizeof(GPS_RecBuffer));
	if( u32Len > 1023 )
	{
		u32Len = 0;
	}

//	u32BoolTickEnable = 1;
//	if( uv32DecMsCounter >= 150 )
//	{
//		uv32DecMsCounter = 0;
//		sprintf(StrTmp,"u32Len = %d\r\n",u32Len);
//		UART2_DMA_Send(StrTmp, strlen(StrTmp));
//	}


	switch(u32GPS_Status)
	{
		case GPS_STATUS_PROCESSING1:
				if( u32Len != 0 )
				{
//					StrTmp[0] = GPS_RecBuffer[u32Len];
					GPS_RecBuffer[u32Len] = '\0';
					pStr = (uint8_t *)strstr( (CHAR *)GPS_RecBuffer, "$GPRMC" );
					if( pStr != NULL )
					{
						u32GPS_Status = GPS_STATUS_PROCESSING2;
					}
					else
					{
						if( u32Len > 1 )
						{
							if( (GPS_RecBuffer[u32Len - 2] == '\r') &&
								(GPS_RecBuffer[u32Len - 1] == '\n')
							  )
							{
								u32Len = 0;
							}
						}
					}
				}

//				u32BoolTickEnable = 1;
//				u32GPS_Status = GPS_STATUS_DELAY;
//				u32GPS_NextStatus = GPS_STATUS_INITSTAGE2;
//				u32GPS_TimeToDelay = 350;
		break;
		case GPS_STATUS_PROCESSING2:
				GPS_RecBuffer[u32Len] = '\0';
				pStrTmp = (uint8_t *)strstr( (CHAR *)pStr, "\r\n" ); 
				if(  pStrTmp != NULL )
				{
					u32Len = pStrTmp - pStr + 2;
					//UART2_DMA_Send(pStr, u32Len);
					for( i = 0; i < u32Len; i++)
					{
						 if( pStr[u32Index++] !=',' )
						 {
						 	continue;
						 }
						 else
						 {
						 	u32ParseState++;
							switch(u32ParseState)
							{
								case 1:
										//Get time of hour,minute,second,milisecond
//										sPacketOfGPS.u16Time_hh = (pStr[u32Index]	<< 8) | pStr[u32Index + 1];
//										sPacketOfGPS.u16Time_mm = (pStr[u32Index + 2]	<< 8) | pStr[u32Index + 3];
//										sPacketOfGPS.u16Time_ss = (pStr[u32Index + 4]	<< 8) | pStr[u32Index + 5];
//										sPacketOfGPS.u16Time_ms = (pStr[u32Index + 7]	<< 8) | pStr[u32Index + 8];
										sPacketOfGPS.u16Time_hh = ((pStr[u32Index] & 0x0f)*10 + (pStr[u32Index + 1] & 0x0f)) << 8;
										sPacketOfGPS.u16Time_mm = ((pStr[u32Index + 2] & 0x0f)*10 + (pStr[u32Index + 3] & 0x0f)) << 8;
										sPacketOfGPS.u16Time_ss = ((pStr[u32Index + 4] & 0x0f)*10 + (pStr[u32Index + 5] & 0x0f)) << 8;
										sPacketOfGPS.u16Time_ms = ((pStr[u32Index + 7] & 0x0f)*10 + (pStr[u32Index + 8] & 0x0f)) << 8;
								break;
								case 2:
										//GPS status: 'A' or 'V'
										sPacketOfGPS.u8Status = pStr[u32Index];

								break;
								case 3:
//										Struct_PacketOfGPS.u32Latitude = AscToNumX10000( pStr + u32Index );
										u32REVtmp = AscToNumX10000( pStr + u32Index );
										sPacketOfGPS.u32Latitude = __rev(u32REVtmp);
								break;
								case 4:
										sPacketOfGPS.u8Lahi = pStr[u32Index];
								break;
								case 5:
//										Struct_PacketOfGPS.u32Longitude = AscToNumX10000( pStr + u32Index);
										u32REVtmp = AscToNumX10000( pStr + u32Index);
										sPacketOfGPS.u32Longitude = __rev(u32REVtmp);
								break;
								case 6:
										sPacketOfGPS.u8Lohi = pStr[u32Index];
								break;
								case 7:
//										sPacketOfGPS.u16Speed = AscToNumX10( pStr + u32Index);
										u32REVtmp = AscToNumX10( pStr + u32Index);
										u32REVtmp = __rev(u32REVtmp);
										sPacketOfGPS.u16Speed = (u32REVtmp >> 16) & 0xffff;
								break;
								case 8:
										u32REVtmp = AscToNumX10( pStr + u32Index);
										u32REVtmp = __rev(u32REVtmp);
										sPacketOfGPS.u16Course = (u32REVtmp >> 16) & 0xffff;
								break;
								case 9:
										//Get time of date,month,year
										sPacketOfGPS.u16Time_DD = ((pStr[u32Index] & 0x0f)*10 + (pStr[u32Index + 1] & 0x0f)) << 8;
										sPacketOfGPS.u16Time_MM = ((pStr[u32Index + 2] & 0x0f)*10 + (pStr[u32Index + 3] & 0x0f)) << 8;
										sPacketOfGPS.u16Time_YY = ((pStr[u32Index + 4] & 0x0f)*10 + (pStr[u32Index + 5] & 0x0f)) << 8;
								break;
								default:
								break;
							}
						 }
					}// End for

					// 每24小时校时一次
					if( (SysRTC.HOUR == 0) && 
							(SysRTC.MIN == 0) &&
							(SysRTC.SEC < 5)
						)
					{
							u32BoolEverCalibtated = 0;
					}
					
					// Modified 20120610！
					if( (sPacketOfGPS.u8Status == 'A') && (((sPacketOfGPS.u16Time_YY >> 8) + 2000) > 2030) )
					{
							// 时间数据异常
							SYSTEM_DEBUG_DMA_SEND( "\r\nGPS bug fixed!\r\n", 18 );
							sPacketOfGPS.u8Status = 'V';
					}
					// End modification 20120610！	
					
					if( (u32BoolEverCalibtated == 0) && (sPacketOfGPS.u8Status == 'A') )
					{
						u32BoolEverCalibtated = 1;

						// 校准片上RTC。
						SysRTC.YEAR = (sPacketOfGPS.u16Time_YY >> 8) + 2000; 
						SysRTC.MONTH = sPacketOfGPS.u16Time_MM >> 8; 
						SysRTC.DOM = sPacketOfGPS.u16Time_DD >> 8; 
						//SysRTC.HOUR = sPacketOfGPS.u16Time_hh
						SysRTC.MIN = sPacketOfGPS.u16Time_mm >> 8; 
						SysRTC.SEC = sPacketOfGPS.u16Time_ss >> 8; 

						SysRTC.HOUR = i = (sPacketOfGPS.u16Time_hh >> 8) + 8;
						if( i > 23 )
						{
							i = i - 24;
							SysRTC.HOUR = i;
							SysRTC.DOM++;
							if( ((sPacketOfGPS.u16Time_YY >> 8) & (4-1)) == 0 )
							{
								// 简化判断为闰年。
								if( SysRTC.DOM > u8DaysOfMonthLeap[(sPacketOfGPS.u16Time_MM >> 8) - 1] )
								{
									SysRTC.DOM = 1;
									SysRTC.MONTH++;
									if( SysRTC.MONTH > 12 )
									{
										SysRTC.MONTH = 1;
										SysRTC.YEAR++;
									}
								}
							}// End if( ((sPacketOfGPS.u16Time_YY) & (4-1)) == 0 )
							else
							{
								// 非闰年情况。
								if( SysRTC.DOM > u8DaysOfMonth[(sPacketOfGPS.u16Time_MM >> 8) - 1] )
								{
									SysRTC.DOM = 1;
									SysRTC.MONTH++;
									if( SysRTC.MONTH > 12 )
									{
										SysRTC.MONTH = 1;
										SysRTC.YEAR++;
									}
								}
							}
							
						}// End if( i > 23 )		差一天的情况			   

						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_SECOND, SysRTC.SEC);
						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MINUTE, SysRTC.MIN);
						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_HOUR, SysRTC.HOUR);
						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_DAYOFMONTH, SysRTC.DOM);
						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MONTH, SysRTC.MONTH);
						RTC_SetTime (LPC_RTC, RTC_TIMETYPE_YEAR, SysRTC.YEAR);
						
						SYSTEM_DEBUG_DMA_SEND( "\r\nSystem time calibrated by GPS!\r\n", 34 );
					}

					//UART2_DMA_Send((uint8_t *)&Struct_PacketOfGPS, sizeof(Struct_PacketOfGPS));
					u32GPS_GPRMC_RecStatus = 1;
//					InsRingFIFO.pFuncWrite( &InsRingFIFO, &Struct_PacketOfGPS );

					// 判断速度，由于此处算出来的速度单位是x0.1节,且采用Q8格式
					// 
					if( ((sPacketOfGPS.u16Speed << 8) <= uq8GPS_LowSpeedLimitMknot)
						&& (sPacketOfGPS.u8Status == 'A' )
					  )
					{
						u32GPS_UploadCondition = GPS_SIGNAL_AVAIL_LOW_SPEED;
						u16GPS_UploadPeriod = u16GPS_UploadT1;
					}
					else if( sPacketOfGPS.u8Status == 'V' )
					{
						u32GPS_UploadCondition = GPS_SIGNAL_INVALID;
						u16GPS_UploadPeriod = u16GPS_UploadT2;
					}
					else
					{
						u32GPS_UploadCondition = GPS_SIGNAL_AVAIL_NORMAL_SPEED;
						u16GPS_UploadPeriod = u16GPS_UploadT0;
					}
					
					// Modified 20120725！
					if( (sPacketOfGPS.u8Status == 'A')
							 &&(sPacketOfGPS.u8Status4_PO_Plunder==1)
						   )
					{
						u32GPS_UploadCondition = GPS_SIGNAL_AVAIL_EMERGENCY;
						u16GPS_UploadPeriod = u16GPS_UploadT3;
					}
					else if( (sPacketOfGPS.u8Status == 'V')
							 &&(sPacketOfGPS.u8Status4_PO_Plunder==1)
						   )
					{
						u32GPS_UploadCondition = GPS_SIGNAL_INVALID_EMERGENCY;
					}
					// End modification 20120725！	

					// 检查GPRS通信状况，以上次的数据有没有发送成功作为判断依据。
					if( (sInsGPRS_StateMachine.u8Flag & GPRS_SEND_GPS_OK) == GPRS_SEND_GPS_OK )
					{
						 // 上次发送成功，清标志位
						 sInsGPRS_StateMachine.u8Flag &= (~GPRS_SEND_GPS_OK);
					}
					else
					{
						 // GPRS通信异常
						 switch( u32GPS_UploadCondition )
						 {
						 	case GPS_SIGNAL_AVAIL_LOW_SPEED:
								memcpy( &sPacketGPS_AvailLowSpeed[sGPS_ALS_Index.u16Current++], 
										(uint8_t *)&sPacketOfGPS, 
										sizeof(sPacketOfGPS) );
								if( sGPS_ALS_Index.u16Current >=8 )
								{
									sGPS_ALS_Index.u16Current = 0;
									
									// 写文件
								}
							break;
						 	case GPS_SIGNAL_AVAIL_NORMAL_SPEED:
							break;
						 	case GPS_SIGNAL_AVAIL_EMERGENCY:
							break;
						 	case GPS_SIGNAL_INVALID_EMERGENCY:
							break;
						 	case GPS_SIGNAL_INVALID:
							break;
							default:
							break;
						 }
					}

					u32Len = 0;
					u32GPS_Status = GPS_STATUS_PROCESSING1;
				}
		break;
		default:
		break;
	}
}

void FlushGPS_FIFO_ToAggregate(void)
{
		uint32_t u32PacketType;
		tsPacketOfDataTypeA *psPacketOfDataTypeA;
		tsListOfConOfDataTypeA *psListOfConOfDataTypeA;	
		tsPacketOfGPS *psPacketOfGPS;	
		
	
		while( IsRingFIFO_Empty( &InsRingFIFO_GPS ) == 0 )				// 若FIFO非空
		{
				// 从数据FIFO中获取数据
				InsRingFIFO_GPS.pFuncRead( &InsRingFIFO_GPS, 
																	 (void **)&psPacketOfDataTypeA, 
																	 &u32PacketType, 
																	 NULL );
			
				psListOfConOfDataTypeA = psPacketOfDataTypeA->pPacketOfData;
				psPacketOfGPS = psListOfConOfDataTypeA->pContentOfData;
			
				memcpy( (uint8_t *)&(sAggregateOfGPS.sPacketOfGPS_Array[sAggregateOfGPS.u16Index]),
								(uint8_t *)psPacketOfGPS,
								sizeof(tsPacketOfGPS)
							);
				sAggregateOfGPS.u16Index++;
				if( sAggregateOfGPS.u16Index >= 28 )
				{
						// sAggregateOfGPS.u16Index为28表明此队列已满。
						// 替换策略
						sAggregateOfGPS.u16Index = 27;		// 简单的覆盖策略。
				}
		 }
}
