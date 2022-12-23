/** @file ADC_interface.h
 *
 * @brief A header file including functions prototypes to init and read ADC
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/* Include Guard */
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* Macros for ADC channels interfacing */
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

/**
 * @brief A function to initialize the ADC peripheral
 * @param void
 * @return void
 */
void ADC_VidInit(void);

/**
 * @brief A function to get the ADC value from the required ADC channel using blocking method
 * @param Copy_u8ChannelNb: the ADC channel number
 * @param Copy_Pu16ADCValue: the Pointer to the variable supposed to hold the ADC value
 * @return the Error state of the function
 */
u8 ADC_u8ReadBlocking(u8 Copy_u8Channel, u16 *Copy_Pu16ADCValue);

/**
 * @brief A function to get the ADC value from the required ADC channel using non-blocking method
 * @param Copy_u8ChannelNb: the ADC channel number
 * @param Copy_Pu16ADCValue: the Pointer to the variable supposed to hold the ADC value
 * @return the Error state of the function
 */
u8 ADC_u8ReadNonBlocking(u8 Copy_u8ChannelNb, u16 *Copy_Pu16ADCValue);

/**
 * @brief A function to set the callback function which will run as ISR on ADC conversion complete
 * @param Copy_PVCallBack: the pointer to the callback function
 * @return the Error state of the function
 */
u8 ADC_u8SetCallBack(void (*Copy_PVCallBack)(void));

#endif /* ADC_INTERFACE_H */

/*** end of file ***/
