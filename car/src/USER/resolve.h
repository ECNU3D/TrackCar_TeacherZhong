

#ifndef 	_RESOLVE_H_
#define 	_RESOLVE_H_


#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
#include "variables.h"
#include "timer.h"
#include "polygon.h"
#include "ringFifo.h"
#include <math.h>



// extern double head2;//����main�еĴ����������ڸ�.c�п���

void order_sendinit();
double hextodex(u8 reply[]);
double rolltodec(u8 reply[]);
double pitchtodec(u8 reply[]);
void gpggaresolve(u8 gpgga[],u8 *LAT,u8 *LNG);
double longtodouble(u8 data[]);
void pathresolve(u8 gpgga[]);
double pathstopathx(u8 pathr[]);
double pathstopathy(u8 pathr[]);
void move(void);
double getspeed(double sx,double sy);


#endif



