/* 
 * File:   Hal_Timer0.c
 * Author: win 10-11
 *
 * Created on 03 ?????, 2024, 04:51 ?
 */

#include "Hal_Timer0.h"

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (* TIMER0Interrupt_Handler)(void) = NULL;
#endif
    
volatile uint16 _16bit_Preload_Temp_Value = 0;
volatile uint8 _8bit_Preload_Temp_Value = 0;
    
/********* Helper Function *************/
    
static inline void TIMER0_Prescaler_CONFG(const Timer0_Type* _Timer);

static inline void TIMER0_Mode_CONFG(const Timer0_Type* _Timer);
  
static inline void TIMER0_Register_CONFG(const Timer0_Type* _Timer);
/*********************************/

Std_ReturnType Timer0_Initilization(const Timer0_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Timer0 */
        TIMER0_DISABLE();
        /* Register Configuration */
        TIMER0_Register_CONFG(_Timer);
        /* Pre-scaler Configuration*/
        TIMER0_Prescaler_CONFG(_Timer);
        T0CONbits.T0PS = _Timer->Prescaler_Value;
        /* Timer0 Mode Configuration */
        TIMER0_Mode_CONFG(_Timer);
        
        
#if TIMER0_REGISTER_CONFIG == _16BIT_CONFIG
        _16bit_Preload_Temp_Value = _Timer->_16bit_Preload_Value;
        TMR0H = (uint8)(_Timer->_16bit_Preload_Value) >> 8;
        TMR0L = (uint8)(_Timer->_16bit_Preload_Value);
    
#elif TIMER0_REGISTER_CONFIG == _8BIT_CONFIG
        _8bit_Preload_Temp_Value = _Timer->_8bit_Preload_Value;
        TMR0L = (uint8)(_Timer->_8bit_Preload_Value);
#endif 
        
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            TIMER0_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            TIMER0_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        TIMER0Interrupt_Handler = _Timer->TIMER0_Interrupt_Handler;
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
#endif
        
        /* Enable Timer0 */
        TIMER0_ENABLE();
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer0_DeInitilization(const Timer0_Type* _Timer)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       /* Disable ADC Module */
        TIMER0_DISABLE();
        /* Disable ADC interrupt */
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}


#if TIMER0_REGISTER_CONFIG == _16BIT_CONFIG
Std_ReturnType Timer0_Write_16Bit_Value(const Timer0_Type* _Timer , uint16 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       TMR0H = (uint8)((_Value) >> 8);
       TMR0L = (uint8)(_Value);
       
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer0_Read_16Bit_Value(const Timer0_Type* _Timer , uint16 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint8 _16bit_timer0H = 0 , _16bit_timer0L = 0;
    if((NULL == _Timer) || (NULL == _Value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        _16bit_timer0L = TMR0L;
        _16bit_timer0H = TMR0H;
        
        *_Value = (uint16)((_16bit_timer0H << 8) + _16bit_timer0L);
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

    
#elif TIMER0_REGISTER_CONFIG == _8BIT_CONFIG
Std_ReturnType Timer0_Write_8Bit_Value(const Timer0_Type* _Timer , uint8 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       TMR0L = (uint8)(_Value); 
       ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

Std_ReturnType Timer0_Read_8Bit_Value(const Timer0_Type* _Timer , uint8 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Timer)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        *_Value = TMR0L;
        ret_state = Func_Not_OK;
    }
    
    return ret_state;
}

#endif

/****************** Helper Functions **************/
static inline void TIMER0_Prescaler_CONFG(const Timer0_Type* _Timer)
{
    if(TIMER0_PRESCALER_ENABLE_CONFG == _Timer->Prescaler_Enable)
    {
        TIMER0_PRESCALER_ENABLE();
    }
    else if (TIMER0_PRESCALER_DISABLE_CONFG == _Timer->Prescaler_Enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else { /* No Thing */}
}

static inline void TIMER0_Mode_CONFG(const Timer0_Type* _Timer)
{
    if(TIMER0_TIMER_MODE_CONFG == _Timer->Timer0_Mode)
    {
        TIMER0_TIMER_MODE();
    }
    else if (TIMER0_COUNTER_MODE_CONFG == _Timer->Timer0_Mode)
    {
        TIMER0_COUNTER_MODE();
        
        if(TIMER0_RISING_SOURCE_EDGE_CONFG == _Timer->Source_Edge)
        {
            TIMER0_RISING_SOURCE_EDGE();
            
        }else if (TIMER0_FALLING_SOURCE_EDGE_CONFG == _Timer->Source_Edge)
        {
            TIMER0_FALLING_SOURCE_EDGE();
            
        }else { /* No Thing */}
    }
    else { /* No Thing */}
}

  
static inline void TIMER0_Register_CONFG(const Timer0_Type* _Timer)
{
    if(TIMER0_16BIT_REGISTER_CONFG == _Timer->Timer0_16_8_bit_Confg)
    {
        TIMER0_16BIT_CONFG();
    }
    else if (TIMER0_8BIT_REGISTER_CONFG == _Timer->Timer0_16_8_bit_Confg)
    {
        TIMER0_8BIT_CONFG();
    }
    else { /* No Thing */}
}

/*************************************************/

/**************************************************/
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TIMER0_ISR(void)
{
    /******* Clear Flag ************/
    TIMER0_INTERRUPT_CLEAR_FLAG();
    
    /******* Code  ******/
#if TIMER0_REGISTER_CONFIG == _16BIT_CONFIG
        TMR0H = (uint8)(_16bit_Preload_Temp_Value) >> 8;
        TMR0L = (uint8)(_16bit_Preload_Temp_Value);
    
#elif TIMER0_REGISTER_CONFIG == _8BIT_CONFIG
        TMR0L = (uint8)(_8bit_Preload_Temp_Value);
#endif 
    
    /****callback function *********/
    if(TIMER0Interrupt_Handler)
    {
        TIMER0Interrupt_Handler();
    }
    
}
#else
/*void ADC_ISR(void)
{
    
}*/

#endif