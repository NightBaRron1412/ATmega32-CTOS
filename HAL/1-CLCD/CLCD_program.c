#include "../Lib/Std_Types.h"
#include "../MCAL/DIO_interface.h"
#include "CLCD_config.h"
#include <util/delay.h>

void CLCD_VidSendCommand(u8 Copy_u8Command) //Function to send commands to CLCD
{
    //Set RS pin as low
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, low);

    //Set RW pin as low to write
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, low);

    //Send command to data port (pins 0 - 7)
    DIO_VidSetPortValue(CLCD_DATA_PORT, Copy_u8Command);

    //Set Enable pin
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, high);

    //Delay
    _delay_ms(2);

    //Clearing Enable pin
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, low);
}

void CLCD_VidSendData(u8 Copy_u8Data) //Function to send data to CLCD
{
    //Set RS pin as high
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, high);

    //Set RW pin as low to write
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, low);

    //Send data to data port (pins 0 - 7)
    DIO_VidSetPortValue(CLCD_DATA_PORT, Copy_u8Data);

    //Set Enable pin
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, high);

    //Delay
    _delay_ms(2);

    //Clearing Enable pin
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, low);
}

void CLCD_VidInit() //Function to initialize CLCD
{
    //Delay
    _delay_ms(40);

    //Function Set
    CLCD_VidSendCommand(0b00111111);

    //Delay
    _delay_us(49);

    //Display ON/OFF Control
    CLCD_VidSendCommand(0b00001100);

    //Delay
    _delay_us(49);

    //Display clear
    CLCD_VidSendCommand(0b00000001);
    //Delay
    _delay_ms(2);
}

void CLCD_VidDisplayClear() //Function to clear display
{
    CLCD_VidSendCommand(0b00000001);
    //Delays
    _delay_ms(2);
}

void CLCD_VidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos) //Function to go to certain position on CLCD
{

    u8 Local_u8Address = 0;

    if (Copy_u8XPos == 0)
    {
        Local_u8Address = Copy_u8YPos;
    }

    else if (Copy_u8XPos == 1)
    {

        Local_u8Address = 0x40 + Copy_u8YPos;
    }

    //Send this adderess to the DDram  128 + Local_u8Address because of the 1 in bit 7 of data sheet

    CLCD_VidSendCommand(0b010000000 + Local_u8Address);
}

void CLCD_VidCreatSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber) //Function to write special character on CLCD
{

    u8 Local_u8CGRAMAddress = 0;

    //Calculate the CGRAM Address
    Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;

    //Send CGRAM address command to LCD with setting bit 6 to 1 -----> 64
    CLCD_VidSendCommand(Local_u8CGRAMAddress + 64);

    //Write pattern into CGRAM
    for (u8 i = 0; i < 8; i++)
    {
        CLCD_VidSendData(Copy_u8Pattern[i]);
    }
}

void CLCD_VidSendString(u8 *Copy_u8Str)
{

    while (*Copy_u8Str != '\0')
    {
        CLCD_VidSendData(*Copy_u8Str);
        Copy_u8Str++;
    }
}
