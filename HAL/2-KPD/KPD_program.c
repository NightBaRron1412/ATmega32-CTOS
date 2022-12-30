/** @file KPD_program.c
 *
 * @brief A program file including functions implementations for KPD interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 24, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../../Lib/Std_Types.h"
#include "../../Lib/Bit_Math.h"
#include "../../MCAL/1-DIO/DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

/*========================== Functions Implementation ==========================*/

/**
 * @brief A function to initialize the keypad
 * @param void
 * @return void
 */
void KPD_VidInit(void)
{
    /* Setting Column pins to output */
    DIO_VidSetPinMode(KPD_PORT, KPD_COLUMN0_PIN, OUTPUT);
    DIO_VidSetPinMode(KPD_PORT, KPD_COLUMN1_PIN, OUTPUT);
    DIO_VidSetPinMode(KPD_PORT, KPD_COLUMN2_PIN, OUTPUT);
    DIO_VidSetPinMode(KPD_PORT, KPD_COLUMN3_PIN, OUTPUT);

    /* Setting Row pins to input or input with pullup enabled */
    if (KPD_CONNECTION_MODE == KPD_INT_PULLUP)
    {
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW0_PIN, INPUT_PULLUP);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW1_PIN, INPUT_PULLUP);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW2_PIN, INPUT_PULLUP);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW3_PIN, INPUT_PULLUP);
    }
    else
    {
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW0_PIN, INPUT);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW1_PIN, INPUT);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW2_PIN, INPUT);
        DIO_VidSetPinMode(KPD_PORT, KPD_ROW3_PIN, INPUT);
    }
}

/**
 * @brief A function to get the pressed key
 * @param void
 * @return The pressed key
 */
u8 KPD_u8GetKey(u8 *Copy_Pu8KeyPressed)
{
    /* Local variable to hold the Error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_Pu8KeyPressed == NULL)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        /* Keypad array *Can be customized at config.h file */
        u8 Local_u8KPDArr[ROWS_NUMBER][COLUMNS_NUMBER] = KPD_U8ARR;

        /* Is Key pressed? */
        u8 Local_u8State = NOT_PRESSED;

        u8 Local_u8ColumnArr[] = {KPD_COLUMN0_PIN, KPD_COLUMN1_PIN, KPD_COLUMN2_PIN, KPD_COLUMN3_PIN};
        u8 Local_u8RowArr[] = {KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};

        /* Loop through the columns */
        for (u8 Local_u8ColumnIdx = 0; Local_u8ColumnIdx < COLUMNS_NUMBER; Local_u8ColumnIdx++)
        {
            Local_u8ErrorState = DIO_VidSetPinValue(KPD_PORT, Local_u8ColumnArr[Local_u8ColumnIdx], LOW);

            /* Check each row status */
            for (u8 Local_u8ROWIdx = 0; Local_u8ROWIdx < ROWS_NUMBER; Local_u8ROWIdx++)
            {
                /* Getting the state of row pin */
                Local_u8ErrorState = DIO_VidGetPinValue(KPD_PORT, Local_u8RowArr[Local_u8ROWIdx], &Local_u8State);

                /* If pull down is enabled */
                if (KPD_CONNECTION_MODE == KPD_PULLDOWN)
                {
                    /* Inverting the state (HIGH = 0, LOW = 1) */
                    Local_u8State = !Local_u8State;
                }

                /* If row is low then button is pressed */
                if (Local_u8State == PRESSED)
                {
                    /* Storing the pressed key at column & row index */
                    *Copy_Pu8KeyPressed = Local_u8KPDArr[Local_u8ROWIdx][Local_u8ColumnIdx];

                    /* Waiting for key to be released */
                    while (Local_u8State == PRESSED)
                    {
                        /* Checking row/key status */
                        Local_u8ErrorState = DIO_VidGetPinValue(KPD_PORT, Local_u8RowArr[Local_u8ROWIdx], &Local_u8State);

                        /* If pull down is enabled */
                        if (KPD_CONNECTION_MODE == KPD_PULLDOWN)
                        {
                            /* Inverting the state (HIGH = 0, LOW = 1) */
                            Local_u8State = !Local_u8State;
                        }
                    }

                    /* Setting column to high after key is released */
                    Local_u8ErrorState = DIO_VidSetPinValue(KPD_PORT, Local_u8ColumnArr[Local_u8ColumnIdx], HIGH);

                    Local_u8State = PRESSED;

                    /* Breaking the rows loop*/
                    break;
                }
            }

            if (Local_u8State == PRESSED)
            {
                /* Breaking the columns loop*/
                break;
            }

            /* Setting column to high again if no key is pressed */
            Local_u8ErrorState = DIO_VidSetPinValue(KPD_PORT, Local_u8ColumnArr[Local_u8ColumnIdx], HIGH);
        }
    }

    /* Returning the error state */
    return Local_u8ErrorState;
}