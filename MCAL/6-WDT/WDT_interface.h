/** @file WDT_interface.h
 * 
 * @brief A header file including functions for WatchDog Timer controlling. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 16, 2021       
 *
 */

#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

#define WDT_16_3_ms 0
#define WDT_32_5_ms 1
#define WDT_65_ms 2
#define WDT_0_13_s 3
#define WDT_0_26_s 4
#define WDT_0_52_s 5
#define WDT_1_s 6
#define WDT_2_1_s 7

void WDT_VidEnable(void);
void WDT_VidSleep(u8 Copy_u8Period);
void WDT_VidDisable(void);

#endif /* WDT_INTERFACE_H */

/*** end of file ***/