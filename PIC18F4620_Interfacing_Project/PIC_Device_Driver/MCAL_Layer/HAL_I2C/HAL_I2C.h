/* 
 * File:   HAL_I2C.h
 * Author: win 10-11
 *
 * Created on 01 ?????, 2024, 05:41 ?
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/*************** Includes  ***********************/
#include "../Std_Types.h"
#include "../GPIO/HAL_GPIO.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/Internal_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

#define MSSP_I2C_MASTER_MODE      0
#define MSSP_I2C_SLAVE_MODE       1

#define MSSP_I2C_MASTER_MODE_WITH_CLOCK_CONFG               0x8
#define MSSP_I2C_MASTER_MODE_FIRMWARE_CONTROLLED            0x0B

#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS                    0x6
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS                   0x7
#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS_INTERRUPT_ENABLE   0x0E
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS_INTERRUPT_ENABLE  0x0F

#define MSSP_I2C_SLOW_RATE_ENABLE                        0
#define MSSP_I2C_SLOW_RATE_DISABLE                       1

#define MSSP_I2C_SMBUS_DISABLE                           0
#define MSSP_I2C_SMBUS_ENABLE                            1

#define MSSP_I2C_GENERAL_CALL_ADDRESS_DISABLE            0
#define MSSP_I2C_GENERAL_CALL_ADDRESS_ENABLE             1

#define MSSP_I2C_MASTER_RECIEVER_MODE_DISABLE            0
#define MSSP_I2C_MASTER_RECIEVER_MODE_ENABLE             1

#define MSSP_I2C_SLAVE_MODE_CLOCK_STRETCHING_DISABLE     0
#define MSSP_I2C_SLAVE_MODE_CLOCK_STRETCHING_ENABLE      1

#define I2C_GPIO_DIRECTION_OUTPUT                        0
#define I2C_GPIO_DIRECTION_INPUT                         1 

#define I2C_CONDITION_NOT_DETECTED                       0
#define I2C_CONDITION_DETECTED                           1

#define I2C_MASTER_SEND_ACK                              0
#define I2C_MASTER_SEND_NOT_ACK                          1

#define I2C_MASTER_RECEIVED_ACK_FROM_SLAVE               0
#define I2C_MASTER_NOT_RECEIVED_ACK_FROM_SLAVE           1
/*************************************************/

/********** Marcos Function Declarations *********/

#define MSSP_I2C_MODULE_ENABLE()                          (SSPCON1bits.SSPEN = 1)
#define MSSP_I2C_MODULE_DISABLE()                         (SSPCON1bits.SSPEN = 0)

#define MSSP_I2C_SLOW_RATE_ENABLE_CONFG()                 (SSPSTATbits.SMP = 0) 
#define MSSP_I2C_SLOW_RATE_DISABLE_CONFG()                (SSPSTATbits.SMP = 1) 

#define MSSP_I2C_SMBUS_DISABLE_CONFG()                    (SSPSTATbits.CKE = 0) 
#define MSSP_I2C_SMBUS_ENABLE_CONFG()                     (SSPSTATbits.CKE = 1) 

#define MSSP_I2C_SLAVE_CLOCK_STRETCHING_DISABLE()         (SSPCON2bits.SEN = 0)
#define MSSP_I2C_SLAVE_CLOCK_STRETCHING_ENABLE()          (SSPCON2bits.SEN = 1)


/*************************************************/

/************ Data Type Declarations **************/

typedef struct
{
    uint8 I2C_Mode_confg;
    uint8 I2C_Slave_Address;
    
    uint8 I2C_Mode               : 1;
    uint8 I2C_SMBus              : 1;
    uint8 I2C_Slow_Rate          : 1;
    uint8 I2C_General_Call       : 1;
    uint8 I2C_Mater_Reciver_Mode : 1;
    
    uint8 I2C_Reserved           : 3;
    
}MSSP_I2C_confg;

typedef struct
{
    uint32 Clock_Rate;
    
    MSSP_I2C_confg I2C_confg;
    
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* I2C_Interrupt_Handler)(void);
    void (* I2C_BUS_Collision_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    
    
}MSSP_I2C_Type;

/*************************************************/

/*********** Function Declarations ***************/

Std_ReturnType MSSP_I2C_Initilization(const MSSP_I2C_Type* _I2C);
Std_ReturnType MSSP_I2C_DeInitilization(const MSSP_I2C_Type* _I2C);

Std_ReturnType MSSP_I2C_Master_Send_Start_Condition(void);
Std_ReturnType MSSP_I2C_Master_Send_RepeatedStart_Condition(void);
Std_ReturnType MSSP_I2C_Master_Send_Stop_Condition(void);

Std_ReturnType MSSP_I2C_Read_Value_Blocking(uint8 *_Data , uint8 ACK);
Std_ReturnType MSSP_I2C_Write_Value_Blocking(uint8 _Data  , uint8 *ACK);

/*************************************************/


#endif	/* HAL_I2C_H */

