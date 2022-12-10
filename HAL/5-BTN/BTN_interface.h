/** @file BTN_interface.h
 *
 * @brief A header file including functions APIS for Buttons Controlling.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Dec 10, 2022
 *
 */

#ifndef BTN_INTERFACE_H
#define BTN_INTERFACE_H

/* Enum to hold Buttons Numbers */
typedef enum
{
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,
    BUTTON_10,
    BUTTON_11,
    BUTTON_12,
    BUTTON_13,
    BUTTON_14,
    BUTTON_15,
    BUTTON_16,
    BUTTON_17,
    BUTTON_18,
    BUTTON_19,
    BUTTON_20,
    BUTTON_21,
    BUTTON_22,
    BUTTON_23,
    BUTTON_24,
    BUTTON_25,
    BUTTON_26,
    BUTTON_27,
    BUTTON_28,
    BUTTON_29,
    BUTTON_30,
    BUTTON_31,
    BUTTON_32,
} enut_BTN;

/* Enum to hold Buttons States */
typedef enum
{
    BTN_RELEASED,
    BTN_PRESSED,
} enut_BTN_STATE;

/*
 * Description: Function to set the initialized configuration of each Button
 * Inputs: none
 * Output: void
 */
void BTN_VidInit(void);

/*
 * Description: Function to get the state of a specific Button
 * Inputs: Button number and the container variable which will hold the state of this switch
 * Output: the Error state of the function
 */
u8 BTN_u8GetButtonState (u8 Copy_u8ButtonNumber, u8 *Copy_u8ButtonState);

#endif /* BTN_INTERFACE_H */

/*** end of file ***/
