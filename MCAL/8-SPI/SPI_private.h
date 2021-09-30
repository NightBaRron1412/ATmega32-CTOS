/** @file SPI_private.h
 * 
 * @brief A header file including memory addresses and Bit nums for SPI. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 5, 2021       
 *
 */

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

/* Define the possible state of Serial Transfer Complete interrupt */
#define SPI_ENABLE 0
#define SPI_DISABLE 1

/* Define the possible order by which the byte will be sent */
#define SPI_LSB 0
#define SPI_MSB 1

/* Define the states of an SPI node (Master/Slave) */
#define SPI_MASTER 0
#define SPI_SLAVE 1

/* Define the clock polarity */
#define SPI_RISINGEDGE 0
#define SPI_FALLINGEDGE 1

/* Define the clock phase */
#define SPI_SAMPLE 0
#define SPI_SETUP 1

/* Define the SPI clock rate */
#define SPI_OVER_4 0
#define SPI_OVER_16 1
#define SPI_OVER_64 2
#define SPI_OVER_128 3
#define SPI_OVER_2_HSPD 4
#define SPI_OVER_8_HSPD 5
#define SPI_OVER_32_HSPD 6
#define SPI_OVER_64_HSPD 7

/*---------------------------SPI Control Register-------------------*/

//Defining SPI Control Register
#define SPCR *((volatile u8 *)(0x2D))

//Defining SPI Control Register bit numbers
#define SPCR_SPR0 0
#define SPCR_SPR1 1
#define SPCR_CPHA 2
#define SPCR_CPOL 3
#define SPCR_MSTR 4
#define SPCR_DORD 5
#define SPCR_SPE 6
#define SPCR_SPIE 7

//Defining SPI Status Register
#define SPSR *((volatile u8 *)(0x2E))

//Defining SPI Status Register
#define SPSR_SPI2X 0
#define SPSR_SPIF 7

/*---------------------------SPI Data Register-------------------*/

//Defining SPI Data Register
#define SPDR *((volatile u8 *)(0x2F))

/*---------------------------ISRs of SPI interrupts  -------------------*/

/*The ISR of Serial Transfer Complete*/
void __vector_12(void) __attribute__((signal));

#endif /* SPI_PRIVATE_H */

/*** end of file ***/
