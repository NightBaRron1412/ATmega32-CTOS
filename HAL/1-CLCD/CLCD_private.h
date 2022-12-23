/** @file CLCD_private.h
 *
 * @brief A header file private definitions for CLCD controlling.
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2020
 *
 */

/* Include guard */
#ifndef CLCD_PRIVATE_H
#define CLCD_PRIVATE_H

/* Macros for defining the CLCD connection modes */
#define CLCD_4BIT 0
#define CLCD_8BIT 1

/* Macros for defining the CLCD function set commands */
#define CLCD_8BIT_1LINE 0x30
#define CLCD_8BIT_2LINES 0x38
#define CLCD_4BIT_1LINE 0x20
#define CLCD_4BIT_2LINES 0x28

/* Macros for defining the CLCD display control commands */
#define CLCD_DISPLAY_OFF_CURSOR_OFF 0x08
#define CLCD_DISPLAY_ON_CURSOR_OFF 0x0C
#define CLCD_DISPLAY_ON_CURSOR_ON 0x0E

#endif /* CLCD_PRIVATE_H */

/*** end of file ***/