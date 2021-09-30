/** @file DIO_interface.h
 * 
 * @brief A header file including functions for DIO controlling. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 16, 2021       
 *
 */

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

typedef enum
{

    input,              //0
    output,             //1
    Port_output = 0xff, //0xff
    Port_input = 0x00,  //0x00
    Port_A,             //2
    Port_B,             //3
    Port_C,             //4
    Port_D,             //5
    low = 0,            //0
    high,               //1
    Port_high = 0xff,   //0xff
    Port_low = 0x00,    //0x00
    Pin_0 = 0,          //0
    Pin_1,              //1
    Pin_2,              //2
    Pin_3,              //3
    Pin_4,              //4
    Pin_5,              //5
    Pin_6,              //6
    Pin_7               //7

} enut_DIO;

//Pin functions
void DIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
void DIO_VidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode);
void DIO_VidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8PinValue);

//Port functions
void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
void DIO_VidSetPortMode(u8 Copy_u8Port, u8 Copy_u8Mode);
void DIO_VidGetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8PortValue);

#endif /* DIO_INTERFACE_H */

/*** end of file ***/