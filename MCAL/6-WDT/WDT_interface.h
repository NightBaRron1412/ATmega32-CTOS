/** @file WDT_interface.h
 *
 * @brief A header file including functions for WatchDog Timer controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/* Includes Guard */
#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

/* Macros for WatchDog Timer Periods (Values at typical 5V) */
#define WDT_16MS 0
#define WDT_32MS 1
#define WDT_65MS 2
#define WDT_130MS 3
#define WDT_260MS 4
#define WDT_520MS 5
#define WDT_1000MS 6
#define WDT_2100MS 7

/*
 * Description: Function to initialize the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidInit(void);

/*
 * Description: Function to Enable the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidEnable(void);

/*
 * Description: Function to set the timeout period of the WatchDog Timer
 * Inputs: the timeout period of the WatchDog Timer
 * Output: Error State of the function
 */
u8 WDT_u8SetTimeout(u8 Copy_u8Period);

/*
 * Description: Function to Disable the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidDisable(void);

/*
 * Description: Function to Reset the WatchDog Timer
 * Inputs: void
 * Output: void
 */
void WDT_VidResetTimer(void);

#endif /* WDT_INTERFACE_H */

/*** end of file ***/