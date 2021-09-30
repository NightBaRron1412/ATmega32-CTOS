/** @file TWI_interface.h
 * 
 * @brief A header file including functions for TWI interfacing. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 31, 2021       
 *
 */

#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

#define TWI_READ 1
#define TWI_WRITE 0

void TWI_VidInit();

void TWI_VidStart();

void TWI_VidStop();

void TWI_VidWrite(u8 Copy_u8Data);

u8 TWI_u8Read();

u8 TWI_u8Status();
void TWI_VidSendAddrres(u8 Cpy_u8Adress, u8 Cpy_u8Operation);

#endif /* TWI_INTERFACE_H */

/*** end of file ***/
