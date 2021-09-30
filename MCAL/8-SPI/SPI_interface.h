/** @file SPI_interface.h
 * 
 * @brief A header file including functions for SPI. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 5, 2021       
 *
 */

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_VidInit();

void SPI_VidSendByte(u8 Copy_u8Data);

u8 SPI_u8ReceiveByte();

u8 SPI_u8TranceiveByte(u8 Copy_u8Data);

void SPI_VidSendString(u8 *Copy_String);

void SPI_VidReceiveString(u8 *Copy_String);

#endif /* SPI_INTERFACE_H */

/*** end of file ***/
