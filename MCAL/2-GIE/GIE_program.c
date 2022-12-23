/** @file GIE_program.c
 *
 * @brief A program that implements GIE functions
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../Lib/Std_Types.h" /* Including standard types header */
#include "../Lib/Bit_Math.h"  /* Includes bit math header functions */
#include "GIE_private.h"      /* Including header file including memory addresses for GIE prot and BIT number */
#include "GIE_config.h"       /* Including header file for GIE configurations */
#include "GIE_interface.h"    /* Including header file for GIE Enable/Disable funtions */

/*========================== Functions ==========================*/

/**
 * @brief A function to enable all the interrupts for AVR ATmega32
 * @param void
 * @return void
 */
void GIE_VidEnable(void)
{
    SET_BIT(SREG, SREG_I_BIT);
}

/**
 * @brief A function to disable all the interrupts for AVR ATmega32
 * @param void
 * @return void
 */
void GIE_VidDisable(void)
{
    CLR_BIT(SREG, SREG_I_BIT);
}
