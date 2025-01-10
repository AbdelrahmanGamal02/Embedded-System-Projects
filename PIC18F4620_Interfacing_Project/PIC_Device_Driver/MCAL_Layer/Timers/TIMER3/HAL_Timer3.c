/* 
 * File:   HAL_Timer3.c
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:55 ?
 */

#include "HAL_Timer3.h"


#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* TIMER3Interrupt_Handler)(void) = NULL;
#endif
    
volatile uint16 Timer3_Preload_Temp_Value = 0;

static inline void TIMER3_Mode_CONFG(const Timer3_Type* _Timer);
static inline void TIMER3_Register_CONFG(const Timer3_Type* _Timer);

Std_ReturnType Timer3_Initilization(const Timer3_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Timer0 */
        TIMER3_DISABLE();
        TIMER3_PRESCALER_Value(_Timer->Prescaler_Value);
        TIMER3_Mode_CONFG(_Timer);
        TIMER3_Register_CONFG(_Timer);
        Timer3_Preload_Temp_Value = _Timer->Preload_Value;
        TMR3H = (uint8)(_Timer->Preload_Value) >> 8;
        TMR3L = (uint8)(_Timer->Preload_Value);

        
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            TIMER3_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            TIMER3_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        TIMER3Interrupt_Handler = _Timer->TIMER3_Interrupt_Handler;
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
#endif
        
        /* Enable Timer0 */
        TIMER3_ENABLE();
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer3_DeInitilization(const Timer3_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       /* Disable ADC Module */
        TIMER3_DISABLE();
        /* Disable ADC interrupt */
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer3_Write_Value(const Timer3_Type* _Timer , uint16 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       TMR3H = (uint8)((_Value) >> 8);
       TMR3L = (uint8)(_Value);
       
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer3_Read_Value(const Timer3_Type* _Timer , uint16 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 _16bit_timer3H = 0 , _16bit_timer3L = 0;
    if((NULL == _Timer) || (NULL == _Value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        _16bit_timer3L = TMR3L;
        _16bit_timer3H = TMR3H;
        
        *_Value = (uint16)((_16bit_timer3H << 8) + _16bit_timer3L);
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

static inline void TIMER3_Mode_CONFG(const Timer3_Type* _Timer)
{
    if(TIMER3_TIMER_MODE_CONFG == _Timer->Timer3_Mode)
    {
        TIMER3_TIMER_MODE();
    }
    else if (TIMER3_COUNTER_MODE_CONFG == _Timer->Timer3_Mode)
    {
        TIMER3_COUNTER_MODE();
        
        if(TIMER3_COUNTER_SYNC_MODE_CONFG == _Timer->Timer3_counter_sync_Mode)
        {
            TIMER3_COUNTER_SYNC_MODE();
            
        }else if (TIMER3_COUNTER_ASYNC_MODE_CONFG == _Timer->Timer3_counter_sync_Mode)
        {
            TIMER3_COUNTER_ASYNC_MODE();
            
        }else { /* No Thing */}
    }
    else { /* No Thing */}
}

static inline void TIMER3_Register_CONFG(const Timer3_Type* _Timer)
{
    if(TIMER3_16BIT_REGISTER_CONFG == _Timer->Timer3_16_8_bit_Confg)
    {
        TIMER3_16BIT_CONFG();
    }
    else if (TIMER3_8BIT_REGISTER_CONFG == _Timer->Timer3_16_8_bit_Confg)
    {
        TIMER3_8BIT_CONFG();
    }
    else { /* No Thing */}
}

void TIMER3_ISR(void)
{
     /******* Clear Flag ************/
    TIMER3_INTERRUPT_CLEAR_FLAG();
    
    /******* Code  ******/

    TMR3H = (uint8)(Timer3_Preload_Temp_Value) >> 8;
    TMR3L = (uint8)(Timer3_Preload_Temp_Value);
   
    /****callback function *********/
    if(TIMER3Interrupt_Handler)
    {
        TIMER3Interrupt_Handler();
    }
    
}