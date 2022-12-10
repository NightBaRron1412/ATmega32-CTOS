/** @file GIE_interface.h
 * 
 * @brief A header file including APIs to enable or disable GIE 
 *
 * @author Amir Shetaia
 * @version 1.2
 * @date Aug 22, 2021       
 *
 */

/* include guard */
#ifndef GIE_INTERFACE_H
#define GIE_INTERFACE_H

/*
 * Description: Function to enable all the interrupts for AVR ATmega32
 * Inputs: void
 * Output: void
 */
void GIE_VidEnable(void);

/*
 * Description: Function to disable all the interrupts for AVR ATmega32
 * Inputs: void
 * Output: void
 */
void GIE_VidDisable(void);

#endif /* GIE_INTERFACE_H */

/*** end of file ***/