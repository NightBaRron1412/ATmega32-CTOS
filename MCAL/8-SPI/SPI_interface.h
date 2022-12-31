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

/**
 * @brief A function to initialize the SPI module.
 * @param void
 * @return void
 */
void SPI_VidInit();

/**
 * @brief A function to send and receive a byte using SPI.
 * @param Copy_u8SentData The data needed to be sent.
 * @param Copy_Pu8ReceivedData A pointer to the variable needed to be filled with the received data.
 * @return u8 The error state.
 */
u8 SPI_u8TranceiveByte(u8 Copy_u8Data);

/**
 * @brief A function to send and receive a string using SPI.
 * @param Copy_Pu8SentString The string needed to be sent.
 * @param Copy_Pu8ReceivedString A pointer to the array needed to be filled with the received data.
 * @param CallBack A pointer to the function needed to be called after finishing transmission the buffer.
 * @return u8 The error state.
 */
u8 SPI_u8TranceiveStringAsynch(u8 *Copy_Pu8SentBuffer, u8 *Copy_Pu8RecBuffer, void (*CallBack)(void));

#endif /* SPI_INTERFACE_H */

/*** end of file ***/
