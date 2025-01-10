
/* 
 * File:   ECUAL_Relay.c
 * Author: abdo
 *
 * Created on November 16, 2023, 9:25 PM
 */


#include "ECUAL_Relay.h"

Std_ReturnType Relay_Initialization(const Relay_Type *Relay_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Relay_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Pin_Config_Type Relay_CONFIG = {
        .Port = Relay_cfg->port_name,
        .Pin = Relay_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = Relay_cfg->Relay_state   
        };
        
        ret_state = GPIO_Pin_Initilization(&Relay_CONFIG); 
    }
    
    return ret_state;
}

Std_ReturnType Relay_Turn_ON(const Relay_Type *Relay_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Relay_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Pin_Config_Type Relay_CONFIG = {
        .Port = Relay_cfg->port_name,
        .Pin = Relay_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = Relay_cfg->Relay_state   
        };
        
        ret_state = GPIO_Pin_Write_Logic(&Relay_CONFIG , GPIO_HIGH);
        
    }
    
    return ret_state;
    
}

Std_ReturnType Relay_Turn_OFF(const Relay_Type *Relay_cfg)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Relay_cfg)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Pin_Config_Type Relay_CONFIG = {
        .Port = Relay_cfg->port_name,
        .Pin = Relay_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = Relay_cfg->Relay_state   
        };
        
        ret_state = GPIO_Pin_Write_Logic(&Relay_CONFIG , GPIO_LOW);
        
    }
    
    return ret_state;
    
}
