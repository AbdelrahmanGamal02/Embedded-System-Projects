/* 
 * File:   HAL_SPI.h
 * Author: win 10-11
 *
 * Created on 31 ?????, 2024, 02:23 ?
 */

#include "HAL_SPI.h"

#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* MSSP_SPIInterrupt_Handler)(void);
#endif

Std_ReturnType MSSP_SPI_Initilization(const MSSP_SPI_Type* _SPI)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _SPI)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Module */
        MSSP_SPI_MODULE_DISABLE();
        /* Configure Mode of Module */
        MSSP_SPI_MODE(_SPI->SPI_Mode_confg);
        if(MSSP_SPI_MASTER_MODE == _SPI->SPI_Mode)
        {
            if((MSSP_SPI_SLAVE_MODE_PIN_CONTROL_ENABLE == _SPI->SPI_Mode_confg) || (MSSP_SPI_SLAVE_MODE_PIN_CONTROL_DSIABLE == _SPI->SPI_Mode_confg))
            {
                ret_state = Func_Not_OK;
            }
            else
            {
                /* Initialize Pins SDI , SCK , SDO IN master mode */
                TRISCbits.RC4 = SPI_GPIO_DIRECTION_INPUT;
                TRISCbits.RC5 = SPI_GPIO_DIRECTION_OUTPUT;
                TRISCbits.RC3 = SPI_GPIO_DIRECTION_OUTPUT;
                
                /* Configure Sample_Output_Data in master mode */
                if(MSSP_SPI_SAMPLE_AT_THE_MIDDLE_OF_DATA == _SPI->SPI_Sample_Data)
                {
                    MSSP_SPI_MIDDLE_SAMPLE();
                }
                else if(MSSP_SPI_SAMPLE_AT_THE_END_OF_DATA == _SPI->SPI_Sample_Data)
                {
                    MSSP_SPI_END_SAMPLE();
                }

                else { /* Nothing */ }
                
                /* Clear Write Collision Detect bit*/
                SSPCON1bits.WCOL = 0;
            }
            
            
        }
        else if(MSSP_SPI_SLAVE_MODE == _SPI->SPI_Mode)
        {
            if(!((MSSP_SPI_SLAVE_MODE_PIN_CONTROL_ENABLE == _SPI->SPI_Mode_confg) || (MSSP_SPI_SLAVE_MODE_PIN_CONTROL_DSIABLE == _SPI->SPI_Mode_confg)))
            {
                ret_state = Func_Not_OK;
            }
            else
            {
                /* Initialize Pins SDI , SCK , SDO IN Slave mode */
                TRISCbits.RC4 = SPI_GPIO_DIRECTION_INPUT;
                TRISCbits.RC5 = SPI_GPIO_DIRECTION_OUTPUT;
                TRISCbits.RC3 = SPI_GPIO_DIRECTION_INPUT;
                
                /* Configure Sample_Output_Data in slave mode */
                MSSP_SPI_MIDDLE_SAMPLE();
                
                /* Clear Receive Overflow Indicator bit */
                SSPCON1bits.SSPOV = 0;
            }
        }
        else { /* Nothing */ }
        
        /* Configure Clock_Polarity */
        if(MSSP_SPI_CLOCK_IDLE_STATE_IS_HIGH == _SPI->SPI_Clock_Polarity)
        {
            MSSP_SPI_HIGH_CLOCK_POLARITY();
        }
        else if(MSSP_SPI_CLOCK_IDLE_STATE_IS_LOW == _SPI->SPI_Clock_Polarity)
        {
            MSSP_SPI_LOW_CLOCK_POLARITY();
        }
 
        else { /* Nothing */ }
        
        
        /* Configure Clock_Phase */
        if(MSSP_SPI_TRANSMIT_FROM_IDLE_TO_ACTINE == _SPI->SPI_Clock_Phase)
        {
            SSPSTATbits.CKE = MSSP_SPI_TRANSMIT_FROM_IDLE_TO_ACTINE;
        }
        else if(MSSP_SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE == _SPI->SPI_Clock_Phase)
        {
            SSPSTATbits.CKE = MSSP_SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE;
        }
 
        else { /* Nothing */ }
        
        /* Configure Interrupt */
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _SPI->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            MSSP_SPI_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _SPI->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            MSSP_SPI_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        MSSP_SPIInterrupt_Handler = _SPI->SPI_Interrupt_Handler;
        MSSP_SPI_INTERRUPT_ENABLE();
        MSSP_SPI_INTERRUPT_CLEAR_FLAG();
#endif       
        /* Enable Module */
        MSSP_SPI_MODULE_ENABLE();

        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType MSSP_SPI_DeInitilization(const MSSP_SPI_Type* _SPI)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _SPI)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        MSSP_SPI_MODULE_DISABLE();
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_INTERRUPT_DISABLE();
#endif
        ret_state = Func_OK;
    }
    
    return ret_state;
}


Std_ReturnType MSSP_SPI_Read_Value_Blocking(uint8 *_Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
    
    while(!(SSPSTATbits.BF));
    
    
    if(MSSP_SPI_NO_COLLISION == SSPCON1bits.WCOL)
    {
        *_Data = SSPBUF;
        ret_state = Func_OK;
    }
    else if(MSSP_SPI_COLLISION_HAPPENED == SSPCON1bits.WCOL)
    {
        ret_state = Func_Not_OK;
    }
    else { /* Nothing */ }
    
    return ret_state;
}

Std_ReturnType MSSP_SPI_Write_Value_Blocking(uint8 _Data)
{
    Std_ReturnType ret_state = Func_OK;
    /* To clear WCOL BIT AUTOMATICALLY IF any collision happened*/
    uint8 Data_In_Register = SSPBUF;
    
    SSPBUF = _Data;
    /* Wait For Transmitting Data */
    while(PIR1bits.SSPIF);
    
    MSSP_SPI_INTERRUPT_CLEAR_FLAG();
    
    return ret_state;
}

void SPI_ISR(void)
{
    MSSP_SPI_INTERRUPT_CLEAR_FLAG();
    
    if(MSSP_SPIInterrupt_Handler)
    {
        MSSP_SPIInterrupt_Handler();
    }
}