/** @file USART_private.h
 * 
 * @brief A header file including memory addresses for USART registers. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 30, 2021       
 *
 */

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

/*---------------------------USART I/O Data Register-------------------*/

//Defining USART I/O Data Register
#define UDR *((volatile u8 *)(0x2C))

/*---------------------------USART Control and Status Register A-------------------*/

//Defining USART Control and Status Register A
#define UCSRA *((volatile u8 *)(0x2B))

//Defining USART Control and Status Register A bit numbers

//USART Receive Complete
#define UCSRA_RXC 7

//USART Transmit Complete
#define UCSRA_TXC 6

//USART Data Register Empty
#define UCSRA_UDRE 5

//Frame Error
#define UCSRA_FE 4

//Data OverRun
#define UCSRA_DOR 3

//Parity Error
#define UCSRA_PE 2

//Double the USART Transmission Speed
#define UCSRA_U2X 1

//Multi-processor Communication Mode
#define UCSRA_MPCM 0

/*---------------------------USART Control and Status Register B-------------------*/

//Defining USART Control and Status Register B
#define UCSRB *((volatile u8 *)(0x2A))

//Defining USART Control and Status Register B bit numbers

//RX Complete Interrupt Enable
#define UCSRB_RXCIE 7

//TX Complete Interrupt Enable
#define UCSRB_TXCIE 6

//USART Data Register Empty Interrupt Enable
#define UCSRB_UDRIE 5

//Receiver Enable
#define UCSRB_RXEN 4

//Transmitter Enable
#define UCSRB_TXEN 3

//Character Size
#define UCSRB_UCSZ2 2

//Receive Data Bit 8
#define UCSRB_RXB8 1

//Transmit Data Bit 8
#define UCSRB_TXB8 0

/*---------------------------USART Control and Status Register C-------------------*/

//Defining USART Control and Status Register C
#define UCSRC *((volatile u8 *)(0x40))

//Defining USART Control and Status Register C bit numbers

//Register Select
#define UCSRC_URSEL 7

//USART Mode Select
#define UCSRC_UMSEL 6

//Parity Mode
#define UCSRC_UPM1 5
#define UCSRC_UPM0 4

//Stop Bit Select
#define UCSRC_USBS 3

//Character Size
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1

//Clock Polarity
#define UCSRC_UCPOL 0

/*---------------------------Configurations-------------------*/

#define USART_NO_PARITY 0
#define USART_EVEN_PARITY 1
#define USART_ODD_PARITY 2

#define USART_FIVE_BITS 5
#define USART_SIX_BITS 6
#define USART_SEVEN_BITS 7
#define USART_EIGHT_BITS 8
#define USART_NINE_BITS 9

#define USART_ONE_BIT 0
#define USART_TWO_BITS 1

#define USART_DISABLE 0
#define USART_ENABLE 1

#define USART_NORMAL_MODE 0
#define USART_DBL_SPD_MODE 1

/*---------------------------USART Baud Rate Registers-------------------*/

//Defining USART Baud Rate Registers
#define UBRRL *((volatile u8 *)(0x29))
#define UBRRH *((volatile u8 *)(0x40))

/*---------------------------ISRs of UART interrupts   -------------------*/

/*The ISR of USART, Rx Complete interrupt*/
void __vector_13(void) __attribute__((signal));

/*The ISR of USART Data Register Empty interrupt*/
void __vector_14(void) __attribute__((signal));

/*The ISR of USART, Tx Complete interrupt*/
void __vector_15(void) __attribute__((signal));

#endif /* USART_PRIVATE_H */

/*** end of file ***/