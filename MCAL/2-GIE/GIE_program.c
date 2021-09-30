#include "../Lib/Std_Types.h" // Including standard types header
#include "../Lib/Bit_Math.h"  // Includes bit math header functions
#include "GIE_interface.h"    // Including header file for GIE Enable/Disable funtions
#include "GIE_private.h"      //Including header file including memory addresses for GIE prot and BIT number

//GIE enable
void GIE_VidEnable()
{
    SET_BIT(SREG, SREG_I_BIT);
}

//GIE disable
void GIE_VidDisable()
{
    CLR_BIT(SREG, SREG_I_BIT);
}
