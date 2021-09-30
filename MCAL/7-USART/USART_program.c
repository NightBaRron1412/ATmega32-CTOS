#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "USART_private.h"
#include "USART_interface.h"
#include "USART_config.h"

void USART_VidInit()
{
#if (USART_MODE == USART_NORMAL_MODE)

    UBRRL = UBRR_Value;
    UBRRH = (UBRR_Value >> 8);

    /* Checking the transmitter state */
    if (USART_TX_STATE == USART_ENABLE)
        SET_BIT(UCSRB, UCSRB_TXEN);

    /* Checking the receiver state */
    if (USART_RX_STATE == USART_ENABLE)
        SET_BIT(UCSRB, UCSRB_RXEN);

    /* Checking the parity type */
    if (USART_PARITY == USART_EVEN_PARITY)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UPM1);
    }

    else if (USART_PARITY == USART_ODD_PARITY)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UPM1) | (1 << UCSRC_UPM0);
    }

    /* Checking the number of stop bits */
    if (USART_NO_OF_STP_BITS == USART_TWO_BITS)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_USBS);
    }

    /* Checking the required character size */
    switch (USART_DATA_SIZE)
    {
    case USART_FIVE_BITS:
        break;

    case USART_SIX_BITS:
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ0);

        break;

    case USART_SEVEN_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1);

        break;

    case USART_EIGHT_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0);

        break;

    case USART_NINE_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0);
        SET_BIT(UCSRB, UCSRB_UCSZ2);

        break;
    }

#elif (USART_MODE == USART_DBL_SPD_MODE)

    SET_BIT(UCSRA, UCSRA_U2X);

    UBRRL = UBRR_Value2X;
    UBRRH = (UBRR_Value2X >> 8);

    /* Checking the transmitter state */
    if (USART_TX_STATE == USART_ENABLE)
        SET_BIT(UCSRB, UCSRB_TXEN);

    /* Checking the receiver state */
    if (USART_RX_STATE == USART_ENABLE)
        SET_BIT(UCSRB, UCSRB_RXEN);

    /* Checking the parity type */
    if (USART_PARITY == USART_EVEN_PARITY)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UPM1);
    }

    else if (USART_PARITY == USART_ODD_PARITY)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UPM1) | (1 << UCSRC_UPM0);
    }

    /* Checking the number of stop bits */
    if (USART_NO_OF_STP_BITS == USART_TWO_BITS)
    {
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_USBS);
    }

    /* Checking the required character size */
    switch (USART_DATA_SIZE)
    {
    case USART_FIVE_BITS:
        break;

    case USART_SIX_BITS:
        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ0);

        break;

    case USART_SEVEN_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1);

        break;

    case USART_EIGHT_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0);

        break;

    case USART_NINE_BITS:

        UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0);
        SET_BIT(UCSRB, UCSRB_UCSZ2);

        break;
    }
#endif
}

void USART_VidSendByte(u8 Copy_u8Data)
{
    /* Put data into buffer, sends the data */
    UDR = Copy_u8Data;

    while (GET_BIT(UCSRA, UCSRA_UDRE) == 0)
        ;
}

u8 USART_u8ReceiveByte()
{
    while (GET_BIT(UCSRA, UCSRA_RXC) == 0)
        ;
    return UDR;
}

void USART_VidSendString(u8 *Copy_u8String)
{
    while (*Copy_u8String != '\0')
    {
        USART_VidSendByte(*Copy_u8String);
        Copy_u8String++;
    }
}

void USART_VidReceiveString(u8 *Copy_u8String)
{
    u8 i = 0;
    Copy_u8String[i] = USART_u8ReceiveByte();
    USART_VidSendByte(Copy_u8String[i]);
    while (Copy_u8String[i] != '\r')
    {
        i++;
        Copy_u8String[i] = USART_u8ReceiveByte();
        USART_VidSendByte(Copy_u8String[i]);
    }
    Copy_u8String[i] = '\0';
}
