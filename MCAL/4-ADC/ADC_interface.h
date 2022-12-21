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

/*
 * Description: Function to initialize the ADC peripheral
 * Inputs: void
 * Output: void
 */
void ADC_VidInit(void);
/*
 * Description: Function to get the ADC value from the required ADC channel using busy wait method
 * Inputs: ADC channel number and the Pointer to the variable supposed to hold the ADC variable
 * Output: the Error state of the function
 */

u8 ADC_u8ReadBlocking(u8 Copy_u8Channel, u16 *Copy_Pu16ADCValue);

/*
 * Description: Function to get the ADC value from the required ADC channel using ISR method
 * Inputs: ADC channel number and the Pointer to the variable supposed to hold the ADC variable
 * Output: the Error state of the function
 */
u8 ADC_u8ReadNonBlocking(u8 Copy_u8ChannelNb, u16 *Copy_Pu16ADCValue);

/*
 * Description: Function to set the callback function which will run as ISR on ADC conversion complete
 * Inputs: a pointer to the callback function
 * Output: the Error state of the function
 */
u8 ADC_u8SetCallBack(void (*Copy_PVCallBack)(void));

#endif /* ADC_INTERFACE_H */

/*** end of file ***/
