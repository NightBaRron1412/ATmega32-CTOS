/** @file TWI_interface.h
 *
 * @brief A header file including functions for TWI interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Jan 01, 2023
 *
 */

/* Include Guard */
#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

/* A Macro to define the TWI Operations (Read or Write) */
#define TWI_READ 1
#define TWI_WRITE 0

/**
 * @brief A function to initialize the AVR Two wire interface.
 * @param void
 * @return void
 */
void TWI_VidInit(void);

/**
 * @brief A function to send a start condition.
 * @param void
 * @return u8 function error state
 */
u8 TWI_u8Start(void);

/**
 * @brief A function to send Address and operation.
 * @param Copy_u8Address The address of the slave.
 * @param Copy_u8Operation The operation to be done (Read or Write).
 * @return u8 function error state
 */
u8 TWI_u8SendAddress(u8 Copy_u8Address, u8 Copy_u8Operation);

/**
 * @brief A function to send data.
 * @param Copy_u8Data The data to be sent.
 * @return u8 function error state
 */
u8 TWI_u8Write(u8 Copy_u8Data);

/**
 * @brief A function to read a byte.
 * @param Pu8RecData Pointer to the variable to hold the received data.
 * @return u8 function error state
 */
u8 TWI_u8ReadByte(u8 *Pu8RecData);

/**
 * @brief A function to send a stop condition.
 * @param void
 * @return u8 function error state
 */
u8 TWI_u8Stop(void);

#endif /* TWI_INTERFACE_H */

/*** end of file ***/
