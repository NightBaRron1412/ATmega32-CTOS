/** @file KPD_config.h
 *
 * @brief A header file including configurations for KPD controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 24, 2022
 *
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/**
 * Macros for setting the connection mode for the keypad
 * Ranges: KPD_EXT_PULLUP
 *         KPD_INT_PULLUP
 *         KPD_PULLDOWN
 */
#define KPD_CONNECTION_MODE KPD_INT_PULLUP

/* Macros for the keypad size */
#define ROWS_NUMBER 4
#define COLUMNS_NUMBER 4

/* Macros for the keypad keys */
#define KPD_U8ARR           \
{                           \
    {'1', '2', '3', 'A'},   \
    {'4', '5', '6', 'B'},   \
    {'7', '8', '9', 'C'},   \
    {'*', '0', '#', 'D'}    \
                            \
}

/* Keypad Port */
#define KPD_PORT PORT_B

/* The the COLUMN pins -Output- */
#define KPD_COLUMN0_PIN PIN_0
#define KPD_COLUMN1_PIN PIN_1
#define KPD_COLUMN2_PIN PIN_2
#define KPD_COLUMN3_PIN PIN_3

/* The the ROW pins -Input- */

#define KPD_ROW0_PIN PIN_4
#define KPD_ROW1_PIN PIN_5
#define KPD_ROW2_PIN PIN_6
#define KPD_ROW3_PIN PIN_7

#endif /* KPD_CONFIG_H */

/*** end of file ***/
