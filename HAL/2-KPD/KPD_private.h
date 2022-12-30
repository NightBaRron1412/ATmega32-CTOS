/** @file KPD_private.h
 *
 * @brief A header file private definitions that shouldn't be edited for KPD.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 24, 2022
 *
 */

/* Include guard */
#ifndef KPD_PRIVATE_H
#define KPD_PRIVATE_H

/* Private Macros for if the button is pressed or not */
#define PRESSED LOW
#define NOT_PRESSED HIGH

/* Private Macros for the connection mode */
#define KPD_EXT_PULLUP 0
#define KPD_INT_PULLUP 1
#define KPD_PULLDOWN 2

#endif /* KPD_PRIVATE_H */

/*** end of file ***/