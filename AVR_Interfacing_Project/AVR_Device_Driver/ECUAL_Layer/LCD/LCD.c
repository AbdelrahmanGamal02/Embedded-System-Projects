/*
 * LCD.c
 *
 *  Created on: ٠٢‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */
#include "LCD.h"

#if (LCD_CONFIGURATION == _ONE_8BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
void LCD_8bit_Init(void)
{
	GPIO_PortDirection(LCD_DATA_PORT,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_ENABLE_PORT, LCD_ENABLE_PIN, GPIO_PIN_DIRECTION_OUTPUT);
	_delay_ms(20);

	LCD_8bit_SendCommand(_LCD_8BIT_TWO_LINE);
	LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);
	LCD_8bit_SendCommand(_LCD_CURSOR_HOME);
	LCD_8bit_SendCommand(_LCD_DISPLAY_ON_CURSOR_OFF);

}

void LCD_8bit_SendCommand(uint8 command)
{
	GPIO_PinWriteLogic(LCD_RS_PORT , LCD_RS_PIN , GPIO_LOGIC_LOW);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
	GPIO_PORTWriteLogic(LCD_DATA_PORT , command);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_LOW);
	_delay_us(1);
}

void LCD_8bit_DisplayCharacter(uint8 character)
{
	GPIO_PinWriteLogic(LCD_RS_PORT , LCD_RS_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
	GPIO_PORTWriteLogic(LCD_DATA_PORT , character);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_LOW);
	_delay_us(1);
}

void LCD_8bit_DisplayStringData(uint8 *string_data)
{
	if(NULL == string_data)
	{
		/* Nothing */
	}
	else
	{
		while(*string_data != '\0')
		{
			LCD_8bit_DisplayCharacter(*string_data);
			string_data++;
		}
	}

}

void LCD_8bit_DisplayStringDataWithPosition(uint8 row , uint8 column , uint8 *string_data)
{
	if(NULL == string_data)
	{
		/* Nothing */
	}
	else
	{
		LCD_8bit_SetCursor(row , column);
		LCD_8bit_DisplayStringData(string_data);
	}
}

void LCD_8bit_SetCursor(uint8 row , uint8 column)
{
	uint8 LCD_Address = 0;
	switch(row)
	{
	case ROW1:
	{
		LCD_Address = column;
	}
	break;

	case ROW2:
	{
		LCD_Address = column + 0x40;
	}
	break;
#ifdef LCD_HARDWARE_CONFUGURATION_20x4
	case ROW3:
	{
		LCD_Address = column + 0x10;
	}
	break;

	case ROW4:
	{
		LCD_Address = column + 0x50;
	}
	break;
#endif


	}
	LCD_8bit_SendCommand(_LCD_DDRAM_START_ADDRESS | LCD_Address);
}
#endif

#if (LCD_CONFIGURATION == _ONE_4BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
static void Send_4bit_Data(uint8 Data)
{
	uint8 data_counter = 0;
    for(data_counter = 0; data_counter < 4; data_counter++)
    {
    	GPIO_PinWriteLogic(LCD_DATA_PORT , (data_counter + LCD_DATA_4BIT_PIN1),((Data >> data_counter) & (uint8)0x01) );
    }
}

void LCD_4bit_Init(void)
{
	/* Data init */
	GPIO_PinDirection(LCD_DATA_PORT, LCD_DATA_4BIT_PIN1, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_DATA_PORT, LCD_DATA_4BIT_PIN2, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_DATA_PORT, LCD_DATA_4BIT_PIN3, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_DATA_PORT, LCD_DATA_4BIT_PIN4, GPIO_PIN_DIRECTION_OUTPUT);

	GPIO_PinDirection(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(LCD_ENABLE_PORT, LCD_ENABLE_PIN, GPIO_PIN_DIRECTION_OUTPUT);
	_delay_ms(20);

	LCD_4bit_SendCommand(_LCD_8BIT_TWO_LINE);
    _delay_ms(5);
    LCD_4bit_SendCommand(_LCD_8BIT_TWO_LINE);
    _delay_us(150);
    LCD_4bit_SendCommand(_LCD_8BIT_TWO_LINE);

    LCD_4bit_SendCommand(_LCD_CLEAR_DIPLAY);
    LCD_4bit_SendCommand(_LCD_CURSOR_HOME);

    LCD_4bit_SendCommand(_LCD_CURSOR_INC_SHIFT_OFF);
    LCD_4bit_SendCommand(_LCD_DISPLAY_ON_CURSOR_OFF);

    LCD_4bit_SendCommand(_LCD_4BIT_TWO_LINE);
}

void LCD_4bit_SendCommand(uint8 command)
{
	GPIO_PinWriteLogic(LCD_RS_PORT , LCD_RS_PIN , GPIO_LOGIC_LOW);
	_delay_us(1);
	Send_4bit_Data(command >> 4);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
	Send_4bit_Data(command);
	_delay_us(1);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
}

void LCD_4bit_DisplayCharacter(uint8 character)
{
	GPIO_PinWriteLogic(LCD_RS_PORT , LCD_RS_PIN , GPIO_LOGIC_HIGH);
	_delay_us(1);
	Send_4bit_Data(character >> 4);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);
	Send_4bit_Data(character);
	GPIO_PinWriteLogic(LCD_ENABLE_PORT , LCD_ENABLE_PIN , GPIO_LOGIC_HIGH);



}

void LCD_4bit_DisplayStringData(uint8 *string_data)
{
	if(NULL == string_data)
	{
		/* Nothing */
	}
	else
	{
		while(*string_data != '\0')
		{
			LCD_4bit_DisplayCharacter(*string_data);
			string_data++;
		}
	}
}

void LCD_4bit_DisplayStringDataWithPosition(uint8 row , uint8 column , uint8 *string_data)
{
	if(NULL == string_data)
	{
		/* Nothing */
	}
	else
	{
		LCD_4bit_SetCursor(row , column);
		LCD_4bit_DisplayStringData(string_data);
	}
}

void LCD_4bit_SetCursor(uint8 row , uint8 column)
{
	uint8 LCD_Address = 0;
	switch(row)
	{
	case ROW1:
	{
		LCD_Address = column;
	}
	break;

	case ROW2:
	{
		LCD_Address = column + 0x40;
	}
	break;
#ifdef LCD_HARDWARE_CONFUGURATION_20x4
	case ROW3:
	{
		LCD_Address = column + 0x10;
	}
	break;

	case ROW4:
	{
		LCD_Address = column + 0x50;
	}
	break;
#endif


	}
	LCD_4bit_SendCommand(_LCD_DDRAM_START_ADDRESS | LCD_Address);
}


#endif


void LCD_Convert_uint8_to_string(uint8 value , uint8 *str)
{
    uint8 Temp_string[5] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
    	/* Nothing */
    }
    else
    {
        memset(str , ' ' , 5);
        str[5] = '\0';
        sprintf((char *)Temp_string , "%i" , value);
        while(Temp_string[Counter] != '\0')
        {
        	str[Counter] = Temp_string[Counter];
            Counter++;
        }
    }
}

void LCD_Convert_uint16_to_string(uint16 value , uint8 *str)
{
    uint8 Temp_string[7] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
    	/* Nothing */
    }
    else
    {
        memset(str , ' ' , 7);
        str[7] = '\0';
        sprintf((char *)Temp_string , "%i" , value);
        while(Temp_string[Counter] != '\0')
        {
            str[Counter] = Temp_string[Counter];
            Counter++;
        }
    }

}

void LCD_Convert_uint32_to_string(uint32 value , uint8 *str)
{
    uint8 Temp_string[12] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
        /* Nothing */
    }
    else
    {
        memset(str , ' ' , 12);
        str[12] = '\0';
        sprintf((char *)Temp_string , "%i" , value);
        while(Temp_string[Counter] != '\0')
        {
            str[Counter] = Temp_string[Counter];
            Counter++;
        }
    }

}

