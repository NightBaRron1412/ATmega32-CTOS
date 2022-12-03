/** @file DIO_config.h
 *
 * @brief A header file including init values for DIO Pins.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 3, 2022
 *
 */

/* Include Guard */
#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H

/* Initial direction for DIO Ports 	*/
/* Options: DIO_INIT_INPUT 	*/
/*          DIO_INIT_OUTPUT	*/

#define DIO_PORTA_INIT_DIR DIO_INIT_INPUT
#define DIO_PORTB_INIT_DIR DIO_INIT_INPUT
#define DIO_PORTC_INIT_DIR DIO_INIT_INPUT
#define DIO_PORTD_INIT_DIR DIO_INIT_INPUT

/* Macros of initialized state for DIO Pins */
/* Range : DIO_INIT_HIGH                 */
/*	       DIO_INIT_LOW                  */
/*		   DIO_INIT_PULL_UP              */
/* 		   DIO_INIT_HIGH_IMP             */

#define DIO_PORTA_INIT_STATE DIO_INIT_LOW
#define DIO_PORTB_INIT_STATE DIO_INIT_LOW
#define DIO_PORTC_INIT_STATE DIO_INIT_LOW
#define DIO_PORTD_INIT_STATE DIO_INIT_LOW

#endif /* DIO_CONFIG_H */

/*** end of file ***/