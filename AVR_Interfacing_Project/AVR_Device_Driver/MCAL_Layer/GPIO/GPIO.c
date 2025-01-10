/*
 * GPIO.c
 *
 *  Created on: 17/9/2022
 *      Author: Abdelrahman Gamal
 */

#include "GPIO.h"

void GPIO_PinDirection(uint8 Port_Number , uint8 Pin_number, GPIO_Direction_Type Pin_Direction)
{
	if(Port_Number > (NUM_OF_PORTS - 1) || Pin_number > (NUM_OF_PINS - 1))
	{
		/* Nothing*/
	}
	else
	{
		switch(Port_Number)
		{
			case PORTA_INDEX:
			{
				if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
				{
					SET_BIT(DDRA , Pin_number);
				}
				else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
				{
					CLEAR_BIT(DDRA , Pin_number);
				}
				else { /* Nothing*/ }

			}
			break;

			case PORTB_INDEX:
			{
				if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
				{
					SET_BIT(DDRB , Pin_number);
				}
				else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
				{
					CLEAR_BIT(DDRB , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

			case PORTC_INDEX:
			{
				if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
				{
					SET_BIT(DDRC , Pin_number);
				}
				else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
				{
					CLEAR_BIT(DDRB , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

			case PORTD_INDEX:
			{
				if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
				{
					SET_BIT(DDRD , Pin_number);
				}
				else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
				{
					CLEAR_BIT(DDRD , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

		}
	}
}



void GPIO_PinWriteLogic(uint8 Port_Number , uint8 Pin_number, GPIO_PIN_Logic_Type Pin_Logic)
{
	if(Port_Number > (NUM_OF_PORTS - 1) || Pin_number > (NUM_OF_PINS - 1) || (Pin_Logic != 0 && Pin_Logic != 1))
	{
		/* Nothing*/
	}
	else
	{
		switch(Port_Number)
		{
			case PORTA_INDEX:
			{
				if(GPIO_LOGIC_HIGH == Pin_Logic)
				{
					SET_BIT(PORTA , Pin_number);
				}
				else if(GPIO_LOGIC_LOW == Pin_Logic)
				{
					CLEAR_BIT(PORTA , Pin_number);
				}
				else { /* Nothing*/ }

			}
			break;

			case PORTB_INDEX:
			{
				if(GPIO_LOGIC_HIGH == Pin_Logic)
				{
					SET_BIT(PORTB , Pin_number);
				}
				else if(GPIO_LOGIC_LOW == Pin_Logic)
				{
					CLEAR_BIT(PORTB , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

			case PORTC_INDEX:
			{
				if(GPIO_LOGIC_HIGH == Pin_Logic)
				{
					SET_BIT(PORTC , Pin_number);
				}
				else if(GPIO_LOGIC_LOW == Pin_Logic)
				{
					CLEAR_BIT(PORTC , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

			case PORTD_INDEX:
			{
				if(GPIO_LOGIC_HIGH == Pin_Logic)
				{
					SET_BIT(PORTD , Pin_number);
				}
				else if(GPIO_LOGIC_LOW == Pin_Logic)
				{
					CLEAR_BIT(PORTD , Pin_number);
				}
				else { /* Nothing*/ }
			}
			break;

		}
	}

}


uint8 GPIO_PinReadLogic(uint8 Port_Number , uint8 Pin_number) // @suppress("No return")
{

    uint8 pin_value = 0;

  /*
   * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
   * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
   * In this case the input is not valid port/pin number
   */
    if((Pin_number >= NUM_OF_PINS) || (Port_Number >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
  else
  {
    /* Read the pin value as required */
    switch(Port_Number)
    {
    case PORTA_INDEX:
      if(BIT_IS_SET(PINA,Pin_number))
      {
        pin_value = GPIO_LOGIC_HIGH;
      }
      else
      {
        pin_value = GPIO_LOGIC_LOW;
      }
      break;
    case PORTB_INDEX:
      if(BIT_IS_SET(PINB,Pin_number))
      {
        pin_value = GPIO_LOGIC_HIGH;
      }
      else
      {
        pin_value = GPIO_LOGIC_LOW;
      }
      break;
    case PORTC_INDEX:
      if(BIT_IS_SET(PINC,Pin_number))
      {
        pin_value = GPIO_LOGIC_HIGH;
      }
      else
      {
        pin_value = GPIO_LOGIC_LOW;
      }
      break;
    case PORTD_INDEX:
      if(BIT_IS_SET(PIND,Pin_number))
      {
        pin_value = GPIO_LOGIC_HIGH;
      }
      else
      {
        pin_value = GPIO_LOGIC_LOW;
      }
      break;
    }
  }
  return pin_value;
}



void GPIO_PortDirection(uint8 Port_Number, GPIO_Direction_Type Pin_Direction)
{
	if(Port_Number > (NUM_OF_PORTS - 1))
		{
			/* Nothing*/
		}
		else
		{
			switch(Port_Number)
			{
				case PORTA_INDEX:
				{
					if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
					{
						DDRA = 0xFF;
					}
					else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
					{
						DDRA = 0x00;
					}
					else { /* Nothing*/ }

				}
				break;

				case PORTB_INDEX:
				{
					if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
					{
						DDRB = 0xFF;
					}
					else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
					{
						DDRB = 0x00;
					}
					else { /* Nothing*/ }
				}
				break;

				case PORTC_INDEX:
				{
					if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
					{
						DDRC = 0xFF;
					}
					else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
					{
						DDRC = 0x00;
					}
					else { /* Nothing*/ }
				}
				break;

				case PORTD_INDEX:
				{
					if(GPIO_PIN_DIRECTION_OUTPUT == Pin_Direction)
					{
						DDRD = 0xFF;
					}
					else if(GPIO_PIN_DIRECTION_INPUT == Pin_Direction)
					{
						DDRD = 0x00;
					}
					else { /* Nothing*/ }
				}
				break;

			}
		}
}


void GPIO_PORTWriteLogic(uint8 Port_Number , uint8 value)
{
	if(Port_Number > (NUM_OF_PORTS - 1))
		{
			/* Nothing*/
		}
		else
		{
			switch(Port_Number)
			{
				case PORTA_INDEX:
				{
					if(DDRA == 0xFF)
					{
						PORTA = value;
					}
					else{ /* Nothing */ }
				}
				break;

				case PORTB_INDEX:
				{
					if(DDRB == 0xFF)
					{
						PORTB = value;
					}
				}
				break;

				case PORTC_INDEX:
				{
					if(DDRC == 0xFF)
					{
						PORTC = value;
					}
					else{ /* Nothing */ }
				}
				break;

				case PORTD_INDEX:
				{
					if(DDRD == 0xFF)
					{
						PORTD = value;
					}
					else{ /* Nothing */ }
				}
				break;

			}
		}
}

uint8 GPIO_PortReadLogic(uint8 Port_Number) // @suppress("No return")
{
	uint8 read_value = 0;
	if(Port_Number > (NUM_OF_PORTS - 1))
	{
		/* Nothing*/
	}
	else
	{
		switch(Port_Number)
		{
			case PORTA_INDEX:
			{
				read_value = PINA;
			}
			break;

			case PORTB_INDEX:
			{
				read_value = PINB;
			}
			break;

			case PORTC_INDEX:
			{
				read_value = PINC;
			}
			break;

			case PORTD_INDEX:
			{
				read_value = PIND;
			}
			break;

		}
		return read_value;
	}



}
