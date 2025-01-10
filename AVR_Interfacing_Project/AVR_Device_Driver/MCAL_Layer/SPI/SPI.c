/*
 * SPI.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */


#include "SPI.h"


void SPI_vInitMaster (void)
{
	//Set the port B mosi(master out slave in ) ,port B ss(slave select),sck(spi clock)  pins as output
	GPIO_PinDirection(PORTB_INDEX , SPI_MOSI, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTB_INDEX , SPI_SS, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTB_INDEX , SPI_SCK, GPIO_PIN_DIRECTION_OUTPUT);

	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);//Enable the SPI,master mode ,Set the clock speed to F/16
}

void SPI_vInitSlave (void)
{
	//Set the port B miso(master in slave out ) pin as output
	GPIO_PinDirection(PORTB_INDEX , SPI_MISO, GPIO_PIN_DIRECTION_OUTPUT);

	SPCR |= (1<<SPE);//Enable the SPI
}

uint8 SPI_ui8TransmitRecive (uint8 data)
{
	SPDR = data;//move the given data to SPI Data register

	//in case of master send data and wait till the data are fully transmitted
	//in case of slave wait the data to be transmitted by the master
	while (((SPSR&(1<<SPIF))>>SPIF)==0);	//wait till the transmitting is done
										   //SPI flag is set to one if the transmission is done

	return SPDR;//return the value of SPI Data register after the transmission or receiving is done
}

void SPI_vChipSelection (uint8 status)
{
	if(ON_STATUS == status)
	{
		GPIO_PinWriteLogic(PORTB_INDEX , SPI_SS , GPIO_LOGIC_LOW);
	}
	else if(OFF_STATUS == status)
	{
		GPIO_PinWriteLogic(PORTB_INDEX , SPI_SS , GPIO_LOGIC_HIGH);
	}
	else{ /* Nothing */ }
}
