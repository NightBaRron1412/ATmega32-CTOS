/** @file DIO_program.c
 *
 * @brief A file that includes functions implementations for AVR.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 3, 2022
 *
 */

/*========================== Libraries Includes ==========================*/
#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "DIO_interface.h"

/*========================== Init function ==========================*/
/**
 * @brief Function to initialize the DIO module
 * @param void
 * @return void
 */
void DIO_VidInit(void)
{
    /* Ports Direction initialization */
    DDRA = DIO_PORTA_INIT_DIR;
    DDRB = DIO_PORTB_INIT_DIR;
    DDRC = DIO_PORTC_INIT_DIR;
    DDRD = DIO_PORTD_INIT_DIR;

    /* Ports States initialization */
    PORTA = DIO_PORTA_INIT_STATE;
    PORTB = DIO_PORTB_INIT_STATE;
    PORTC = DIO_PORTC_INIT_STATE;
    PORTD = DIO_PORTD_INIT_STATE;
}

/*========================== Pins functions ==========================*/

/**
 * @brief Function to set a specific pin in a specified port with a specified direction
 * @param Copy_u8Port the port
 * @param Copy_u8Pin the pin number
 * @param Copy_u8Direction the direction of the pin
 * @return the Error state of the function
 */
u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
    /*Local Variable holding the error state*/
    u8 Local_u8Error;

    /*checking the error possibilities of the inputs*/
    if ((Copy_u8Port > PORT_D) || (Copy_u8Pin > PIN_7) || ((Copy_u8Direction != INPUT) && (Copy_u8Direction != INPUT_PULLUP) && (Copy_u8Direction != OUTPUT)))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {

        /* Check for input mode 0 for input without pull up */
        if (Copy_u8Direction == INPUT)
        {
            /* Set pin as input without pull up enabled */
            switch (Copy_u8Port)
            {

            case (PORT_A):
                CLR_BIT(DDRA, Copy_u8Pin);
                CLR_BIT(PORTA, Copy_u8Pin);
                break;
            case (PORT_B):
                CLR_BIT(DDRB, Copy_u8Pin);
                CLR_BIT(PORTB, Copy_u8Pin);
                break;
            case (PORT_C):
                CLR_BIT(DDRC, Copy_u8Pin);
                CLR_BIT(PORTC, Copy_u8Pin);
                break;
            case (PORT_D):
                CLR_BIT(DDRD, Copy_u8Pin);
                CLR_BIT(PORTD, Copy_u8Pin);
                break;
            }
        }

        /* Check for input mode 1 for input with pull up enabled */
        else if (Copy_u8Direction == INPUT_PULLUP)
        {

            /* Clearing Pull-up disable bit in SFIOR register */
            CLR_BIT(SFIOR, PUD);

            switch (Copy_u8Port)
            {
                /* Set pin as input and enable pull up */
            case (PORT_A):
                SET_BIT(DDRA, Copy_u8Pin);
                SET_BIT(PORTA, Copy_u8Pin);
                break;
            case (PORT_B):
                SET_BIT(DDRB, Copy_u8Pin);
                SET_BIT(PORTB, Copy_u8Pin);
                break;
            case (PORT_C):
                SET_BIT(DDRC, Copy_u8Pin);
                SET_BIT(PORTC, Copy_u8Pin);
                break;
            case (PORT_D):
                SET_BIT(DDRD, Copy_u8Pin);
                SET_BIT(PORTD, Copy_u8Pin);
                break;
            }
        }

        /* Check for input mode 2 for output */
        else if (Copy_u8Direction == OUTPUT)
        {

            switch (Copy_u8Port)
            {
                /* Set pin as output */
            case (PORT_A):
                SET_BIT(DDRA, Copy_u8Pin);
                break;
            case (PORT_B):
                SET_BIT(DDRB, Copy_u8Pin);
                break;
            case (PORT_C):
                SET_BIT(DDRC, Copy_u8Pin);
                break;
            case (PORT_D):
                SET_BIT(DDRD, Copy_u8Pin);
                break;
            }
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to set a specific pin in a specified port with a specified value (LOW = 0, HIGH = 1)
 * @param Copy_u8Port the port
 * @param Copy_u8Pin the pin number
 * @param Copy_u8Value the value of the pin
 * @return the Error state of the function
 */
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
    /*Local Variable holding the error state*/
    u8 Local_u8Error;

    if ((Copy_u8Port > PORT_D) || (Copy_u8Pin > PIN_7) || ((Copy_u8Value != HIGH) && (Copy_u8Value != LOW)))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {

        if (Copy_u8Value == HIGH)
        {
            switch (Copy_u8Port)
            {

            case (PORT_A):
                SET_BIT(PORTA, Copy_u8Pin);
                break;
            case (PORT_B):
                SET_BIT(PORTB, Copy_u8Pin);
                break;
            case (PORT_C):
                SET_BIT(PORTC, Copy_u8Pin);
                break;
            case (PORT_D):
                SET_BIT(PORTD, Copy_u8Pin);
                break;
            }
        }

        else if (Copy_u8Value == LOW)
        {
            switch (Copy_u8Port)
            {

            case (PORT_A):
                CLR_BIT(PORTA, Copy_u8Pin);
                break;
            case (PORT_B):
                CLR_BIT(PORTB, Copy_u8Pin);
                break;
            case (PORT_C):
                CLR_BIT(PORTC, Copy_u8Pin);
                break;
            case (PORT_D):
                CLR_BIT(PORTD, Copy_u8Pin);
                break;
            }
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to toggle the value of a certain pin in a specified port
 * @param Copy_u8Port the port
 * @param Copy_u8Pin the pin number
 * @return the Error state of the function
 */
u8 DIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    /*Local Variable holding the error state*/
    u8 Local_u8Error;

    if ((Copy_u8Port > PORT_D) || (Copy_u8Pin > PIN_7))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8Port)
        {

        case (PORT_A):
            TOG_BIT(PORTA, Copy_u8Pin);
            break;
        case (PORT_B):
            TOG_BIT(PORTB, Copy_u8Pin);
            break;
        case (PORT_C):
            TOG_BIT(PORTC, Copy_u8Pin);
            break;
        case (PORT_D):
            TOG_BIT(PORTD, Copy_u8Pin);
            break;
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to get the value of a certain pin in a specified port
 * @param Copy_u8Port the port
 * @param Copy_u8Pin the pin number
 * @param Copy_Pu8PinValue the container variable which will hold the value of the pin
 * @return the Error state of the function
 */
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8PinValue)
{
    /*Local Variable holding the error state*/
    u8 Local_u8Error;

    if ((Copy_u8Port > PORT_D) || (Copy_u8Pin > PIN_7) || (Copy_Pu8PinValue == NULL))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8Port)
        {
        case (PORT_A):
            *Copy_Pu8PinValue = GET_BIT(PINA, Copy_u8Pin);
            break;
        case (PORT_B):
            *Copy_Pu8PinValue = GET_BIT(PINB, Copy_u8Pin);
            break;
        case (PORT_C):
            *Copy_Pu8PinValue = GET_BIT(PINC, Copy_u8Pin);
            break;
        case (PORT_D):
            *Copy_Pu8PinValue = GET_BIT(PIND, Copy_u8Pin);
            break;
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/*========================== Ports functions ==========================-*/

/**
 * @brief Function to set the direction of a specified port with a specified direction
 * @param Copy_u8Port the port
 * @param Copy_u8Direction the direction of the port
 * @return the Error state of the function
 */
u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
{
    /* Local variable holding the error state */
    u8 Local_u8Error;

    /* Checking the error possibilities of the inputs */
    if ((Copy_u8Port > PORT_D) || ((Copy_u8Direction != INPUT) && (Copy_u8Direction != INPUT_PULLUP) && (Copy_u8Direction != OUTPUT)))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        /* Set Port Direction to input with pull up disabled */
        if (Copy_u8Direction == INPUT)
        {
            switch (Copy_u8Port)
            {
            case (PORT_A):
                DDRA = PORT_INPUT;
                PORTA = PORT_LOW;
                break;
            case (PORT_B):
                DDRB = PORT_INPUT;
                PORTB = PORT_LOW;
                break;
            case (PORT_C):
                DDRC = PORT_INPUT;
                PORTC = PORT_LOW;
                break;
            case (PORT_D):
                DDRD = PORT_INPUT;
                PORTD = PORT_LOW;
                break;
            }
        }
        /* Set Port Direction to input with pull up enabled */
        else if (Copy_u8Direction == INPUT_PULLUP)
        {
            /* Clearing Pull-up disable bit in SFIOR register */
            CLR_BIT(SFIOR, PUD);

            switch (Copy_u8Port)
            {
            case (PORT_A):
                DDRA = PORT_INPUT;
                PORTA = PORT_HIGH;
                break;
            case (PORT_B):
                DDRB = PORT_INPUT;
                PORTB = PORT_HIGH;
                break;
            case (PORT_C):
                DDRC = PORT_INPUT;
                PORTC = PORT_HIGH;
                break;
            case (PORT_D):
                DDRD = PORT_INPUT;
                PORTD = PORT_HIGH;
                break;
            }
        }

        /* Set Port Direction to output */
        else if (Copy_u8Direction == OUTPUT)
        {
            switch (Copy_u8Port)
            {
            case (PORT_A):
                DDRA = PORT_OUTPUT;
                break;
            case (PORT_B):
                DDRB = PORT_OUTPUT;
                break;
            case (PORT_C):
                DDRC = PORT_OUTPUT;
                break;
            case (PORT_D):
                DDRD = PORT_OUTPUT;
                break;
            }
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to set the value of a specified port with a specified value (LOW = 0, HIGH = 1)
 * @param Copy_u8Port the port
 * @param Copy_u8Value the value of the port
 * @return the Error state of the function
 */
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
    /*Local Variable holding the error state */
    u8 Local_u8Error;

    /*checking the error possibilities of the inputs*/
    if ((Copy_u8Port > PORT_D) || (Copy_u8Value > PORT_HIGH))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8Port)
        {
        case (PORT_A):
            PORTA = Copy_u8Value;
            break;
        case (PORT_B):
            PORTB = Copy_u8Value;
            break;
        case (PORT_C):
            PORTC = Copy_u8Value;
            break;
        case (PORT_D):
            PORTD = Copy_u8Value;
            break;
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to toggle the value of a specified port
 * @param Copy_u8Port the port
 * @return the Error state of the function
 */
u8 DIO_u8TogglePortValue(u8 Copy_u8Port)
{
    /*Local Variable holding the error state */
    u8 Local_u8Error;

    /*checking the error possibilities of the inputs*/
    if (Copy_u8Port > PORT_D)
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8Port)
        {
        case (PORT_A):
            PORTA = PORTA ^ PORT_HIGH;
            break;
        case (PORT_B):
            PORTB = PORTB ^ PORT_HIGH;
            break;
        case (PORT_C):
            PORTC = PORTC ^ PORT_HIGH;
            break;
        case (PORT_D):
            PORTD = PORTD ^ PORT_HIGH;
            break;
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}

/**
 * @brief Function to get the value of a specified port
 * @param Copy_u8Port the port
 * @param Copy_Pu8PortValue the container variable which will hold the value of the port
 * @return the Error state of the function
 */
u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8PortValue)
{
    /*Local Variable holding the error state */
    u8 Local_u8Error;

    /*checking the error possibilities of the inputs*/
    if ((Copy_u8Port > PORT_D) || (Copy_Pu8PortValue == NULL))
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8Port)
        {
        case (PORT_A):
            *Copy_Pu8PortValue = PINA;
            break;
        case (PORT_B):
            *Copy_Pu8PortValue = PINB;
            break;
        case (PORT_C):
            *Copy_Pu8PortValue = PINC;
            break;
        case (PORT_D):
            *Copy_Pu8PortValue = PIND;
            break;
        }
        Local_u8Error = STATUS_OK;
    }

    /* Function return */
    return Local_u8Error;
}
