/* 
 * File:   HAL_Timer2.c
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:54 ?
 */

#include "HAL_Timer2.h"
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* TIMER2Interrupt_Handler)(void);
#endif
    
volatile uint8 Timer2_Preload_Temp_Value = 0;


Std_ReturnType Timer2_Initilization(const Timer2_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Timer0 */
        TIMER2_DISABLE();
        TIMER2_PRESCALER_Value(_Timer->Prescaler_Value);
        TIMER2_POSTSCALER_Value(_Timer->Postscaler_Value);
        Timer2_Preload_Temp_Value = _Timer->Preload_Value;
        TMR2 = (uint8)(_Timer->Preload_Value);

        
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            TIMER2_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            TIMER2_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        TIMER2Interrupt_Handler = _Timer->TIMER2_Interrupt_Handler;
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
#endif
        
        /* Enable Timer0 */
        TIMER2_ENABLE();
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer2_DeInitilization(const Timer2_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       /* Disable ADC Module */
        TIMER2_DISABLE();
        /* Disable ADC interrupt */
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer2_Write_Value(const Timer2_Type* _Timer , uint8 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        TMR2 = (uint8)(_Value);
       
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer2_Read_Value(const Timer2_Type* _Timer , uint8 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 timer2_temp_value = 0;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        timer2_temp_value = TMR2;
        *_Value = timer2_temp_value;
       
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

void TIMER2_ISR(void)
{
     /******* Clear Flag ************/
    TIMER2_INTERRUPT_CLEAR_FLAG();
    
    /******* Code  ******/

    TMR2 = (uint8)(Timer2_Preload_Temp_Value);
   
    /****callback function *********/
    if(TIMER2Interrupt_Handler)
    {
        TIMER2Interrupt_Handler();
    }
    
}