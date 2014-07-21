//*****************************************************************************
//
// ringFifo.c - Ring FIFO management utilities.
//
// 
//
//*****************************************************************************

#include "stm32f10x.h"
#include "ringFifo.h"


//tRingFIFO_Object	InsRingFIFO;

//*****************************************************************************
//
//! \addtogroup ringFIFO_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Define NULL, if not already defined.
//
//*****************************************************************************
#ifndef NULL
#define NULL                    ((void *)0)
#endif


//*****************************************************************************
//
//! Determines whether the ring buffer whose pointers and size are provided
//! is full or not.
//!
//! \param ptRingBuf is the ring buffer object to empty.
//!
//! This function is used to determine whether or not a given ring buffer is
//! full.  The structure is specifically to ensure that we do not see
//! warnings from the compiler related to the order of volatile accesses
//! being undefined.
//!
//! \return Returns \b true if the buffer is full or \b false otherwise.
//
//*****************************************************************************
uint32_t
IsRingFIFO_Full( tRingFIFO_Object *ptRingFIFO )
{
    uint32_t u32Write;
    uint32_t u32Read;

    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Copy the Read/Write indices for calculation.
    //
    u32Write = ptRingFIFO->u32WriteIndex;
    u32Read = ptRingFIFO->u32ReadIndex;

    //
    // Return the full status of the buffer.
    //
    return((((u32Write + 1) % ptRingFIFO->u32Size) == u32Read) ? 1 : 0);
}

//*****************************************************************************
//
//! Determines whether the ring buffer whose pointers and size are provided
//! is empty or not.
//!
//! \param ptRingBuf is the ring buffer object to empty.
//!
//! This function is used to determine whether or not a given ring buffer is
//! empty.  The structure is specifically to ensure that we do not see
//! warnings from the compiler related to the order of volatile accesses
//! being undefined.
//!
//! \return Returns \b true if the buffer is empty or \b false otherwise.
//
//*****************************************************************************
uint32_t 
IsRingFIFO_Empty( tRingFIFO_Object *ptRingFIFO )
{
    uint32_t u32Write;
    uint32_t u32Read;

    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Copy the Read/Write indices for calculation.
    //
    u32Write = ptRingFIFO->u32WriteIndex;
    u32Read = ptRingFIFO->u32ReadIndex;

    //
    // Return the empty status of the buffer.
    //
    return((u32Write == u32Read) ? 1 : 0);
}

//*****************************************************************************
//
//! Empties the ring buffer.
//!
//! \param ptRingBuf is the ring buffer object to empty.
//!
//! Discards all data from the ring buffer.
//!
//! \return None.
//
//*****************************************************************************
void 
RingFIFO_Flush( tRingFIFO_Object *ptRingFIFO )
{
    uint32_t bIntsOff;

    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Set the Read/Write pointers to be the same. Do this with interrupts
    // disabled to prevent the possibility of corruption of the read index.
    //
//	bIntsOff = 0;
//	__disable_irq();

    ptRingFIFO->u32ReadIndex = ptRingFIFO->u32WriteIndex;
    if(!bIntsOff)
    {
//		__enable_irq();
    }
}


//*****************************************************************************
//
//! Reads a single byte of data from a ring buffer.
//!
//! \param ptRingBuf points to the ring buffer to be written to.
//!
//! This function reads a single byte of data from a ring buffer.
//!
//! \return The byte read from the ring buffer.
//
//*****************************************************************************
void  
RingFIFO_Read( tRingFIFO_Object *ptRingFIFO, 
			   void **pPopData, 
			   uint32_t *pu32DataType, 
			   void *(*pfUsr)(void *, uint32_t, uint32_t) )
{
    uint32_t u32Temp;

    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Verify that space is available in the buffer.
    //
//    ASSERT(RingBufUsed(ptRingBuf) != 0);

	if( IsRingFIFO_Empty( ptRingFIFO ) == 1 )
	{
		pPopData = NULL;
		return;
	}

    //
    // Pop one FIFO data.
    //
	*pu32DataType = ptRingFIFO->ArrayElementOfFIFO_Object[ptRingFIFO->u32ReadIndex].u32ElementType;
    *pPopData = ptRingFIFO->ArrayElementOfFIFO_Object[ptRingFIFO->u32ReadIndex].pElementData;

    //
    // Increment the read index.
    //
    //
    // Turn interrupts off temporarily.
    //
//    bIntsOff = IntMasterDisable();
//	bIntsOff = 0;
//	__disable_irq();

    //
    // Update the FIFO readindex.
    //
    ptRingFIFO->u32ReadIndex++;

    //
    // Correct for wrap. We use a loop here since we don't want to use a
    // modulus operation with interrupts off but we don't want to fail in
    // case ulDelta is greater than ulSize (which is extremely unlikely but...)
    //
    while(ptRingFIFO->u32ReadIndex >= ptRingFIFO->u32Size)
    {
        ptRingFIFO->u32ReadIndex -= ptRingFIFO->u32Size;
    }

    //
    // Restore the interrupt state
    //
//    if(!bIntsOff)
//    {
////        IntMasterEnable();
//		__enable_irq();
//    }

    //
    // Return .
    //
    return;
}


//*****************************************************************************
//
//! Writes a single byte of data to a ring buffer.
//!
//! \param ptRingBuf points to the ring buffer to be written to.
//! \param ucData is the byte to be written.
//!
//! This function writes a single byte of data into a ring buffer.
//!
//! \return None.
//
//*****************************************************************************
void  
RingFIFO_Write( tRingFIFO_Object *ptRingFIFO, 
				void *pPushData, 
				uint32_t u32DataType, 
				void *(*pfUsr)(void *, uint32_t, uint32_t) )
{
    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Verify that space is available in the buffer.
    //
//    ASSERT(RingBufFree(ptRingBuf) != 0);

	if( pfUsr != NULL )
	{
		pPushData = (*pfUsr)(pPushData, u32DataType, ptRingFIFO->u32WriteIndex);
	}

    //
    // Write the data byte.
    //
	ptRingFIFO->ArrayElementOfFIFO_Object[ptRingFIFO->u32WriteIndex].u32ElementType = u32DataType;
	ptRingFIFO->ArrayElementOfFIFO_Object[ptRingFIFO->u32WriteIndex].pElementData = pPushData;

    //
    // Increment the write index.
    //

    // Turn interrupts off temporarily.
    //
//    bIntsOff = IntMasterDisable();
//	bIntsOff = 0;
//	__disable_irq();

    //
    // Update the FIFO readindex.
    //
    ptRingFIFO->u32WriteIndex++;

    //
    // Correct for wrap. We use a loop here since we don't want to use a
    // modulus operation with interrupts off but we don't want to fail in
    // case ulDelta is greater than ulSize (which is extremely unlikely but...)
    //
    while(ptRingFIFO->u32WriteIndex >= ptRingFIFO->u32Size)
    {
        ptRingFIFO->u32WriteIndex -= ptRingFIFO->u32Size;
    }

    //
    // Restore the interrupt state
    //
//    if(!bIntsOff)
//    {
////        IntMasterEnable();
//		__enable_irq();
//    }

}


//*****************************************************************************
//
//! Initialize a ring buffer object.
//!
//! \param ptRingBuf points to the ring buffer to be initialized.
//! \param pucBuf points to the data buffer to be used for the ring buffer.
//! \param ulSize is the size of the buffer in bytes.
//!
//! This function initializes a ring buffer object, preparing it to store data.
//!
//! \return None.
//
//*****************************************************************************
void 
RingFIFO_Init( tRingFIFO_Object *ptRingFIFO, uint32_t u32DataType, void (*pfUsr)(uint32_t) )
{
    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);
//    ASSERT(pucBuf != NULL);
//    ASSERT(ulSize != 0);

    //
    // Initialize the ring buffer object.
    //
    ptRingFIFO->u32Size = 16;
//    ptRingFIFO->pFIFO_DataBuf = FIFO_DataBuf;

    ptRingFIFO->u32WriteIndex = ptRingFIFO->u32ReadIndex = 0;

	ptRingFIFO->pFuncRead =	(void(*)(void *, void **, uint32_t *, void *(*pfUsr)(void *, uint32_t, uint32_t)))RingFIFO_Read;
	ptRingFIFO->pFuncWrite = (void (*)(void *, void *, uint32_t, void *(*pfUsr)(void *, uint32_t, uint32_t)))RingFIFO_Write;
	// pFuncIntrinsic points to RingFIFO_Init firstly. 
	ptRingFIFO->pFuncIntrinsic = RingFIFO_Init;

	if( pfUsr != NULL )
	{
		(*pfUsr)(u32DataType);
	}
}


//*****************************************************************************
//
//! 
//! 
//!
//! 
//!
//!
//! \return Returns \b true if the buffer is full or \b false otherwise.
//
//*****************************************************************************
uint32_t
IsRingFIFO_MoreThanOne( tRingFIFO_Object *ptRingFIFO )
{
    uint32_t u32Write;
    uint32_t u32Read;

    //
    // Check the arguments.
    //
//    ASSERT(ptRingBuf != NULL);

    //
    // Copy the Read/Write indices for calculation.
    //
    u32Write = ptRingFIFO->u32WriteIndex;
    u32Read = ptRingFIFO->u32ReadIndex;

    if( u32Write > u32Read )
		{
				if( (u32Write - u32Read) > 1 )
				{
						return 1;
				}
				else
				{
						return 0;
				}
		}
		else if( u32Write < u32Read )
		{
						 if( (u32Write + ptRingFIFO->u32Size - u32Read) > 1 )
						 {
								 return 1;
						 }
						 else
						 {
								 return 0;
						 }
		}
		else
		{
				return 0;
		}
			
		//
    // Return the full status of the buffer.
    //
    //return((((u32Write + 1) % ptRingFIFO->u32Size) == u32Read) ? 1 : 0);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
