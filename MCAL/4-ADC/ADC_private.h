/** @file ADC_private.h
 * 
 * @brief A header file including Ports and Bits numbers for EXTI
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 23, 2021       
 *
 */

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/*--------------------------ADC Multiplexer Selection Register-------------------*/

//Defining ADC Multiplexer Selection Register memory address
#define ADMUX *((volatile u8 *)(0x27))

//Defining ADC Multiplexer Selection Register bit numbers for Reference Selection Bits
#define ADMUX_REFS1 7
#define ADMUX_REFS0 6

//Defining ADC Multiplexer Selection Register bit numbers for ADC Left Adjust Result
#define ADMUX_ADLAR 5

//Defining ADC Multiplexer Selection Register bit numbers for Analog Channel and Gain Selection Bits
#define ADMUX_MUX4 4
#define ADMUX_MUX3 3
#define ADMUX_MUX2 2
#define ADMUX_MUX1 1
#define ADMUX_MUX0 0

/*---------------------------ADC Control and Status Register A-------------------*/

//Defining ADC Control and Status Register A
#define ADCSRA *((volatile u8 *)(0x26))

//Defining ADC Control and Status Register A bit numbers
#define ADCSRA_ADEN 7  //ADC Enable
#define ADCSRA_ADSC 6  //ADC Start Conversion
#define ADCSRA_ADATE 5 //ADC Auto Trigger Enable
#define ADCSRA_ADIF 4  //ADC Interrupt Flag
#define ADCSRA_ADIE 3  //ADC Interrupt Enable

//ADC Prescaler Select Bits
#define ADCSRA_ADPS2 2
#define ADCSRA_ADPS1 1
#define ADCSRA_ADPS0 0

/*----------------------------ADCL and ADCH-------------------*/

//Defining ADCL and ADCH memory address
#define ADCH *((volatile u8 *)(0x25))
#define ADCL *((volatile u8 *)(0x24))

/*------------------------Special FunctionIO Register-------------------*/

//Defining Special FunctionIO Register memory address
#define SFIOR *((volatile u8 *)(0x50))

//ADC Auto Trigger Source
#define SFIOR_ADTS2 6
#define SFIOR_ADTS1 7
#define SFIOR_ADTS0 5

#endif /* ADC_PRIVATE_H */

/*** end of file ***/