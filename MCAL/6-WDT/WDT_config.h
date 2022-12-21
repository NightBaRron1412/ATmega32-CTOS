/** @file WDT_config.h
 * 
 * @brief A header file configs for WatchDog Timer. 
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022       
 *
 */

/* Includes Guard */
#ifndef WDT_CONFIG_
#define WDT_CONFIG_

/** Macros for WatchDog Timer initialization state
 * Range: WDT_ENABLE
 *        WDT_DISABLE
 */
#define WDT_INIT_STATE WDT_DISABLE

/** Macros for WatchDog Timer Periods (Values at typical 5V)
 * Range: WDT_16MS
 *        WDT_32MS
 *        WDT_65MS
 *        WDT_130MS
 *        WDT_260MS
 *        WDT_520MS
 *        WDT_1000MS
 *        WDT_2100MS
 */
#define WDT_INIT_PERIOD WDT_16MS

#endif /* WDT_CONFIG_H */

/*** end of file ***/