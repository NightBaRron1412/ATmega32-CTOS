/** @file CLCD_config.h
 *
 * @brief A header file including functions for CLCD controlling.
 *
 * @author Amir Shetaia
 * @version 1.1
 * @date Nov 06, 2022
 *
 */

/* Include guard */
#ifndef CLCD_CONFIG_H
#define CLCD_CONFIG_H

/**
 * Macros for setting CLCD connection mode
 * Range:  CLCD_4BIT
 *         CLCD_8BIT
 */
#define CLCD_MODE CLCD_4BIT

/**
 * Macros for setting initial commands for CLCD function set
 * Range:  CLCD_8BIT_1LINE
 *         CLCD_8BIT_2LINES
 *         CLCD_4BIT_1LINE
 *         CLCD_4BIT_2LINES
 */
#define CLCD_INIT_FUNCTION_SET CLCD_4BIT_2LINES

/**
 * Macros for setting the initial commands for Display on/off control
 * Range:  CLCD_DISPLAY_OFF_CURSOR_OFF
 *         CLCD_DISPLAY_ON_CURSOR_OFF
 *         CLCD_DISPLAY_ON_CURSOR_ON
 */
#define CLCD_INIT_DISPLAY_CONTROL CLCD_DISPLAY_ON_CURSOR_OFF

/* Control Port */
#define CLCD_CTRL_PORT PORT_D
#define CLCD_RS_PIN PIN_0
#define CLCD_RW_PIN PIN_1
#define CLCD_EN_PIN PIN_2

/* Data Port */
#define CLCD_DATA_PORT PORT_D

#endif /* CLCD_CONFIG_H */

/*** end of file ***/