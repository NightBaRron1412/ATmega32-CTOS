#include "../Lib/Std_Types.h" // Including standard types header
#include "../Lib/Bit_Math.h"  // Includes bit math header functions
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

/*EXTI Enable */
void EXTI0_VidInit()
{

/*------------------Sense control-----------------------------*/
#if EXTI0_SENSE_CONTROL == EXTI_LOW_LEVEL_SC

    CLR_BIT(MCUCR, MCUCR_ISC01_PIN);
    CLR_BIT(MCUCR, MCUCR_ISC00_PIN);

#elif EXTI0_SENSE_CONTROL == EXTI_FALLING_EDGE_SC

    SET_BIT(MCUCR, MCUCR_ISC01_PIN);
    CLR_BIT(MCUCR, MCUCR_ISC00_PIN);

#elif EXTI0_SENSE_CONTROL == EXTI_RISING_EDGE_SC

    SET_BIT(MCUCR, MCUCR_ISC01_PIN);
    SET_BIT(MCUCR, MCUCR_ISC00_PIN);

#elif EXTI0_SENSE_CONTROL == EXTI_ONCHANGE_SC

    CLR_BIT(MCUCR, MCUCR_ISC01_PIN);
    SET_BIT(MCUCR, MCUCR_ISC00_PIN);

#else

#error No Sense control selected, kindly take a look at Config File.

#endif

    //Enable interupt
    SET_BIT(GICR, GICR_INT0_PIN);
}

void EXTI1_VidInit()
{

/*------------------Sense control-----------------------------*/
#if EXTI1_SENSE_CONTROL == EXTI_LOW_LEVEL_SC

    CLR_BIT(MCUCR, MCUCR_ISC11_PIN);
    CLR_BIT(MCUCR, MCUCR_ISC10_PIN);

#elif EXTI1_SENSE_CONTROL == EXTI_FALLING_EDGE_SC

    SET_BIT(MCUCR, MCUCR_ISC11_PIN);
    CLR_BIT(MCUCR, MCUCR_ISC10_PIN);

#elif EXTI1_SENSE_CONTROL == EXTI_RISING_EDGE_SC

    SET_BIT(MCUCR, MCUCR_ISC11_PIN);
    SET_BIT(MCUCR, MCUCR_ISC10_PIN);

#elif EXTI1_SENSE_CONTROL == EXTI_ONCHANGE_SC

    CLR_BIT(MCUCR, MCUCR_ISC11_PIN);
    SET_BIT(MCUCR, MCUCR_ISC10_PIN);

#else

#error No Sense control selected, kindly take a look at Config File.

#endif

    //Enable interupt
    SET_BIT(GICR, GICR_INT1_PIN);
}

void EXTI2_VidInit()
{
    /*------------------Sense control-----------------------------*/
#if EXTI2_SENSE_CONTROL == EXTI_FALLING_EDGE_SC

    CLR_BIT(MCUCSR, MCUCSR_ISC2_PIN);

#elif EXTI2_SENSE_CONTROL == EXTI_RISING_EDGE_SC

    SET_BIT(MCUCSR, MCUCR_ISC2_PIN);

#else

#error No Sense control selected, kindly take a look at Config File.

#endif

    //Enable interupt
    SET_BIT(GICR, GICR_INT1_PIN);
}
