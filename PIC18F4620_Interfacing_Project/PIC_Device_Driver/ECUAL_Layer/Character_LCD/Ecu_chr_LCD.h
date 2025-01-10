/* 
 * File:   Ecu_chr_LCD.h
 * Author: abdo
 *
 * Created on February 17, 2024, 1:52 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/*************** Includes  ***********************/

#include "Ecu_chr_LCD_cfg.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"


/*************************************************/

/************** Marcos Declarations **************/


/*                 configuration of LCD              */

#define _ONE_4BIT_LCD            0
#define _ONE_8BIT_LCD            1 
#define _BOTH_4BIT_8BIT_LCD      2

#define LCD_CONFIGURATION     _ONE_4BIT_LCD

/*               Commands of LCD                            */ 
#define _LCD_CLEAR_DIPLAY                                          0x01
#define _LCD_CURSOR_HOME                                           0x02

#define _LCD_CURSOR_DEC_SHIFT_OFF                                  0x04
#define _LCD_CURSOR_DEC_SHIFT_ON                                   0x05
#define _LCD_CURSOR_INC_SHIFT_OFF                                  0x06
#define _LCD_CURSOR_INC_SHIFT_ON                                   0x07

#define _LCD_DISPLAY_OFF_CURSOR_OFF                                0x08
#define _LCD_DISPLAY_ON_CURSOR_OFF                                 0x0C
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_ON      0x0D
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_OFF      0x0E

#define _LCD_MOVE_CURSOR_LEFT                                      0x10
#define _LCD_MOVE_CURSOR_RIGHT                                     0x14
#define _LCD_SHIFT_ALL_DATA_LEFT                                   0x18
#define _LCD_SHIFT_ALL_DATA_RIGHT                                  0x1C

#define _LCD_4BIT_ONE_LINE                                         0x20 
#define _LCD_8BIT_ONE_LINE                                         0x30         
#define _LCD_4BIT_TWO_LINE                                         0x28
#define _LCD_8BIT_TWO_LINE                                         0x38

#define _LCD_DDRAM_START_ADDRESS                                   0x80
#define _LCD_CGRAM_START_ADDRESS                                   0x40

/*******************************************************************************/

#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/

typedef struct
{
    Pin_Config_Type LCD_RS;
    Pin_Config_Type LCD_Enable;
    
#if LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD
    Pin_Config_Type LCD_4BIT_Data[4];
    Pin_Config_Type LCD_8BIT_Data[8];
    
#elif LCD_CONFIGURATION == _ONE_4BIT_LCD
    Pin_Config_Type LCD_4BIT_Data[4];
    
#elif LCD_CONFIGURATION == _ONE_8BIT_LCD
    Pin_Config_Type LCD_8BIT_Data[8];
    
#endif   
    
}Chr_LCD_Type;

/*************************************************/
/*********** Function Declarations ***************/

#if LCD_CONFIGURATION == _ONE_4BIT_LCD
Std_ReturnType LCD_4BIT_Initilization(const Chr_LCD_Type* LCD);
Std_ReturnType LCD_4BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command);
Std_ReturnType LCD_4BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data);
Std_ReturnType LCD_4BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data);
Std_ReturnType LCD_4BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str);
Std_ReturnType LCD_4BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str);
Std_ReturnType LCD_4BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position);
#endif

#if LCD_CONFIGURATION == _ONE_8BIT_LCD
Std_ReturnType LCD_8BIT_Initilization(const Chr_LCD_Type* LCD);
Std_ReturnType LCD_8BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command);
Std_ReturnType LCD_8BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data);
Std_ReturnType LCD_8BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data);
Std_ReturnType LCD_8BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str);
Std_ReturnType LCD_8BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str);
Std_ReturnType LCD_8BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position);
#endif

#if LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD
Std_ReturnType LCD_4BIT_Initilization(const Chr_LCD_Type* LCD);
Std_ReturnType LCD_4BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command);
Std_ReturnType LCD_4BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data);
Std_ReturnType LCD_4BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data);
Std_ReturnType LCD_4BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str);
Std_ReturnType LCD_4BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str);
Std_ReturnType LCD_4BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position);

Std_ReturnType LCD_8BIT_Initilization(const Chr_LCD_Type* LCD);
Std_ReturnType LCD_8BIT_Send_Command(const Chr_LCD_Type* LCD , uint8 command);
Std_ReturnType LCD_8BIT_Send_char_data(const Chr_LCD_Type* LCD , uint8 Data);
Std_ReturnType LCD_8BIT_Send_char_data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 Data);
Std_ReturnType LCD_8BIT_Send_String_data(const Chr_LCD_Type* LCD , uint8 *str);
Std_ReturnType LCD_8BIT_Send_String_Data_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, uint8 *str);
Std_ReturnType LCD_8BIT_Send_custom_Character_With_Position(const Chr_LCD_Type* LCD ,uint8 row , uint8 column, const uint8 _chr[] , uint8 memory_position);

#endif

Std_ReturnType Convert_uint8_to_string(uint8 value , uint8 *str);
Std_ReturnType Convert_uint16_to_string(uint16 value , uint8 *str);
Std_ReturnType Convert_uint32_to_string(uint32 value , uint8 *str);
Std_ReturnType LCD_8BIT_Set_Cursor(const Chr_LCD_Type* LCD , uint8 row , uint8 column);

/*************************************************/

#endif	/* ECU_CHR_LCD_H */

