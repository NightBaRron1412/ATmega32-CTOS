/** @file ADC_private.h
 *
 * @brief A header file including Ports and Bits numbers for ADC
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/* Include Guard */
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* Private Macros to define the number of the ADC channels */
#define ADC_CHANNELS_COUNT 8

/* Private Macros to define the Enable/Disable state of the ADC peripheral, its interrupt and auto trigger */
#define ADC_ENABLE 1
#define ADC_DISABLE 0

/* Private Macros to define the ADC Voltage Reference Selection Bits */
#define ADC_AREF 0
#define ADC_AVCC 1
#define ADC_INTERNAL_VREF 2

/* Private Macros to define the ADC reading resolution */
#define ADC_10BITS 0
#define ADC_8BITS 1

/* Private Macros to define the ADC Prescaler */
#define ADC_PRESCALER_2 2
#define ADC_PRESCALER_4 4
#define ADC_PRESCALER_8 8
#define ADC_PRESCALER_16 16
#define ADC_PRESCALER_32 32
#define ADC_PRESCALER_64 64
#define ADC_PRESCALER_128 128

/* Private Macros to define the ADC Left Or Right Adjustment */
#define ADC_LEFT_ADJ 0
#define ADC_RIGHT_ADJ 1

/* Private Macros to define the ADC auto trigger source */
#define ADC_FREE_RUNNING 0
#define ADC_ANALOG_COMPARATOR 1
#define ADC_EXTI0 2
#define ADC_TIMER0_COMPARE_MATCH 3
#define ADC_TIMER0_OVERFLOW 4
#define ADC_TIMER_COMPARE_MATCH_B 5
#define ADC_TIMER1_OVERFLOW 6
#define ADC_TIMER1_CAPTURE_EVENT 7

/*========================== ADC Multiplexer Selection Register ==========================*/

/* Defining ADC Multiplexer Selection Register memory address */
#define ADMUX *((volatile u8 *)(0x27))

/* Defining ADC Multiplexer Selection Register bit numbers for Reference Selection Bits */
#define ADMUX_REFS1 7
#define ADMUX_REFS0 6

/* Defining ADC Multiplexer Selection Register bit numbers for ADC Left Adjust Result */
#define ADMUX_ADLAR 5

/* Defining ADC Multiplexer Selection Register bit numbers for Analog Channel and Gain Selection Bits */
#define ADMUX_MUX4 4
#define ADMUX_MUX3 3
#define ADMUX_MUX2 2
#define ADMUX_MUX1 1
#define ADMUX_MUX0 0

/*========================== ADC Control and Status Register A ==========================*/

/* Defining ADC Control and Status Register A memory address */
#define ADCSRA *((volatile u8 *)(0x26))

/* Defining ADC Control and Status Register A bit numbers */
#define ADCSRA_ADEN 7  /* ADC Enable */
#define ADCSRA_ADSC 6  /* ADC Start Conversion */
#define ADCSRA_ADATE 5 /* ADC Auto Trigger Enable */
#define ADCSRA_ADIF 4  /* ADC Interrupt Flag */
#define ADCSRA_ADIE 3  /* ADC Interrupt Enable */

/* ADC Prescaler Select Bits */
#define ADCSRA_ADPS2 2
#define ADCSRA_ADPS1 1
#define ADCSRA_ADPS0 0

/*========================== ADCL and ADCH ==========================*/

/* Defining ADCL and ADCH memory address */
#define ADCH *((volatile u8 *)(0x25))
#define ADCL *((volatile u8 *)(0x24))
#define ADCVAL_10BITS *((volatile u16 *)(0x24))

/*========================== Special FunctionIO Register ==========================*/

/* Defining Special FunctionIO Register memory address */
#define SFIOR *((volatile u8 *)(0x50))

/* ADC Auto Trigger Source */
#define SFIOR_ADTS2 6
#define SFIOR_ADTS1 7
#define SFIOR_ADTS0 5

/*========================== ISR ==========================*/

/* The ISR of ADC Conversion Complete */
void __vector_16(void) __attribute__((signal));

#endif /* ADC_PRIVATE_H */

/*** end of file ***/