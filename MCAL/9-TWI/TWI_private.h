/** @file TWI_private.h
 *
 * @brief A header file including memory addresses for AVR Two wire interface registers.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Jan 01, 2023
 *
 */

/* Include guard */
#ifndef TWI_PRIVATE_H
#define TWI_PRIVATE_H

/* Macros to define the Status codes for Master Transmitter Mode */
#define TWI_START_SENT 0x08
#define TWI_REPEATED_START_SENT 0x10
#define TWI_MT_SLA_W_ACK 0x18
#define TWI_MT_SLA_W_NACK 0x20
#define TWI_MT_DATA_ACK 0x28
#define TWI_MT_DATA_NACK 0x30

/* Macros to define the TWI transmission states */
#define TWI_START 0
#define TWI_SEND_ADDRESS 1
#define TWI_SEND_DATA 2
#define TWI_STOP 3

/* Private macros to define the possible state of Two-wire Serial Interface Interrupts and the Ack Bit */
#define TWI_ENABLE 0
#define TWI_DISABLE 1

/* Private macros to define the available TWI Prescaler Bits */
#define TWI_PRESCALER_1 0
#define TWI_PRESCALER_4 1
#define TWI_PRESCALER_16 2
#define TWI_PRESCALER_64 3

/*========================== TWI Bit Rate Register ==========================*/

#define TWBR (*((volatile u8 *)0x20))

/* Defining the bits of TWBR register */

/* TWI Bit Rate Register */
#define TWBR_TWBR0 0
#define TWBR_TWBR1 1
#define TWBR_TWBR2 2
#define TWBR_TWBR3 3
#define TWBR_TWBR4 4
#define TWBR_TWBR5 5
#define TWBR_TWBR6 6
#define TWBR_TWBR7 7

/*========================== TWI Control Register ==========================*/

#define TWCR (*((volatile u8 *)0x56))

/*Defining the bits of TWCR register*/

/* TWI Interrupt Enable */
#define TWCR_TWIE 0

/* TWI Enable Bit */
#define TWCR_TWEN 2

/* TWI Write Collision Flag */
#define TWCR_TWWC 3

/* TWI STOP Condition Bit */
#define TWCR_TWSTO 4

/* TWI START Condition Bit */
#define TWCR_TWSTA 5

/* TWI Enable Acknowledge Bit */
#define TWCR_TWEA 6

/* TWI Interrupt Flag */
#define TWCR_TWINT 7

/*========================== TWI Status Register ==========================*/

#define TWSR (*((volatile u8 *)0x21))

/* Defining the bits of TWSR register * /

/* TWI Prescaler Bits */
#define TWSR_TWPS0 0
#define TWSR_TWPS1 1

/* TWI Status */
#define TWSR_TWS3 3
#define TWSR_TWS4 4
#define TWSR_TWS5 5
#define TWSR_TWS6 6
#define TWSR_TWS7 7

/*========================== TWI Data Register ==========================*/

#define TWDR (*((volatile u8 *)0x23))

/* Defining the bits of TWDR register */

/* TWI Data Register */
#define TWDR_TWD0 0
#define TWDR_TWD1 1
#define TWDR_TWD2 2
#define TWDR_TWD3 3
#define TWDR_TWD4 4
#define TWDR_TWD5 5
#define TWDR_TWD6 6
#define TWDR_TWD7 7

/*========================== TWI (Slave) Address Register ==========================*/

#define TWAR (*((volatile u8 *)0x22))

/* Defining the bits of TWAR register */

/* TWI General Call Recognition Enable Bit */
#define TWAR_TWGCE 0

/*========================== ISRs of TWI interrupts ==========================*/

/* The ISR of Two-wire Serial Interface Interrupt */
void __vector_19(void) __attribute__((signal));

#endif /* TWI_PRIVATE_H */

/*** end of file ***/