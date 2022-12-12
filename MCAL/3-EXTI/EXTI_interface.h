/** @file EXTI_interface.h
 *
 * @brief A header file including APIs for EXTI controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 11, 2022
 *
 */

/* Include guard */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* Enum to hold Variables related to EXTI */
typedef enum
{

    EXTI_INT0,         /* 0 */
    EXTI_INT1,         /* 1 */
    EXTI_INT2,         /* 2 */
    EXTI_RISING_EDGE,  /* 3 */
    EXTI_FALLING_EDGE, /* 4 */
    EXTI_ONCHANGE,     /* 5 */
    EXTI_LOW_LEVEL,    /* 6 */

} enut_EXTI;

/*
 * Description: Function to initialize the external interrupts (INT0,INT1,INT2) according to the configurations
 * Inputs: void
 * Output: void
 */
void EXTI_VidInit(void);

/*
 * Description: Function to enable one of the required external interrupts (INT0,INT1,INT2)
 * Inputs: the number of the external interrupt (0,1,2)
 * Output: the Error state of the function
 */
u8 EXTI_u8Enable(u8 Copy_u8IntNumber);

/*
 * Description: Function to disable one of the required external interrupts (INT0,INT1,INT2)
 * Inputs: the number of the external interrupt (0,1,2)
 * Output: the Error state of the function
 */
u8 EXTI_u8Disable(u8 Copy_u8IntNumber);

/*
 * Description: Function to set the sense level of the required external interrupts (INT0,INT1,INT2)
 * Inputs: the number of the external interrupt (0,1,2) and the required sense level
 * Output: the Error state of the function
 */
u8 EXTI_u8SetSenseLevel(u8 Copy_u8IntNumber, u8 Copy_u8SenseLevel);

/*
 * Description: Function to set the callback function for the required external interrupts (INT0,INT1,INT2)
 * Inputs: the number of the external interrupt (0,1,2) and the callback function
 * Output: the Error state of the function
 */
u8 EXTI_u8SetCallBack(u8 Copy_u8IntNumber, void (*Copy_PVCallBack)(void));

#endif /* EXTI_INTERFACE_H */

/*** end of file ***/