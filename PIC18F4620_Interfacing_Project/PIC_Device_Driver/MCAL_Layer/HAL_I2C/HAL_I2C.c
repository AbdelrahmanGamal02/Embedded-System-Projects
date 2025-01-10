/* 
 * File:   HAL_I2C.h
 * Author: win 10-11
 *
 * Created on 01 ?????, 2024, 05:41 ?
 */

#include "HAL_I2C.h"

/* Call Back of I2C interrupt */
#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* MSSP_I2CInterrupt_Handler)(void);
#endif

/* Call Back of I2C Bus Collision interrupt */   
#if MSSP_I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   static void (* MSSP_I2C_BUS_CollisionInterrupt_Handler)(void);
#endif

static Std_ReturnType MSSP_I2C_Master_Set_Configuration(const MSSP_I2C_Type* _I2C);
static Std_ReturnType MSSP_I2C_Slave_Set_Configuration(const MSSP_I2C_Type* _I2C);

Std_ReturnType MSSP_I2C_Initilization(const MSSP_I2C_Type* _I2C)
{
     Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _I2C)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Module */
        MSSP_I2C_MODULE_DISABLE();
        /* Configure master and receiver mode */
        if(MSSP_I2C_MASTER_MODE == _I2C->I2C_confg.I2C_Mode)
        {
            ret_state = MSSP_I2C_Master_Set_Configuration(_I2C);
        }
        else if(MSSP_I2C_SLAVE_MODE == _I2C->I2C_confg.I2C_Mode)
        {
            ret_state = MSSP_I2C_Slave_Set_Configuration(_I2C);
        }
        else { /* Nothing */ }
        
        /* configure GPIO Pins */
        TRISCbits.RC3 = I2C_GPIO_DIRECTION_INPUT;
        TRISCbits.RC4 = I2C_GPIO_DIRECTION_INPUT;
        /* configure Slow Rate */
        if(MSSP_I2C_SLOW_RATE_ENABLE == _I2C->I2C_confg.I2C_Slow_Rate)
        {
            MSSP_I2C_SLOW_RATE_ENABLE_CONFG();
        }
        else if(MSSP_I2C_SLOW_RATE_DISABLE == _I2C->I2C_confg.I2C_Slow_Rate)
        {
            MSSP_I2C_SLOW_RATE_DISABLE_CONFG();
        }
        else { /* Nothing */ }
        
        if(MSSP_I2C_SMBUS_DISABLE == _I2C->I2C_confg.I2C_SMBus)
        {
            MSSP_I2C_SMBUS_DISABLE_CONFG();
        }
        else if(MSSP_I2C_SMBUS_ENABLE == _I2C->I2C_confg.I2C_SMBus)
        {
            MSSP_I2C_SMBUS_ENABLE_CONFG();
        }
        else { /* Nothing */ }
        
        /* configure I2C interrupt */
#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _I2C->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            MSSP_I2C_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _I2C->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            MSSP_I2C_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        MSSP_I2CInterrupt_Handler = _I2C->I2C_Interrupt_Handler;
        MSSP_I2C_INTERRUPT_ENABLE();
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
#endif

/* configure I2C Bus Collision interrupt */
#if MSSP_I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
        INTERRUPT_PRIORTY_LEVELS_ENABLE();
         if(INTERRUPT_LOW_PRIORITY == _I2C->Priority)
        {
            INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
            MSSP_I2C_BUS_COLLISION_INTERRUPT_LOW_Priority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _I2C->Priority)
        {
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
            MSSP_I2C_BUS_COLLISION_INTERRUPT_HIGH_Priority();
        }
        else { /* NoThing */ }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_Preipheral_INTERRUPT_ENABLE();  
#endif
        
        MSSP_I2C_BUS_CollisionInterrupt_Handler = _I2C->I2C_BUS_Collision_Interrupt_Handler;
        MSSP_I2C_BUS_COLLISION_INTERRUPT_ENABLE();
        MSSP_I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
#endif        
        
        /* Enable Module */
        MSSP_I2C_MODULE_ENABLE();
        ret_state &= Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType MSSP_I2C_DeInitilization(const MSSP_I2C_Type* _I2C)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _I2C)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Module */
        MSSP_I2C_MODULE_DISABLE();
        
#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE        
        MSSP_I2C_INTERRUPT_DISABLE();
#endif
        
        ret_state = Func_OK;
    }
    
    return ret_state;
}


Std_ReturnType MSSP_I2C_Master_Send_Start_Condition(void)
{
    Std_ReturnType ret_state = Func_Not_OK;
    
        /* initiate start condition */
        SSPCON2bits.SEN = 1;
        /* ensure that start condition on bus */
        while(SSPCON2bits.SEN);
        /* Clear Flag result from start condition*/
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        /* Detect start condition */
        if(I2C_CONDITION_DETECTED == SSPSTATbits.S)
        {
            ret_state = Func_OK;
        }
        else if(I2C_CONDITION_NOT_DETECTED == SSPSTATbits.S)
        {
            ret_state = Func_Not_OK;
        }
        else { /* Nothing */ } 
        
    return ret_state;
}

Std_ReturnType MSSP_I2C_Master_Send_RepeatedStart_Condition(void)
{
    Std_ReturnType ret_state = Func_Not_OK;

        /* initiate repeated start condition */
        SSPCON2bits.RSEN = 1;
        /* ensure that repeated start condition on bus */
        while(SSPCON2bits.RSEN);
        /* Clear Flag result from repeated start condition*/
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
         
        ret_state = Func_OK;
        
    return ret_state;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop_Condition()
{
    Std_ReturnType ret_state = Func_Not_OK;
    
        /* initiate stop condition */
        SSPCON2bits.PEN = 1;
        /* ensure that stop condition on bus */
        while(SSPCON2bits.PEN);
        /* Clear Flag result from stop condition*/
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        /* Detect stop condition */
        if(I2C_CONDITION_DETECTED == SSPSTATbits.P)
        {
            ret_state = Func_OK;
        }
        else if(I2C_CONDITION_NOT_DETECTED == SSPSTATbits.P)
        {
            ret_state = Func_Not_OK;
        }
        else { /* Nothing */ } 
        
    return ret_state;
}


Std_ReturnType MSSP_I2C_Read_Value_Blocking(uint8 *Received_Data , uint8 ACK)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Received_Data)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Enable Master Receiver mode */
        SSPCON2bits.RCEN = MSSP_I2C_MASTER_RECIEVER_MODE_ENABLE;
        /* wait until master receive data from slave */
        while(!SSPSTATbits.BF);
        /* Read Data */
        *Received_Data = SSPBUF;
        /* MASTER send Acknowledge */
        if(I2C_MASTER_SEND_ACK == ACK)
        {
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
            SSPCON2bits.ACKEN = 1;
        }
        else if(I2C_MASTER_SEND_NOT_ACK == ACK)
        {
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NOT_ACK;
            SSPCON2bits.ACKEN = 1;
        }
        else{ /* Nothing */ }
        ret_state = Func_OK;
    }
    
    return ret_state;
}

Std_ReturnType MSSP_I2C_Write_Value_Blocking(uint8 _Data  , uint8 *ACK)
{
    Std_ReturnType ret_state = Func_Not_OK;

        /* Write Value to Register */
        SSPBUF = _Data;
        /* Wait until data is being transmitted */
        while(!PIR1bits.SSPIF);
        /* Clear Flag */
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        /* ACK */
        if(I2C_MASTER_RECEIVED_ACK_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *ACK = I2C_MASTER_RECEIVED_ACK_FROM_SLAVE;
        }
        else if(I2C_MASTER_NOT_RECEIVED_ACK_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *ACK = I2C_MASTER_NOT_RECEIVED_ACK_FROM_SLAVE;
        }
        else { /* Nothing */ }
        ret_state = Func_OK;
        
    return ret_state;
}


Std_ReturnType MSSP_I2C_Master_Set_Configuration(const MSSP_I2C_Type* _I2C)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _I2C)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        if(MSSP_I2C_MASTER_MODE_FIRMWARE_CONTROLLED == _I2C->I2C_confg.I2C_Mode_confg)
        {
            /* Code that used to configure master with firmware control */
        }
        else
        {
            /* Configure Clock */
            SSPCON1bits.SSPM = MSSP_I2C_MASTER_MODE_WITH_CLOCK_CONFG;
            SSPADD = (uint8)(((_XTAL_FREQ) / (4 * _I2C->Clock_Rate)) + 1);
            
            /* Configure Master Receiver */
            if(MSSP_I2C_MASTER_RECIEVER_MODE_ENABLE == _I2C->I2C_confg.I2C_Mater_Reciver_Mode)
            {
                SSPCON2bits.RCEN = MSSP_I2C_MASTER_RECIEVER_MODE_ENABLE;
            }
            else if(MSSP_I2C_MASTER_RECIEVER_MODE_DISABLE == _I2C->I2C_confg.I2C_Mater_Reciver_Mode)
            {
                SSPCON2bits.RCEN = MSSP_I2C_MASTER_RECIEVER_MODE_DISABLE;
            }
            else { /* Nothing */ }
            
            /* initiate Collision */
            SSPCON1bits.WCOL = 0;
        }
              
        ret_state = Func_OK;
    }
    
    return ret_state;
    
}

Std_ReturnType MSSP_I2C_Slave_Set_Configuration(const MSSP_I2C_Type* _I2C)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == _I2C)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Configure Slave mode */
        SSPCON1bits.SSPM = _I2C->I2C_confg.I2C_Mode_confg;
        
        /* Configure Slave Address */
        SSPADD = _I2C->I2C_confg.I2C_Slave_Address;
        
        /* Configure General Call */
        SSPCON2bits.GCEN =  _I2C->I2C_confg.I2C_General_Call;
        
        /* initiate overflow  , Collision  , Interrupt Flag*/
        SSPCON1bits.SSPOV = 0;
        SSPCON1bits.WCOL = 0;
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        
        /* Release Clock */
        SSPCON1bits.CKP = 1;
        ret_state = Func_OK;
    }
    
    return ret_state;
    
}

void I2C_ISR(void)
{
    MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    
    if(MSSP_I2CInterrupt_Handler)
    {
        MSSP_I2CInterrupt_Handler();
    }
}

void I2C_Bus_Collision_ISR(void)
{
    MSSP_I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
    
    if(MSSP_I2C_BUS_CollisionInterrupt_Handler)
    {
        MSSP_I2C_BUS_CollisionInterrupt_Handler();
    }
}