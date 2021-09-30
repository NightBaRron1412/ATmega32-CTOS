/** @file TMR_private.h
 * 
 * @brief A header file including Ports, Bits numbers, ISR decletaions for TMR
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 25, 2021       
 *
 */

#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H

/*-----------------------------------------Timers---------------------------------------------*/
#define TMR_NO_OF_TIMERS 3
#define TMR_TIMER0 0
#define TMR_TIMER1 1
#define TMR_TIMER2 2

/*-----------------------------------------Registers Max Values---------------------------------------------*/

#define TMR_MAXVAL_TIMER02_REG 256
#define TMR_MAXVAL_TIMER1_REG 65536

/*-----------------------------------------Timer 0---------------------------------------------*/

/*---------------------------Timer/Counter Control Register-------------------*/

//Defining Timer/Counter Control Register
#define TCCR0 *((volatile u8 *)(0x53))

//Defining Timer/Counter Control Register bit numbers

//Waveform Generation Mode
#define TCCR0_WGM00 6
#define TCCR0_WGM01 3

//Compare Match Output Mode
#define TCCR0_COM01 5
#define TCCR0_COM00 4

//Clock Select
#define TCCR0_CS02 2
#define TCCR0_CS01 1
#define TCCR0_CS00 0

/*---------------------------Timer/Counter Register-------------------*/

//Defining Timer/Counter Register
#define TCNT0 *((volatile u8 *)(0x52))

/*---------------------------Output Compare Register-------------------*/

//Defining Output Compare Register
#define OCR0 *((volatile u8 *)(0x5C))

/*---------------------------Timer/Counter Interrupt Mask Register-------------------*/

//Defining Timer/Counter Interrupt Mask Register
#define TIMSK *((volatile u8 *)(0x59))

//Defining Timer/Counter Interrupt Mask Register bit numbers

//Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_TOIE0 0

//Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_OCIE0 1

//Timer/Counter1, Overflow Interrupt Enable
#define TIMSK_TOIE1 2

//Timer/Counter1, Output Compare B Match Interrupt Enable
#define TIMSK_OCIE1B 3

//Timer/Counter1, Output Compare A Match Interrupt Enable
#define TIMSK_OCIE1A 4

//Timer/Counter1, Input Capture Interrupt Enable
#define TIMSK_TICIE1 5

//Timer/Counter2 Overflow Interrupt Enable
#define TIMSK_TOIE2 6

//Timer/Counter2 Output Compare Match Interrupt Enable
#define TIMSK_OCIE2 7

/*---------------------------Timer/Counter Interrupt Flag Register-------------------*/

//Defining Timer/Counter Interrupt Flag Register
#define TIFR *((volatile u8 *)(0x58))

//Defining Timer/Counter Interrupt Flag Register bit numbers

//Timer/Counter0 Overflow Flag
#define TIFR_TOV0 0

//Output Compare Flag 0
#define TIFR_OCF0 1

//Timer/Counter1, Overflow Flag
#define TIFR_TOV1 2

//Timer/Counter1, Output Compare B Match Flag
#define TIFR_OCF1B 3

//Timer/Counter1, Output Compare A Match Flag
#define TIFR_OCF1A 4

//Timer/Counter1, Input Capture Flag
#define TIFR_ICF1 5

/*-----------------------------------------Timer 1---------------------------------------------*/

/*---------------------------Timer/Counter1 Control Register A-------------------*/

//Defining Timer/Counter1 Control Register A
#define TCCR1A *((volatile u8 *)(0x4F))

//Defining Timer/Counter Interrupt Flag Register bit numbers

//Compare Output Mode for Compare unit A
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1A0 6

//Compare Output Mode for Compare unit B
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1B0 4

//Force Output Compare for Compare unit A
#define TCCR1A_FOC1A 3

//Force Output Compare for Compare unit B
#define TCCR1A_FOC1B 2

//Waveform Generation Mode
#define TCCR1A_WGM11 1
#define TCCR1A_WGM10 0

/*---------------------------Timer/Counter1 Control Register B-------------------*/

//Defining Timer/Counter1 Control Register B
#define TCCR1B *((volatile u8 *)(0x4E))

//Defining Timer/Counter Interrupt Flag Register bit numbers

//Input Capture Noise Canceler
#define TCCR1B_ICNC1 7

//Input Capture Edge Select
#define TCCR1B_ICES1 6

//Waveform Generation Mode
#define TCCR1B_WGM13 4
#define TCCR1B_WGM12 3

//Clock Select
#define TCCR1B_CS12 2
#define TCCR1B_CS11 1
#define TCCR1B_CS10 0

/*---------------------------Timer/Counter1-------------------*/
//Defining Timer/Counter1
#define TCNT1H *((volatile u8 *)(0x4D))
#define TCNT1L *((volatile u8 *)(0x4C))
#define TCNT1 *((u16 *)0x4C)

/*---------------------------Output Compare Register 1 A-------------------*/
//Defining Output Compare Register 1 A
#define OCR1AH *((volatile u8 *)(0x4B))
#define OCR1AL *((volatile u8 *)(0x4A))
#define OCRA1 *((u16 *)0x4A)

/*---------------------------Output Compare Register 1 B-------------------*/
//Defining Output Compare Register 1 B
#define OCR1BH *((volatile u8 *)(0x49))
#define OCR1BL *((volatile u8 *)(0x48))
#define OCRB1 *((u16 *)0x48)

/*---------------------------Input Capture Register 1-------------------*/
//Defining Input Capture Register 1
#define ICR1H *((volatile u8 *)(0x47))
#define ICR1L *((volatile u8 *)(0x46))
#define ICR1 *((u16 *)0x46)

/*-----------------------------------------Timer 2---------------------------------------------*/

/*---------------------------Timer/Counter Control Register-------------------*/

//Defining Timer/Counter Control Register
#define TCCR2 *((volatile u8 *)(0x45))

//Defining Timer/Counter Control Register bit numbers

//Force Output Compare
#define TCCR2_FOC2 7

//Waveform Generation Mode
#define TCCR2_WGM20 6
#define TCCR2_WGM21 3

//Compare Match Output Mode
#define TCCR2_COM21 5
#define TCCR2_COM20 4

//Clock Select
#define TCCR2_CS22 2
#define TCCR2_CS21 1
#define TCCR2_CS20 0

/*---------------------------Timer/Counter Register-------------------*/

//Defining Timer/Counter Register
#define TCNT2 *((volatile u8 *)(0x44))

/*---------------------------Output Compare Register-------------------*/

//Defining Output Compare Register
#define OCR2 *((volatile u8 *)(0x43))

/*---------------------------ISRs of Overflow timer interrupts-------------------*/
/*The ISR of Timer/Counter0 Overflow interrupt*/
void __vector_11(void) __attribute__((signal));

/*The ISR of Timer/Counter1 Overflow interrupt*/
void __vector_9(void) __attribute__((signal));

/*The ISR of Timer/Counter2 Overflow interrupt*/
void __vector_5(void) __attribute__((signal));

/*---------------------------ISRs of Compare Match timer interrupts-------------------*/

/*The ISR of Timer/Counter0 Compare Match interrupt*/
void __vector_10(void) __attribute__((signal));

/*The ISR of Timer/Counter1 Compare Match A interrupt*/
void __vector_7(void) __attribute__((signal));

/*The ISR of Timer/Counter1 Compare Match B interrupt*/
void __vector_8(void) __attribute__((signal));

/*The ISR of Timer/Counter2 Compare Match interrupt*/
void __vector_4(void) __attribute__((signal));

/*ISRs of Input Capture interrupts */
void __vector_6(void) __attribute__((signal));

#endif /* TMR_PRIVATE_H */

/*** end of file ***/