/* 
 * File:   HAL_USART.C
 * Author: win 10-11
 *
 * Created on 21 ?????, 2024, 09:05 ?
 */

#include "HAL_USART.h"

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (* EUSARTTXInterrupt_Handler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (* EUSARTRXInterrupt_Handler)(void) = NULL;
        void (* EUSARTRXFraming_Error_Interrupt_Handler)(void) = NULL;
        void (* EUSARTRXOverrun_Error_Interrupt_Handler)(void) = NULL;
#endif        

static Std_ReturnType EUSART_BaudRate_Calculation(const EUSART_Type* _eusart);

static Std_ReturnType EUSART_TX_Initilization(const EUSART_Type* _eusart);
static Std_ReturnType EUSART_RX_Initilization(const EUSART_Type* _eusart);

Std_ReturnType EUSART_Initilization(const EUSART_Type* _eusart)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _eusart)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        EUSART_MODULE_DISABLE();
        ret_state = EUSART_BaudRate_Calculation(_eusart);        
        ret_state &= GPIO_Pin_Direction_Initilization(&(_eusart->EUSART_TX_Pin_Config));
        ret_state &= GPIO_Pin_Direction_Initilization(&(_eusart->EUSART_RX_Pin_Config));
        EUSART_MODULE_ENABLE();
        
        ret_state &= EUSART_TX_Initilization(_eusart);
        ret_state &= EUSART_RX_Initilization(_eusart);   
    }
    
    return ret_state;
}

Std_ReturnType EUSART_DeInitilization(const EUSART_Type* _eusart)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _eusart)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        EUSART_MODULE_DISABLE();
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                EUSART_RX_INTERRUPT_DISABLE();
#endif
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                EUSART_TX_INTERRUPT_DISABLE();
#endif
                
    }
    return ret_state;
}


Std_ReturnType EUSART_Read_Value_Blocking(uint8 *_Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Data)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        while(!(PIR1bits.RCIF));
        EUSART_RX_INTERRUPT_ENABLE();
        *_Data = RCREG;
        /* if you 9bit Configuration 
         handle it here
         */
    }
    
    return ret_state;
}

Std_ReturnType EUSART_Write_Value_Blocking(uint8 _Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
        while(!(TXSTAbits.TRMT));
        EUSART_TX_INTERRUPT_ENABLE();
        TXREG = _Data;
        /* if you 9bit Configuration 
         handle it here
         */
    
    return ret_state;
}


Std_ReturnType EUSART_Read_Value_Non_Blocking(uint8 *_Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _Data)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(EUSART_INTERRUPT_OCCUR == PIR1bits.RCIF)
        {
            *_Data = RCREG;
         /* if you 9bit Configuration 
         handle it here
         */
        }
        else{ /*Nothing */}
    }
    
    return ret_state;
}

Std_ReturnType EUSART_Write_Value_Non_Blocking(uint8 _Data)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(EUSART_TSR_EMPTY == TXSTAbits.TRMT)
        {
            TXREG = _Data;
         /* if you 9bit Configuration 
         handle it here
         */
        }
        else{ /*Nothing */}
    return ret_state;
}


Std_ReturnType EUSART_Write_String(uint8 *_Data , uint16 str_length)
{
    Std_ReturnType ret_state = Func_Not_OK;
    uint16 Str_Counter = 0;
    if(NULL == _Data)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        for(Str_Counter = 0; Str_Counter < str_length; Str_Counter++)
        {
            ret_state = EUSART_Write_Value_Blocking(_Data[Str_Counter]);
        }
    }
    
    return ret_state;
}

Std_ReturnType EUSART_Receiver_Restart(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
        EUSART_Receiver_DISABLE();
        EUSART_Receiver_ENABLE();
    
    return ret_state;
}

void EUSART_TX_ISR(void)
{
    EUSART_TX_INTERRUPT_DISABLE();
    if(EUSARTTXInterrupt_Handler)
    {
        EUSARTTXInterrupt_Handler();
    }
}

void EUSART_RX_ISR(void)
{
    EUSART_RX_INTERRUPT_DISABLE();
    if(EUSARTRXInterrupt_Handler)
    {
        EUSARTRXInterrupt_Handler();
    }
    
    if(EUSARTRXFraming_Error_Interrupt_Handler)
    {
        EUSARTRXFraming_Error_Interrupt_Handler();
    }
    
    if(EUSARTRXOverrun_Error_Interrupt_Handler)
    {
        EUSARTRXOverrun_Error_Interrupt_Handler();
    }
}

static Std_ReturnType EUSART_BaudRate_Calculation(const EUSART_Type* _eusart)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _eusart)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        float32 temp_value = 0;
        switch(_eusart->Baud_Rate_Generator_confg)
        {
            case EUSART_ASYNCHRONOUS_MODE_8BIT_LOW_SPPED:
            {
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_LOW_SPEED_BAUDRATE_SELECT;
                BAUDCONbits.BRG16 = EUSART_8bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 64) - 1;
            }
            break;
            
            case EUSART_ASYNCHRONOUS_MODE_8BIT_HIGH_SPPED:
            {
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_HIGH_SPEED_BAUDRATE_SELECT;
                BAUDCONbits.BRG16 = EUSART_8bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 16) - 1;
            }
            break;
            
            case EUSART_ASYNCHRONOUS_MODE_16BIT_LOW_SPPED:
            {
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_LOW_SPEED_BAUDRATE_SELECT;
                BAUDCONbits.BRG16 = EUSART_16bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 16) - 1;
            }
            break;
            
            case EUSART_ASYNCHRONOUS_MODE_16BIT_HIGH_SPPED:
            {
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_HIGH_SPEED_BAUDRATE_SELECT;
                BAUDCONbits.BRG16 = EUSART_16bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 4) - 1;
            }
            break;
            
            case EUSART_SYNCHRONOUS_MODE_8BIT_REG:
            {
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_8bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 4) - 1;
            }
            break;
            
            case EUSART_SYNCHRONOUS_MODE_16BIT_REG:
            {
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_16bitBaud_Rate_Generator_REG;
                temp_value = (float32)((_XTAL_FREQ / _eusart->baudRate_Generator) / 4) - 1;
            }
            break;
            
            default : ret_state = Func_Not_OK;
            
        }
        
        SPBRG = (uint8)((uint32) temp_value);
        SPBRGH = (uint8)(((uint32) temp_value) >> 8);
    }
    
    return ret_state;
}

static Std_ReturnType EUSART_TX_Initilization(const EUSART_Type* _eusart)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _eusart)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(EUSART_Transmitter_ENABLE_CONF == (_eusart->EUSART_Transmitter_Confg).EUSART_Transmitter_Enable)
        {
            EUSART_Transmitter_ENABLE();
            
            if(EUSART_Transmitter_INTERRUPT_ENABLE_CONF == (_eusart->EUSART_Transmitter_Confg).EUSART_Transmitter_Interrupt_Enable)
            {
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
             if(INTERRUPT_LOW_PRIORITY == _eusart->EUSART_Transmitter_Confg.Priority)
            {
                INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
                EUSART_TX_INTERRUPT_LOW_Priority();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _eusart->EUSART_Transmitter_Confg.Priority)
            {
                INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
                EUSART_TX_INTERRUPT_HIGH_Priority();
            }
            else { /* NoThing */ }
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
            EUSARTTXInterrupt_Handler = (_eusart->EUSART_Transmitter_Confg).EUSART_TX_Interrupt_Handler;
            EUSART_TX_INTERRUPT_ENABLE();
            
#endif
        
            }
            else if (EUSART_Transmitter_INTERRUPT_DISABLE_CONF == (_eusart->EUSART_Transmitter_Confg).EUSART_Transmitter_Interrupt_Enable)
            {
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                EUSART_TX_INTERRUPT_DISABLE();
#endif
            }
            else { /* Nothing */}
            
            if(EUSART_Transmitter_8BIT_TRANSMISSION_CONF == (_eusart->EUSART_Transmitter_Confg).EUSART_9Bit_Transmission_confg)
            {
                EUSART_Transmitter_8BIT_TRANSMISSION();
            }
            else if (EUSART_Transmitter_9BIT_TRANSMISSION_CONF == (_eusart->EUSART_Transmitter_Confg).EUSART_9Bit_Transmission_confg)
            {
                EUSART_Transmitter_9BIT_TRANSMISSION();
                /* calculate the ninth bit and put the value in  TXSTA<0> (TX9D) */
            }
            else { /* Nothing */ }
        }
        else { 
            /*TX is Disabled */
            EUSART_Transmitter_DISABLE();
        } 

    }
    
    return ret_state;
}

static Std_ReturnType EUSART_RX_Initilization(const EUSART_Type* _eusart)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _eusart)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(EUSART_Receiver_ENABLE_CONF == (_eusart->EUSART_Receiver_Confg).EUSART_Receiver_Enable)
        {
            EUSART_Receiver_ENABLE();
            
            if(EUSART_Receiver_INTERRUPT_ENABLE_CONF == (_eusart->EUSART_Receiver_Confg).EUSART_Receiver_Interrupt_Enable)
            {
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
             if(INTERRUPT_LOW_PRIORITY == _eusart->EUSART_Receiver_Confg.Priority)
            {
                INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
                EUSART_RX_INTERRUPT_LOW_Priority();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _eusart->EUSART_Receiver_Confg.Priority)
            {
                INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
                EUSART_RX_INTERRUPT_HIGH_Priority();
            }
            else { /* NoThing */ }
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
            EUSARTRXInterrupt_Handler = (_eusart->EUSART_Receiver_Confg).EUSART_RX_Interrupt_Handler;
            EUSARTRXFraming_Error_Interrupt_Handler = (_eusart->EUSART_Receiver_Confg).EUSART_RX_Framing_Error_Interrupt_Handler;
            EUSARTRXOverrun_Error_Interrupt_Handler = (_eusart->EUSART_Receiver_Confg).EUSART_RX_Overrun_Error_Interrupt_Handler;
            EUSART_RX_INTERRUPT_ENABLE();
#endif
        
            }
            else if (EUSART_Receiver_INTERRUPT_DISABLE_CONF == (_eusart->EUSART_Receiver_Confg).EUSART_Receiver_Interrupt_Enable)
            {
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                EUSART_RX_INTERRUPT_DISABLE();
#endif
            }
            else { /* Nothing */}
            
            if(EUSART_Receiver_8BIT_RECEPTION_CONF == (_eusart->EUSART_Receiver_Confg).EUSART_9Bit_Receiver_confg)
            {
                EUSART_Receiver_8BIT_RECEPTION();
            }
            else if (EUSART_Receiver_9BIT_RECEPTION_CONF == (_eusart->EUSART_Receiver_Confg).EUSART_9Bit_Receiver_confg)
            {
                EUSART_Receiver_9BIT_RECEPTION();
                /* Receive the ninth bit from  RCSTA<0> (RX9D) */
            }
            else { /* Nothing */ }
        }
        else { 
            /*TX is Disabled */
            EUSART_Receiver_DISABLE();
        } 

    }
    
    return ret_state;
}