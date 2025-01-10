/*
 * CAN_Transmitter.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "CAN_Transmitter.h"

uint8 CAN_vReadRegister(uint8 address)
{
	uint8 Read_Data = 0;

	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(READ_INST);
	SPI_ui8TransmitRecive(address);
	Read_Data = SPI_ui8TransmitRecive(0);
	SPI_vChipSelection(0);

	return Read_Data;
}

void CAN_vWriteRegister(uint8 address , uint8 data)
{
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(WRITE_INST);
	SPI_ui8TransmitRecive(address);
	SPI_ui8TransmitRecive(data);
	SPI_vChipSelection(0);
}

void CAN_vBitModifyRegister(uint8 address , uint8 Mask ,uint8 data)
{
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(BIT_MODIFY_INST);
	SPI_ui8TransmitRecive(address);
	SPI_ui8TransmitRecive(Mask);
	SPI_ui8TransmitRecive(data);
	SPI_vChipSelection(0);
}

void CAN_vSetBitTiming(uint8 CANF1_value , uint8 CANF2_value , uint8 CANF3_value)
{
	CAN_vWriteRegister(CANF1 , CANF1_value);
	CAN_vWriteRegister(CANF2 , CANF2_value);
	CAN_vWriteRegister(CANF3 , CANF3_value);
}


void CAN_vSetMode(uint8 mode)
{
	CAN_vBitModifyReceiverRegister(CANCTRL , 0xE0 , mode<<5);
}

void CAN_vTransmitterInit(void)
{
	/* SPI Init */
	SPI_vInitMaster();
	/* Reset if you need */
	CAN_vWriteRegister(CANCTRL,CONFG_MODE);
	CAN_vSetBitTiming(0x80 , 0xB1 , 0x05);
	CAN_vSetMode(NORMAL_MODE);
}

void CAN_vSendMessage(uint8 BufferID , uint32 ID , uint8 DLC , uint8* data)
{
	uint8 counter = 0;
	SPI_vChipSelection(1);
	SPI_ui8TransmitRecive(WRITE_INST);
	if(BUFFER0 == BufferID)
	{
		SPI_ui8TransmitRecive(TXB0CTRL);
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(ID>>3);
		SPI_ui8TransmitRecive(ID<<5);
		/* For Extended ID */
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(DLC & 0x0F);
		/* Send Data */
		for(counter = 0; counter < (DLC & 0x0F); counter++)
		{
			SPI_ui8TransmitRecive(data[counter]);
		}

		SPI_vChipSelection(0);
		/* Request to send */
		SPI_vChipSelection(1);
		SPI_ui8TransmitRecive(BUFFER0_REQU_TO_SEND_INST);
		SPI_vChipSelection(0);
	}
	else if(BUFFER1 == BufferID)
	{
		SPI_ui8TransmitRecive(TXB1CTRL);
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(ID>>3);
		SPI_ui8TransmitRecive(ID<<5);
		/* For Extended ID */
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(DLC & 0x0F);
		/* Send Data */
		for(counter = 0; counter < (DLC & 0x0F); counter++)
		{
			SPI_ui8TransmitRecive(data[counter]);
		}

		SPI_vChipSelection(0);
		/* Request to send */
		SPI_vChipSelection(1);
		SPI_ui8TransmitRecive(BUFFER1_REQU_TO_SEND_INST);
		SPI_vChipSelection(0);
	}
	else if (BUFFER2 == BufferID)
	{
		SPI_ui8TransmitRecive(TXB2CTRL);
		/* Priority */
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(ID>>3);
		SPI_ui8TransmitRecive(ID<<5);
		/* For Extended ID */
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(0);
		SPI_ui8TransmitRecive(DLC & 0x0F);
		/* Send Data */
		for(counter = 0; counter < (DLC & 0x0F); counter++)
		{
			SPI_ui8TransmitRecive(data[counter]);
		}

		SPI_vChipSelection(0);
		/* Request to send */
		SPI_vChipSelection(1);
		SPI_ui8TransmitRecive(BUFFER2_REQU_TO_SEND_INST);
		SPI_vChipSelection(0);
	}
	else{ /* Nothing */ }
}
