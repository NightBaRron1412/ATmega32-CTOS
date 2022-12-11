/** @file EXTI_private.h
 *
 * @brief A header file including Ports and Bits numbers for EXTI
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 11, 2022
 *
 */

/* Include guard */
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* Private Macro for the number of available external interrupts in AVR ATmega32 */
#define EXTI_NO_OF_EXTI 3

/*Private Macros for the External interrupts state (Disabled/Enabled) */
#define EXTI_DISABLE 0
#define EXTI_ENABLE 1

/*Private Macros for the probable sense level for the external interrupt */
#define EXTI_LOW_LEVEL_SC 0
#define EXTI_FALLING_EDGE_SC 1
#define EXTI_RISING_EDGE_SC 2
#define EXTI_ONCHANGE_SC 3

/*========================== Microcontroller Control Register ==========================*/

/* Defining Microcontroller Control Register memory address for INT0 - INT1 */
#define MCUCR *((volatile u8 *)(0x55))

/* Defining MCU Control Register bit numbers for INT0 - INT1 */
#define MCUCR_ISC00_BIT 0
#define MCUCR_ISC01_BIT 1
#define MCUCR_ISC10_BIT 2
#define MCUCR_ISC11_BIT 3

/*========================== MCU Control and Status Register ==========================*/

/* Defining MCU Control and Status Register memory address for INT2 */
#define MCUCSR *((volatile u8 *)(0x54))

/* Defining MCU Control Register bit numbers for INT2 */
#define MCUCSR_ISC2_BIT 6

/*========================== General Interrupt Control Register ==========================*/

/* Defining General Interrupt Control Register memory address */
#define GICR *((volatile u8 *)(0x5B))

/* Defining General Interrupt Control Register bit numbers */
#define GICR_INT0_BIT 6
#define GICR_INT1_BIT 7
#define GICR_INT2_BIT 5

/*========================== General Interrupt Flag Register ==========================*/

/* Defining General Interrupt Flag Register memory address */
#define GIFR *((volatile u8 *)(0x5A))

/* Defining General Interrupt Flag Register bit numbers */
#define GIFR_INTF0_BIT 6
#define GIFR_INTF1_BIT 7
#define GIFR_INTF2_BIT 5

/*========================== ISRs of the external interrupts ==========================*/

/* The ISR of the external interrupt INT0 */
void __vector_1(void) __attribute__((signal));

/* The ISR of the external interrupt INT1 */
void __vector_2(void) __attribute__((signal));

/* The ISR of the external interrupt INT2 */
void __vector_3(void) __attribute__((signal));

#endif /* EXTI_PRIVATE_H */

/*** end of file ***/