
/* 
 * File:   Push_Buttom.h
 * Author: abdo
 *
 * Created on November 15, 2023, 9:52 PM
 */

#include "Push_Buttom.h"

Std_ReturnType Push_Button_Initialization(const Button_Type *Button_cfg) {
    
    Std_ReturnType ret_state = Func_Not_OK;
    if (NULL == Button_cfg) {
        ret_state = Func_Not_OK;
        
    } else {
        ret_state = GPIO_Pin_Direction_Initilization(&(Button_cfg->Button_Pin));
    }

    return ret_state;
}

Std_ReturnType Read_Button_State(const Button_Type *Button_cfg, Push_Button_State_Type* Ret_State) {
    
    Std_ReturnType ret_state = Func_Not_OK;
    Logic_Type Ret_Logic = GPIO_HIGH;
    
    if ((NULL == Button_cfg) || (NULL == Ret_State)) {
        ret_state = Func_Not_OK;
        
    } else {
        ret_state = GPIO_Pin_Read_Logic(&(Button_cfg->Button_Pin), &Ret_Logic);

        if (ACTIVE_LOW_CONNECTION == Button_cfg->Push_Button_Connection) {
            
            if (GPIO_LOW == Ret_Logic) {
                *Ret_State = PUSH_BUTTON_PRESSED;
            } else {
                *Ret_State = PUSH_BUTTON_RELEASED;
            }
        } else if (ACTIVE_HIGH_CONNECTION == Button_cfg->Push_Button_Connection) {
            
            if (GPIO_LOW == Ret_Logic) {
                *Ret_State = PUSH_BUTTON_RELEASED;
            } else if(GPIO_HIGH == Ret_Logic) {
                *Ret_State = PUSH_BUTTON_PRESSED;
            }
        }
    }


    return ret_state;
}