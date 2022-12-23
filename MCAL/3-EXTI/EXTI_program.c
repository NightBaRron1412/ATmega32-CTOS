/** @file EXTI_program.c
 *
 * @brief A program file including functions implementation for EXTI controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 11, 2022
 *
 */

/*========================== Libraries Includes ==========================*/

#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

/*Static array where each element is a pointer to function of each one of the external int (INT0,INT1-INT2)*/
static void (*PVCallBack[EXTI_NO_OF_EXTI])(void) = {NULL, NULL, NULL};

/*========================== Functions ==========================*/

/**
 * @brief A function to initialize the external interrupts (INT0,INT1,INT2)
 * @param void
 * @return void
 */
void EXTI_VidInit(void)
{
    /* Checking init state of each external interrupt */
    switch (EXTI0_INIT_STATE)
    {
    case EXTI_ENABLE:
        SET_BIT(GICR, GICR_INT0_BIT);
        break;
    case EXTI_DISABLE:
        CLR_BIT(GICR, GICR_INT0_BIT);
        break;
    default:
        break;
    }

    switch (EXTI1_INIT_STATE)
    {
    case EXTI_ENABLE:
        SET_BIT(GICR, GICR_INT1_BIT);
        break;
    case EXTI_DISABLE:
        CLR_BIT(GICR, GICR_INT1_BIT);
        break;
    default:
        break;
    }

    switch (EXTI2_INIT_STATE)
    {
    case EXTI_ENABLE:
        SET_BIT(GICR, GICR_INT2_BIT);
        break;
    case EXTI_DISABLE:
        CLR_BIT(GICR, GICR_INT2_BIT);
        break;
    default:
        break;
    }

    /* Checking init Sense control setting of each interrupt */
    switch (EXTI0_SENSE_CONTROL)
    {
    case EXTI_LOW_LEVEL_SC:
        CLR_BIT(MCUCR, MCUCR_ISC01_BIT);
        CLR_BIT(MCUCR, MCUCR_ISC00_BIT);
        break;

    case EXTI_FALLING_EDGE_SC:
        SET_BIT(MCUCR, MCUCR_ISC01_BIT);
        CLR_BIT(MCUCR, MCUCR_ISC00_BIT);
        break;

    case EXTI_RISING_EDGE_SC:
        SET_BIT(MCUCR, MCUCR_ISC01_BIT);
        SET_BIT(MCUCR, MCUCR_ISC00_BIT);
        break;

    case EXTI_ONCHANGE_SC:
        CLR_BIT(MCUCR, MCUCR_ISC01_BIT);
        SET_BIT(MCUCR, MCUCR_ISC00_BIT);
        break;
    }

    switch (EXTI1_SENSE_CONTROL)
    {
    case EXTI_LOW_LEVEL_SC:
        CLR_BIT(MCUCR, MCUCR_ISC11_BIT);
        CLR_BIT(MCUCR, MCUCR_ISC10_BIT);
        break;

    case EXTI_FALLING_EDGE_SC:
        SET_BIT(MCUCR, MCUCR_ISC11_BIT);
        CLR_BIT(MCUCR, MCUCR_ISC10_BIT);
        break;

    case EXTI_RISING_EDGE_SC:
        SET_BIT(MCUCR, MCUCR_ISC11_BIT);
        SET_BIT(MCUCR, MCUCR_ISC10_BIT);
        break;

    case EXTI_ONCHANGE_SC:
        CLR_BIT(MCUCR, MCUCR_ISC11_BIT);
        SET_BIT(MCUCR, MCUCR_ISC10_BIT);
        break;
    }

    switch (EXTI2_SENSE_CONTROL)
    {
    case EXTI_FALLING_EDGE_SC:
        CLR_BIT(MCUCSR, MCUCSR_ISC2_BIT);
        break;

    case EXTI_RISING_EDGE_SC:
        SET_BIT(MCUCSR, MCUCSR_ISC2_BIT);
        break;
    }
}

/**
 * @brief A function to enable the required external interrupts (INT0,INT1,INT2)
 * @param Copy_u8IntNumber: the number of the external interrupt (0,1,2)
 * @return the Error state of the function
 */
u8 EXTI_u8Enable(u8 Copy_u8IntNumber)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8IntNumber >= EXTI_NO_OF_EXTI)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8IntNumber)
        {
        case EXTI_INT0:
            SET_BIT(GICR, GICR_INT0_BIT);
            break;
        case EXTI_INT1:
            SET_BIT(GICR, GICR_INT1_BIT);
            break;
        case EXTI_INT2:
            SET_BIT(GICR, GICR_INT2_BIT);
            break;
        }
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to disable the required external interrupts (INT0,INT1,INT2)
 * @param Copy_u8IntNumber: the number of the external interrupt (0,1,2)
 * @return the Error state of the function
 */
u8 EXTI_u8Disable(u8 Copy_u8IntNumber)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8IntNumber >= EXTI_NO_OF_EXTI)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8IntNumber)
        {
        case EXTI_INT0:
            CLR_BIT(GICR, GICR_INT0_BIT);
            break;
        case EXTI_INT1:
            CLR_BIT(GICR, GICR_INT1_BIT);
            break;
        case EXTI_INT2:
            CLR_BIT(GICR, GICR_INT2_BIT);
            break;
        }
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to set the sense level of the required external interrupts (INT0,INT1,INT2)
 * @param Copy_u8IntNumber: the number of the external interrupt (0,1,2)
 * @param Copy_u8SenseLevel: the sense level of the external interrupt
 * @return the Error state of the function
 */
u8 EXTI_u8SetSenseLevel(u8 Copy_u8IntNumber, u8 Copy_u8SenseLevel)
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8IntNumber >= EXTI_NO_OF_EXTI)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8IntNumber)
        {
        case EXTI_INT0:
            switch (Copy_u8SenseLevel)
            {
            case EXTI_LOW_LEVEL_SC:
                CLR_BIT(MCUCR, MCUCR_ISC01_BIT);
                CLR_BIT(MCUCR, MCUCR_ISC00_BIT);
                break;

            case EXTI_FALLING_EDGE_SC:
                SET_BIT(MCUCR, MCUCR_ISC01_BIT);
                CLR_BIT(MCUCR, MCUCR_ISC00_BIT);
                break;

            case EXTI_RISING_EDGE_SC:
                SET_BIT(MCUCR, MCUCR_ISC01_BIT);
                SET_BIT(MCUCR, MCUCR_ISC00_BIT);
                break;

            case EXTI_ONCHANGE_SC:
                CLR_BIT(MCUCR, MCUCR_ISC01_BIT);
                SET_BIT(MCUCR, MCUCR_ISC00_BIT);
                break;
            }
            break;

        case EXTI_INT1:
            switch (Copy_u8SenseLevel)
            {
            case EXTI_LOW_LEVEL_SC:
                CLR_BIT(MCUCR, MCUCR_ISC11_BIT);
                CLR_BIT(MCUCR, MCUCR_ISC10_BIT);
                break;

            case EXTI_FALLING_EDGE_SC:
                SET_BIT(MCUCR, MCUCR_ISC11_BIT);
                CLR_BIT(MCUCR, MCUCR_ISC10_BIT);
                break;

            case EXTI_RISING_EDGE_SC:
                SET_BIT(MCUCR, MCUCR_ISC11_BIT);
                SET_BIT(MCUCR, MCUCR_ISC10_BIT);
                break;

            case EXTI_ONCHANGE_SC:
                CLR_BIT(MCUCR, MCUCR_ISC11_BIT);
                SET_BIT(MCUCR, MCUCR_ISC10_BIT);
                break;
            }
            break;

        case EXTI_INT2:
            if (Copy_u8SenseLevel == EXTI_LOW_LEVEL_SC || Copy_u8SenseLevel == EXTI_ONCHANGE_SC)
            {
                Local_u8ErrorState = STATUS_ERROR;
            }

            else
            {
                switch (Copy_u8SenseLevel)
                {
                case EXTI_FALLING_EDGE_SC:
                    CLR_BIT(MCUCSR, MCUCSR_ISC2_BIT);
                    break;

                case EXTI_RISING_EDGE_SC:
                    SET_BIT(MCUCSR, MCUCSR_ISC2_BIT);
                    break;
                }
            }
        }
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/**
 * @brief A function to set the callback function for the required external interrupts (INT0,INT1,INT2)
 * @param Copy_u8IntNumber: the number of the external interrupt (0,1,2)
 * @param Copy_PVCallBack: the address of the callback function
 * @return the Error state of the function
 */
u8 EXTI_u8SetCallBack(u8 Copy_u8IntNumber, void (*Copy_PVCallBack)(void))
{
    /* Local variable to hold the error state */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8IntNumber >= EXTI_NO_OF_EXTI)
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    else
    {
        PVCallBack[Copy_u8IntNumber] = Copy_PVCallBack;
    }

    /* Return the error state */
    return Local_u8ErrorState;
}

/* The ISR of the external interrupt INT0 */
void __vector_1(void)
{
    if (PVCallBack[EXTI_INT0] != NULL)
        PVCallBack[EXTI_INT0]();
}

/* The ISR of the external interrupt INT1 */
void __vector_2(void)
{
    if (PVCallBack[EXTI_INT1] != NULL)
        PVCallBack[EXTI_INT1]();
}

/* The ISR of the external interrupt INT2 */
void __vector_3(void)
{
    if (PVCallBack[EXTI_INT2] != NULL)
        PVCallBack[EXTI_INT2]();
}
