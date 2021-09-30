/** @file SPI_config.h
 * 
 * @brief A header file including configurations for SPI. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 5, 2021       
 *
 */

#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

//Specify the role of the SPI node
#define SPI_SELECTROLE SPI_MASTER

/**
 * Options:
 * SPI_MASTER
 * SPI_SLAVE
*/

//Specify state of the Serial Transfer Complete interrupt
#define SPI_INT_STATE SPI_DISABLE

/**
 * Options:
 * SPI_ENABLE
 * SPI_DISABLE
*/

//Specify order by which the byte will be sent
#define SPI_DATA_ORDER SPI_MSB

/**
 * Options:
 * SPI_LSB
 * SPI_MSB
*/

//Specify the clock polarity
#define SPI_CLKPOL SPI_RISINGEDGE

/**
 * Options:
 * SPI_RISINGEDGE
 * SPI_FALLINGEDGE
*/

//Specify the clock phase
#define SPI_CLKPHASE SPI_SAMPLE

/**
 * Options:
 * SPI_SAMPLE
 * SPI_SETUP
*/

//Specify the SPI clock rate
#define SPI_CLKRATE SPI_OVER_16

/**
 * Options:
 * SPI_OVER_4
 * SPI_OVER_16
 * SPI_OVER_64
 * SPI_OVER_128
 * SPI_OVER_2_HSPD
 * SPI_OVER_8_HSPD
 * SPI_OVER_32_HSPD
 * SPI_OVER_64_HSPD
*/

#if (SPI_CLKRATE == SPI_OVER_4)
#define SPI_SPRBITS 0

#elif (SPI_CLKRATE == SPI_OVER_16)
#define SPI_SPRBITS 1

#elif (SPI_CLKRATE == SPI_OVER_64)
#define SPI_SPRBITS 2

#elif (SPI_CLKRATE == SPI_OVER_128)
#define SPI_SPRBITS 3

#elif (SPI_CLKRATE == SPI_OVER_2_HSPD)
#define SPI_SPRBITS 0

#elif (SPI_CLKRATE == SPI_OVER_8_HSPD)
#define SPI_SPRBITS 1

#elif (SPI_CLKRATE == SPI_OVER_32_HSPD)
#define SPI_SPRBITS 2

#elif (SPI_CLKRATE == SPI_OVER_64_HSPD)
#define SPI_SPRBITS 3

#endif

#endif /* SPI_CONFIG_H */

/*** end of file ***/
