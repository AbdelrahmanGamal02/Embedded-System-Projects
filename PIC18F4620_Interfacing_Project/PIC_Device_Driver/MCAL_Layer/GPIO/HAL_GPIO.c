
/* 
 * File:   HAL_GPIO.c
 * Author: abdo
 *
 * Created on September 19, 2023, 4:58 PM
 */

#include "HAL_GPIO.h"


/*************** Helper Functions *****************/
/**
 * @brief use to initialize direction of specific pin
 * @param Pin_Config pointer point to structure represent data of pin ( @ref Pin_Config_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */
Std_ReturnType GPIO_Pin_Direction_Initilization(const Pin_Config_Type* Pin_Config)
{
    Std_ReturnType State = Func_OK;
    if( NULL == Pin_Config || Pin_Config->Pin > Max_Number_Of_Pins - 1){
        State = Func_Not_OK;
    }else
    {
        switch(Pin_Config->Direction)
        {
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*Tris_Registers[Pin_Config->Port] , Pin_Config->Pin);
                break;
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*Tris_Registers[Pin_Config->Port] , Pin_Config->Pin);
                break;
            default : State = Func_Not_OK;
        }
        State = Func_OK;
    }
    
    return State;
}
/**************************************************/
/*************** Function Definitions *************/

/**
 * @brief use to initialize pin ( it's direction and it's startup logic  )
 * @param Pin_Config pointer point to structure represent data of pin ( @ref Pin_Config_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

 // condition to save your interfacing configrations
#if PIN_CONVEGRATIONS==INTERFACES_ENABLES   
Std_ReturnType GPIO_Pin_Initilization(const Pin_Config_Type* Pin_Config)
{
    Std_ReturnType State = Func_OK;
    if( NULL == Pin_Config || Pin_Config->Pin > Max_Number_Of_Pins - 1){
        State = Func_Not_OK;
    }else
    {
        State = GPIO_Pin_Direction_Initilization(Pin_Config);
        State = GPIO_Pin_Write_Logic(Pin_Config, Pin_Config->Logic);
    }
    
    return State;
}
#endif

/**
 * @breif use to write a logic ( 1 or 0 ( 5v or 0v )) on a specific pin
 * @param Pin_Config pointer point to structure represent data of pin ( @ref Pin_Config_Type )
 * @param Logic logic will be written on the pin ( 0 or 1)
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */
#if PIN_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Pin_Write_Logic(const Pin_Config_Type* Pin_Config , Logic_Type Logic)
{
    Std_ReturnType State = Func_OK;
    if( (NULL == Pin_Config) || (Pin_Config->Pin > Max_Number_Of_Pins - 1)){
        State = Func_Not_OK;
    }else
    {
        switch(Logic)
        {
            case GPIO_LOW :
                CLEAR_BIT(*Lat_Registers[Pin_Config->Port] , Pin_Config->Pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*Lat_Registers[Pin_Config->Port] , Pin_Config->Pin);
                break;
            default : State = Func_Not_OK;    
        }
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @breif use to read a logic on a specific pin
 * @param Pin_Config pointer point to structure represent data of pin ( @ref Pin_Config_Type )
 * @param Ret_Logic pointer point on Logic_Type to store logic on pin
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PIN_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Pin_Read_Logic(const Pin_Config_Type* Pin_Config , Logic_Type* Ret_Logic)
{
    Std_ReturnType State = Func_OK;
    if( NULL == Pin_Config || Pin_Config->Pin > Max_Number_Of_Pins - 1 || NULL == Ret_Logic){
        State = Func_Not_OK;
    }else
    {
        *Ret_Logic = READ_BIT(*Port_Registers[Pin_Config->Port] , Pin_Config->Pin);
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @breif use to toggle a logic of a specific pin ( 1 become 0 and 0 become 1)
 * @param Pin_Config pointer point to structure represent data of pin ( @ref Pin_Config_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PIN_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Pin_Toggle_Pin(const Pin_Config_Type* Pin_Config)
{
    Std_ReturnType State = Func_OK;
    if( NULL == Pin_Config || Pin_Config->Pin > Max_Number_Of_Pins - 1){
        State = Func_Not_OK;
    }else
    {
        TOGGLE_BIT(*Lat_Registers[Pin_Config->Port] , Pin_Config->Pin);
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @brief use to initialize the direction on specific port (All pins)
 * @param Port the index of specific port ( @ref Port_Index_Type )
 * @param Direction Direction will be written on the pin ( output( 0 ) or input ( 1 ) )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PORT_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Port_Direction_Initilization(Port_Index_Type Port , uint8 Direction)
{
    Std_ReturnType State = Func_OK;
    if( Port > Max_Number_Of_Ports - 1){
        State = Func_Not_OK;
    }else
    {
        *Tris_Registers[Port] = Direction;
        State = Func_OK;
    }
    
    return State;

}
#endif

/**
 * @breif use to Know  the direction on specific port (All pins)
 * @param Port the index of specific port ( @ref Port_Index_Type )
 * @param Direction pointer point on Direction_Type to store direction of port
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PORT_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Port_Get_Direction_Status(Port_Index_Type Port , uint8* Direction)
{
    Std_ReturnType State = Func_OK;
    if( Port > Max_Number_Of_Ports - 1 || NULL == Direction){
        State = Func_Not_OK;
    }else
    {
        *Direction = *Tris_Registers[Port];
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @breif use to write a logic ( 1 or 0 ( 5v or 0v )) on a specific port
 * @param Port the index of specific port ( @ref Port_Index_Type )
 * @param Logic logic will be written on the port ( 0 or 1)
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PORT_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Port_Write_Logic(Port_Index_Type Port , uint8 Logic)
{
    Std_ReturnType State = Func_OK;
    if( Port > Max_Number_Of_Ports - 1){
        State = Func_Not_OK;
    }else
    {
        *Lat_Registers[Port] = Logic;
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @breif use to read a logic on a specific port
 * @param Port the index of specific port ( @ref Port_Index_Type )
 * @param Logic pointer point on Logic_Type to store logic on port
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function 
 */

#if PORT_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Port_Read_Logic(Port_Index_Type Port , uint8* Logic)
{
    Std_ReturnType State = Func_OK;
    if( Port > Max_Number_Of_Ports - 1 || NULL == Logic){
        State = Func_Not_OK;
    }else
    {
        *Logic = *Port_Registers[Port];
        State = Func_OK;
    }
    
    return State;
}
#endif

/**
 * @breif use to toggle a logic of a specific port ( 1 become 0 and 0 become 1)
 * @param Port the index of specific port ( @ref Port_Index_Type )
 * @return Std_ReturnType return state of function 
 *    (Func_OK) if function does it's operation correctly
 *    (Func_Not_OK)  if there is issue in the function  
 */

#if PORT_CONVEGRATIONS==INTERFACES_ENABLES
Std_ReturnType GPIO_Port_Toggle(Port_Index_Type Port)
{
    Std_ReturnType State = Func_OK;
    if(Port > Max_Number_Of_Ports - 1){
        State = Func_Not_OK;
    }else
    {
        *Lat_Registers[Port] ^= 0xff; 
        /* let LAT Register contain  0b01010101 
                             0xFF  = 0b11111111
         * if LAT register ^ 0xFF 
         *                  result = 0b10101010
         * 
         * result is the toggle number of LAT register
         */
        State = Func_OK;
    }
    
    return State;
}
#endif
/**************************************************/




