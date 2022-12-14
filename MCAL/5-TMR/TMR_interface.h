/** @file TMR_interface.h
 *
 * @brief A header file including Functions prototypes for TMR
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 10, 2022
 *
 */

/* Include guard */
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

/* definitions for time */
#define SEC (u32)1000000
#define mSEC (u32)1000

/* Enum to hold Timer names for interfacing */
typedef enum
{
    TIMER_0, /* 0 */
    TIMER_1, /* 1 */
    TIMER_2, /* 2 */

} enut_TMR;

/*
 * Description: Function to set the initialized state and prescaler for each timer (0,1,2)
 * Inputs: none
 * Output: void
 */
void TMR_VidInit(void);

/*
 * Description: Function to enable one of the available timers in AVR ATmega32 (0,1,2)
 * Inputs: Timer Number
 * Output: the Error state of the function
 */
u8 TMR_u8EnableTimer(u8 Copy_u8TimerNumber);

/*
 * Description: Function to disable one of the available timers in AVR ATmega32 (0,1,2)
 * Inputs: Timer Number
 * Output: the Error state of the function
 */
u8 TMR_u8DisableTimer(u8 Copy_u8TimerNumber);

/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timers(0,1,2)
 * Inputs: Timer Number and the desired duty cycle
 * Output: the Error state of the function
 */
u8 TMR_u8SetDutyCycle(u8 Copy_u8TimerNumber, u8 Copy_u8DutyCycle);

/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timer1,Pins OC1A or/and OC1B
 * (used mainly in servo interfacing)
 * Inputs: The desired timer compare value
 * Output: void
 */
void TMR_VidSetPWM(u16 Copy_u16ReqCompValue);

/*
 * Description: Function to set the delay time for the required timer
 * this function can be used for making delay (in case of Timer normal mode)
 * or for specifying a sampling time (in case of Timer CTC mode)
 * Inputs: the delay time in microsecond
 * Output: the Error state of the function
 */
u8 TMR_u8SetDesiredTime(u8 Copy_u8TimerNumber, u32 Copy_u32Time_us);

/*
 * Description: Function to set the callback function for a certain timer in case of firing its interrupt
 * Inputs: the number of the available timer (0,1,2) and a pointer to its callback function
 * Output: the Error state of the function
 */
u8 TMR_u8SetCallBack(u8 Copy_u8TimerNumber, void (*Copy_PVCallBack)(void));

/*========================== Functions related to Input Capture Mode ==========================*/

/*
 * Description: Function to enable input capture interrupt
 * Inputs: void
 * Output: void
 */
void TMR_VidEnableIcuInterrupt(void);

/*
 * Description: Function to disable input capture interrupt
 * Inputs: void
 * Output: void
 */
void TMR_VidDisableIcuInterrupt(void);

/*
 * Description: Function to get the Period of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the period
 * Output: the Error state of the function
 */
u8 TMR_u8GetPeriod(u16 *Copy_Pu16Period);

/*
 * Description: Function to get the Duty Cycle of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the Duty Cycle
 * Output: the Error state of the function
 */
u8 TMR_u8GetDutyCycle(u16 *Copy_Pu16DutyCycle);

/*
 * Description: Function to get the OnTime of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the OnTime
 * Output: the Error state of the function
 */
u8 TMR_u8OnTime(u16 *Copy_Pu16OnTime);

/*
 * Description: Function to get the OffTime of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the OffTime
 * Output: the Error state of the function
 */
u8 TMR_u8OffTime(u16 *Copy_Pu16OffTime);

#endif /* TMR_INTERFACE_H */

/*** end of file ***/