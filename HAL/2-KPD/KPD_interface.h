/** @file KPD_interface.h
 *
 * @brief A header file including functions for KPD interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 24, 2022
 *
 */

/* Include guard */
#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

/**
 * @brief A function to initialize the keypad
 * @param void
 * @return void
 */
void KPD_VidInit(void);

/**
 * @brief A function to get the pressed key
 * @param void
 * @return The pressed key
 */
u8 KPD_u8GetKey(u8 *Copy_Pu8KeyPressed);

#endif /* KPD_INTERFACE_H */

/*** end of file ***/