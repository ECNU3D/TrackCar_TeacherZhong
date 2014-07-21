
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

// InsRingFIFO_GPS��ΪGPS�������ݵ�FIFO
tRingFIFO_Object	InsRingFIFO_GPS;

/*************************************************************************
GPS���ݵ�FIFO���ļ��洢������ԣ�
GPS���ݵı������ȼ�������5�ࣺ
1��GPS�ź������ҳ����٣�����<=v��,GPS_AvailLowSpeed��
2��GPS�ź������ҳ��ٴ���V��GPS_AvailNormalSpeed��
3��GPS�ź��������б����¼���GPS_AvailEmergency��
4��GPS�źŲ��������б����¼���GPS_InvaidEmergency��
5��GPS�źŲ�������û�б����¼���GPS_Invaid��
���У���5���κ�����²���SD���ϴ洢GPS���ݡ�
��GPRS�����ߣ����ն˺ͷ�����ͨ���жϺ�GPS���ݰ�һ������洢��SD���С�
SD����GPS������ļ����ݱ������ȼ���4�ࣺ
1��GPS�ź������ҳ����٣�����<=v��,GPS_AvailLowSpeed.dat����Ӧ��¼�ļ�GPS_ALS_Index.txt��
2��GPS�ź������ҳ��ٴ���V��GPS_AvailNormalSpeed.dat����Ӧ��¼�ļ�GPS_ANS_Index.txt��
3��GPS�ź��������б����¼���GPS_AvailEmergency.dat����Ӧ��¼�ļ�GPS_AE_Index.txt��
4��GPS�źŲ��������б����¼���GPS_InvaidEmergency.dat����Ӧ��¼�ļ�GPS_IE_Index.txt��
��¼�ļ���ʽ������ASC��ʽ��¼�ܼ�¼�����ѱ��ͼ�¼�������£�
				Total record��xxxx(9999max)
				Record uploaded:xxxx(9999max)
д�ļ����ԣ�
RAM��4�����ȼ���Ӧ�Ļ�����������ÿ������Ϊ8��tsPacketOfGPS��С��GPRSͨ���жϵ�����£�
ÿ����������������ִ��һ��д�ļ���append����������GPRSͨ�Żָ��󣬲��ܻ����������Ƿ�
����������ִ��һ��д�ļ���append��������ÿ��д�ļ�����ָ����дGPS�����Լ����¼�¼�ļ���
GPRSͨ�Żָ���ı��Ͳ��ԣ�
���͵�ǰGPS����Ϊ�����ȼ�����Ъʱ�䲹�������GPS���ݣ������ȼ��ֱ���4���ļ��е����ݣ�
��������ؼ�¼�ļ���
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
// ����5��ֵ���ɷ�����Զ�̸�������
uint16_t			u16GPS_UploadT0 = 15;
uint16_t			u16GPS_UploadT1 = 90;
uint16_t			u16GPS_UploadT2 = 120;
uint16_t			u16GPS_UploadT3 = 5;
// ����Q8��ʽ����ζ���ж�ʱGPSԭʼ���������2^8=256��
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

					// ÿ24СʱУʱһ��
					if( (SysRTC.HOUR == 0) && 
							(SysRTC.MIN == 0) &&
							(SysRTC.SEC < 5)
						)
					{
							u32BoolEverCalibtated = 0;
					}
					
					// Modified 20120610��
					if( (sPacketOfGPS.u8Status == 'A') && (((sPacketOfGPS.u16Time_YY >> 8) + 2000) > 2030) )
					{
							// ʱ�������쳣
							SYSTEM_DEBUG_DMA_SEND( "\r\nGPS bug fixed!\r\n", 18 );
							sPacketOfGPS.u8Status = 'V';
					}
					// End modification 20120610��	
					
					if( (u32BoolEverCalibtated == 0) && (sPacketOfGPS.u8Status == 'A') )
					{
						u32BoolEverCalibtated = 1;

						// У׼Ƭ��RTC��
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
								// ���ж�Ϊ���ꡣ
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
								// �����������
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
							
						}// End if( i > 23 )		��һ������			   

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

					// �ж��ٶȣ����ڴ˴���������ٶȵ�λ��x0.1��,�Ҳ���Q8��ʽ
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
					
					// Modified 20120725��
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
					// End modification 20120725��	

					// ���GPRSͨ��״�������ϴε�������û�з��ͳɹ���Ϊ�ж����ݡ�
					if( (sInsGPRS_StateMachine.u8Flag & GPRS_SEND_GPS_OK) == GPRS_SEND_GPS_OK )
					{
						 // �ϴη��ͳɹ������־λ
						 sInsGPRS_StateMachine.u8Flag &= (~GPRS_SEND_GPS_OK);
					}
					else
					{
						 // GPRSͨ���쳣
						 switch( u32GPS_UploadCondition )
						 {
						 	case GPS_SIGNAL_AVAIL_LOW_SPEED:
								memcpy( &sPacketGPS_AvailLowSpeed[sGPS_ALS_Index.u16Current++], 
										(uint8_t *)&sPacketOfGPS, 
										sizeof(sPacketOfGPS) );
								if( sGPS_ALS_Index.u16Current >=8 )
								{
									sGPS_ALS_Index.u16Current = 0;
									
									// д�ļ�
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
		
	
		while( IsRingFIFO_Empty( &InsRingFIFO_GPS ) == 0 )				// ��FIFO�ǿ�
		{
				// ������FIFO�л�ȡ����
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
						// sAggregateOfGPS.u16IndexΪ28�����˶���������
						// �滻����
						sAggregateOfGPS.u16Index = 27;		// �򵥵ĸ��ǲ��ԡ�
				}
		 }
}
