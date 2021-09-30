/* Library */
#include "Lib/Std_Types.h"
#include "Lib/Bit_Math.h"

/* Own drive includes */
#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"

void WDT_VidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_vVidSleep(u8 Copy_u8Period)
{
	WDTCR &= ~(7 << WDTCR_WDP0);
	WDTCR |= (Copy_u8Period << WDTCR_WDP0);
}

void WDT_VidDisable(void)
{
	WDTCR = 0x18;
	WDTCR = 0;
}
