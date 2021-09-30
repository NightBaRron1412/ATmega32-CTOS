/** @file TMR_interface.h
 * 
 * @brief A header file including Funtions prototypes for TMR
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 25, 2021       
 *
 */

#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

void TMR_VidInit();

void TMR_VidDisableTimer(u8 Copy_u8TimerNb);

void TMR_VidEnableTimer(u8 Copy_u8TimerNb);

void TMR_VidSetDutyCycle(u8 Copy_u8TimerNb, u8 Copy_u8DutyCycle);

void TMR_VidSetPWM(u16 Copy_u16ReqCompValue);

void TMR_VidSetCallBack(u8 Copy_u8TimerNb, void (*Copy_PVCallBack)(void));

/*-----------------------------Functions related to Input Capture Mode----------------------------------*/

void TMR_VidEnableIcuInterrupt();

void TMR_VidDisbleIcuInterrupt();

u16 TMR_u16GetPeriod();

u16 TMR_u16GetDutyCycle();

u16 TMR_u16OnTime();

u16 TMR_u16OffTime();

#endif /* TMR_INTERFACE_H */

/*** end of file ***/