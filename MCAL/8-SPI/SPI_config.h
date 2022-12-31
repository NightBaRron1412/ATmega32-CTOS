/** @file SPI_config.h
 *
 * @brief A header file including configurations for SPI.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 31, 2022
 *
 */

/* Include guard */
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/**
 * Macro to select the role of the SPI node (Master/Slave)
 * Range: SPI_MASTER
 *        SPI_SLAVE
 */
#define SPI_SELECTROLE SPI_MASTER

/**
 * Macro to select the initial state of the SPI node
 * Range: SPI_ENABLE
 *        SPI_DISABLE
 */
#define SPI_INT_STATE SPI_DISABLE

/**
 * Macro to select the first bit to be sent
 * Range: SPI_LSB
 *        SPI_MSB
 */
#define SPI_DATA_ORDER SPI_MSB

/**
 * Macro to select the clock polarity
 * Range: SPI_RISINGEDGE
 *        SPI_FALLINGEDGE
 */
#define SPI_CLKPOL SPI_RISINGEDGE

/**
 * Macro to select the clock phase
 * Range: SPI_SAMPLE
 *        SPI_SETUP
 */
#define SPI_CLKPHASE SPI_SAMPLE

/**
 * Options:
 * SPI_SAMPLE
 * SPI_SETUP
 */

/**
 * Macro to select the clock rate
 * Range: SPI_OVER_4
 *        SPI_OVER_16
 *        SPI_OVER_64
 *        SPI_OVER_128
 *        SPI_OVER_2_HSPD
 *        SPI_OVER_8_HSPD
 *        SPI_OVER_32_HSPD
 *        SPI_OVER_64_HSPD
 */
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

/* Macro to define the timeout which determines the fault time in the SPI upon transmitting or receiving */
#define SPI_TIMEOUT 50000

#endif /* SPI_CONFIG_H */

/*** end of file ***/
