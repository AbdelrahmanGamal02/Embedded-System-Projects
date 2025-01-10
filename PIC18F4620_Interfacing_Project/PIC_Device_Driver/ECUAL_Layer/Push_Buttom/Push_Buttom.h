/* 
 * File:   Push_Buttom.h
 * Author: abdo
 *
 * Created on November 15, 2023, 9:52 PM
 */

#ifndef PUSH_BUTTOM_H
#define	PUSH_BUTTOM_H


/*************** Includes  ***********************/
#include "Push_Buttom_cfg.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef enum{
    PUSH_BUTTON_PRESSED = 0,
    PUSH_BUTTON_RELEASED
}Push_Button_State_Type;

typedef enum{
    ACTIVE_LOW_CONNECTION = 0,
    ACTIVE_HIGH_CONNECTION
}Push_Button_Connection_Type;

typedef struct
{
    Pin_Config_Type Button_Pin;
    Push_Button_State_Type Push_Button_State;
    Push_Button_Connection_Type Push_Button_Connection;
    
}Button_Type;


/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType Push_Button_Initialization(const Button_Type* Button_cfg);

Std_ReturnType Read_Button_State(const Button_Type* Button_cfg , Push_Button_State_Type* Ret_State);


/*************************************************/

#endif	/* PUSH_BUTTOM_H */

