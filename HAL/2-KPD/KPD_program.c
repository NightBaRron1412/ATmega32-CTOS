#include "../Lib/Std_Types.h"      //Includes standard types header
#include "../MCAL/DIO_interface.h" // Including DIO functions to control ports and pins
#include "KPD_config.h"            //Including config header
#include "KPD_interface.h"         // Including KPD functions

u8 KPD_u8GetKey(void)
{

    u8 Local_KeyPressd = NOT_PRESSED;
    u8 Local_u8KPDArr[4][4] = KPD_U8ARR; //Keypad array *Can bve customized with config.h file
    u8 Local_u8ColumnIdx = 0;            //Column index
    u8 Local_u8ROWIdx = 0;               //Row index
    u8 Local_u8State = 1;                //Is Key pressed?

    u8 Local_u8ColumnArr[] = {KPD_u8COLUMN0_PIN, KPD_u8COLUMN1_PIN, KPD_u8COLUMN2_PIN, KPD_u8COLUMN3_PIN};
    u8 Local_u8RowArr[] = {KPD_u8ROW0_PIN, KPD_u8ROW1_PIN, KPD_u8ROW2_PIN, KPD_u8ROW3_PIN};

    for (Local_u8ColumnIdx = 0; Local_u8ColumnIdx < 4; Local_u8ColumnIdx++) //Loop through the columns
    {
        DIO_VidSetPinValue(KPD_u8PORT, Local_u8ColumnArr[Local_u8ColumnIdx], low);

        for (Local_u8ROWIdx = 0; Local_u8ROWIdx < 4; Local_u8ROWIdx++) //Check each row status
        {
            DIO_VidGetPinValue(KPD_u8PORT, Local_u8RowArr[Local_u8ROWIdx], &Local_u8State); //Getting the state of row pin

            if (Local_u8State == low) //If row is low then button is pressed
            {
                Local_KeyPressd = Local_u8KPDArr[Local_u8ColumnIdx][Local_u8ROWIdx]; //Storing the pressed key at column & row index

                while (Local_u8State == low) //Waiting for key to be released
                {
                    DIO_VidGetPinValue(KPD_u8PORT, Local_u8RowArr[Local_u8ROWIdx], &Local_u8State); //Checking row/key status
                }

                DIO_VidSetPinValue(KPD_u8PORT, Local_u8ColumnArr[Local_u8ColumnIdx], high); //Setting column to high after key is released

                return Local_KeyPressd; //Returning the pressed key
            }
        }

        DIO_VidSetPinValue(KPD_u8PORT, Local_u8ColumnArr[Local_u8ColumnIdx], high); //Setting column to high again if no key is pressed
    }

    return Local_KeyPressd; //Returning the pressed key
}