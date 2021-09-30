#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

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

    //if Double SPI Speed is selected
    if (SPI_CLKRATE > 3)
        SET_BIT(SPSR, SPSR_SPI2X);

    SET_BIT(SPCR, SPCR_SPE);
}

void SPI_VidSendByte(u8 Copy_u8Data)
{
    SPDR = Copy_u8Data;
    while (GET_BIT(SPSR, SPSR_SPIF) == 0)
        ;
}

u8 SPI_u8ReceiveByte()
{
    while (GET_BIT(SPSR, SPSR_SPIF) == 0)
        ;
    return SPDR;
}

u8 SPI_u8TranceiveByte(u8 Copy_u8Data)
{
    SPDR = Copy_u8Data;
    
    while (GET_BIT(SPSR, SPSR_SPIF) == 0)
        ;

    return SPDR;
}

void SPI_VidSendString(u8 *Copy_String)
{
    while (*Copy_String)
    {
        SPI_VidSendByte(*Copy_String);
        Copy_String++;
    }
}

void SPI_VidReceiveString(u8 *Copy_String)
{
    u8 i = 0;
    Copy_String[i] = SPI_u8ReceiveByte();
    while (Copy_String[i] != '#')
    {
        i++;
        Copy_String[i] = SPI_u8ReceiveByte();
    }
    Copy_String[i] = '\0';
}

/* The ISR of Serial Transfer Complete */
void __vector_12(void)
{
}
