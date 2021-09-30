#include "../Lib/Std_Types.h"
#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "../MCAL/TWI_interface.h"
#include <util/delay.h>

void EEPROM_VidWrite(u8 Copy_u8Address, u8 Copy_u8Value)
{
	TWI_VidStart();
	TWI_VidSendAddrres(EEPROM_ADDRESS, TWI_WRITE);
	TWI_VidWrite(Copy_u8Address);
	TWI_VidWrite(Copy_u8Value);
	TWI_VidStop();
}

u8 EEPROM_u8Read(u8 Copy_u8Address)
{
	u8 Local_u8ReadData = 0;
	TWI_VidStart();
	TWI_VidSendAddrres(EEPROM_ADDRESS, TWI_WRITE);
	TWI_VidWrite(Copy_u8Address);
	TWI_VidStart();
	TWI_VidSendAddrres(EEPROM_ADDRESS, TWI_READ);
	Local_u8ReadData = TWI_u8Read();
	TWI_VidStop();
	return Local_u8ReadData;
}

void EEPROM_VidWirteBlock(u8 Copy_u8StartAddress, u8 *Copy_u8BlockData)
{
	for (u8 i = 0; Copy_u8BlockData[i] != '\0'; i++, Copy_u8StartAddress++)
	{
		EEPROM_VidWrite(Copy_u8StartAddress, Copy_u8BlockData[i]);
		_delay_ms(200);
	}
}

void EEPROM_VidReadBlock(u8 Copy_u8StartAddress, u32 Copy_u16DataSize, u8 *Data)
{
	u8 Local_u8DataRead[Copy_u16DataSize + 1], i;
	for (i = 0; i < Copy_u16DataSize; i++, Copy_u8StartAddress++)
	{
		Local_u8DataRead[i] = EEPROM_u8Read(Copy_u8StartAddress);
	}
	Local_u8DataRead[i] = '\0';
	for (i = 0; Local_u8DataRead[i] != '\0'; i++)
	{
		Data[i] = Local_u8DataRead[i];
	}
	Data[i] = '\0';
}
