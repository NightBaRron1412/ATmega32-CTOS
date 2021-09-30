/** @file ADC_interface.h
 * 
 * @brief A header file including functions prototypes to init and read ADC
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 23, 2021       
 *
 */

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

void ADC_VidInit(void);
u16 ADC_u16Read(u8 Copy_u8Channel);

#define A0 0b00000000
#define A1 0b00000001
#define A2 0b00000010
#define A3 0b00000011
#define A4 0b00000100
#define A5 0b00000101
#define A6 0b00000110
#define A7 0b00000111

#endif /* ADC_INTERFACE_H */

/*** end of file ***/
