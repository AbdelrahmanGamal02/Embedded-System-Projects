/*
 * UART.c
 *
 *  Created on: ٢٣‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "UART.h"

void UART_Init(void)
{
	uint16 UBRR_Value = 0;
	/* Double asynchronous Speed */
	SET_BIT(UCSRA , 1);
	/* Enable transmitter and receiver */
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
	/* to write in UCSRC Register */
	SET_BIT(UCSRB,7);
	/* One Stop Bit  if you want two stop bit use SET_BIT(UCSRB,3);*/
	/* character size is 8 bit*/
	SET_BIT(UCSRB,1);
	SET_BIT(UCSRB,2);

	/* Baud Rate */
	CLEAR_BIT(UCSRB,7);

	UBRR_Value = (uint16)(((F_CPU / (8 * BAUD_RATE))) - 1);

	UBRRH = (uint8)(UBRR_Value >> 8);
	UBRRL = (uint8)(UBRR_Value);
}


void UART_SendByte(uint8 Data)
{
	while(BIT_IS_CLEAR(UCSRA , UDRE)){} /* wait until transmission buffer is empty */

	UDR = Data; /* Transmit Data */
}

uint8 UART_ReceiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA , RXC)){} /* wait until Receiving is done */

	return UDR; /* return Data */
}

void UART_SendString(uint8 *str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_SendByte(str[i]);
		i++;
	}
}

void UART_ReceiveString(uint8 *str)
{
	uint8 i = 0;

	while(str[i] != '\0')
	{
		str[i] = UART_ReceiveByte();
		i++;
	}
	str[i] = '\0';
}

