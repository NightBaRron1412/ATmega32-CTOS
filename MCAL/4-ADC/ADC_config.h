/** @file ADC_config.h
 *
 * @brief A header file including some configurations for ADC driver.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/* Include Guard */
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/**
 * Macros for the ADC Enable/Disable
 * Range:  ADC_ENABLE
 *         ADC_DISABLE
 */
#define ADC_INIT_STATE ADC_ENABLE

/**
 * Macros for the Voltage Reference Selection Bits
 * Range:  ADC_AREF           AREF, Internal Vref turned off
 *         ADC_AVCC           AVCC with external capacitor at AREF pin
 *         ADC_INTERNAL_VREF  Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
#define ADC_REFRENCE_SELECTION ADC_AVCC

/**
 * Macros for specifying Left Or Right Adjustment of Data Registers for reading resolutions
 * Range:  ADC_10_BIT
 *         ADC_8_BIT
 */
#define ADC_READING_RESOLUTION ADC_10BITS

/**
 * Macros for specifying the ADC Prescaler
 * Range:  ADC_PRESCALER_2
 *         ADC_PRESCALER_4
 *         ADC_PRESCALER_8
 *         ADC_PRESCALER_16
 *         ADC_PRESCALER_32
 *         ADC_PRESCALER_64
 *         ADC_PRESCALER_128
 */
#define ADC_PRESCALER ADC_PRESCALER_128

/**
 * Macros for specifying the ADC Left Or Right Adjustment
 * Range:  ADC_LEFT_ADJ
 *         ADC_RIGHT_ADJ
 */
#define ADC_ADJUSTMENT ADC_LEFT_ADJ

/**
 * Macros for specifying the ADC Interrupt Enable/Disable
 * Range:  ADC_ENABLE
 *         ADC_DISABLE
 */
#define ADC_INT_STATE ADC_ENABLE

/**
 * Macros for specifying the ADC Auto Trigger Enable/Disable
 * Range:  ADC_ENABLE
 *         ADC_DISABLE
 */
#define ADC_AUTO_TRIGGER_STATE ADC_DISABLE

/**
 * Macros for specifying the ADC Auto Trigger Source
 * Range:  ADC_FREE_RUNNING
 *         ADC_ANALOG_COMPARATOR
 *         ADC_EXTI0
 *         ADC_TIMER0_COMPARE_MATCH
 *         ADC_TIMER0_OVERFLOW
 *         ADC_TIMER_COMPARE_MATCH_B
 *         ADC_TIMER1_OVERFLOW
 *         ADC_TIMER1_CAPTURE_EVENT
 */
#define ADC_AUTO_TRIGGER_SOURCE ADC_FREE_RUNNING

#endif /* ADC_CONFIG_H */

/*** end of file ***/
