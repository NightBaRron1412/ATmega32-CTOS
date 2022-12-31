/** @file USART_interface.h
 * 
 * @brief A header file including functions for USART. 
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022    
 *
 */

/* Include guard */
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/**
 * @brief A function to initialize USART.
 * @param void
 * @return void
 */
void USART_VidInit();

/**
 * @brief A function to send a byte using USART.
 * @param Copy_u8Data The data to be sent.
 * @return u8 The status of the function.
 */
u8 USART_u8SendByte(u8 Copy_u8Data);

/**
 * @brief A function to send a string using USART in synchronous mode.
 * @param Copy_u8String The string to be sent.
 * @return u8 The status of the function.
 */
u8 USART_VidSendStringSynch(u8 *Copy_u8String);

/**
 * @brief A function to send a string using USART in asynchronous mode.
 * @param Copy_u8String The string to be sent.
 * @param Callback The function to be called when the transmission is done.
 * @return u8 The status of the function.
 */
u8 USART_VidSendStringAsynch(u8 *Copy_u8String, void (*Callback)(void));

/**
 * @brief A function to receive a byte using USART.
 * @param Copy_u8Byte The byte to be received.
 * @return u8 The status of the function.
 */
u8 USART_u8ReceiveByte(u8 *Copy_u8Byte);

/**
 * @brief A function to receive a string using USART in synchronous mode.
 * @param Copy_u8String The string to be received.
 * @return u8 The status of the function.
 */
u8 USART_VidReceiveStringSynch(u8 *Copy_u8String);

/**
 * @brief A function to receive a string using USART in asynchronous mode.
 * @param Copy_u8String The string to be received.
 * @param Callback The function to be called when the reception is done.
 * @return u8 The status of the function.
 */
u8 USART_VidReceiveStringAsynch(u8 *Copy_u8String, void (*Callback)(void));

#endif /* USART_INTERFACE_H */

/*** end of file ***/
