/** @file DIO_private.h
 * 
 * @brief A header file including memory addresses for AVR ports registers. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 16, 2021       
 *
 */

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

//Defining PORTA registers addresses 
#define PORTA *((volatile u8 *)0x3B)
#define DDRA  *((volatile u8 *)0x3A)
#define PINA  *((volatile u8 *)0x39)

//Defining PORTB registers addresses
#define PORTB *((volatile u8 *)0x38)
#define DDRB  *((volatile u8 *)0x37)
#define PINB  *((volatile u8 *)0x36)

//Defining PORTC registers addresses
#define PORTC *((volatile u8 *)0x35)
#define DDRC  *((volatile u8 *)0x34)
#define PINC  *((volatile u8 *)0x33)

//Defining PORTD registers addresses
#define PORTD *((volatile u8 *)0x32)
#define DDRD  *((volatile u8 *)0x31)
#define PIND  *((volatile u8 *)0x30)

#endif /* DIO_PRIVATE_H */

/*** end of file ***/