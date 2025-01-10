/* 
 * File:   Ecu_chr_LCD_cfg.c
 * Author: abdo
 *
 * Created on February 17, 2024, 1:52 PM
 */

#include "Ecu_chr_LCD.h"

/*************** Helper Functions *****************/

#if LCD_CONFIGURATION == _ONE_4BIT_LCD
static Std_ReturnType Send_4bit_Data(const Chr_LCD_Type* LCD , uint8 data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 data_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        for(data_counter = 0; data_counter < 4; data_counter++)
        {
            ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_4BIT_Data[data_counter]) , ((data >> data_counter) & (uint8)0x01) );
        }
        
    }
    
    return ret_state;
}

static Std_ReturnType LCD_4BIT_Set_Cursor(const Chr_LCD_Type* LCD , uint8 row , uint8 column)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        // decrement column by one because first column is Zero
       column--;
       switch(row)
       {
           case ROW1 : ret_state = LCD_4BIT_Send_Command(LCD , (0x80 + column)); break;
           case ROW2 : ret_state = LCD_4BIT_Send_Command(LCD , (0xC0 + column)); break;
           case ROW3 : ret_state = LCD_4BIT_Send_Command(LCD , (0x94 + column)); break;
           case ROW4 : ret_state = LCD_4BIT_Send_Command(LCD , (0xD4 + column)); break;
           default : break;
       }
    }
    
    return ret_state;
}

#endif

#if LCD_CONFIGURATION == _ONE_8BIT_LCD

Std_ReturnType LCD_8BIT_Set_Cursor(const Chr_LCD_Type* LCD , uint8 row , uint8 column)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        // decrement column by one because first column is Zero
       column--;
       switch(row)
       {
           case ROW1 : ret_state = LCD_8BIT_Send_Command(LCD , (0x80 + column)); break;
           case ROW2 : ret_state = LCD_8BIT_Send_Command(LCD , (0xC0 + column)); break;
           case ROW3 : ret_state = LCD_8BIT_Send_Command(LCD , (0x94 + column)); break;
           case ROW4 : ret_state = LCD_8BIT_Send_Command(LCD , (0xD5 + column)); break;
           default : break;
       }
    }
    
    return ret_state;
}

#endif


static Std_ReturnType Send_Enable(const Chr_LCD_Type* LCD)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_Enable) , GPIO_HIGH);
       __delay_us(100);
       ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_Enable) , GPIO_LOW);
    }
    
    return ret_state;
}


/**************************************************/

/*************** Function Definitions *****************/

#if LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD

Std_ReturnType LCD_4BIT_Initilization(const Chr_LCD_Type* LCD)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 init_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_RS));
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_Enable));
        for(init_counter = 0; init_counter < 4; ++init_counter)
        {
            ret_state = GPIO_Pin_Initilization(&(LCD->LCD_4BIT_Data[init_counter]));
        }
        
        __delay_ms(20);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_ms(5);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_us(150);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CLEAR_DIPLAY);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_HOME);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_INC_SHIFT_OFF);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_DISPLAY_ON_CURSOR_OFF);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_4BIT_TWO_LINE);
        ret_state = LCD_4BIT_Send_Command(LCD , 0x80);

    }
    
    return ret_state;
    
}

Std_ReturnType LCD_4BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_LOW);
        ret_state = Send_4bit_Data(LCD , (command >> 4));
        ret_state = Send_Enable(LCD);
        ret_state = Send_4bit_Data(LCD , command);
        ret_state = Send_Enable(LCD);
        
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_HIGH);
        ret_state = Send_4bit_Data(LCD , (Data >> 4));
        ret_state = Send_Enable(LCD);
        ret_state = Send_4bit_Data(LCD , Data);
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Set_Cursor(LCD , row , column);
        ret_state = LCD_4BIT_Send_char_data(LCD , Data);
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        while(*str)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Set_Cursor(LCD , row , column);
        while(*str)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 custom_Character_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Send_Command(LCD , (_LCD_CGRAM_START_ADDRESS + (memory_position * 8)));
        for(custom_Character_counter =0 ;custom_Character_counter < 8;custom_Character_counter++)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , _chr[custom_Character_counter]);
        }
        ret_state = LCD_4BIT_Send_char_data_With_Position(LCD , row , column , memory_position);
    }
    
    return ret_state;
}


Std_ReturnType LCD_8BIT_Initilization(const Chr_LCD_Type* LCD)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 init_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_RS));
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_Enable));
        for(init_counter = 0; init_counter < 8; ++init_counter)
        {
            ret_state = GPIO_Pin_Initilization(&(LCD->LCD_8BIT_Data[init_counter]));
        }
        __delay_ms(20);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_ms(5);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_us(150);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CLEAR_DIPLAY);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_HOME);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_INC_SHIFT_OFF);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_DISPLAY_ON_CURSOR_OFF);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        ret_state = LCD_4BIT_Send_Command(LCD , 0x80);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 data_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_LOW);
        for(data_counter = 0; data_counter < 8; data_counter++)
        {
            ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_8BIT_Data[data_counter]) , ((command >> data_counter) & (uint8)0x01) );
        }
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 data_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_HIGH);
        for(data_counter = 0; data_counter < 8; data_counter++)
        {
            ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_8BIT_Data[data_counter]) , ((Data >> data_counter) & (uint8)0x01) );
        }
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Set_Cursor(LCD , row , column);
        ret_state = LCD_8BIT_Send_char_data(LCD , Data);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        while(*str)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Set_Cursor(LCD , row , column);
        while(*str)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 custom_Character_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Send_Command(LCD , (_LCD_CGRAM_START_ADDRESS + (memory_position * 8)));
        for(custom_Character_counter =0 ;custom_Character_counter < 8;custom_Character_counter++)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , _chr[custom_Character_counter]);
        }
        ret_state = LCD_8BIT_Send_char_data_With_Position(LCD , row , column , memory_position);
    }
    
    return ret_state;
}
#endif

#if LCD_CONFIGURATION == _ONE_4BIT_LCD

Std_ReturnType LCD_4BIT_Initilization(const Chr_LCD_Type* LCD)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 init_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_RS));
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_Enable));
        for(init_counter = 0; init_counter < 4; ++init_counter)
        {
            ret_state = GPIO_Pin_Initilization(&(LCD->LCD_4BIT_Data[init_counter]));
        }
        
        __delay_ms(20);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_ms(5);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_us(150);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CLEAR_DIPLAY);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_HOME);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_CURSOR_INC_SHIFT_OFF);
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_DISPLAY_ON_CURSOR_OFF);
        
        ret_state = LCD_4BIT_Send_Command(LCD , _LCD_4BIT_TWO_LINE);
        ret_state = LCD_4BIT_Send_Command(LCD , 0x80);

    }
    
    return ret_state;
    
}

Std_ReturnType LCD_4BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_LOW);
        ret_state = Send_4bit_Data(LCD , (command >> 4));
        ret_state = Send_Enable(LCD);
        ret_state = Send_4bit_Data(LCD , command);
        ret_state = Send_Enable(LCD);
        
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_HIGH);
        ret_state = Send_4bit_Data(LCD , (Data >> 4));
        ret_state = Send_Enable(LCD);
        ret_state = Send_4bit_Data(LCD , Data);
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Set_Cursor(LCD , row , column);
        ret_state = LCD_4BIT_Send_char_data(LCD , Data);
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        while(*str)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Set_Cursor(LCD , row , column);
        while(*str)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_4BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 custom_Character_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_4BIT_Send_Command(LCD , (_LCD_CGRAM_START_ADDRESS + (memory_position * 8)));
        for(custom_Character_counter =0 ;custom_Character_counter < 8;custom_Character_counter++)
        {
            ret_state = LCD_4BIT_Send_char_data(LCD , _chr[custom_Character_counter]);
        }
        ret_state = LCD_4BIT_Send_char_data_With_Position(LCD , row , column , memory_position);
    }
    
    return ret_state;
}
#endif

#if LCD_CONFIGURATION == _ONE_8BIT_LCD

Std_ReturnType LCD_8BIT_Initilization(const Chr_LCD_Type* LCD)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 init_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_RS));
        ret_state = GPIO_Pin_Initilization(&(LCD->LCD_Enable));
        for(init_counter = 0; init_counter <= 7; ++init_counter)
        {
            ret_state = GPIO_Pin_Initilization(&(LCD->LCD_8BIT_Data[init_counter]));
        }
        __delay_ms(20);
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_ms(5);
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        __delay_us(150);
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_CLEAR_DIPLAY);
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_CURSOR_HOME);
        
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_CURSOR_INC_SHIFT_OFF);
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_DISPLAY_ON_CURSOR_OFF);
        
        ret_state = LCD_8BIT_Send_Command(LCD , _LCD_8BIT_TWO_LINE);
        ret_state = LCD_8BIT_Send_Command(LCD , 0x80);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 data_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_LOW);
        for(data_counter = 0; data_counter < 8; ++data_counter)
        {
            ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_8BIT_Data[data_counter]) , ((command >> data_counter) & (uint8)0x01) );
        }
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 data_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_RS) , GPIO_HIGH);
        for(data_counter = 0; data_counter < 8; data_counter++)
        {
            ret_state = GPIO_Pin_Write_Logic(&(LCD->LCD_8BIT_Data[data_counter]) , ((Data >> data_counter) & (uint8)0x01) );
        }
        ret_state = Send_Enable(LCD);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Set_Cursor(LCD , row , column);
        ret_state = LCD_8BIT_Send_char_data(LCD , Data);
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        while(*str)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == LCD) || (NULL == str))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Set_Cursor(LCD , row , column);
        while(*str)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , *str++);
        }
    }
    
    return ret_state;
}

Std_ReturnType LCD_8BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 custom_Character_counter = 0;
    if(NULL == LCD)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = LCD_8BIT_Send_Command(LCD , (_LCD_CGRAM_START_ADDRESS + (memory_position * 8)));
        for(custom_Character_counter =0 ;custom_Character_counter < 8;custom_Character_counter++)
        {
            ret_state = LCD_8BIT_Send_char_data(LCD , _chr[custom_Character_counter]);
        }
        ret_state = LCD_8BIT_Send_char_data_With_Position(LCD , row , column , memory_position);
    }
    
    return ret_state;
}
#endif



Std_ReturnType Convert_uint8_to_string(uint8 value , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 Temp_string[5] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
        ret_state = Func_Not_OK;
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
    
    return ret_state;
}

Std_ReturnType Convert_uint16_to_string(uint16 value , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 Temp_string[7] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
        ret_state = Func_Not_OK;
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
    
    return ret_state;
}

Std_ReturnType Convert_uint32_to_string(uint32 value , uint8 *str)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 Temp_string[12] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
        ret_state = Func_Not_OK;
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
    
    return ret_state;
}

/***********************************************************************************************/

