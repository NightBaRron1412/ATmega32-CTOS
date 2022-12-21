/** @file WDT_program.c
 *
 * @brief A program file including functions implementations for WatchDog Timer
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "Lib/Std_Types.h"
#include "Lib/Bit_Math.h"
#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"

/*========================== Functions Implementation ==========================*/

/*
 * Description: Function to initialize the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidInit(void)
{
	if (WDT_INIT_STATE == WDT_ENABLE)
	{
		/* Enable the WatchDog Timer */
		SET_BIT(WDTCR, WDTCR_WDE);
	}

	/* Set the timeout period of the WatchDog Timer */
	WDTCR &= ~(7 << WDTCR_WDP0);
	WDTCR |= (WDT_INIT_PERIOD << WDTCR_WDP0);
}

/*
 * Description: Function to set the timeout period of the WatchDog Timer
 * Inputs: the timeout period of the WatchDog Timer
 * Output: Error State of the function
 */
u8 WDT_u8SetTimeout(u8 Copy_u8Period)
{
	/* Local Variable to hold the Error State */
	u8 Local_u8ErrorState = STATUS_OK;

	if (Copy_u8Period < 8)
	{
		WDTCR &= ~(7 << WDTCR_WDP0);
		WDTCR |= (Copy_u8Period << WDTCR_WDP0);

		Local_u8ErrorState = STATUS_OK;
	}
	else
	{
		Local_u8ErrorState = STATUS_ERROR;
	}

	/* Return the Error State */
	return Local_u8ErrorState;
}

/*
 * Description: Function to Enable the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

/*
 * Description: Function to Disable the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidDisable(void)
{
	/* Writing logical one to WDTOE and WDE */
	WDTCR |= (1 << WDTCR_WDTOE) | (1 << WDTCR_WDE);

	/* Turn off WDT */
	WDTCR = 0x00;
}

/*
 * Description: Function to Reset the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidResetTimer(void)
{
	/* Assembly instruction to reset the WDT */
	_WDR();
}