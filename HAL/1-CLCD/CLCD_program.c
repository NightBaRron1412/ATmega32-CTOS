/** @file CLCD_program.c
 *
 * @brief A file including functions implementations for CLCD controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../../Lib/Std_Types.h"
#include "../../MCAL/1-DIO/DIO_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"

/*========================== Functions Implementation ==========================*/

/**
 * @brief A function for initializing the CLCD.
 * @param void
 * @return void
 */
void CLCD_VidInit(void)
{
    /* Make LCD data port direction as O/P */
    DIO_VidSetPortMode(CLCD_DATA_PORT, PORT_OUTPUT);

    /* Make LCD ctrl port direction as O/P */
    DIO_VidSetPinMode(CLCD_CTRL_PORT, PIN_0, OUTPUT);
    DIO_VidSetPinMode(CLCD_CTRL_PORT, PIN_1, OUTPUT);
    DIO_VidSetPinMode(CLCD_CTRL_PORT, PIN_2, OUTPUT);

    /* Delay */
    delay_ms(40);

    /* Switching to 4-bit mode */
    if (CLCD_MODE == CLCD_4BIT)
    {
        CLCD_VidSendCommand(0x33);
        CLCD_VidSendCommand(0x32);
    }

    /* Function Set */
    CLCD_VidSendCommand(CLCD_INIT_FUNCTION_SET);

    /* Delay */
    delay_us(49);

    /* Display ON/OFF Control */
    CLCD_VidSendCommand(CLCD_INIT_DISPLAY_CONTROL);

    /* Delay */
    delay_us(49);

    /* Display clear */
    CLCD_VidDisplayClear();

    /* Delay */
    delay_ms(2);
}

/**
 * @brief A function for sending a command to the CLCD.
 * @param Copy_u8Command: The command to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_u8SendCommand(u8 Copy_u8Command)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

#if (CLCD_u8_MODE == CLCD_4BIT)
    /* Set RS pin as LOW */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, LOW);

    /* Set RW pin as LOW to write */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, LOW);

    /* Send higher nipple */
    Local_u8ErrorState = DIO_VidSetPortValue(CLCD_DATA_PORT, (Copy_u8Command & 0xF0));

    /* Set Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);

    /* Delay */
    delay_us(200);

    /* Send lower nipple */
    Local_u8ErrorState = DIO_VidSetPortValue(CLCD_DATA_PORT, ((Copy_u8Command << 4) & 0xF0));

    /* Set Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);
#endif

#if (CLCD_u8_MODE == CLCD_u8_8BIT)

    /* Set RS pin as LOW */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, LOW);

    /* Set RW pin as LOW to write */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, LOW);

    /* Send command to data port (pins 0 - 7) */
    Local_u8ErrorState = DIO_VidSetPortValue(CLCD_DATA_PORT, Copy_u8Command);

    /* Set Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    Local_u8ErrorState = DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);
#endif

    /* return Error State */
    return Local_u8ErrorState;
}

/**
 * @brief A function for sending a data to the CLCD.
 * @param Copy_u8Data: The data to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_u8SendData(u8 Copy_u8Data)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

#if (CLCD_MODE == CLCD_4BIT)
    /* Send higher nipple */
    DIO_VidSetPortValue(CLCD_DATA_PORT, Copy_u8Data & 0xF0);

    /* Set RS pin as HIGH */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, HIGH);

    /* Set RW pin as LOW to write */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, LOW);

    /* Set Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);

    /* Delay */
    delay_us(200);

    /* Send lower nipple */
    DIO_VidSetPortValue(CLCD_DATA_PORT, (Copy_u8Data << 4) & 0xF0);

    /* Set RS pin as HIGH */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, HIGH);

    /* Set RW pin as LOW to write */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, LOW);

    /* Set Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);
#endif

#if (CLCD_MODE == CLCD_8BIT)
    /* Set RS pin as HIGH */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, HIGH);

    /* Set RW pin as LOW to write */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, LOW);

    /* Send command to data port (pins 0 - 7) */
    DIO_VidSetPortValue(CLCD_DATA_PORT, Copy_u8Data);

    /* Set Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, HIGH);

    /* Delay */
    delay_ms(2);

    /* Clearing Enable pin */
    DIO_VidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, LOW);
#endif

    /* return Error State */
    return Local_u8ErrorState;
}

/**
 * @brief A function for clearing the CLCD.
 * @param void
 * @return void
 */
void CLCD_VidDisplayClear(void)
{
    CLCD_VidSendCommand(0b00000001);
    /* Delay */
    delay_ms(2);
}

/**
 * @brief A function for going to a specific position on the CLCD.
 * @param Copy_u8XPos: The X position to go to.
 * @param Copy_u8YPos: The Y position to go to.
 * @return void
 */
void CLCD_VidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
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

    /* Send this address to the DDram  128 + Local_u8Address because of the 1st in bit 7 of datasheet */

    CLCD_VidSendCommand(0b010000000 + Local_u8Address);
}

/**
 * @brief A function for creating a special character.
 * @param Copy_u8Pattern: The pattern of the special character.
 * @param Copy_u8PatternNumber: The number of the special character.
 * @return The Error state of the function.
 */
u8 CLCD_u8CreatSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Local Variable to hold the CGRAM Address */
    u8 Local_u8CGRAMAddress = 0;

    /* Calculate the CGRAM Address */
    Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;

    /* Send CGRAM address command to LCD with setting bit 6 to 1 -----> 64 */
    CLCD_VidSendCommand(Local_u8CGRAMAddress + 64);

    /* Write pattern into CGRAM */
    for (u8 i = 0; i < 8; i++)
    {
        CLCD_VidSendData(Copy_u8Pattern[i]);
    }

    /* return Error State */
    return Local_u8ErrorState;
}

/**
 * @brief A function for sending a string to the CLCD.
 * @param Copy_u8Str: The string to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_VidSendString(u8 *Copy_u8Str)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

    while (*Copy_u8Str != '\0')
    {
        Local_u8ErrorState = CLCD_VidSendData(*Copy_u8Str);
        Copy_u8Str++;
    }

    /* return Error State */
    return Local_u8ErrorState;
}