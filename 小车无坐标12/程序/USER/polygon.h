
#ifndef 	_POLYGON_H_
#define 	_POLYGON_H_

//#include "lpc17xx_libcfg.h"

#include "ringFifo.h"

// extern double head2;//声明main中的传感器变量在该.c中可用

typedef __packed struct{
			   uint8_t	u8Longitude[3];
			   uint8_t	u8Latitude[3];
				}tsVertex;

typedef __packed struct{
			   uint8_t	u8Motive;
			   uint8_t	u8ID[4];
			   tsVertex sVertex[16];
			  }tsContentOfCmdC_C4;

typedef __packed struct{
			   uint8_t	u8NumOfVertex;
			   uint8_t	u8ID[4];
			  }tsSysPolygonInfo;

typedef __packed struct{
			   uint16_t u16Time_YY;
			   uint16_t u16Time_MM;
			   uint16_t u16Time_DD;
				 uint16_t u16Time_hh;
			   uint16_t u16Time_mm;
			   uint16_t u16Time_ss;
			   uint16_t u16Time_ms;
			   uint8_t	u8ID[4];
			   }tsContentOfCmdA_A7;


typedef struct{
		double x,y;
}MakestrMapNode;

extern tRingFIFO_Object	InsRingFIFO_AREA;

extern tsContentOfCmdA_A7 sContentOfCmdA_A7;
extern MakestrMapNode ptPolygon[16];

void GaussProjCal(double longitude, double latitude, double *X, double *Y);

void TranslateLTude(tsContentOfCmdC_C4 *psContentOfCmdC_C4, uint32_t u32Count);

char PtInPolygon (MakestrMapNode *pMapNode, int nCount);

void changeformat(double flongitude,double flatitude,double *longitude,double *latitude);

double getheading(double x1,double y1,double x2,double y2);

void changedirections(double x3,double y3,double x1,double y1,double x2,double y2);

void gettoorbit(double fai,double fai1);

void lright(void);
void lleft(void);
void ldr(void);
void bright(void);
void bleft(void);

#endif

