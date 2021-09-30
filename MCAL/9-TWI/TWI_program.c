#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "TWI_private.h"
#include "TWI_interface.h"
#include "TWI_config.h"

//Function to initialize the TWI peripheral
void TWI_VidInit()
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

void TWI_VidStart()
{
    SET_BIT(TWCR, TWCR_TWINT);
    SET_BIT(TWCR, TWCR_TWSTA);
    SET_BIT(TWCR, TWCR_TWEN);
    while (GET_BIT(TWCR, TWCR_TWINT) == 0)
        ;
}

void TWI_VidStop()
{
    SET_BIT(TWCR, TWCR_TWINT);
    SET_BIT(TWCR, TWCR_TWSTO);
    SET_BIT(TWCR, TWCR_TWEN);
}

void TWI_VidWrite(u8 Copy_u8Data)
{
    TWDR = Copy_u8Data;
    SET_BIT(TWCR, TWCR_TWINT);
    while (GET_BIT(TWCR, TWCR_TWINT) == 0)
        ;
}

u8 TWI_u8Read()
{
    SET_BIT(TWCR, TWCR_TWINT);
    SET_BIT(TWCR, TWCR_TWEN);
    while (GET_BIT(TWCR, TWCR_TWINT) == 0)
        ;
    return TWDR;
}

u8 TWI_u8Status()
{
    u8 status;
    status = (TWSR & 0xF8);
    return status;
}

void TWI_VidSendAddrres(u8 Cpy_u8Adress, u8 Cpy_u8Operation)
{
    u8 local_address;

    if (Cpy_u8Operation == TWI_READ)
    {
        local_address = ((Cpy_u8Adress << 1) | 1);
    }
    else if (Cpy_u8Operation == TWI_WRITE)
    {
        local_address = ((Cpy_u8Adress << 1) | 0);
    }

    /* Write address to data register */
    TWDR = local_address;

    /* Clear start condition */
    CLR_BIT(TWCR, TWCR_TWSTA);

    /* Clear flag so TWI start its job */
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait till Job is finished */
    while (GET_BIT(TWCR, TWCR_TWINT) == 0)
        ;
}

void __vector_19(void)
{
}
