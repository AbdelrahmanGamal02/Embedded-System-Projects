/*
 * CAN_Receiver.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */


/*
 * CAN_Transmitter.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "CAN_Receiver.h"

uint8 CAN_vReceiverReadRegister(uint8 address)
{
	uint8 Read_Data = 0;

	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(READ_INST);
	SPI_ui8TransmitRecive(address);
	Read_Data = SPI_ui8TransmitRecive(0);
	SPI_vChipSelection(0);

	return Read_Data;
}

void CAN_vReceiverWriteRegister(uint8 address , uint8 data)
{
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(WRITE_INST);
	SPI_ui8TransmitRecive(address);
	SPI_ui8TransmitRecive(data);
	SPI_vChipSelection(0);
}

void CAN_vBitModifyReceiverRegister(uint8 address , uint8 Mask ,uint8 data)
{
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(BIT_MODIFY_INST);
	SPI_ui8TransmitRecive(address);
	SPI_ui8TransmitRecive(Mask);
	SPI_ui8TransmitRecive(data);
	SPI_vChipSelection(0);
}

void CAN_vSetBitTimingReceiver(uint8 CANF1_value , uint8 CANF2_value , uint8 CANF3_value)
{
	CAN_vReceiverWriteRegister(CANF1 , CANF1_value);
	CAN_vReceiverWriteRegister(CANF2 , CANF2_value);
	CAN_vReceiverWriteRegister(CANF3 , CANF3_value);
}

void CAN_vReceiverSetMode(uint8 mode)
{
	CAN_vBitModifyReceiverRegister(CANCTRL , 0xE0 , mode<<5);
}

void CAN_vSetMask(uint8 mask_adress , uint32 value)
{
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(WRITE_INST);
	if(RXM0SIDH == mask_adress)
	{
		SPI_ui8TransmitRecive(RXM0SIDH);
		SPI_ui8TransmitRecive(value>>3);
		SPI_ui8TransmitRecive(value<<5);
		SPI_vChipSelection(0);
	}
	else if(RXM1SIDH == mask_adress)
	{
		SPI_ui8TransmitRecive(RXM1SIDH);
		SPI_ui8TransmitRecive(value>>3);
		SPI_ui8TransmitRecive(value<<5);
		SPI_vChipSelection(0);
	}
	else{ /* Nothing */ }
}

void CAN_vReceiverInit(void)
{
	/* SPI Init */
	SPI_vInitSlave();
	/* Reset if you need */
	CAN_vReceiverWriteRegister(CANCTRL,CONFG_MODE);
	CAN_vSetBitTimingReceiver(0x80 , 0xB1 , 0x05);
	CAN_vSetMask(RXM0SIDH , 0x00000000);
	CAN_vReceiverWriteRegister(CANINTE , 0x03);
	CAN_vReceiverSetMode(NORMAL_MODE);
}

void CAN_vReadMessage(uint8 BufferID , uint8 *data)
{
	uint8 arr[14] , counter = 0;
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(READ_INST);
	if(BUFFER0 == BufferID)
	{
		SPI_ui8TransmitRecive(RXB0CTRL);
		for(counter = 0; counter < 14; counter++)
		{
			arr[counter] = SPI_ui8TransmitRecive(0);
			if(counter>=6)
			{
				data[counter - 6] = arr[counter];
			}
		}
	}
	else if(BUFFER1 == BufferID)
	{
		SPI_ui8TransmitRecive(RXB0CTRL);
		for(counter = 0; counter < 14; counter++)
		{
			arr[counter] = SPI_ui8TransmitRecive(0);
			if(counter>=6)
			{
				data[counter - 6] = arr[counter];
			}
		}
	}
	else{ /* Nothing */ }

	SPI_vChipSelection(0);
	CAN_vReceiverWriteRegister(CANINTF , 0x00);
}



