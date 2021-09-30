/** @file USART_interface.h
 * 
 * @brief A header file including functions for USART. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 30, 2021       
 *
 */

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_VidInit();

void USART_VidSendByte(u8 Copy_u8Data);

u8 USART_u8ReceiveByte();

void USART_VidSendString(u8 *Copy_u8String);

void USART_VidReceiveString(u8 *Copy_u8String);

#endif /* USART_INTERFACE_H */

/*** end of file ***/
