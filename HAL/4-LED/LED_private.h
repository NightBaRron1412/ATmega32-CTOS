/** @file LED_private.h
 *
 * @brief A header file including LED config options.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 10, 2022
 *
 */

/* Include Guard */
#ifndef LED_PRIVATE_H
#define LED_PRIVATE_H

/*========================================================*/

/* Macros for LEDs ports connection options */
#define LED_PORT_A PORT_A
#define LED_PORT_B PORT_B
#define LED_PORT_C PORT_C
#define LED_PORT_D PORT_D

/* Macros for LEDs pins connection options */
#define LED_PIN_0 PIN_0
#define LED_PIN_1 PIN_1
#define LED_PIN_2 PIN_2
#define LED_PIN_3 PIN_3
#define LED_PIN_4 PIN_4
#define LED_PIN_5 PIN_5
#define LED_PIN_6 PIN_6
#define LED_PIN_7 PIN_7

/* Macros for LEDs direction options */
#define LED_FORWARD 0
#define LED_REVERSE 1

/* Macros for LEDs init state options */
#define LED_ON 1
#define LED_OFF 0

/*========================================================*/

#endif /* LED_PRIVATE_H */

/*** end of file ***/