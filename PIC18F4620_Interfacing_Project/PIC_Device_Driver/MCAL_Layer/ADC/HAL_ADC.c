/* 
 * File:   HAL_ADC.c
 * Author: abdo
 *
 * Created on May 4, 2024, 11:32 AM
 */

#include "HAL_ADC.h"



/********* Helper Function *************/

void (* ADCInterrupt_Handler)(void) = NULL;

static void Channal_pin_Initilization(ADC_Channel_Select_Type channel);
static Std_ReturnType ADC_VOLATAGE_REFERENCE_Control(const ADC_Configeration_type* _adc);
static Std_ReturnType ADC_Result_Format_Control(const ADC_Configeration_type* _adc);
/*****************************************/
/****************************** Function Definition  *******************/

Std_ReturnType ADC_Initilization(const ADC_Configeration_type* _adc)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable ADC Module */
        ADC_CONVERTER_DISABLE();
        /* Select ADC Conversion clock */
        ADC_Conversion_Clock_CONTROL(_adc->Conversion_Clock);
        /* configure ADC voltage reference */
        ret_state =  ADC_VOLATAGE_REFERENCE_Control(_adc);
        /* Select ADC input Channel */
        ADC_Select_Chanal_CONTROL(_adc->channel);
        Channal_pin_Initilization(_adc->channel);
        /* Select ADC result format */
        ret_state &= ADC_Result_Format_Control(_adc);
        /* Select ADC acquisition time */
        ADC_Acquisition_Time_CONTROL(_adc->acquisition_time);
        /* configure ADC interrupt */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _adc->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            ADC_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _adc->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            ADC_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        ADCInterrupt_Handler = _adc->ADC_Interrupt_Handler;
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_Clear_FLAG();
#endif
        
        
        /* Enable ADC Module */
        ADC_CONVERTER_ENABLE();
        
    }
    
    return ret_state;
}

Std_ReturnType ADC_DeInitilization(const ADC_Configeration_type* _adc)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable ADC Module */
        ADC_CONVERTER_DISABLE();
        /* Disable ADC interrupt */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
#endif
    }
    
    return ret_state;
}

Std_ReturnType ADC_Select_Channel(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ADC_Select_Chanal_CONTROL(channel);
        Channal_pin_Initilization(channel);
    }
    
    return ret_state;
}

Std_ReturnType ADC_Start_Conversion(const ADC_Configeration_type* _adc)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ADC_START_CONVERSION(); 
    }
    
    return ret_state;
}

Std_ReturnType ADC_Is_Conversion_Done(const ADC_Configeration_type* _adc , uint8 *Conversion_state)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == _adc) || (NULL == Conversion_state))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        *Conversion_state = ADC_GET_CONVERSION_STATUS();
    }
    
    return ret_state;
}

Std_ReturnType ADC_Get_Conversion_Result(const ADC_Configeration_type* _adc , uint16 *Conversion_result)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == _adc) || (NULL == Conversion_result))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT_FORMAT == _adc->result_format)
        {
            *Conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT_FORMAT == _adc->result_format)
        {
            *Conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            /** Default ADC Result_Format */
            *Conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    
    return ret_state;
}

Std_ReturnType ADC_Get_Conversion_Blocking(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel,
                                           uint16 *Conversion_result)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == _adc) || (NULL == Conversion_result))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Select ADC input Channel */
        ret_state = ADC_Select_Channel(_adc , channel);
        /** Start conversion  */
        ret_state &= ADC_Start_Conversion(_adc);
        /* blocking while conversion completed */
        while(ADC_GET_CONVERSION_STATUS());
        /* Get conversion value */
        ret_state &= ADC_Get_Conversion_Result(_adc , Conversion_result);
    }
    
    return ret_state;
}

Std_ReturnType ADC_Conversion_Interrupt(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Select ADC input Channel */
        ret_state = ADC_Select_Channel(_adc , channel);
        /** Start conversion  */
        ret_state &= ADC_Start_Conversion(_adc);
       
    }
    
    return ret_state;
}

/**********************************************************************/

/****************** Helper Function Definition ************************/
static void Channal_pin_Initilization(ADC_Channel_Select_Type channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0:  { SET_BIT(TRISA , _TRISA_RA0_POSN); break;}
        case ADC_CHANNEL_AN1:  { SET_BIT(TRISA , _TRISA_RA1_POSN); break;}
        case ADC_CHANNEL_AN2:  { SET_BIT(TRISA , _TRISA_RA2_POSN); break;}
        case ADC_CHANNEL_AN3:  { SET_BIT(TRISA , _TRISA_RA3_POSN); break;}
        case ADC_CHANNEL_AN4:  { SET_BIT(TRISA , _TRISA_RA5_POSN); break;}
        case ADC_CHANNEL_AN5:  { SET_BIT(TRISE , _TRISE_RE0_POSN); break;}
        case ADC_CHANNEL_AN6:  { SET_BIT(TRISE , _TRISE_RE1_POSN); break;}
        case ADC_CHANNEL_AN7:  { SET_BIT(TRISE , _TRISE_RE2_POSN); break;}
        case ADC_CHANNEL_AN8:  { SET_BIT(TRISB , _TRISB_RB2_POSN); break;}
        case ADC_CHANNEL_AN9:  { SET_BIT(TRISB , _TRISB_RB3_POSN); break;}
        case ADC_CHANNEL_AN10: { SET_BIT(TRISB , _TRISB_RB1_POSN); break;}
        case ADC_CHANNEL_AN11: { SET_BIT(TRISB , _TRISB_RB4_POSN); break;}
        case ADC_CHANNEL_AN12: { SET_BIT(TRISB , _TRISB_RB0_POSN); break;} 
    }
}

static Std_ReturnType ADC_VOLATAGE_REFERENCE_Control(const ADC_Configeration_type* _adc)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(ADC_Vdd_Vss_VOLATAGE_REFERENCE == _adc->voltage_referance)
        {
            VOLATAGE_REFERENCE_Vdd_Vss_Enable();
        }
        else if(ADC_CUSTOM_VOLATAGE_REFERENCE == _adc->voltage_referance)
        {
            CUSTOM_VOLATAGE_REFERENCE_Enable();
        }
        else
        {
            /** Default ADC voltage reference */
            VOLATAGE_REFERENCE_Vdd_Vss_Enable();
        }
    }
    
    return ret_state;
}

static Std_ReturnType ADC_Result_Format_Control(const ADC_Configeration_type* _adc)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _adc)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT_FORMAT == _adc->result_format)
        {
            ADC_RESULT_RIGHT_FORMAT_CONTROL();
        }
        else if(ADC_RESULT_LEFT_FORMAT == _adc->result_format)
        {
            ADC_RESULT_LEFT_FORMAT_CONTROL();
        }
        else
        {
            /** Default ADC Result_Format */
            ADC_RESULT_RIGHT_FORMAT_CONTROL();
        }
    }
    
    return ret_state;
}
/**********************************************************************/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void)
{
    /******* Clear Flag ************/
    ADC_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(ADCInterrupt_Handler)
    {
        ADCInterrupt_Handler();
    }
    
}
#else
void ADC_ISR(void)
{
    
}

#endif
