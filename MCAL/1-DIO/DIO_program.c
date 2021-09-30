#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "DIO_private.h"
#include "DIO_interface.h"

/*------------------------------------Pins functions------------------------------------------------*/

void DIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value) //Setting pin value to High or Low
{
    if (Copy_u8Value == high)
    {
        switch (Copy_u8Port)
        {

        case (Port_A):
            SET_BIT(PORTA, Copy_u8Pin);
            break;
        case (Port_B):
            SET_BIT(PORTB, Copy_u8Pin);
            break;
        case (Port_C):
            SET_BIT(PORTC, Copy_u8Pin);
            break;
        case (Port_D):
            SET_BIT(PORTD, Copy_u8Pin);
            break;
        }
    }

    else if (Copy_u8Value == low)
    {
        switch (Copy_u8Port)
        {

        case (Port_A):
            CLR_BIT(PORTA, Copy_u8Pin);
            break;
        case (Port_B):
            CLR_BIT(PORTB, Copy_u8Pin);
            break;
        case (Port_C):
            CLR_BIT(PORTC, Copy_u8Pin);
            break;
        case (Port_D):
            CLR_BIT(PORTD, Copy_u8Pin);
            break;
        }
    }
}

void DIO_VidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode) //Setting pin mode to Input or Output
{
    //Check for input mode 0 for input
    if (Copy_u8Mode == input)
    {
        //Set pin as input
        switch (Copy_u8Port)
        {

        case (Port_A):
            CLR_BIT(DDRA, Copy_u8Pin);
            break;
        case (Port_B):
            CLR_BIT(DDRB, Copy_u8Pin);
            break;
        case (Port_C):
            CLR_BIT(DDRC, Copy_u8Pin);
            break;
        case (Port_D):
            CLR_BIT(DDRD, Copy_u8Pin);
            break;
        }
    }
    //check for mode 1 for output */

    else if (Copy_u8Mode == output)
    {

        switch (Copy_u8Port)
        {
            //Set pin as output
        case (Port_A):
            SET_BIT(DDRA, Copy_u8Pin);
            break;
        case (Port_B):
            SET_BIT(DDRB, Copy_u8Pin);
            break;
        case (Port_C):
            SET_BIT(DDRC, Copy_u8Pin);
            break;
        case (Port_D):
            SET_BIT(DDRD, Copy_u8Pin);
            break;
        }
    }
}

void DIO_VidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8PinValue) //Getting current pin value
{

    switch (Copy_u8Port)
    {
        //Set pin as output
    case (Port_A):
        *Copy_Pu8PinValue = GET_BIT(PINA, Copy_u8Pin);
        break;
    case (Port_B):
        *Copy_Pu8PinValue = GET_BIT(PINB, Copy_u8Pin);
        break;
    case (Port_C):
        *Copy_Pu8PinValue = GET_BIT(PINC, Copy_u8Pin);
        break;
    case (Port_D):
        *Copy_Pu8PinValue = GET_BIT(PIND, Copy_u8Pin);
        break;
    }
}

/*------------------------------------Ports functions------------------------------------------------*/

void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value) //Setting all pins values on port to High or Low  
{

    switch (Copy_u8Port)
    {
        //Set pin as output
    case (Port_A):
        PORTA = Copy_u8Value;
        break;
    case (Port_B):
        PORTB = Copy_u8Value;
        break;
    case (Port_C):
        PORTC = Copy_u8Value;
        break;
    case (Port_D):
        PORTD = Copy_u8Value;
        break;
    }
}

void DIO_VidSetPortMode(u8 Copy_u8Port, u8 Copy_u8Mode) //Setting all pins modes on port to Input or Output
{

    switch (Copy_u8Port)
    {
        /*Set pin as output */
    case (Port_A):
        DDRA = Copy_u8Mode;
        break;
    case (Port_B):
        DDRB = Copy_u8Mode;
        break;
    case (Port_C):
        DDRC = Copy_u8Mode;
        break;
    case (Port_D):
        DDRD = Copy_u8Mode;
        break;
    }
}

void DIO_VidGetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8PortValue) //Getting current pins values on port
{

    switch (Copy_u8Port)
    {
    case (Port_A):
        *Copy_Pu8PortValue = PINA;
        break;
    case (Port_B):
        *Copy_Pu8PortValue = PINB;
        break;
    case (Port_C):
        *Copy_Pu8PortValue = PINC;
        break;
    case (Port_D):
        *Copy_Pu8PortValue = PIND;
        break;
    }
}
