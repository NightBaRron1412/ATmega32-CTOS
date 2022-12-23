/** @file GIE_private.h
 * 
 * @brief A header file including memory addresses for GIE prot and BIT number. 
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 23, 2022    
 *
 */

#ifndef GIE_PRIVATE_H
#define GIE_PRIVATE_H

/* Defining SREG registers addresses */
#define SREG *((volatile u8 *)0x5F)

/* Defining SREG BIT "i" Location */
#define SREG_I_BIT 7

#endif /* GIE_PRIVATE_H */

/*** end of file ***/