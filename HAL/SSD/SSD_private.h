/** @file SSD_interface.h
 *
 * @brief A header file including SSD Numbers Array for 7SEG interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 30, 2022
 *
 */

/* Include Guard */
#ifndef SSD_PRIVATE_H
#define SSD_PRIVATE_H

/* Private Macros for SSD Types */
#define SSD_COMMON_CATHODE 0
#define SSD_COMMON_ANODE 1

/* Private Macro for the maximum number that can be displayed on a SSD */
#define SSD_MAX_NUM 9

/* Private Macro for the minimum number that can be displayed on a SSD */
#define SSD_MIN_NUM 0

/*
 * array that contains seven segment numbers' representation in binary that will be
 * used to display corresponding number when assigned to a given port
 */
const u8 SSD_Au87SegArray[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x4F};

#endif /* SSD_PRIVATE_H */

/*** end of file ***/