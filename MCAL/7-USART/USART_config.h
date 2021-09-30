/** @file USART_config.h
 * 
 * @brief A header file including configurations for USART. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 30, 2021       
 *
 */

#ifndef USART_CONFIG_H
#define USART_CONFIG_H

//Defining the System clock which feeds the USART peripheral
#define FCPU 8000000

//Specifying the desired USART Baudrate
#define USART_BAUDRATE 9600
#define UBRR_Value (((FCPU / (USART_BAUDRATE * 16UL))) - 1)
#define UBRR_Value2X (((FCPU / (USART_BAUDRATE * 8UL))) - 1)

//Specifying the USART mode
#define USART_MODE USART_DBL_SPD_MODE

/**
 * Options:
 * USART_NORMAL_MODE
 * USART_DBL_SPD_MODE
*/

//Specifying state of the USART transmitter and the receiver
#define USART_TX_STATE USART_ENABLE
#define USART_RX_STATE USART_ENABLE

/**
 * Options:
 * USART_ENABLE
 * USART_DISABLE
*/

//Selecting the parity type
#define USART_PARITY USART_NO_PARITY

/**
 * Options:
 * USART_NO_PARITY
 * USART_EVEN_PARITY
 * USART_ODD_PARITY
*/

//Selecting the number of the stop bits
#define USART_NO_OF_STP_BITS USART_ONE_BIT

/**
 * Options:
 * USART_ONE_BIT
 * USART_TWO_BITS
*/

//Selecting the data size

#define USART_DATA_SIZE USART_EIGHT_BITS

/**
 * Options:
 * USART_FIVE_BITS
 * USART_SIX_BITS
 * USART_SEVEN_BITS
 * USART_EIGHT_BITS
 * USART_NINE_BITS
*/

//Defining the timeout which determines the fault time in the USART TX/RX

#endif /* USART_CONFIG_H */

/*** end of file ***/