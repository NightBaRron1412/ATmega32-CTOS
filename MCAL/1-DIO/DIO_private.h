/** @file DIO_private.h
 *
 * @brief A header file including memory addresses for AVR ports registers.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 3, 2022
 *
 */

/* Include Guard */
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/*======================================================== */

/* Direction Macros for ports initialized direction */
/* their definition are specific to AVR */
#define DIO_INIT_INPUT 0x00
#define DIO_INIT_OUTPUT 0xFF

/* Macros for pins initialized states in case the port is output */
#define DIO_INIT_LOW 0x00
#define DIO_INIT_HIGH 0xFF

/* Macros for pins initialized states in case the port is input */
#define DIO_INIT_HIGH_IMP 0x00
#define DIO_INIT_PULL_UP 0xFF

/*======================================================== */

/* Defining PORTA registers addresses */
#define PORTA *((volatile u8 *)0x3B)
#define DDRA *((volatile u8 *)0x3A)
#define PINA *((volatile u8 *)0x39)

/* Defining PORTB registers addresses */
#define PORTB *((volatile u8 *)0x38)
#define DDRB *((volatile u8 *)0x37)
#define PINB *((volatile u8 *)0x36)

/* Defining PORTC registers addresses */
#define PORTC *((volatile u8 *)0x35)
#define DDRC *((volatile u8 *)0x34)
#define PINC *((volatile u8 *)0x33)

/* Defining PORTD registers addresses */
#define PORTD *((volatile u8 *)0x32)
#define DDRD *((volatile u8 *)0x31)
#define PIND *((volatile u8 *)0x30)

/* Defining SFIOR register address and PUD Bit Number */
#define SFIOR *((volatile u8 *) 0x50)
#define PUD 2

#endif /* DIO_PRIVATE_H */

/*** end of file ***/