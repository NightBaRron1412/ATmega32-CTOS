/** @file EEPROM_interface.h
 * 
 * @brief A header file including functions for EEPROM interfacing. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 4, 2021           
 *
 */

#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void EEPROM_VidWrite(u8 Copy_u8Address, u8 Copy_u8Value);

u8 EEPROM_u8Read(u8 Copy_u8Address);

void EEPROM_VidWirteBlock(u8 Copy_u8StartAddress, u8 *Copy_u8BlockData);

void EEPROM_VidReadBlock(u8 Copy_u8StartAddress, u32 Copy_u16DataSize, u8 *Data);

#endif /* EEPROM_INTERFACE_H */

    /*** end of file ***/
