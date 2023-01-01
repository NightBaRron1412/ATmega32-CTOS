/** @file SSD_config.h
 *
 * @brief A header file including config for 7SEG interfacing.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 30, 2022
 *
 */

/* Include Guard */
#ifndef SSD_CONFIG_H
#define SSD_CONFIG_H

/* Number of connected 7SEGs */
#define SSD_CONNECTED_NUM 2

/* 7SEGs ports (Starting from Segment A to Pin 0) */
#define SSD_SSD0_PORT PORT_A
#define SSD_SSD1_PORT PORT_B

/**
 * Macros for 7SEGs types
 * Range: SSD_COMMON_CATHODE
 *        SSD_COMMON_ANODE
 */
#define SSD_SSD0_TYPE SSD_COMMON_CATHODE
#define SSD_SSD1_TYPE SSD_COMMON_CATHODE

/**
 * Macros for the initial value of 7SEGs
 * Range: SSD_ZERO
 *        SSD_ONE
 *        SSD_TWO
 *        SSD_THREE
 *        SSD_FOUR
 *        SSD_FIVE
 *        SSD_SIX
 *        SSD_SEVEN
 *        SSD_EIGHT
 *        SSD_NINE
 */
#define SSD_SSD0_INIT_VAL SSD_ZERO
#define SSD_SSD1_INIT_VAL SSD_ZERO

/* Array holding the SSDs Ports */
u8 SSD_Au8SSDPort[SSD_CONNECTED_NUM] = {SSD_SSD0_PORT, SSD_SSD1_PORT};

/* Array holding the SSDs Types */
u8 SSD_Au8SSDType[SSD_CONNECTED_NUM] = {SSD_SSD0_TYPE, SSD_SSD1_TYPE};

/* Array holding the initial values of each SSD */
u8 SSD_Au8SSDInitValue[SSD_CONNECTED_NUM] = {SSD_SSD0_INIT_VAL, SSD_SSD1_INIT_VAL};

#endif /* SSD_CONFIG_H */

/*** end of file ***/