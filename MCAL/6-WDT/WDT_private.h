/** @file WDT_private.h
 * 
 * @brief A header file including registers and bit definitions for WatchDog Timer controlling. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 9, 2021       
 *
 */

#ifndef WDT_PRIVATE_
#define WDT_PRIVATE_

#define WDTCR (*(volatile u8 *)0x41)

/* WDTCR bits */
#define WDTCR_WDTOE 4
#define WDTCR_WDE 3
#define WDTCR_WDP2 2
#define WDTCR_WDP1 1
#define WDTCR_WDP0 0

#endif /* WDT_PRIVATE_H */

/*** end of file ***/