/** @file TWI_config.h
 *
 * @brief A header file including configurations for AVR Two wire interface.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Jan 01, 2023
 *
 */

/* Include guard */
#ifndef TWI_CONFIG_H
#define TWI_CONFIG_H

/* Select the division factor for the bit rate generator */
#define TWI_BIT_RATE 0x02

/**
 * Macro to select the state of the TWI Prescaler Bits
 * Range: TWI_PRESCALER_1
 *        TWI_PRESCALER_4
 *        TWI_PRESCALER_16
 *        TWI_PRESCALER_64
 */
#define TWI_PRESCALER_BITS TWI_PRESCALER_1

/**
 * Macro to select the state of the TWI Ack Bit
 * Range: TWI_ENABLE
 *        TWI_DISABLE
 */
#define TWI_ACK_BIT_STATE TWI_ENABLE

/**
 * Macro to select the state of the TWI Interrupts
 * Range: TWI_ENABLE
 *        TWI_DISABLE
 */
#define TWI_INT_STATE TWI_DISABLE

/* The slave address of the controller in case it becomes slave in the network */
#define TWI_SLAVE_ADDRESS 0x44

/**
 * Macro to select the state of the TWI General Call Recognition
 * Range: TWI_ENABLE
 *        TWI_DISABLE
 */
#define TWI_GEN_CALL_RECOG_STATE TWI_DISABLE

/* Macro to define the timeout which determines the fault time in the SPI upon transmitting or receiving */
#define TWI_TIMEOUT 50000

#endif /* TWI_CONFIG_H */

/*** end of file ***/