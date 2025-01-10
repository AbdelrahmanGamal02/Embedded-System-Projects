
/* 
 * File:   ECUAL_LED.h
 * Author: abdo
 *
 * Created on September 19, 2023, 5:04 PM
 */

/*****************Include Section****************/
#include "ECUAL_LED.h"

/************************************************/


/************* Function Definition **************/
/**
 * @breif use to initialize Led ( its port number, its initial logic, and its pin number in the port)
 * @param LED_cfg pointer point to structure represent data of Led ( @ref LED_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if  LED_CONVEGRATIONS == INTERFACES_ENABLES
Std_ReturnType Led_Initialization(const LED_Type *LED_cfg)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(NULL == LED_cfg)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        Pin_Config_Type LED_CONFIG = {
        .Port = LED_cfg->port_name,
        .Pin = LED_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = LED_cfg->init_state
                
        };
        
        
        Ret_state = GPIO_Pin_Initilization(&LED_CONFIG);
    
    }
    
    return Ret_state;
}
#endif

/**
 * @breif Turn on the Led (Write logic 1 on the Led) 
 * @param LED_cfg pointer point to structure represent data of Led ( @ref LED_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if  LED_CONVEGRATIONS == INTERFACES_ENABLES
Std_ReturnType Led_Turn_ON(const LED_Type *LED_cfg)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(NULL == LED_cfg)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        Pin_Config_Type LED_CONFIG = {
        .Port = LED_cfg->port_name,
        .Pin = LED_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = LED_cfg->init_state
                
        };
        
        Ret_state = GPIO_Pin_Write_Logic(&LED_CONFIG , GPIO_HIGH);
    
    }
    
    return Ret_state;
}
#endif

/**
 * @breif Turn off the Led (Write logic 0 on the Led) 
 * @param LED_cfg pointer point to structure represent data of Led ( @ref LED_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if  LED_CONVEGRATIONS == INTERFACES_ENABLES
Std_ReturnType Led_Turn_OFF(const LED_Type *LED_cfg)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(NULL == LED_cfg)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        Pin_Config_Type LED_CONFIG = {
        .Port = LED_cfg->port_name,
        .Pin = LED_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = LED_cfg->init_state
                
        };
        
        Ret_state = GPIO_Pin_Write_Logic(&LED_CONFIG , GPIO_LOW);
    
    }
    
    return Ret_state;
}
#endif

/**
 * @brief Toggle the Led ( 1 become 0 and 0 become 1)
 * @param LED_cfg pointer point to structure represent data of Led ( @ref LED_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if  LED_CONVEGRATIONS == INTERFACES_ENABLES
Std_ReturnType Led_Turn_TOGGLE(const LED_Type *LED_cfg)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(NULL == LED_cfg)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        Pin_Config_Type LED_CONFIG = {
        .Port = LED_cfg->port_name,
        .Pin = LED_cfg->pin_number,
        .Direction = GPIO_DIRECTION_OUTPUT,
        .Logic = LED_cfg->init_state
                
        };
        
        Ret_state = GPIO_Pin_Toggle_Pin(&LED_CONFIG);
    
    }
    
    return Ret_state;
}
#endif
/************************************************/