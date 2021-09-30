/** @file Bit_Math.h
 * 
 * @brief A header file including some Bit operations. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 15, 2021       
 *
 */ 

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR, BIT) (VAR) |=  (1 << (BIT))
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR, BIT) (VAR) ^=  (1 << (BIT))
#define GET_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01 )

#endif /* BIT_MATH_H */

/*** end of file ***/