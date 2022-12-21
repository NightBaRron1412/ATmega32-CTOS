/** @file WDT_private.h
 *
 * @brief A header file including registers and bit definitions for WatchDog Timer controlling.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 21, 2022
 *
 */

/* Includes Guard */
#ifndef WDT_PRIVATE_
#define WDT_PRIVATE_

/* Private Macros for WatchDog Timer Periods (Values at typical 5V) */
#define WDT_16MS 0
#define WDT_32MS 1
#define WDT_65MS 2
#define WDT_130MS 3
#define WDT_260MS 4
#define WDT_520MS 5
#define WDT_1000MS 6
#define WDT_2100MS 7

/* Private Macros for WatchDog Timer initialization state */
#define WDT_ENABLE 1
#define WDT_DISABLE 0

/* WDTCR Register */
#define WDTCR (*(volatile u8 *)0x41)

/* WDTCR bits */
#define WDTCR_WDTOE 4
#define WDTCR_WDE 3
#define WDTCR_WDP2 2
#define WDTCR_WDP1 1
#define WDTCR_WDP0 0

#endif /* WDT_PRIVATE_H */

/*** end of file ***/