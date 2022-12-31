/** @file USART_config.h
 *
 * @brief A header file including configurations for USART.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022
 *
 */

/* Include guard */
#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/* Defining the System clock which feeds the USART peripheral */
#define FCPU 8000000

/* Specifying the desired USART Baudrate */
#define USART_BAUDRATE 9600

#define UBRR_Value (((FCPU / (USART_BAUDRATE * 16UL))) - 1)
#define UBRR_Value2X (((FCPU / (USART_BAUDRATE * 8UL))) - 1)

/**
 * Macro to specify the desired USART mode of operation
 * Range: USART_NORMAL_MODE
 *        USART_DBL_SPD_MODE
 */
#define USART_MODE USART_DBL_SPD_MODE

/**
 * Macro to specify the desired USART state of TX and RX
 * Range: USART_ENABLE
 *        USART_DISABLE
 */
#define USART_TX_STATE USART_ENABLE
#define USART_RX_STATE USART_ENABLE

/**
 * Macro to specify the parity bit type
 * Range: USART_NO_PARITY
 *        USART_EVEN_PARITY
 *        USART_ODD_PARITY
 */
#define USART_PARITY USART_NO_PARITY

/**
 * Macro to specify the number of stop bits
 * Range: USART_ONE_BIT
 *        USART_TWO_BITS
 */
#define USART_NO_OF_STP_BITS USART_ONE_BIT

/**
 * Macro to specify the data size
 * Range: USART_FIVE_BITS
 *        USART_SIX_BITS
 *        USART_SEVEN_BITS
 *        USART_EIGHT_BITS
 *        USART_NINE_BITS
 */
#define USART_DATA_SIZE USART_EIGHT_BITS

/* Defining the timeout which determines the fault time in the USART TX/RX */
#define USART_TIMEOUT 40000

#endif /* USART_CONFIG_H */

/*** end of file ***/