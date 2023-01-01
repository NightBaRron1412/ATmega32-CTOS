/** @file TWI_program.c
 *
 * @brief A source file including functions for AVR Two wire interface.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Jan 01, 2023
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "TWI_private.h"
#include "TWI_interface.h"
#include "TWI_config.h"

/*========================== Functions ==========================*/

/**
 * @brief A function to initialize the AVR Two wire interface.
 * @param void
 * @return void
 */
void TWI_VidInit(void)
{
    TWBR = TWI_BIT_RATE;

    /* Checking the TWI Prescaler Bits */
    switch (TWI_PRESCALER_BITS)
    {
    case TWI_PRESCALER_1:
        CLR_BIT(TWSR, TWSR_TWPS0);
        CLR_BIT(TWSR, TWSR_TWPS1);
        break;

    case TWI_PRESCALER_4:

        SET_BIT(TWSR, TWSR_TWPS0);
        CLR_BIT(TWSR, TWSR_TWPS1);
        break;

    case TWI_PRESCALER_16:

        CLR_BIT(TWSR, TWSR_TWPS0);
        SET_BIT(TWSR, TWSR_TWPS1);
        break;

    case TWI_PRESCALER_64:

        SET_BIT(TWSR, TWSR_TWPS0);
        SET_BIT(TWSR, TWSR_TWPS1);
        break;
    }

    /* Checking the state of the Acknowledge Bit */
    if (TWI_ACK_BIT_STATE == TWI_ENABLE)
    {
        SET_BIT(TWCR, TWCR_TWEA);
    }

    /* Checking the state of the Two-wire Serial Interface Interrupt */
    if (TWI_INT_STATE == TWI_ENABLE)
    {
        SET_BIT(TWCR, TWCR_TWINT);
    }

    TWAR = TWI_SLAVE_ADDRESS;

    CLR_BIT(TWAR, TWAR_TWGCE);

    /* Checking the state of the recognition of a General Call given over the Two-wire Serial Bus */
    if (TWI_GEN_CALL_RECOG_STATE == TWI_ENABLE)
    {
        SET_BIT(TWAR, TWAR_TWGCE);
    }

    SET_BIT(TWCR, TWCR_TWEN);
}

/**
 * @brief A function to send a start condition.
 * @param void
 * @return u8 function error state
 */
u8 TWI_u8Start(void)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;
    SET_BIT(TWCR, TWCR_TWSTA);
    SET_BIT(TWCR, TWCR_TWEN);
    SET_BIT(TWCR, TWCR_TWINT);
    while (GET_BIT(TWCR, TWCR_TWINT) == 0 && Local_u16Timeout < TWI_TIMEOUT)
    {
        Local_u16Timeout++;
    }

    if (TWSR & 0xF8 != TWI_START || Local_u16Timeout == TWI_TIMEOUT)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        /* Clearing interrupt flag */
        SET_BIT(TWCR, TWCR_TWINT);
    }

    /* Return error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send Address and operation.
 * @param Copy_u8Address The address of the slave.
 * @param Copy_u8Operation The operation to be done (Read or Write).
 * @return u8 function error state
 */
u8 TWI_u8SendAddress(u8 Copy_u8Address, u8 Copy_u8Operation)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;

    if (Copy_u8Operation == TWI_READ)
    {
        SET_BIT(Copy_u8Address, 0);
    }
    else if (Copy_u8Operation == TWI_WRITE)
    {
        CLR_BIT(Copy_u8Address, 0);
    }

    /* Write address to data register */
    TWDR = Copy_u8Address;

    /* Clear start condition */
    CLR_BIT(TWCR, TWCR_TWSTA);

    /* Clear flag so TWI start its job */
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait till Job is finished */
    while (GET_BIT(TWCR, TWCR_TWINT) == 0 && Local_u16Timeout < TWI_TIMEOUT)
    {
        Local_u16Timeout++;
    }

    if ((TWSR & 0xF8 != TWI_MT_SLA_W_ACK) && (TWSR & 0xF8 != TWI_MT_SLA_W_NACK) || Local_u16Timeout == TWI_TIMEOUT)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        /* Clearing interrupt flag */
        SET_BIT(TWCR, TWCR_TWINT);
    }

    /* Return error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send data.
 * @param Copy_u8Data The data to be sent.
 * @return u8 function error state
 */
u8 TWI_u8Write(u8 Copy_u8Data)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;

    /* Write data to data register */
    TWDR = Copy_u8Data;
    SET_BIT(TWCR, TWCR_TWINT);
    while (GET_BIT(TWCR, TWCR_TWINT) == 0 && Local_u16Timeout < TWI_TIMEOUT)
    {
        Local_u16Timeout++;
    }

    if (((TWSR & 0xF8 != TWI_MT_DATA_ACK) && (TWSR & 0xF8 != TWI_MT_DATA_NACK)) || Local_u16Timeout == TWI_TIMEOUT)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        /* Clearing interrupt flag */
        SET_BIT(TWCR, TWCR_TWINT);
    }

    /* Return error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to read a byte.
 * @param Pu8RecData Pointer to the variable to hold the received data.
 * @return u8 function error state
 */
u8 TWI_u8ReadByte(u8 *Pu8RecData)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;

    if (Pu8RecData == NULL)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }
    else
    {
        SET_BIT(TWCR, TWCR_TWINT);
        SET_BIT(TWCR, TWCR_TWEN);
        while (GET_BIT(TWCR, TWCR_TWINT) == 0 && Local_u16Timeout < TWI_TIMEOUT)
        {
            Local_u16Timeout++;
        }

        if (Local_u16Timeout == TWI_TIMEOUT)
        {
            Local_u8ErrorState = STATUS_ERROR;
        }

        else
        {
            *Pu8RecData = TWDR;
        }
    }

    /* Return error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to send a stop condition.
 * @param void
 * @return u8 function error state
 */
u8 TWI_u8Stop(void)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local variable to hold the timeout counter */
    u16 Local_u16Timeout = 0;

    SET_BIT(TWCR, TWCR_TWINT);
    SET_BIT(TWCR, TWCR_TWSTO);
    SET_BIT(TWCR, TWCR_TWEN);
    while (GET_BIT(TWCR, TWCR_TWSTO) == 1)
    {
        Local_u16Timeout++;
    }

    if (Local_u16Timeout == TWI_TIMEOUT)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return error state */
    return Local_u8ErrorState;
}

/*========================== ISR ==========================*/

void __vector_19(void)
{
}
