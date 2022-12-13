/** @file Std_Types.h
 *
 * @brief This header file is dedicated for defining fixed size data types which are reliable to be used Embedded System development.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 4, 2022
 *
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* unsigned 8 bit type */
typedef unsigned char u8;

/* signed 8 bit type */
typedef signed char s8;

/* unsigned 16 bit type */
typedef unsigned short int u16;

/* signed 16 bit type */
typedef signed short int s16;

/* unsigned 32 bit type */
typedef unsigned long int u32;

/* signed 32 bit type */
typedef signed long int s32;

/* floating type 32 bit */
typedef float f32;

/* floating type 64 bit */
typedef double f64;

/* Error status */
#define STATUS_OK (u8)0
#define STATUS_ERROR (u8)1

/* Macro for NULL */
#define NULL ((void *)0)

#endif /* STD_TYPES_H */

/*** end of file ***/