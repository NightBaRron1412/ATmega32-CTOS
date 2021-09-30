/** @file EXTI_private.h
 * 
 * @brief A header file including Ports and Bits numbers for EXTI
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 22, 2021       
 *
 */

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/*--------------------------Microcontroller Control Register-------------------*/

//Defining Microcontroller Control Register memory address for INT0 - INT1
#define MCUCR *((volatile u8 *)(0x55))

//Defining MCU Control Register bit numbers for INT0 - INT1
#define MCUCR_ISC00_PIN 0
#define MCUCR_ISC01_PIN 1
#define MCUCR_ISC10_PIN 2
#define MCUCR_ISC11_PIN 3

/*---------------------------MCU Control and Status Register-------------------*/

//Defining MCU Control and Status Register memory address for INT2
#define MCUCSR *((volatile u8 *)(0x54))

//Defining MCU Control Register bit numbers for INT2
#define MCUCSR_ISC2_PIN 6

/*----------------------------General Interput Control Register-------------------*/

//Defining General Interput Control Register memory address
#define GICR *((volatile u8 *)(0x5B))

//Defining General Interput Control Register bit numbers
#define GICR_INT0_PIN 6
#define GICR_INT1_PIN 7
#define GICR_INT2_PIN 5

/*------------------------General Interput Flag Register-------------------*/

//Defining General Interput Flag Register memory address
#define GIFR *((volatile u8 *)(0x5A))

//Defining General Interput Flag Register bit numbers
#define GIFR_INTF0_PIN 6
#define GIFR_INTF1_PIN 7
#define GIFR_INTF2_PIN 5

#endif /* EXTI_PRIVATE_H */

/*** end of file ***/