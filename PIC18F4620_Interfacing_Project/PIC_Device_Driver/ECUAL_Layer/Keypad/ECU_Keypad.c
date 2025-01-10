/* 
 * File:   ECU_Keypad.c
 * Author: abdo
 *
 * Created on February 13, 2024, 4:25 PM
 */


#include "ECU_Keypad.h"

/* to determine values of keypad */
/* depend on the structure of Keypad*/
uint8 Keypad_Values[KEYPAD_ROWS_NUMBER][KEYPAD_COLUMNS_NUMBER] = 
                   {
                    { 7  ,  8  ,  9  , '/' },
                    { 4  ,  5  ,  6  , '*' },
                    { 1  ,  2  ,  3  , '-' },
                    {'#' ,  0  , '=' , '+' },
                                            };
uint8 number_of_Preesed_counter = 0;

Std_ReturnType Keypad_Initialization (const Keypad_Type *Keypad_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 Rows_Counter = 0 , Columns_Counter = 0;
    if(NULL == Keypad_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        for(Rows_Counter = 0; Rows_Counter < KEYPAD_ROWS_NUMBER; Rows_Counter++)
        {
            ret_state = GPIO_Pin_Initilization(&(Keypad_cfg->Keypad_Rows_Pins[Rows_Counter]));
        }
        
        for(Columns_Counter = 0; Columns_Counter < KEYPAD_COLUMNS_NUMBER; Columns_Counter++)
        {
            ret_state = GPIO_Pin_Direction_Initilization(&(Keypad_cfg->Keypad_Columns_Pins[Columns_Counter]));
        }
    }
    
    return ret_state;
}

Std_ReturnType Keypad_Get_Value (const Keypad_Type *Keypad_cfg , uint8 *value , uint8 *number_of_Preesed)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 counter = 0 ;
    Logic_Type value_checked = GPIO_LOW;
    uint8 L_Rows_Counter = 0 , L_Columns_Counter = 0;
    *number_of_Preesed = KEYPAD_NOT_PRESSED;
    if((NULL == Keypad_cfg) || (NULL == value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        for(L_Rows_Counter = 0; L_Rows_Counter < KEYPAD_ROWS_NUMBER; L_Rows_Counter++)
        {
            /* to write logic low on all rows to ensure that all rows initially has logic zero*/
            for(counter = 0; counter < KEYPAD_ROWS_NUMBER; counter++)
            {
                ret_state = GPIO_Pin_Write_Logic(&(Keypad_cfg->Keypad_Rows_Pins[counter]) , GPIO_LOW);
            }
            __delay_ms(20);
            /* write logic high on rows to scan rows */
            ret_state = GPIO_Pin_Write_Logic(&(Keypad_cfg->Keypad_Rows_Pins[L_Rows_Counter]) , GPIO_HIGH);
            
            for(L_Columns_Counter = 0; L_Columns_Counter < KEYPAD_COLUMNS_NUMBER; L_Columns_Counter++)
            {
                ret_state = GPIO_Pin_Read_Logic(&(Keypad_cfg->Keypad_Columns_Pins[L_Columns_Counter]) , &value_checked);
                
                if(GPIO_HIGH == value_checked)
                {
                    *value = Keypad_Values[L_Rows_Counter][L_Columns_Counter];

                    
                    *number_of_Preesed = KEYPAD_PRESSED;
                }
            }
        }
    }
    
    return ret_state;
}