/** @file SSD_interface.h
 *
 * @brief A header file including functions for 7SEG interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 30, 2022
 *
 */

/* Include Guard */
#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

/* A enum for SSD Numbers */
typedef enum
{
    SSD_ZERO,
    SSD_ONE,
    SSD_TWO,
    SSD_THREE,
    SSD_FOUR,
    SSD_FIVE,
    SSD_SIX,
    SSD_SEVEN,
    SSD_EIGHT,
    SSD_NINE
} enut_SSD;

/**
 * @brief SSD Initialization function
 * @param void
 * @return void
 */
void SSD_VidInit(void);

/**
 * @brief SSD Display Number function
 * @param Copy_u8SSDNum: SSD number
 * @param Copy_u8Number: Number to be displayed
 * @return u8: Error state
 */
u8 SSD_VidDisplayNumber(u8 Copy_u8SSDNum, u8 Copy_u8Number);
#endif /* SSD_INTERFACE_H */

/*** end of file ***/