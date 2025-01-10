/*
 * SPI.h
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef MCAL_LAYER_SPI_SPI_H_
#define MCAL_LAYER_SPI_SPI_H_

/*********** Includes ******************/
#include "../GPIO/GPIO.h"
/***************************************/
/************* Macros ******************/
#define DEMAND_RESPONSE 0xFF

#define ON_STATUS   0x01
#define OFF_STATUS  0x00

#define SPI_SCK  GPIO_PIN7
#define SPI_MISO GPIO_PIN6
#define SPI_MOSI GPIO_PIN5
#define SPI_SS   GPIO_PIN4
/***************************************/
/************** APIs *****************/
/*
	Function Name        : SPI_vInitMaster
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize the master.
*/
void SPI_vInitMaster (void);

/*
	Function Name        : SPI_vInitSlave
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize the slave.
*/
void SPI_vInitSlave (void);

/*
	Function Name        : SPI_ui8TransmitRecive
	Function Returns     : uint8
	Function Arguments   : uint8 data
	Function Description : Send data in case of master or receive data and send response in case of slave.
*/
uint8 SPI_ui8TransmitRecive (uint8 data);

/*
	Function Name        : SPI_vChipSelection
	Function Returns     : void
	Function Arguments   : uint8 status
	Function Description : used for CAN driver to allow node to take the bus and send or receive data.
*/
void SPI_vChipSelection (uint8 status);
/************************************/

#endif /* MCAL_LAYER_SPI_SPI_H_ */
