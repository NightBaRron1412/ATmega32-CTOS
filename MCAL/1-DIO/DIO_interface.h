/** @file DIO_interface.h
 *
 * @brief A header file including functions for DIO controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 3, 2022
 *
 */

/* Include Guard */
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/* Enum to hold Variables related to DIO */
typedef enum
{

    INPUT,              /* 0 */
    INPUT_PULLUP,       /* 1 */
    OUTPUT,             /* 2 */
    PORT_OUTPUT = 0xFF, /* 0xFF */
    PORT_INPUT = 0x00,  /* 0x00 */
    PORT_A,             /* 1 */
    PORT_B,             /* 2 */
    PORT_C,             /* 3 */
    PORT_D,             /* 4 */
    LOW = 0,            /* 0 */
    HIGH,               /* 1 */
    PORT_HIGH = 0xFF,   /* 0xFF */
    PORT_LOW = 0x00,    /* 0x00 */
    PIN_0 = 0,          /* 0 */
    PIN_1,              /* 1 */
    PIN_2,              /* 2 */
    PIN_3,              /* 3 */
    PIN_4,              /* 4 */
    PIN_5,              /* 5 */
    PIN_6,              /* 6 */
    PIN_7               /* 7 */

} enut_DIO;

/*========================== Init function ========================== */

/*
 * Description: Function to set the initialized direction and value of each port
 * Inputs: none
 * Output: void
 */
void DIO_VidInit(void);

/*========================== Pin functions ==========================*/

/*
 * Description: Function to set the direction of a specific pin in a specified port
 * Inputs: the port, the pin number, the pin direction
 * Output: the Error state of the function
 */
u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

/*
 * Description: Function to set a specific pin in a specified port with a specified value (INPUT = 0, OUTPUT = 1)
 * Inputs: the port, the pin number, the pin value
 * Output: the Error state of the function
 */
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/*
 * Description: Function to toggle a specific pin in a specified port
 * Inputs: the port, the pin number
 * Output: the Error state of the function
 */
u8 DIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin);

/*
 * Description: Function to get the value of a certain input pin in a specified port
 * Inputs: the port, the pin number, the container variable which will hold the value on this pin
 * output: the Error state of the function
 */
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8PinValue);

/*========================== Port functions ==========================*/

/*
 * Description: Function to set the direction of the whole pins ins a specified port
 * Inputs: the port and direction
 * Output: the Error state of the function
 */
u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);

/*
 * Description: Function to set pins of a specified port with a specified value
 * Inputs: the port, the port value
 * Output: the Error state of the function
 */
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

/*
 * Description: Function to toggle the pins value of a specified port
 * Inputs: the port
 * Output: the Error state of the function
 */
u8 DIO_u8TogglePortValue(u8 Copy_u8Port);

/*
 * Description: Function to get the value of a specified port
 * Inputs: the port, the container variable which will hold the value on this port
 * output: the Error state of the function
 */
u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8PortValue);

#endif /* DIO_INTERFACE_H */

/*** end of file ***/