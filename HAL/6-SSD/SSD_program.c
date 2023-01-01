/** @file SSD_program.c
 *
 * @brief A program file including functions for 7SEG interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 30, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../../Lib/Std_Types.h"
#include "../../Lib/Bit_Math.h"
#include "../../MCAL/1-DIO/DIO_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"

/*========================== Functions ==========================*/

/**
 * @brief SSD Initialization function
 * @param void
 * @return void
 */
void SSD_VidInit(void)
{

    for (u8 Local_u8Counter = 0; Local_u8Counter < SSD_CONNECTED_NUM; Local_u8Counter++)
    {
        /* Set SSD port as output */
        DIO_VidSetPortDirection(SSD_Au8SSDPort[Local_u8Counter], PORT_OUTPUT);

        /* Set SSD port value to initial value */
        SSD_VidDisplayNumber(SSD_Au8SSDPort[Local_u8Counter], SSD_Au8SSDInitValue[Local_u8Counter]);
    }
}

/**
 * @brief SSD Display Number function
 * @param Copy_u8SSDNum: SSD number
 * @param Copy_u8Number: Number to be displayed
 * @return u8: Error state
 */
u8 SSD_VidDisplayNumber(u8 Copy_u8SSDNum, u8 Copy_u8Number)
{
    /* Local variable to hold error state */
    u8 Local_u8ErrorState = STATUS_OK;

    /* Display Number check condition */
    if ((Copy_u8Number >= SSD_MIN_NUM) || (Copy_u8Number <= SSD_MAX_NUM))
    {
        /*Display number from seven segment array*/
        switch (SSD_Au8SSDType[Copy_u8SSDNum])
        {
        case SSD_COMMON_CATHODE:
            Local_u8ErrorState = DIO_VidSetPortValue(SSD_Au8SSDPort[Copy_u8SSDNum], SSD_Au87SegArray[Copy_u8Number]);
            break;

        case SSD_COMMON_ANODE:
            Local_u8ErrorState = DIO_VidSetPortValue(SSD_Au8SSDPort[Copy_u8SSDNum], ~(SSD_Au87SegArray[Copy_u8Number]));
            break;
        }
    }

    else
    {
        /* Set error state to error */
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return error state */
    return Local_u8ErrorState;
}