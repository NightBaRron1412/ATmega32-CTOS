/** @file BTN_config.h
 *
 * @brief A header file including init values and configs for Buttons.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 10, 2022
 *
 */

/* Include Guard */
#ifndef BTN_CONFIG_H
#define BTN_CONFIG_H

/* the number of Buttons connected to the controller */
#define BTN_NUM_OF_BUTTONS 3

/* BTNs ports                                         */
/* Range: BTN_PORT_A                                  */
/*         BTN_PORT_B                                 */
/*         BTN_PORT_C                                 */
/*         BTN_PORT_D                                 */
#define BTN0_DIO_PORT BTN_PORT_A
#define BTN1_DIO_PORT BTN_PORT_A
#define BTN2_DIO_PORT BTN_PORT_A

/* Array containing the ports connected to each configured Button */
u8 BTN_Au8ButtonPort[BTN_NUM_OF_BUTTONS] = {BTN0_DIO_PORT, BTN1_DIO_PORT, BTN2_DIO_PORT};

/* BTNs pins                                */
/* Range: BTN_PIN_0                         */
/*        BTN_PIN_1                         */
/*        BTN_PIN_2                         */
/*        BTN_PIN_3                         */
/*        BTN_PIN_4                         */
/*        BTN_PIN_5                         */
/*        BTN_PIN_6                         */
/*        BTN_PIN_7                         */
#define BTN0_DIO_PIN BTN_PIN_0
#define BTN1_DIO_PIN BTN_PIN_1
#define BTN2_DIO_PIN BTN_PIN_2

/* Array containing the pins connected to each configured Button */
u8 BTN_Au8ButtonPin[BTN_NUM_OF_BUTTONS] = {BTN0_DIO_PIN, BTN1_DIO_PIN, BTN2_DIO_PIN};

/* BTNs connection                             */
/* Range: BTN_PULL_DOWN                        */
/*        BTN_INT_PULL_UP                      */
/*        BTN_EXT_PULL_UP                      */
#define BTN0_CONNECTION BTN_INT_PULL_UP
#define BTN1_CONNECTION BTN_INT_PULL_UP
#define BTN2_CONNECTION BTN_INT_PULL_UP

/*Array containing the connection of each button */
u8 BTN_Au8ButtonConnection[BTN_NUM_OF_BUTTONS] = {BTN0_CONNECTION, BTN1_CONNECTION, BTN2_CONNECTION};

#endif /* BTN_CONFIG_H */

/*** end of file ***/