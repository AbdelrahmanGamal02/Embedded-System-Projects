/* 
 * File:   DC_Motor.c
 * Author: abdo
 *
 * Created on December 6, 2023, 9:28 PM
 */

#include "DC_Motor.h"


Std_ReturnType DC_Motor_Initialization(const DC_Motor_Type *DC_Motor_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == DC_Motor_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Initilization(&(DC_Motor_cfg->DC_Motor_Pins[0]));
        ret_state = GPIO_Pin_Initilization(&(DC_Motor_cfg->DC_Motor_Pins[1]));
    }
    
    return ret_state;
    
}

Std_ReturnType DC_Motor_Move_Right(const DC_Motor_Type *DC_Motor_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == DC_Motor_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[0]) , GPIO_HIGH);
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[1]) , GPIO_LOW);
    }
    
    return ret_state;
    
}

Std_ReturnType DC_Motor_Move_Left(const DC_Motor_Type *DC_Motor_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == DC_Motor_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[0]) , GPIO_LOW);
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[1]) , GPIO_HIGH);
    }
    
    return ret_state;
    
}

Std_ReturnType DC_Motor_Stop(const DC_Motor_Type *DC_Motor_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == DC_Motor_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[0]) , GPIO_LOW);
        ret_state = GPIO_Pin_Write_Logic(&(DC_Motor_cfg->DC_Motor_Pins[1]) , GPIO_LOW);
    }
    
    return ret_state;
    
}