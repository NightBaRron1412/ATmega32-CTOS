/** @file TMR_config.h
 *
 * @brief A header file including configurations for TMR
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 10, 2022
 *
 */

/* Include guard */
#ifndef TMR_CONFIG_H
#define TMR_CONFIG_H

/*========================== General Configurations for Timer0,Timer1,Timer2  ==========================*/

/**
 * Macros for the initial state of each timer (0,1,2)
 * Range:   TMR_DISABLE
 *          TMR_ENABLE
 */
#define TMR_TIMER0_INIT_STATE TMR_DISABLE
#define TMR_TIMER1_INIT_STATE TMR_ENABLE
#define TMR_TIMER2_INIT_STATE TMR_DISABLE

/**
 * Macros for the mode of each timer (0,1,2)
 * Range:  TMR_NORMAL
 *         TMR_PWM_PHASE_CORRECT
 *         TMR_CTC
 *         TMR_FASTPWM_8BIT
 *         TMR_FASTPWM_9BIT  (for Timer1 only)
 *         TMR_FASTPWM_10BIT (for Timer1 only)
 *         TMR_FASTPWM_ICR1  (for Timer1 only)
 *         TMR_FASTPWM_OCRA1 (for Timer1 only)
 */
#define TMR_TIMER0_MODE TMR_FASTPWM_8BIT
#define TMR_TIMER1_MODE TMR_CTC
#define TMR_TIMER2_MODE TMR_NORMAL

/**
 * Macros for the prescaler of each timer (0,1,2)
 * Range:  TMR_NO_PRESCALER
 *         TMR_PRESCALER_8
 *         TMR_PRESCALER_32 (for Timer2 only)
 *         TMR_PRESCALER_64
 *         TMR_PRESCALER_128 (for Timer2 only)
 *         TMR_PRESCALER_256
 *         TMR_PRESCALER_1024
 */
#define TMR_TIMER0_PRESCALER TMR_PRESCALER_8
#define TMR_TIMER1_PRESCALER TMR_PRESCALER_1024
#define TMR_TIMER2_PRESCALER TMR_PRESCALER_8

/**
 * Macros for edge needed to be captured by the input capture pin D6
 * Range:  TMR_RISING_EDGE
 *         TMR_FALLING_EDGE
 */
#define TMR_ICES TMR_RISING_EDGE

/* Macros to specify preload for timers overflow */
#define TMR_Timer0Preload 0
#define TMR_Timer1Preload 0
#define TMR_Timer2Preload 0

/* Macros to specify required counts for ISR counters */
#define TMR_ReqTimer0Cntr 0
#define TMR_ReqTimer1Cntr 10
#define TMR_ReqTimer2Cntr 0

/*========================== Configurations for Timer1A/Timer1B ==========================*/

/**
 * Macros to specify which compare register of Timer1 you will use (Timer1A/Timer1B)
 * upon which compare match interrupt is enabled for Timer1A or Timer1B
 * Range:   TMR_DISABLE
 *	   	    TMR_ENABLE
 */
#define TMR_TIMER1A_COMP_STATE TMR_ENABLE
#define TMR_TIMER1B_COMP_STATE TMR_DISABLE

/**
 * Macros to specify on which pin related to Timer1A/Timer1B you will apply compare output mode (OC1A/OC1B)
 * Range:   TMR_DISABLE
 *	   	    TMR_ENABLE
 */
#define TMR_TIMER1A_COPT_STATE TMR_ENABLE
#define TMR_TIMER1B_COPT_STATE TMR_DISABLE

/**
 * Macro to specify the top value of the timer upon which the period of the generated PWM signal
 * will be determined (in case of TMR_u8_FASTPWM_ICR1 mode)
 */
#define TMR_ICR1_VAL 0

/*========================== Interrupts Configurations ==========================*/

/**
 * Macros to enable or disable the overflow interrupt for each timer (0,1,2)
 * Range:  TMR_EN_INT
 * 	   	   TMR_DIS_INT
 */
#define TMR_TIMER0_OVF_INT TMR_DIS_INT
#define TMR_TIMER1_OVF_INT TMR_DIS_INT
#define TMR_TIMER2_OVF_INT TMR_EN_INT

/**
 * Macros to enable or disable the output compare interrupt for each timer (0,1,2)
 * Range:  TMR_EN_INT
 * 	   	   TMR_DIS_INT
 */
#define TMR_TIMER0_CTC_INT TMR_DIS_INT
#define TMR_TIMER1_CTC_INT TMR_EN_INT
#define TMR_TIMER2_CTC_INT TMR_DIS_INT

/**
 * Macros to set the Compare Output Mode for each timer (0,1,2)
 * Range:   TMR_NORMAL
 *          TMR_TOGGLE_OCX
 *          TMR_CLEAR_OCX (non-inverting mode in Fast PWM)
 *          TMR_SET_OCX   (inverting mode in Fast PWM)
 */
#define TMR_TIMER0_COPT_MODE TMR_CLEAR_OCX
#define TMR_TIMER1_COPT_MODE TMR_NORMAL
#define TMR_TIMER2_COPT_MODE TMR_NORMAL

/**
 * Macro to determine the state of the INput Capture Interrupt
 * Range:  TMR_EN_INT
 * 	   	   TMR_DIS_INT
 */
#define TMR_ICP_INT TMR_DIS_INT

/*========================== Setting the Timer overflow according to the configured prescaler ==========================*/
#if (TMR_TIMER0_PRESCALER == TMR_PRESCALER_NO_PRESCALER)
#define TMR_TIMER0_TOVF 32

#elif (TMR_TIMER0_PRESCALER == TMR_PRESCALER_8)
#define TMR_TIMER0_TOVF 256

#elif (TMR_TIMER0_PRESCALER == TMR_PRESCALER_64)
#define TMR_TIMER0_TOVF 2048

#elif (TMR_TIMER0_PRESCALER == TMR_PRESCALER_256)
#define TMR_TIMER0_TOVF 8192

#elif (TMR_TIMER0_PRESCALER == TMR_PRESCALER_1024)
#define TMR_TIMER0_TOVF 32768
#endif

#if (TMR_TIMER1_PRESCALER == TMR_PRESCALER_NO_PRESCALER)
#define TMR_TIMER1_TOVF 8192

#elif (TMR_TIMER1_PRESCALER == TMR_PRESCALER_8)
#define TMR_TIMER1_TOVF 65536
#define TMR_TIMER1_TICKTIME 1

#elif (TMR_TIMER1_PRESCALER == TMR_PRESCALER_64)
#define TMR_TIMER1_TOVF 524288
#define TMR_TIMER1_TICKTIME 8

#elif (TMR_TIMER1_PRESCALER == TMR_PRESCALER_256)
#define TMR_TIMER1_TOVF 2097152
#define TMR_TIMER1_TICKTIME 32

#elif (TMR_TIMER1_PRESCALER == TMR_PRESCALER_1024)
#define TMR_TIMER1_TOVF 8388608
#define TMR_TIMER1_TICKTIME 128
#endif

#if (TMR_TIMER2_PRESCALER == TMR_PRESCALER_NO_PRESCALER)
#define TMR_TIMER2_TOVF 32

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_8)
#define TMR_TIMER2_TOVF 256

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_32)
#define TMR_TIMER2_TOVF 1024

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_64)
#define TMR_TIMER2_TOVF 2048

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_128)
#define TMR_TIMER2_TOVF 4096

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_256)
#define TMR_TIMER2_TOVF 8192

#elif (TMR_TIMER2_PRESCALER == TMR_PRESCALER_1024)
#define TMR_TIMER2_TOVF 32768
#endif

#endif /* TMR_CONFIG_H */

/*** end of file ***/
