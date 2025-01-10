/* 
 * File:   ECU_7_SEGMENT.c
 * Author: abdo
 *
 * Created on February 12, 2024, 10:55 AM
 */

#include "ECU_7_SEGMENT.h"

Std_ReturnType _7_Segment_Initilization(const Segment_Type* Segment)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Segment)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state =  GPIO_Pin_Initilization(&(Segment->Segment_Pins[_7_SEGMENT_PIN0]));
        ret_state =  GPIO_Pin_Initilization(&(Segment->Segment_Pins[_7_SEGMENT_PIN1]));
        ret_state =  GPIO_Pin_Initilization(&(Segment->Segment_Pins[_7_SEGMENT_PIN2]));
        ret_state =  GPIO_Pin_Initilization(&(Segment->Segment_Pins[_7_SEGMENT_PIN3]));
    }
    
    return ret_state;
}

Std_ReturnType _7_Segment_Write_Number(const Segment_Type* Segment , uint8 Number)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == Segment) || (Number > 9))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Write_Logic(&(Segment->Segment_Pins[_7_SEGMENT_PIN0]) , (Number & 0x01));
        ret_state = GPIO_Pin_Write_Logic(&(Segment->Segment_Pins[_7_SEGMENT_PIN1]) , ((Number >> 1) & 0x01));
        ret_state = GPIO_Pin_Write_Logic(&(Segment->Segment_Pins[_7_SEGMENT_PIN2]) , ((Number >> 2) & 0x01));
        ret_state = GPIO_Pin_Write_Logic(&(Segment->Segment_Pins[_7_SEGMENT_PIN3]) , ((Number >> 3) & 0x01));
    }
    
    return ret_state;
}