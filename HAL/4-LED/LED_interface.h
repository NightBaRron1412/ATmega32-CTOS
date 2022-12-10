/** @file LED_interface.h
 *
 * @brief A header file including functions APIS for LEDs Controlling.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 10, 2022
 *
 */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/* Enum to hold LEDs Numbers */
typedef enum
{
    LED_0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_10,
    LED_11,
    LED_12,
    LED_13,
    LED_14,
    LED_15,
    LED_16,
    LED_17,
    LED_18,
    LED_19,
    LED_20,
    LED_21,
    LED_22,
    LED_23,
    LED_24,
    LED_25,
    LED_26,
    LED_27,
    LED_28,
    LED_29,
    LED_30,
    LED_31,
    LED_32,
} enut_LED;

/*
 * Description: Function to set the initialized configuration of each LED
 * Inputs: none
 * Output: void
 */
void LED_VidInit(void);

/*
 * Description: Function to turn on a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8On(u8 Copy_u8LedNumber);

/*
 * Description: Function to turn off a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8Off(u8 Copy_u8LedNumber);

/*
 * Description: Function to toggle a specific LED
 * Inputs: LED number
 * Output: the Error state of the function
 */
u8 LED_u8Toggle(u8 Copy_u8LedNumber);

/*
 * Description: Function to blink a specific LED
 * Inputs: LED number, On time in ms, Off time in ms
 * Output: the Error state of the function
 */
u8 LED_u8Blink(u8 Copy_u8LedNumber, u8 Copy_u16OnTime_ms, u8 Copy_u16OffTime_ms);

#endif /* LED_INTERFACE_H */

/*** end of file ***/
