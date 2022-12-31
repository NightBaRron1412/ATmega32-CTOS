/** @file USART_program.c
 *
 * @brief A c file including USART functions implementations
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "USART_private.h"
#include "USART_interface.h"
#include "USART_config.h"

/* Static pointer to the passed string needed to be sent using the Asynchronous transmitting function */
static u8 *USART_Pu8TransmittedString;

/* Static pointer to the passed array needed to be filled using the Asynchronous receiving function */
static u8 *USART_Pu8ReceivedString;

/* Static variable that will be equal the required length of the received msg */
static u8 USART_u8ReceivedMsgSize;

/* Incremented index using in asynchronous transmitting and receiving */
static u8 USART_u8Index;

static void (*PtrASychCallback)(void) = NULL;

/*========================== Functions ==========================*/

/**
 * @brief A function to initialize USART.
 * @param void
 * @return void
 */
void USART_VidInit()
{
#if (USART_MODE == USART_NORMAL_MODE)

    UBRRL = UBRR_Value;
    UBRRH = (UBRR_Value >> 8);

    /* Checking the transmitter state */
    if (USART_TX_STATE == USART_ENABLE)
    {
        SET_BIT(UCSRB, UCSRB_TXEN);
    }

    /* Checking the receiver state */
    if (USART_RX_STATE == USART_ENABLE)
    {
        SET_BIT(UCSRB, UCSRB_RXEN);
    }

    /* Checking the parity type */
    if (USART_PARITY == USART_EVEN_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UPM1);
        CLR_BIT(UCSRC, UCSRC_UPM0);
    }

    else if (USART_PARITY == USART_ODD_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UPM1);
        SET_BIT(UCSRC, UCSRC_UPM0);
    }

    else if (USART_PARITY == USART_NO_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UPM1);
        CLR_BIT(UCSRC, UCSRC_UPM0);
    }

    /* Checking the number of stop bits */
    if (USART_NO_OF_STP_BITS == USART_TWO_BITS)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_USBS);
    }

    else if (USART_NO_OF_STP_BITS == USART_ONE_BIT)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_USBS);
    }

    /* Checking the required character size */
    switch (USART_DATA_SIZE)
    {
    case USART_FIVE_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UCSZ0);
        CLR_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_SIX_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        CLR_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_SEVEN_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_EIGHT_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_NINE_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        SET_BIT(UCSRB, UCSRB_UCSZ2);
        break;
    }

#elif (USART_MODE == USART_DBL_SPD_MODE)

    /* Setting the U2X bit to enable double speed mode */
    SET_BIT(UCSRA, UCSRA_U2X);

    /* Setting the baud rate */
    UBRRL = UBRR_Value2X;
    UBRRH = (UBRR_Value2X >> 8);

    /* Checking the transmitter state */
    if (USART_TX_STATE == USART_ENABLE)
    {
        SET_BIT(UCSRB, UCSRB_TXEN);
    }

    /* Checking the receiver state */
    if (USART_RX_STATE == USART_ENABLE)
    {
        SET_BIT(UCSRB, UCSRB_RXEN);
    }

    /* Checking the parity type */
    if (USART_PARITY == USART_EVEN_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UPM1);
        CLR_BIT(UCSRC, UCSRC_UPM0);
    }

    else if (USART_PARITY == USART_ODD_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UPM1);
        SET_BIT(UCSRC, UCSRC_UPM0);
    }

    else if (USART_PARITY == USART_NO_PARITY)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UPM1);
        CLR_BIT(UCSRC, UCSRC_UPM0);
    }

    /* Checking the number of stop bits */
    if (USART_NO_OF_STP_BITS == USART_TWO_BITS)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_USBS);
    }

    else if (USART_NO_OF_STP_BITS == USART_ONE_BIT)
    {
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_USBS);
    }

    /* Checking the required character size */
    switch (USART_DATA_SIZE)
    {
    case USART_FIVE_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UCSZ0);
        CLR_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_SIX_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        CLR_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_SEVEN_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        CLR_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_EIGHT_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
        break;

    case USART_NINE_BITS:
        SET_BIT(UCSRC, UCSRC_URSEL);
        SET_BIT(UCSRC, UCSRC_UCSZ0);
        SET_BIT(UCSRC, UCSRC_UCSZ1);
        SET_BIT(UCSRB, UCSRB_UCSZ2);
        break;
    }
#endif
}

/**
 * @brief A function to send a byte using USART.
 * @param Copy_u8Data The data to be sent.
 * @return u8 The status of the function.
 */
u8 USART_u8SendByte(u8 Copy_u8Data)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the Timeout */
    u16 Local_u16TimeOut = 0;

    /* Put data into buffer, sends the data */
    UDR = Copy_u8Data;

    /* Wait for empty transmit buffer */
    while ((GET_BIT(UCSRA, UCSRA_UDRE) == 0) && (Local_u16TimeOut < USART_TIMEOUT))
    {
        Local_u16TimeOut++;
    }
    if (Local_u16TimeOut == USART_TIMEOUT)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send a string using USART in synchronous mode.
 * @param Copy_u8String The string to be sent.
 * @return u8 The status of the function.
 */
u8 USART_VidSendStringSynch(u8 *Copy_u8String)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the Timeout */
    u16 Local_u16TimeOut = 0;

    if (Copy_u8String != NULL)
    {
        /* Loop until null character is reached */
        while (*Copy_u8String != '\0')
        {
            /* Put data into buffer, sends the data */
            UDR = *Copy_u8String;

            /* Wait for empty transmit buffer */
            while ((GET_BIT(UCSRA, UCSRA_UDRE) == 0) && (Local_u16TimeOut < USART_TIMEOUT))
            {
                Local_u16TimeOut++;
            }
            if (Local_u16TimeOut == USART_TIMEOUT)
            {
                Local_u8ErrorState = STATUS_ERROR;
                break;
            }

            /* Increment the string pointer */
            Copy_u8String++;
        }
    }

    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send a string using USART in asynchronous mode.
 * @param Copy_u8String The string to be sent.
 * @param Callback The function to be called when the transmission is done.
 * @return u8 The status of the function.
 */
u8 USART_VidSendStringAsynch(u8 *Copy_u8String, void (*Callback)(void))
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8String != NULL && Callback != NULL)
    {
        /* Resetting the index */
        USART_u8Index = 0;

        /* Save the string pointer */
        USART_Pu8TransmittedString = Copy_u8String;

        /* Save the callback function */
        PtrASychCallback = Callback;

        /* Enable the data register empty interrupt */
        SET_BIT(UCSRB, UCSRB_UDRIE);
    }

    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to receive a byte using USART.
 * @param Copy_u8Byte The byte to be received.
 * @return u8 The status of the function.
 */
u8 USART_u8ReceiveByte(u8 *Copy_u8Byte)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the Timeout */
    u16 Local_u16TimeOut = 0;

    if (Copy_u8Byte != NULL)
    {
        /* Wait for data to be received */
        while ((GET_BIT(UCSRA, UCSRA_RXC) == 0) && (Local_u16TimeOut < USART_TIMEOUT))
        {
            Local_u16TimeOut++;
        }
        if (Local_u16TimeOut == USART_TIMEOUT)
        {
            Local_u8ErrorState = STATUS_ERROR;
        }

        else
        {
            /* Get and return received data from buffer */
            *Copy_u8Byte = UDR;
        }
    }

    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to receive a string using USART in synchronous mode.
 * @param Copy_u8String The string to be received.
 * @return u8 The status of the function.
 */
u8 USART_VidReceiveStringSynch(u8 *Copy_u8String)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to be used as an iterator */
    u8 Local_u8Iterator = 0;

    /* Local variable to hold the Timeout */
    u16 Local_u16TimeOut = 0;

    if (Copy_u8String != NULL)
    {
        while (Copy_u8String[Local_u8Iterator] != '\r')
        {
            /* Wait for data to be received */
            while ((GET_BIT(UCSRA, UCSRA_RXC) == 0) && (Local_u16TimeOut < USART_TIMEOUT))
            {
                Local_u16TimeOut++;
            }
            if (Local_u16TimeOut == USART_TIMEOUT)
            {
                Local_u8ErrorState = STATUS_ERROR;
                break;
            }

            else
            {
                /* Get and return received data from buffer */
                Copy_u8String[Local_u8Iterator] = UDR;
            }

            /* Increment the iterator */
            Local_u8Iterator++;
        }

        /* Add the null character at the end of the string */
        Copy_u8String[Local_u8Iterator] = '\0';
    }

    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to receive a string using USART in asynchronous mode.
 * @param Copy_u8String The string to be received.
 * @param Callback The function to be called when the reception is done.
 * @return u8 The status of the function.
 */
u8 USART_VidReceiveStringAsynch(u8 *Copy_u8String, void (*Callback)(void))
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8String != NULL && Callback != NULL)
    {
        /* Resetting the index */
        USART_u8Index = 0;

        /* Save the string pointer */
        USART_Pu8ReceivedString = Copy_u8String;

        /* Save the callback function */
        PtrASychCallback = Callback;

        /* Enable the register empty interrupt */
        SET_BIT(UCSRB, UCSRB_UDRIE);
    }

    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/*========================== ISRs ==========================*/

/* The ISR of USART, Rx Complete interrupt */
void __vector_13(void)
{
    /* Save the received data in the string */
    USART_Pu8ReceivedString[USART_u8Index] = UDR;

    /* Increment the index */
    USART_u8Index++;

    /* Check if the received data is the end of the string */
    if (USART_Pu8ReceivedString[USART_u8Index - 1] == '\r')
    {
        /* Reset the index */
        USART_u8Index = 0;

        /* Add the null character at the end of the string */
        USART_Pu8ReceivedString[USART_u8Index] = '\0';

        /* Disable the receive complete interrupt */
        CLR_BIT(UCSRB, UCSRB_RXCIE);

        /* Call the callback function */
        PtrASychCallback();
    }
}

/* The ISR of USART Data Register Empty interrupt */
void __vector_14(void)
{
    /* Put data into buffer, sends the data */
    UDR = USART_Pu8TransmittedString[USART_u8Index];

    /* Increment the index */
    USART_u8Index++;

    /* Check if the end of the string is reached */
    if (USART_Pu8TransmittedString[USART_u8Index] == '\0')
    {
        /* Reset the index */
        USART_u8Index = 0;

        /* Disable the data register empty interrupt */
        CLR_BIT(UCSRB, UCSRB_UDRIE);

        /* Call the callback function */
        PtrASychCallback();
    }
}

/* The ISR of USART, Tx Complete interrupt */
void __vector_15(void)
{
    /* Do nothing */
}