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

/**
 * @brief A function to initialize the Timer peripheral
 * @param void
 * @return void
 */
void TMR_VidInit(void);

/**
 * @brief A function to enable one of the available timers in AVR ATmega32 (0,1,2)
 * @param Copy_u8TimerNumber: the number of the available timer (0,1,2)
 * @return the Error state of the function
 */
u8 TMR_u8EnableTimer(u8 Copy_u8TimerNumber);

/**
 * @brief A function to disable one of the available timers in AVR ATmega32 (0,1,2)
 * @param Copy_u8TimerNumber: the number of the available timer (0,1,2)
 * @return the Error state of the function
 */
u8 TMR_u8DisableTimer(u8 Copy_u8TimerNumber);

/**
 * @brief Function to set the duty cycle of the PWM signal generated from Timers(0,1,2)
 * @param Copy_u8TimerNumber: the number of the available timer (0,1,2)
 * @param Copy_u8DutyCycle: the desired duty cycle
 * @return the Error state of the function
 */
u8 TMR_u8SetDutyCycle(u8 Copy_u8TimerNumber, u8 Copy_u8DutyCycle);

/**
 * @brief Function to set the duty cycle of the PWM signal generated from Timer1,Pins OC1A or/and OC1B
 * @param Copy_u16ReqCompValue: the desired timer compare value
 * @return the Error state of the function
 */
void TMR_VidSetPWM(u16 Copy_u16ReqCompValue);

/**
 * @brief Function to set the desired time for a certain timer in case of firing its interrupt
 * @param Copy_u8TimerNumber: the number of the available timer (0,1,2)
 * @param Copy_u32Time_us: the desired time in micro seconds
 * @return the Error state of the function
 */
u8 TMR_u8SetDesiredTime(u8 Copy_u8TimerNumber, u32 Copy_u32Time_us);

/**
 * @brief Function to set the callback function for a certain timer
 * @param Copy_u8TimerNumber: the number of the available timer (0,1,2)
 * @param Copy_PVCallBack: the address of the callback function
 * @return the Error state of the function
 */
u8 TMR_u8SetCallBack(u8 Copy_u8TimerNumber, void (*Copy_PVCallBack)(void));

/*========================== Functions related to Input Capture Mode ==========================*/

/**
 * @brief Function to enable input capture interrupt
 * @param void
 * @return void
 */
void TMR_VidEnableIcuInterrupt(void);

/**
 * @brief Function to disable input capture interrupt
 * @param void
 * @return void
 */
void TMR_VidDisableIcuInterrupt(void);

/**
 * @brief Function to get the period of the signal received by the input capture pin ICP1 (D6)
 * @param Copy_Pu16Period: the container variable which will hold the value of the period
 * @return the Error state of the function
 */
u8 TMR_u8GetPeriod(u16 *Copy_Pu16Period);

/**
 * @brief Function to get the duty cycle of the signal received by the input capture pin ICP1 (D6)
 * @param Copy_Pu16DutyCycle: the container variable which will hold the value of the duty cycle
 * @return the Error state of the function
 */
u8 TMR_u8GetDutyCycle(u16 *Copy_Pu16DutyCycle);

/**
 * @brief Function to get the OnTime of the signal received by the input capture pin ICP1 (D6)
 * @param Copy_Pu16OnTime: the container variable which will hold the value of the OnTime
 * @return the Error state of the function
 */
u8 TMR_u8OnTime(u16 *Copy_Pu16OnTime);

/**
 * @brief Function to get the OffTime of the signal received by the input capture pin ICP1 (D6)
 * @param Copy_Pu16OffTime: the container variable which will hold the value of the OffTime
 * @return the Error state of the function
 */
u8 TMR_u8OffTime(u16 *Copy_Pu16OffTime);

#endif /* TMR_INTERFACE_H */

/*** end of file ***/