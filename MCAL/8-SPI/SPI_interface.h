/** @file SPI_interface.h
 * 
 * @brief A header file including functions for SPI. 
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022      
 *
 */

/* Include guard */
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_VidInit();

u8 SPI_u8TranceiveByte(u8 Copy_u8Data);

void SPI_VidSendString(u8 *Copy_String);

void SPI_VidReceiveString(u8 *Copy_String);

#endif /* SPI_INTERFACE_H */

/*** end of file ***/
