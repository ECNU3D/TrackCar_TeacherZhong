//*****************************************************************************
//
// ringbuf.h - Defines and Macros for the ring buffer utilities.
//
// 
//
//*****************************************************************************

#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include "stm32f10x.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif


typedef		uint32_t	tBoolean;
	
//*****************************************************************************
//
// The structure used for encapsulating all the items associated with a
// ring buffer.
//
//*****************************************************************************
typedef struct
{
    //
    // The ring buffer size.
    //
    unsigned long ulSize;

    //
    // The ring buffer write index.
    //
    volatile unsigned long ulWriteIndex;

    //
    // The ring buffer read index.
    //
    volatile unsigned long ulReadIndex;

    //
    // The ring buffer.
    //
    unsigned char *pucBuf;

}
tRingBufObject;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern tBoolean RingBufFull(tRingBufObject *ptRingBuf);
extern tBoolean RingBufEmpty(tRingBufObject *ptRingBuf);
extern void RingBufFlush(tRingBufObject *ptRingBuf);
extern unsigned long RingBufUsed(tRingBufObject *ptRingBuf);
extern unsigned long RingBufFree(tRingBufObject *ptRingBuf);
extern unsigned long RingBufContigUsed(tRingBufObject *ptRingBuf);
extern unsigned long RingBufContigFree(tRingBufObject *ptRingBuf);
extern unsigned long RingBufSize(tRingBufObject *ptRingBuf);
extern unsigned char RingBufReadOne(tRingBufObject *ptRingBuf);
extern void RingBufRead(tRingBufObject *ptRingBuf, unsigned char *pucData,
                        unsigned long ulLength);
extern void RingBufWriteOne(tRingBufObject *ptRingBuf, unsigned char ucData);
extern void RingBufWrite(tRingBufObject *ptRingBuf, unsigned char *pucData,
                         unsigned long ulLength);
extern void RingBufAdvanceWrite(tRingBufObject *ptRingBuf,
                                unsigned long ulNumBytes);
extern void RingBufAdvanceRead(tRingBufObject *ptRingBuf,
                                unsigned long ulNumBytes);
extern void RingBufInit(tRingBufObject *ptRingBuf, unsigned char *pucBuf,
                        unsigned long ulSize);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __RINGBUF_H__
