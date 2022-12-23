/** @file CLCD_interface.h
 *
 * @brief A header file including functions for CLCD controlling.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2022
 *
 */

/* Include Guard */
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

/**
 * @brief A function for initializing the CLCD.
 * @param void
 * @return void
 */
void CLCD_VidInit(void);

/**
 * @brief A function for sending a command to the CLCD.
 * @param Copy_u8Command: The command to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_u8SendCommand(u8 Copy_u8Command);

/**
 * @brief A function for sending a data to the CLCD.
 * @param Copy_u8Data: The data to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_u8SendData(u8 Copy_u8Data);

/**
 * @brief A function for clearing the CLCD.
 * @param void
 * @return void
 */
void CLCD_VidDisplayClear(void);

/**
 * @brief A function for going to a specific position on the CLCD.
 * @param Copy_u8XPos: The X position to go to.
 * @param Copy_u8YPos: The Y position to go to.
 * @return void
 */
void CLCD_VidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);

/**
 * @brief A function for creating a special character.
 * @param Copy_u8Pattern: The pattern of the special character.
 * @param Copy_u8PatternNumber: The number of the special character.
 * @return The Error state of the function.
 */
u8 CLCD_u8CreatSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber);

/**
 * @brief A function for sending a string to the CLCD.
 * @param Copy_u8Str: The string to be sent.
 * @return The Error state of the function.
 */
u8 CLCD_u8SendString(u8 *Copy_u8Str);

#endif /* CLCD_INTERFACE_H */

/*** end of file ***/