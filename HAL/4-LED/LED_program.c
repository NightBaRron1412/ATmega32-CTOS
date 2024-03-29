/** @file LED_program.c
 *
 * @brief A file that includes functions implementations for LEDs controlling.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 10, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../../Lib/Std_Types.h"
#include "../../Lib/Bit_Math.h"
#include "../../MCAL/1-DIO/DIO_interface.h"
#include "LED_private.h"
#include "LED_config.h"
#include "LED_interface.h"

/*========================== Functions ==========================*/

/*
 * Description: Function to set the initialized configuration of each LED
 * Inputs: none
 * Output: void
 */
void LED_VidInit(void)
{
	/* Loop on all LEDs */
	for (u8 Local_u8LEDNb = 0; Local_u8LEDNb < LED_NUM_OF_LEDS; Local_u8LEDNb++)
	{
		/* Set pin direction to output */
		DIO_u8SetPinDirection(LED_Au8LedPort[Local_u8LEDNb], LED_Au8LedPin[Local_u8LEDNb], OUTPUT);

		/* Setting LED to init state */
		switch (LED_Au8LedDirection[Local_u8LEDNb])
		{
		case LED_FORWARD:
			switch (LED_Au8LedState[Local_u8LEDNb])
			{
			case LED_ON:
				DIO_u8SetPinValue(LED_Au8LedPort[Local_u8LEDNb], LED_Au8LedPin[Local_u8LEDNb], HIGH);
				break;
			case LED_OFF:
				DIO_u8SetPinValue(LED_Au8LedPort[Local_u8LEDNb], LED_Au8LedPin[Local_u8LEDNb], LOW);
				break;
			}
			break;

		case LED_REVERSE:
			switch (LED_Au8LedState[Local_u8LEDNb])
			{
			case LED_ON:
				DIO_u8SetPinValue(LED_Au8LedPort[Local_u8LEDNb], LED_Au8LedPin[Local_u8LEDNb], LOW);
				break;
			case LED_OFF:
				DIO_u8SetPinValue(LED_Au8LedPort[Local_u8LEDNb], LED_Au8LedPin[Local_u8LEDNb], HIGH);
				break;
			}
			break;
		}
	}
}

/*
 * Description: Function to turn on a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8On(u8 Copy_u8LedNumber)
{
	/* Local variable to hold the error state */
	u8 Local_u8ErrorState = STATUS_OK;

	/* Check if the LED number is valid */
	if (Copy_u8LedNumber >= LED_NUM_OF_LEDS)
	{
		/* Set the error state to Error */
		Local_u8ErrorState = STATUS_ERROR;
	}

	else
	{
		/* Check if the LED is forward or reverse */
		switch (LED_Au8LedDirection[Copy_u8LedNumber])
		{
		case LED_FORWARD:
			Local_u8ErrorState = DIO_u8SetPinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber], HIGH);
			break;
		case LED_REVERSE:
			Local_u8ErrorState = DIO_u8SetPinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber], LOW);
			break;
		}
	}

	/* Return the error state */
	return Local_u8ErrorState;
}

/*
 * Description: Function to turn off a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8Off(u8 Copy_u8LedNumber)
{
	/* Local variable to hold the error state */
	u8 Local_u8ErrorState = STATUS_OK;

	/* Check if the LED number is valid */
	if (Copy_u8LedNumber >= LED_NUM_OF_LEDS)
	{
		/* Set the error state to Error */
		Local_u8ErrorState = STATUS_ERROR;
	}

	else
	{
		/* Check if the LED is forward or reverse */
		switch (LED_Au8LedDirection[Copy_u8LedNumber])
		{
		case LED_FORWARD:
			Local_u8ErrorState = DIO_u8SetPinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber], LOW);
			break;
		case LED_REVERSE:
			Local_u8ErrorState = DIO_u8SetPinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber], HIGH);
			break;
		}
	}

	/* Return the error state */
	return Local_u8ErrorState;
}

/*
 * Description: Function to toggle a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8Toggle(u8 Copy_u8LedNumber)
{
	/* Local variable to hold the error state */
	u8 Local_u8ErrorState = STATUS_OK;

	/* Check if the LED number is valid */
	if (Copy_u8LedNumber >= LED_NUM_OF_LEDS)
	{
		/* Set the error state to Error */
		Local_u8ErrorState = STATUS_ERROR;
	}

	else
	{
		/* Check if the LED is forward or reverse */
		switch (LED_Au8LedDirection[Copy_u8LedNumber])
		{
		case LED_FORWARD:
			Local_u8ErrorState = DIO_u8TogglePinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber]);
			break;
		case LED_REVERSE:
			Local_u8ErrorState = DIO_u8TogglePinValue(LED_Au8LedPort[Copy_u8LedNumber], LED_Au8LedPin[Copy_u8LedNumber]);
			break;
		}
	}

	/* Return the error state */
	return Local_u8ErrorState;
}