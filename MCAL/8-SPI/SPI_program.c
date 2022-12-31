/**
 * @file SPI_program.c
 *
 * @brief A source file including functions for SPI.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

/* Static pointer to the passed string needed to be sent using the Asynchronous transmitting function */
static u8 *SPI_Pu8TransmittedString;

/* Static pointer to the passed array needed to be filled using the Asynchronous receiving function */
static u8 *SPI_Pu8ReceivedString;

/* Static variable that will be equal the required length of the received msg */
static u8 SPI_u8NoOfBytes;

/* Incremented index using in asynchronous transmitting and receiving */
static u8 SPI_u8Index;

/* Static Global callback function which refers to the function needed to be called after finishing transmission the buffer */
static void (*PtrASynchCallback)(void) = NULL;

/*========================== Functions ==========================*/

/**
 * @brief A function to initialize the SPI module.
 * @param void
 * @return void
 */
void SPI_VidInit()
{
    if (SPI_SELECTROLE == SPI_MASTER)
    {
        SET_BIT(SPCR, SPCR_MSTR);
    }

    if (SPI_DATA_ORDER == SPI_LSB)
    {
        SET_BIT(SPCR, SPCR_DORD);
    }

    if (SPI_CLKPOL == SPI_FALLINGEDGE)
    {
        SET_BIT(SPCR, SPCR_CPOL);
    }

    if (SPI_CLKPHASE == SPI_SETUP)
    {
        SET_BIT(SPCR, SPCR_CPHA);
    }

    SPCR |= SPI_SPRBITS;

    /* if Double SPI Speed is selected */
    if (SPI_CLKRATE > 3)
    {
        SET_BIT(SPSR, SPSR_SPI2X);
    }

    SET_BIT(SPCR, SPCR_SPE);
}

/**
 * @brief A function to send and receive a byte using SPI.
 * @param Copy_u8SentData The data needed to be sent.
 * @param Copy_Pu8ReceivedData A pointer to the variable needed to be filled with the received data.
 * @return u8 The error state.
 */
u8 SPI_u8TranceiveByteSynch(u8 Copy_u8SentData, u8 *Copy_Pu8ReceivedData)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_ERROR;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;

    if (Copy_Pu8ReceivedData != NULL)
    {
        Local_u8ErrorState = STATUS_OK;

        /* Send the data */
        SPDR = Copy_u8SentData;

        /* Wait until the transmission is complete */
        while ((GET_BIT(SPSR, SPSR_SPIF) == 0) && Local_u16Timeout < SPI_TIMEOUT)
        {
            Local_u16Timeout++;
        }

        /* Check if the transmission is complete */
        if (Local_u16Timeout >= SPI_TIMEOUT)
        {
            Local_u8ErrorState = STATUS_ERROR;
        }

        /* Receive the data */
        *Copy_Pu8ReceivedData = SPDR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send a string using SPI in Asynchronous mode.
 * @param Copy_pu8SentBuffer A pointer to the string needed to be sent.
 * @param Copy_u8RecBuffer A pointer to the array needed to be filled with the received data.
 * @param Copy_u8NoOfBytes The length of the string.
 * @return u8 The error state.
 */
u8 SPI_u8SendReceiveBuffer_Asynch(u8 *Copy_pu8SentBuffer, u8 *Copy_Pu8RecBuffer, u8 Copy_u8NoOfBytes, void (*CallBack)(void))
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_ERROR;

    if (Copy_pu8SentBuffer != NULL && Copy_Pu8RecBuffer != NULL && CallBack != NULL)
    {
        Local_u8ErrorState = STATUS_OK;

        /* Initialize the static variables */
        SPI_Pu8TransmittedString = Copy_pu8SentBuffer;
        SPI_Pu8ReceivedString = Copy_Pu8RecBuffer;
        SPI_u8NoOfBytes = Copy_u8NoOfBytes;
        SPI_u8Index = 0;

        /* Initialize the callback function */
        PtrASynchCallback = CallBack;

        /* Enable the SPI interrupt */
        SET_BIT(SPCR, SPCR_SPIE);
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/*========================== Functions ==========================*/

void __vector_12(void)
{
    SPI_Pu8ReceivedString[SPI_u8Index] = SPDR;
    if (SPI_u8Index == SPI_u8NoOfBytes)
    {
        SPI_u8Index = 0;
        SPI_u8NoOfBytes = 0;
        CLEAR_BIT(SPCR, SPCR_SPIE);
        PtrASychCallback();
    }
    else
    {
        SPI_u8Index++;
        SPDR = SPI_Pu8TransmittedString[SPI_u8Index];
    }
    return;
}
