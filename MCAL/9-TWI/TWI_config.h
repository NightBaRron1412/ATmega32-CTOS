/** @file TWI_config.h
 * 
 * @brief A header file including configurations for AVR Two wire interface. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 31, 2021       
 *
 */

#ifndef TWI_CONFIG_H
#define TWI_CONFIG_H

#define TWI_READ 1
#define TWI_WRITE 0

//Select the division factor for the bit rate generator
#define TWI_BIT_RATE 0x02

//Specify state of the TWI Prescaler Bits
#define TWI_PRESCALER_BITS TWI_PRESCALER_1

/**
 * Options:
 * TWI_PRESCALER_1
 * TWI_PRESCALER_4
 * TWI_PRESCALER_16
 * TWI_PRESCALER_64
*/

//Specify state of the Acknowledge Bit
#define TWI_ACK_BIT_STATE TWI_ENABLE

/**
 * Options:
 * TWI_ENABLE
 * TWI_DISABLE
*/

//Specify state of the Two-wire Serial Interface Interrupt
#define TWI_INT_STATE TWI_DISABLE

/**
 * Options:
 * TWI_ENABLE
 * TWI_DISABLE
*/

//Determine the slave address of the controller in case if it becomes slave in the network
#define TWI_SLAVE_ADDRESS 0x44

//Enable/disable the recognition of a General Call given over the Two-wire Serial Bus
#define TWI_GEN_CALL_RECOG_STATE TWI_DISABLE

/**
 * Options:
 * TWI_ENABLE
 * TWI_DISABLE
*/

#endif /* TWI_CONFIG_H */

/*** end of file ***/