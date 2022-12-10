/** @file BTN_program.c
 *
 * @brief A file that includes functions implementations for Buttons controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 3, 2022
 *
 */

/*========================== Libraries Includes ==========================*/
#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "../MCAL/1-DIO/DIO_interface.h"
#include "BTN_private.h"
#include "BTN_config.h"
#include "BTN_interface.h"

/*========================== Functions ==========================*/

/*
 * Description: Function to set the initialized configuration of each Button
 * Inputs: none
 * Output: void
 */
void BTN_VidInit(void)
{
	/* Loop on all buttons */
	for (u8 Local_u8ButtonNb = 0; Local_u8ButtonNb < BTN_NUM_OF_BUTTONS; Local_u8ButtonNb++)
	{
		switch (BTN_Au8ButtonConnection[Local_u8ButtonNb])
		{
		case BTN_INT_PULL_UP:
			DIO_u8SetPinDirection(BTN_Au8ButtonPort[Local_u8ButtonNb], BTN_Au8ButtonPin[Local_u8ButtonNb], INPUT_PULLUP);
			break;
		case BTN_EXT_PULL_UP:
			DIO_u8SetPinDirection(BTN_Au8ButtonPort[Local_u8ButtonNb], BTN_Au8ButtonPin[Local_u8ButtonNb], INPUT);
			break;
		case BTN_PULL_DOWN:
			DIO_u8SetPinDirection(BTN_Au8ButtonPort[Local_u8ButtonNb], BTN_Au8ButtonPin[Local_u8ButtonNb], INPUT);
			break;
		}
	}
}

/*
 * Description: Function to get the state of a specific Button
 * Inputs: Button number and the container variable which will hold the state of this switch
 * Output: the Error state of the function
 */
u8 BTN_u8GetButtonState(u8 Copy_u8ButtonNumber, u8 *Copy_u8ButtonState)
{
	/* Local variable to hold the error state */
	u8 Local_u8ErrorState = STATUS_OK;

	u8 Local_u8ButtonState;

	/* Check if the button number is valid */
	if (Copy_u8ButtonNumber >= BTN_NUM_OF_BUTTONS || Copy_u8ButtonState == NULL)
	{
		Local_u8ErrorState = STATUS_ERROR;
	}

	else
	{
		Local_u8ErrorState = DIO_u8GetPinValue(BTN_Au8ButtonPort[Copy_u8ButtonNumber], BTN_Au8ButtonPin[Copy_u8ButtonNumber], Local_u8ButtonState);

		/* Check the button connection type */
		switch (BTN_Au8ButtonConnection[Copy_u8ButtonNumber])
		{
		case BTN_INT_PULL_UP:
			if (Local_u8ButtonState == LOW)
			{
				*Copy_u8ButtonState = BTN_PRESSED;
			}
			else
			{
				*Copy_u8ButtonState = BTN_RELEASED;
			}
			break;

		case BTN_EXT_PULL_UP:
			if (Local_u8ButtonState == LOW)
			{
				*Copy_u8ButtonState = BTN_PRESSED;
			}
			else
			{
				*Copy_u8ButtonState = BTN_RELEASED;
			}
			break;

		case BTN_PULL_DOWN:
			if (Local_u8ButtonState == HIGH)
			{
				*Copy_u8ButtonState = BTN_PRESSED;
			}
			else
			{
				*Copy_u8ButtonState = BTN_RELEASED;
			}
			break;
		}

		/* Return the error state */
		return Local_u8ErrorState;
	}
}