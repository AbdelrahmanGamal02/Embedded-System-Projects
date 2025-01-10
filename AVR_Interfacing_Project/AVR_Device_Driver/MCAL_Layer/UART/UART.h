/*
 * UART.h
 *
 *  Created on: ٢٣‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef MCAL_LAYER_UART_UART_H_
#define MCAL_LAYER_UART_UART_H_

/*********** Includes ******************/
#include "../GPIO/GPIO.h"
/***************************************/
/************* Macros ******************/

#define BAUD_RATE      9600

/***************************************/
/************** APIs *****************/
/*
	Function Name        : UART_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize UART.
*/
void UART_Init(void);
/*
	Function Name        : UART_SendByte
	Function Returns     : void
	Function Arguments   : uint8 Data
	Function Description : Send Data From Micro-controller using UART.
*/
void UART_SendByte(uint8 Data);
/*
	Function Name        : UART_ReceiveByte
	Function Returns     : uint8
	Function Arguments   : void
	Function Description : Receive data using UART.
*/
uint8 UART_ReceiveByte(void);

/*
	Function Name        : UART_SendString
	Function Returns     : void
	Function Arguments   : uint8 Data
	Function Description : Send String From Micro-controller using UART.
*/
void UART_SendString(uint8 *str);

/*
	Function Name        : UART_ReceiveByte
	Function Returns     : uint8
	Function Arguments   : void
	Function Description : Receive string using UART.
*/
void UART_ReceiveString(uint8 *str);

/************************************/

#endif /* MCAL_LAYER_UART_UART_H_ */
