//*****************************************************************************
//
// ringFifo.h - Defines and Macros for the ring FIFO utilities.
//
// 
//
//*****************************************************************************

#ifndef __RINGFIFO_H__
#define __RINGFIFO_H__


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


typedef struct
{
    //
    // The type of FIFO elemnet.
    //
    uint32_t u32ElementType;

    //
    // The pointer to element databuf.
    //
    void *pElementData;
}
tElementOfFIFO_Object;


//*****************************************************************************
//
// The structure used for encapsulating all the items associated with a
// ring buffer.
//
//*****************************************************************************
typedef struct
{
    //
    // The ring FIFO size.
    //
    uint32_t u32Size;

    //
    // The ring FIFO write index.
    //
    volatile uint32_t u32WriteIndex;

    //
    // The ring FIFO read index.
    //
    volatile uint32_t u32ReadIndex;

//    //
//    // The ring FIFO data.
//    //
//    void **pFIFO_DataBuf;
	tElementOfFIFO_Object ArrayElementOfFIFO_Object[16];

    //
    // The ring FIFO intrinsic function.
    //
    void (*pFuncIntrinsic)();

    //
    // The ring FIFO read function.
    //
		// Modified 20130308!
    //void (*pFuncRead)(void *, void *, uint32_t *, void (*pfUsr)(void **, uint32_t, uint32_t));
		void (*pFuncRead)(void *, void **, uint32_t *, void *(*pfUsr)(void *, uint32_t, uint32_t));
		// End modification 20130308!
		
    //
    // The ring FIFO write function.
    //
		// Modified 20130308!
    //void (*pFuncWrite)(void *, void *, uint32_t, void (*pfUsr)(void **, uint32_t, uint32_t));
		void (*pFuncWrite)(void *, void *, uint32_t, void *(*pfUsr)(void *, uint32_t, uint32_t));
		// End modification 20130308!

}
tRingFIFO_Object;


extern tRingFIFO_Object	InsRingFIFO_Task;
extern tRingFIFO_Object	InsRingFIFO_TAXI;
extern tRingFIFO_Object	InsRingFIFO_GPS;
extern tRingFIFO_Object	InsRingFIFO_RemoteUpdate;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern uint32_t IsRingFIFO_Full( tRingFIFO_Object *ptRingFIFO );

extern uint32_t IsRingFIFO_Empty( tRingFIFO_Object *ptRingFIFO );

extern void RingFIFO_Flush( tRingFIFO_Object *ptRingFIFO );

extern void RingFIFO_Read( tRingFIFO_Object *ptRingFIFO, void **pPopData, 
						   uint32_t *pu32DataType, void *(*pfUsr)(void *, uint32_t, uint32_t) );

extern void RingFIFO_Write( tRingFIFO_Object *ptRingFIFO, void *pPushData, 
							uint32_t u32DataType, void *(*pfUsr)(void *, uint32_t, uint32_t) );

extern void RingFIFO_Init( tRingFIFO_Object *ptRingFIFO, uint32_t u32DataType, void (*pfUsr)(uint32_t) );

extern uint32_t	IsRingFIFO_MoreThanOne( tRingFIFO_Object *ptRingFIFO );

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __RINGBUF_H__
