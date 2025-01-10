/* 
 * File:   GPIO_CONFIG.h
 * Author: abdo
 *
 * 
 */

#include "HAL_CCP2.h"

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* CCP2Interrupt_Handler)(void) = NULL;
#endif

static Std_ReturnType Mode_Variant_Configuration(const CCP2_Type* _CCP2);   

#if ((CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT) || (CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT))
static Std_ReturnType Capture_Mode_Timer_Configuration(const CCP2_Type* _CCP2);
#endif
   
Std_ReturnType CCP2_Initilization(const CCP2_Type* _CCP2)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        CPP2_CONFG_SET(CPP2_MODULE_DISABLE);
        /** Adjust Mode variant according to mode entered  */
        ret_state = Mode_Variant_Configuration(_CCP2);
        /** Adjust Capture_Mode_Timer_Configuration  */
#if ((CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT) || (CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT))
        ret_state = Capture_Mode_Timer_Configuration(_CCP2);
#endif
        
        ret_state = GPIO_Pin_Initilization(&(_CCP2->CCP2_pin));


        
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _CCP2->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            CCP2_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _CCP2->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            CCP2_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        CCP2Interrupt_Handler = _CCP2->CPP2_Interrupt_Handler;
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
#endif
               
        
    }
    
    return ret_state;
}

Std_ReturnType CCP2_DeInitilization(const CCP2_Type* _CCP2)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
       CPP2_CONFG_SET(CPP2_MODULE_DISABLE);
  
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
       CCP2_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}


#if CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType IS_CPP2_CAPTURE_MODE_READY(uint8 *Capture_Status)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Capture_Status)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CAPTURE_IS_READY == PIR2bits.CCP2IF)
        {
            *Capture_Status = CAPTURE_IS_READY;
        }
        else if(CAPTURE_IS_NOT_READY == PIR2bits.CCP2IF)
        {
            *Capture_Status = CAPTURE_IS_NOT_READY;
        }
        else { /* NOTHING */ }
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP2_CAPTURE_MODE_Read_Value(const CCP2_Type* _CCP2 , uint16 *_Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    CCP2_Reg_Confg_t Temp_Value = {._8bit_reg_low_value = 0 , ._8bit_reg_high_value = 0};
    if((NULL == _CCP2) || (NULL == _Value))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Temp_Value._8bit_reg_low_value = CCPR2L;
        Temp_Value._8bit_reg_high_value = CCPR2H;
        
        *_Value = Temp_Value._16bit_reg_value;
        ret_state = Func_OK;
    }
    
    return ret_state;
}

#endif
    
#if CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType IS_CPP2_COMPARE_MODE_READY(uint8 *Compare_Status)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Compare_Status)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(COMPARE_IS_READY == PIR2bits.CCP2IF)
        {
            *Compare_Status = COMPARE_IS_READY;
        }
        else if(CAPTURE_IS_NOT_READY == PIR2bits.CCP2IF)
        {
            *Compare_Status = COMPARE_IS_NOT_READY;
        }
        else { /* NOTHING */ }
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP2_COMPARE_MODE_Write_Value(const CCP2_Type* _CCP2 , uint16 _Value)
{
    Std_ReturnType ret_state = Func_Not_OK;
    CCP2_Reg_Confg_t Temp_Value = {._8bit_reg_low_value = 0 , ._8bit_reg_high_value = 0};
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Temp_Value._16bit_reg_value = (uint16)_Value;
        
        CCPR2L = Temp_Value._8bit_reg_low_value;
        CCPR2H = Temp_Value._8bit_reg_high_value;
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

#endif

#if CPP2_PWM_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType CCP2_PWM_Duty_Cycle(const CCP2_Type* _CCP2 , uint8 duty_cycle)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint16 Temp_Value = 0;
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
      
        Temp_Value = (uint16)((PR2 + 1) * (duty_cycle / 100.0) * 4);
        
        CCP2CONbits.DC2B = (uint8)(Temp_Value & 0x03);
        CCPR2L = (uint8)(Temp_Value >> 2);
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType CPP2_PWM_MODE_START(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
    CPP2_CONFG_SET(CPP2_PWM_MODE_ENABLE);
    ret_state = Func_OK;
 
    return ret_state;

}

Std_ReturnType CPP2_PWM_MODE_STOP(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
    CPP2_CONFG_SET(CPP2_MODULE_DISABLE);
    ret_state = Func_OK;
 
    return ret_state;
}

#endif


void CCP2_ISR(void)
{
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2Interrupt_Handler)
    {
        CCP2Interrupt_Handler();
    }
}

static Std_ReturnType Mode_Variant_Configuration(const CCP2_Type* _CCP2)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CPP2_CAPTURE_MODE == _CCP2->CCP2_Mode)
            {
                switch(_CCP2->CCP2_Mode_Variant)
                {
                    case CPP2_Capture_MODE_EVERY_FALLING_EDGE:
                    {
                        CPP2_CONFG_SET(CPP2_Capture_MODE_EVERY_FALLING_EDGE);
                    }
                    break;

                    case CPP2_Capture_MODE_EVERY_1TH_RISING_EDGE:
                    {
                        CPP2_CONFG_SET(CPP2_Capture_MODE_EVERY_1TH_RISING_EDGE);
                    }
                    break;

                    case CPP2_Capture_MODE_EVERY_4TH_RISING_EDGE:
                    {
                        CPP2_CONFG_SET(CPP2_Capture_MODE_EVERY_4TH_RISING_EDGE);
                    }
                    break;

                    case CPP2_Capture_MODE_EVERY_16TH_RISING_EDGE:
                    {
                        CPP2_CONFG_SET(CPP2_Capture_MODE_EVERY_16TH_RISING_EDGE);
                    }
                    break;

                    default : ret_state = Func_Not_OK;
                }
            }
            else if(CPP2_COMPARE_MODE == _CCP2->CCP2_Mode)
            {
                switch(_CCP2->CCP2_Mode_Variant)
                {
                    case CPP2_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH:
                    {
                        CPP2_CONFG_SET(CPP2_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH);
                    }
                    break;

                    case CPP2_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH:
                    {
                        CPP2_CONFG_SET(CPP2_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH);
                    }
                    break;

                    case CPP2_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH:
                    {
                        CPP2_CONFG_SET(CPP2_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH);
                    }
                    break;

                    case CPP2_Compare_MODE_SOFT_INTERRUPT_ON_MATCH:
                    {
                        CPP2_CONFG_SET(CPP2_Compare_MODE_SOFT_INTERRUPT_ON_MATCH);
                    }
                    break;

                    case CPP2_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH:
                    {
                        CPP2_CONFG_SET(CPP2_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH);
                    }
                    break;

                    default : ret_state = Func_Not_OK;
                }
            }
            else if(CPP2_PWM_MODE == _CCP2->CCP2_Mode)
            {
#if CPP2_PWM_MODE_SELECTED == CPP2_MODE_SELECT
                PR2 = (uint8)((_XTAL_FREQ) / (_CCP2->PWM_Frequency * 4 * _CCP2->Timer2_Postscaler_Value * _CCP2->Timer2_Prescaler_Value)) - 1;
#endif            
            }
        else { /* NOTHING */}
    }
    
    return ret_state;

}

#if ((CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT) || (CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT))
static Std_ReturnType Capture_Mode_Timer_Configuration(const CCP2_Type* _CCP2)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _CCP2)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(CCP2_TMR1_TWO_CCP_MODULES == _CCP2->Timer_Confg)
        {
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP2_TMR3_CCP2_TMR1_CCP1 == _CCP2->Timer_Confg)
        {
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP2_TMR3_TWO_CCP_MODULES == _CCP2->Timer_Confg)
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
