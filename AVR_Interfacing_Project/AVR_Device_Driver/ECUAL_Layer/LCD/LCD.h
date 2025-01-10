/*
 * LCD.h
 *
 *  Created on: ٠٢‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_LCD_LCD_H_
#define ECUAL_LAYER_LCD_LCD_H_

/*********** Includes ******************/
#include <util/delay.h>
#include "../../MCAL_Layer/GPIO/GPIO.h"
/***************************************/
/************* Macros ******************/
// 	LCD Configuration

#define _ONE_4BIT_LCD            0
#define _ONE_8BIT_LCD            1
#define _BOTH_4BIT_8BIT_LCD      2

#define LCD_CONFIGURATION     _ONE_8BIT_LCD

#define LCD_HARDWARE_CONFUGURATION_20x2
//#define LCD_HARDWARE_CONFUGURATION_20x4
/***********************************************/


#if (LCD_CONFIGURATION == _ONE_8BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
#define LCD_DATA_PORT         	  PORTC_INDEX

#define LCD_RS_PORT           	  PORTD_INDEX
#define LCD_RS_PIN            	  GPIO_PIN0

#define LCD_ENABLE_PORT           PORTD_INDEX
#define LCD_ENABLE_PIN            GPIO_PIN2
#endif

#if (LCD_CONFIGURATION == _ONE_4BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
#define LCD_DATA_PORT         	   PORTC_INDEX

#define LCD_DATA_4BIT_PIN1         GPIO_PIN4
#define LCD_DATA_4BIT_PIN2         GPIO_PIN5
#define LCD_DATA_4BIT_PIN3         GPIO_PIN6
#define LCD_DATA_4BIT_PIN4         GPIO_PIN7

#define LCD_RS_PORT           	   PORTD_INDEX
#define LCD_RS_PIN            	   GPIO_PIN0

#define LCD_ENABLE_PORT            PORTD_INDEX
#define LCD_ENABLE_PIN             GPIO_PIN1
#endif


/********* LCD Commands **************/
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
/************************************/
#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4
/****************************************/
/*************** Data Types ************/


/***************************************/
/************** APIs *****************/
#if (LCD_CONFIGURATION == _ONE_8BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
void LCD_8bit_Init(void);
void LCD_8bit_SendCommand(uint8 command);
void LCD_8bit_DisplayCharacter(uint8 character);
void LCD_8bit_DisplayStringData(uint8 *string_data);
void LCD_8bit_DisplayStringDataWithPosition(uint8 row , uint8 column , uint8 *string_data);
void LCD_8bit_SetCursor(uint8 row , uint8 column);
#endif

#if (LCD_CONFIGURATION == _ONE_4BIT_LCD) || (LCD_CONFIGURATION == _BOTH_4BIT_8BIT_LCD)
void LCD_4bit_Init(void);
void LCD_4bit_SendCommand(uint8 command);
void LCD_4bit_DisplayCharacter(uint8 character);
void LCD_4bit_DisplayStringData(uint8 *string_data);
void LCD_4bit_DisplayStringDataWithPosition(uint8 row , uint8 column , uint8 *string_data);
void LCD_4bit_SetCursor(uint8 row , uint8 column);
#endif


void LCD_Convert_uint8_to_string(uint8 value , uint8 *str);
void LCD_Convert_uint16_to_string(uint16 value , uint8 *str);
void LCD_Convert_uint32_to_string(uint32 value , uint8 *str);
/************************************/

#endif /* ECUAL_LAYER_LCD_LCD_H_ */
