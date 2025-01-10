/*
 * _7_Segment.c
 *
 *  Created on: ٠٨‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */


#include "_7_Segment.h"

void _7_SEGMENT_vInit(void)
{
#if _7_SEGMENT_CONNECTION == _7_SEGMENT_WITHOUT_DECODER
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_FIRST_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_SECOND_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_THIRD_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_FOURTH_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_FIFTH_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_SIXTH_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_SEVENTH_PIN , GPIO_PIN_DIRECTION_OUTPUT);

#elif _7_SEGMENT_CONNECTION == _7_SEGMENT_WITH_DECODER
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_FIRST_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_SECOND_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_THIRD_PIN , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(_7_SEGMENT_PORT , _7_SEGMENT_FOURTH_PIN , GPIO_PIN_DIRECTION_OUTPUT);

#endif
}


void _7_SEGMENT_Write_Number_without_decoder(uint8 number)
{
#if _7_SEGMENT_TYPE == _7_SEGMENT_COMMON_CATHODE
	switch(number)
	{
	case 0:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x3F;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x3F;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x3F;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x3F;
		}
		break;
		}
	}
	break;

	case 1:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x06;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x06;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x06;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x06;
		}
		break;
		}
	}
	break;

	case 2:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x5B;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x5B;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x5B;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x5B;
		}
		break;
		}
	}
	break;

	case 3:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x4F;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x4F;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x4F;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x4F;
		}
		break;
		}
	}
	break;

	case 4:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x66;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x66;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x66;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x66;
		}
		break;
		}
	}
	break;

	case 5:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x6D;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x6D;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x6D;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x6D;
		}
		break;
		}
	}
	break;

	case 6:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x7D;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x7D;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x7D;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x7D;
		}
		break;
		}
	}
	break;

	case 7:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x07;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x07;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x07;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x07;
		}
		break;
		}
	}
	break;

	case 8:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x7F;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x7F;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x7F;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x7F;
		}
		break;
		}
	}
	break;

	case 9:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x6F;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x6F;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x6F;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x6F;
		}
		break;
		}
	}
	break;
	}

#elif _7_SEGMENT_TYPE == _7_SEGMENT_COMMON_ANODE
	switch(number)
	{
	case 0:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0xC0;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0xC0;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0xC0;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0xC0;
		}
		break;
		}
	}
	break;

	case 1:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0xF9;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0xF9;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0xF9;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0xF9;
		}
		break;
		}
	}
	break;

	case 2:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0xA4;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0xA4;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0xA4;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0xA4;
		}
		break;
		}
	}
	break;

	case 3:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0xB0;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0xB0;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0xB0;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0xB0;
		}
		break;
		}
	}
	break;

	case 4:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x99;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x99;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x99;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x99;
		}
		break;
		}
	}
	break;

	case 5:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x92;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x92;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x92;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x92;
		}
		break;
		}
	}
	break;

	case 6:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x82;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x82;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x82;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x82;
		}
		break;
		}
	}
	break;

	case 7:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0xF8;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0xF8;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0xF8;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0xF8;
		}
		break;
		}
	}
	break;

	case 8:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x80;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x80;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x80;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x80;
		}
		break;
		}
	}
	break;

	case 9:
	{
		switch(_7_SEGMENT_PORT)
		{
		case PORTA_INDEX:
		{
			PORTA = 0x90;
		}
		break;

		case PORTB_INDEX:
		{
			PORTB = 0x90;
		}
		break;

		case PORTC_INDEX:
		{
			PORTC = 0x90;
		}
		break;

		case PORTD_INDEX:
		{
			PORTD = 0x90;
		}
		break;
		}
	}
	break;
	}


#endif
}



void _7_SEGMENT_Write_Number_with_decoder(uint8 number)
{
	GPIO_PinWriteLogic(_7_SEGMENT_PORT , _7_SEGMENT_FIRST_PIN , (number & 0x01));
	GPIO_PinWriteLogic(_7_SEGMENT_PORT , _7_SEGMENT_SECOND_PIN  , ((number >> 1) & 0x01));
	GPIO_PinWriteLogic(_7_SEGMENT_PORT , _7_SEGMENT_THIRD_PIN  , ((number >> 2) & 0x01));
	GPIO_PinWriteLogic(_7_SEGMENT_PORT , _7_SEGMENT_FOURTH_PIN  , ((number >> 3) & 0x01));
}


