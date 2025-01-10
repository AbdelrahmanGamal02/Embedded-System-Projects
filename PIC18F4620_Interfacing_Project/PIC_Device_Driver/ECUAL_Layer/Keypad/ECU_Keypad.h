/* 
 * File:   ECU_Keypad.h
 * Author: abdo
 *
 * Created on February 13, 2024, 4:25 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*************** Includes  ***********************/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ECU_Keypad_cfg.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/
/********** Marcos Function Declarations *********/

#define KEYPAD_ROWS_NUMBER       4
#define KEYPAD_COLUMNS_NUMBER    4

#define KEYPAD_PRESSED           1
#define KEYPAD_NOT_PRESSED       0

/*************************************************/
/************ Data Type Declarations **************/

typedef struct
{
    Pin_Config_Type Keypad_Rows_Pins[KEYPAD_ROWS_NUMBER];
    Pin_Config_Type Keypad_Columns_Pins[KEYPAD_COLUMNS_NUMBER];
}Keypad_Type;

/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType Keypad_Initialization (const Keypad_Type *Keypad_cfg);

Std_ReturnType Keypad_Get_Value (const Keypad_Type *Keypad_cfg , uint8 *value, uint8 *number_of_Preesed);

/*************************************************/

#endif	/* ECU_KEYPAD_H */

