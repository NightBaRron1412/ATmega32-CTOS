/** @file Bit_Math.h
 *
 * @brief A header file including some Bit operations.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 4, 2022
 *
 */

/* include Guard */
#ifndef BIT_MATH_H
#define BIT_MATH_H

/*
Macro definition to set a specific bit in a variable
Input: (1) the variable itself (2) the bit number of the variable needed to be set
*/
#define SET_BIT(VAR, BIT) (VAR) |= (1 << (BIT))

/*
Macro definition to clear a specific bit in a variable
Input: (1) the variable itself (2) the bit number of the variable needed to be cleared
*/
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))

/*
Macro definition to toggle a specific bit in a variable
Inputs: (1) the variable itself (2) the bit number of the variable needed to be toggled
*/
#define TOG_BIT(VAR, BIT) (VAR) ^= (1 << (BIT))

/*
Macro definition to get the state of a specific bit in a variable
Inputs: (1) the variable itself (2) the bit number of the variable we need to get its state
*/
#define GET_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01)

#endif /* BIT_MATH_H */

/*** end of file ***/