/* 
 * File:   GPIO_CONFIG.h
 * Author: abdo
 *
 * 
 */

#include "HAL_CCP1.h"
#include "../../Timers/TIMER1/HAL_Timer1.h"

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* CCP1Interrupt_Handler)(void) = NULL;
#endif

static Std_ReturnType Mode_Variant_Configuration(const CCP1_Type* _CCP1);   

#if ((CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT) || (CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT))
static Std_ReturnType Capture_Mode_Timer_Configuration(const CCP1_Type* _CCP1);
#endif
   
Std_ReturnType CCP1_Initilization(const CCP1_Type* _CCP1)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        CPP1_CONFG_SET(CPP1_MODULE_DISABLE);
        /** Adjust Mode variant according to mode entered  */
        ret_state = Mode_Variant_Configuration(_CCP1);
        /** Adjust Capture_Mode_Timer_Configuration  */
#if ((CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT) || (CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT))
        ret_state = Capture_Mode_Timer_Configuration(_CCP1);
#endif
        
        ret_state = GPIO_Pin_Initilization(&(_CCP1->CCP1_pin));


        
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _CCP1->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            CCP1_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _CCP1->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            CCP1_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        CCP1Interrupt_Handler = _CCP1->CPP1_Interrupt_Handler;
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
#endif
               
        
    }
    
    return ret_state;
}

Std_ReturnType CCP1_DeInitilization(const CCP1_Type* _CCP1)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       CPP1_CONFG_SET(CPP1_MODULE_DISABLE);
  
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
       CCP1_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}


#if CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType IS_CPP1_CAPTURE_MODE_READY(uint8 *Capture_Status)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Capture_Status)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CAPTURE_IS_READY == PIR1bits.CCP1IF)
        {
            *Capture_Status = CAPTURE_IS_READY;
            
        }
        else if(CAPTURE_IS_NOT_READY == PIR1bits.CCP1IF)
        {
            *Capture_Status = CAPTURE_IS_NOT_READY;
        }
        else { /* NOTHING */ }
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP1_CAPTURE_MODE_Read_Value(const CCP1_Type* _CCP1 , uint16 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    CCP1_Reg_Confg_t Temp_Value = {._8bit_reg_low_value = 0 , ._8bit_reg_high_value = 0};
    if((NULL == _CCP1) || (NULL == _Value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Temp_Value._8bit_reg_low_value = CCPR1L;
        Temp_Value._8bit_reg_high_value = CCPR1H;
        
        *_Value = Temp_Value._16bit_reg_value;
        ret_state = Func_OK;
    }
    
    return ret_state;
}

#endif
    
#if CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType IS_CPP1_COMPARE_MODE_READY(uint8 *Compare_Status)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Compare_Status)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(COMPARE_IS_READY == PIR1bits.CCP1IF)
        {
            *Compare_Status = COMPARE_IS_READY;
        }
        else if(CAPTURE_IS_NOT_READY == PIR1bits.CCP1IF)
        {
            *Compare_Status = COMPARE_IS_NOT_READY;
        }
        else { /* NOTHING */ }
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP1_COMPARE_MODE_Write_Value(const CCP1_Type* _CCP1 , uint16 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    CCP1_Reg_Confg_t Temp_Value = {._8bit_reg_low_value = 0 , ._8bit_reg_high_value = 0};
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Temp_Value._16bit_reg_value = (uint16)_Value;
        
        CCPR1L = Temp_Value._8bit_reg_low_value;
        CCPR1H = Temp_Value._8bit_reg_high_value;
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

#endif

#if CPP1_PWM_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType CCP1_PWM_Duty_Cycle(const CCP1_Type* _CCP1 , uint8 duty_cycle)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint16 Temp_Value = 0;
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
      
        Temp_Value = (uint16)((PR2 + 1) * (duty_cycle / 100.0) * 4);
        
        CCP1CONbits.DC1B = (uint8)(Temp_Value & 0x03);
        CCPR1L = (uint8)(Temp_Value >> 2);
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP1_PWM_MODE_START(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
    CPP1_CONFG_SET(CPP1_PWM_MODE_ENABLE);
    ret_state = Func_OK;
 
    return ret_state;

}

Std_ReturnType CPP1_PWM_MODE_STOP(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
    CPP1_CONFG_SET(CPP1_MODULE_DISABLE);
    ret_state = Func_OK;
 
    return ret_state;
}

#endif





void CCP1_ISR(void)
{
    CCP1_INTERRUPT_CLEAR_FLAG();
    
    if(CCP1Interrupt_Handler)
    {
        CCP1Interrupt_Handler();
    }
}

static Std_ReturnType Mode_Variant_Configuration(const CCP1_Type* _CCP1)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CPP1_CAPTURE_MODE == _CCP1->CCP1_Mode)
            {
                switch(_CCP1->CCP1_Mode_Variant)
                {
                    case CPP1_Capture_MODE_EVERY_FALLING_EDGE:
                    {
                        CPP1_CONFG_SET(CPP1_Capture_MODE_EVERY_FALLING_EDGE);
                    }
                    break;

                    case CPP1_Capture_MODE_EVERY_1TH_RISING_EDGE:
                    {
                        CPP1_CONFG_SET(CPP1_Capture_MODE_EVERY_1TH_RISING_EDGE);
                    }
                    break;

                    case CPP1_Capture_MODE_EVERY_4TH_RISING_EDGE:
                    {
                        CPP1_CONFG_SET(CPP1_Capture_MODE_EVERY_4TH_RISING_EDGE);
                    }
                    break;

                    case CPP1_Capture_MODE_EVERY_16TH_RISING_EDGE:
                    {
                        CPP1_CONFG_SET(CPP1_Capture_MODE_EVERY_16TH_RISING_EDGE);
                    }
                    break;

                    default : ret_state = Func_Not_OK;
                }
            }
            else if(CPP1_COMPARE_MODE == _CCP1->CCP1_Mode)
            {
                switch(_CCP1->CCP1_Mode_Variant)
                {
                    case CPP1_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH:
                    {
                        CPP1_CONFG_SET(CPP1_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH);
                    }
                    break;

                    case CPP1_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH:
                    {
                        CPP1_CONFG_SET(CPP1_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH);
                    }
                    break;

                    case CPP1_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH:
                    {
                        CPP1_CONFG_SET(CPP1_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH);
                    }
                    break;

                    case CPP1_Compare_MODE_SOFT_INTERRUPT_ON_MATCH:
                    {
                        CPP1_CONFG_SET(CPP1_Compare_MODE_SOFT_INTERRUPT_ON_MATCH);
                    }
                    break;

                    case CPP1_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH:
                    {
                        CPP1_CONFG_SET(CPP1_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH);
                    }
                    break;

                    default : ret_state = Func_Not_OK;
                }
            }
            else if(CPP1_PWM_MODE == _CCP1->CCP1_Mode)
            {
#if CPP1_PWM_MODE_SELECTED == CPP1_MODE_SELECT
                PR2 = (uint8)((_XTAL_FREQ) / (_CCP1->PWM_Frequency * 4 * _CCP1->Timer2_Postscaler_Value * _CCP1->Timer2_Prescaler_Value)) - 1;
#endif            
            }
        else { /* NOTHING */}
    }
    
    return ret_state;

}

#if ((CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT) || (CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT))
static Std_ReturnType Capture_Mode_Timer_Configuration(const CCP1_Type* _CCP1)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP1)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CCP1_TMR1_TWO_CCP_MODULES == _CCP1->Timer_Confg)
        {
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP1_TMR3_CCP2_TMR1_CCP1 == _CCP1->Timer_Confg)
        {
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP1_TMR3_TWO_CCP_MODULES == _CCP1->Timer_Confg)
        {
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 1;
        }
        else { /* NOTHING */}
        
        ret_state = Func_OK;
    
    }
    
    return ret_state;
}
#endif 