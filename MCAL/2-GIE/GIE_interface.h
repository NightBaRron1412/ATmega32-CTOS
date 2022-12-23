/** @file GIE_interface.h
 *
 * @brief A header file including APIs to enable or disable GIE
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2022
 *
 */

/* include guard */
#ifndef GIE_INTERFACE_H
#define GIE_INTERFACE_H

/**
 * @brief A function to enable all the interrupts for AVR ATmega32
 * @param void
 * @return void
 */
void GIE_VidEnable(void);

/**
 * @brief A function to disable all the interrupts for AVR ATmega32
 * @param void
 * @return void
 */
void GIE_VidDisable(void);

#endif /* GIE_INTERFACE_H */

/*** end of file ***/