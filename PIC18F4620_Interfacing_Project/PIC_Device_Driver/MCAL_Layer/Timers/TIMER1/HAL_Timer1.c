/* 
 * File:   HAL_Timer1.c
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:52 ?
 */

#include "HAL_Timer1.h"

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* TIMER1Interrupt_Handler)(void);
#endif
    
volatile uint16 Timer1_Preload_Temp_Value = 0;

static inline void TIMER1_Mode_CONFG(const Timer1_Type* _Timer);
static inline void TIMER1_OSC_CONFG(const Timer1_Type* _Timer);
static inline void TIMER1_Register_CONFG(const Timer1_Type* _Timer);

Std_ReturnType Timer1_Initilization(const Timer1_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Timer0 */
        TIMER1_DISABLE();
        TIMER1_PRESCALER_Value(_Timer->Prescaler_Value);
        TIMER1_Mode_CONFG(_Timer);
        TIMER1_OSC_CONFG(_Timer);
        TIMER1_Register_CONFG(_Timer);
        Timer1_Preload_Temp_Value = _Timer->Preload_Value;
        TMR1H = (uint8)(_Timer->Preload_Value) >> 8;
        TMR1L = (uint8)(_Timer->Preload_Value);

        
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            TIMER1_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            TIMER1_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        TIMER1Interrupt_Handler = _Timer->TIMER1_Interrupt_Handler;
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
#endif
        
        /* Enable Timer0 */
        TIMER1_ENABLE();
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer1_DeInitilization(const Timer1_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       /* Disable ADC Module */
        TIMER1_DISABLE();
        /* Disable ADC interrupt */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer1_Write_Value(const Timer1_Type* _Timer , uint16 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       TMR1H = (uint8)((_Value) >> 8);
       TMR1L = (uint8)(_Value);
       
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer1_Read_Value(const Timer1_Type* _Timer , uint16 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 _16bit_timer1H = 0 , _16bit_timer1L = 0;
    if((NULL == _Timer) || (NULL == _Value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        _16bit_timer1L = TMR1L;
        _16bit_timer1H = TMR1H;
        
        *_Value = (uint16)((_16bit_timer1H << 8) + _16bit_timer1L);
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

static inline void TIMER1_Mode_CONFG(const Timer1_Type* _Timer)
{
    if(TIMER1_TIMER_MODE_CONFG == _Timer->Timer1_Mode)
    {
        TIMER1_TIMER_MODE();
    }
    else if (TIMER1_COUNTER_MODE_CONFG == _Timer->Timer1_Mode)
    {
        TIMER1_COUNTER_MODE();
        
        if(TIMER1_COUNTER_SYNC_MODE_CONFG == _Timer->Timer1_counter_sync_Mode)
        {
            TIMER1_COUNTER_SYNC_MODE();
            
        }else if (TIMER1_COUNTER_ASYNC_MODE_CONFG == _Timer->Timer1_counter_sync_Mode)
        {
            TIMER1_COUNTER_ASYNC_MODE();
            
        }else { /* No Thing */}
    }
    else { /* No Thing */}
}

static inline void TIMER1_OSC_CONFG(const Timer1_Type* _Timer)
{
    if(TIMER1_OSC_DISABLE_CONFG == _Timer->Timer1_OSC_Confg)
    {
        TIMER1_OSC_CONFG_DISABLE();
    }
    else if (TIMER1_OSC_ENABLE_CONFG == _Timer->Timer1_OSC_Confg)
    {
        TIMER1_OSC_CONFG_ENABLE();
    }
    else { /* No Thing */}
}
static inline void TIMER1_Register_CONFG(const Timer1_Type* _Timer)
{
    if(TIMER1_16BIT_REGISTER_CONFG == _Timer->Timer1_16_8_bit_Confg)
    {
        TIMER1_16BIT_CONFG();
    }
    else if (TIMER1_8BIT_REGISTER_CONFG == _Timer->Timer1_16_8_bit_Confg)
    {
        TIMER1_8BIT_CONFG();
    }
    else { /* No Thing */}
}
void TIMER1_ISR(void)
{
     /******* Clear Flag ************/
    TIMER1_INTERRUPT_CLEAR_FLAG();
    
    /******* Code  ******/

    TMR1H = (uint8)(Timer1_Preload_Temp_Value) >> 8;
    TMR1L = (uint8)(Timer1_Preload_Temp_Value);
   
    /****callback function *********/
    if(TIMER1Interrupt_Handler)
    {
        TIMER1Interrupt_Handler();
    }
    
}