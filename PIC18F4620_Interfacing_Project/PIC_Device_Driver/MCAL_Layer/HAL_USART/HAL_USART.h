/* 
 * File:   HAL_USART.h
 * Author: win 10-11
 *
 * Created on 21 ?????, 2024, 09:05 ?
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*************** Includes  ***********************/
#include "../Std_Types.h"
#include "../GPIO/HAL_GPIO.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/Internal_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

/* baud rate configuration */
#define EUSART_ASYNCHRONOUS_MODE                 0
#define EUSART_SYNCHRONOUS_MODE                  1

#define EUSART_8bitBaud_Rate_Generator_REG       0
#define EUSART_16bitBaud_Rate_Generator_REG      1

#define EUSART_LOW_SPEED_BAUDRATE_SELECT         0
#define EUSART_HIGH_SPEED_BAUDRATE_SELECT        1
/***************************/
/* EUSART Transmitter configuration */
#define EUSART_Transmitter_DISABLE_CONF              0
#define EUSART_Transmitter_ENABLE_CONF               1

#define EUSART_Transmitter_INTERRUPT_DISABLE_CONF    0
#define EUSART_Transmitter_INTERRUPT_ENABLE_CONF     1

#define EUSART_Transmitter_8BIT_TRANSMISSION_CONF    0
#define EUSART_Transmitter_9BIT_TRANSMISSION_CONF   1
/*****************************************/
/* EUSART Receiver configuration */
#define EUSART_Receiver_DISABLE_CONF              0
#define EUSART_Receiver_ENABLE_CONF               1

#define EUSART_Receiver_INTERRUPT_DISABLE_CONF    0
#define EUSART_Receiver_INTERRUPT_ENABLE_CONF     1

#define EUSART_Receiver_8BIT_RECEPTION_CONF       0
#define EUSART_Receiver_9BIT_RECEPTION_CONF       1
/*****************************************/

#define EUSART_INTERRUPT_OCCUR             1

#define EUSART_TSR_EMPTY                   1

/*************************************************/

/********** Marcos Function Declarations *********/

#define EUSART_MODULE_DISABLE()               (RCSTAbits.SPEN = 0)
#define EUSART_MODULE_ENABLE()                (RCSTAbits.SPEN = 1)

/* EUSART Transmitter configuration */
#define EUSART_Transmitter_DISABLE()           (TXSTAbits.TXEN = 0)
#define EUSART_Transmitter_ENABLE()            (TXSTAbits.TXEN = 1)

#define EUSART_Transmitter_8BIT_TRANSMISSION() (TXSTAbits.TX9 = 0)
#define EUSART_Transmitter_9BIT_TRANSMISSION() (TXSTAbits.TX9 = 1)

/****************************************/
/* EUSART Receiver configuration */
#define EUSART_Receiver_DISABLE()               (RCSTAbits.CREN = 0)
#define EUSART_Receiver_ENABLE()                (RCSTAbits.CREN = 1)

#define EUSART_Receiver_8BIT_RECEPTION()        (RCSTAbits.RX9 = 0)
#define EUSART_Receiver_9BIT_RECEPTION()        (RCSTAbits.RX9 = 1)
/****************************************/

/*************************************************/

/************ Data Type Declarations **************/

typedef enum
{
    EUSART_ASYNCHRONOUS_MODE_8BIT_LOW_SPPED = 0,
    EUSART_ASYNCHRONOUS_MODE_8BIT_HIGH_SPPED,
    EUSART_ASYNCHRONOUS_MODE_16BIT_LOW_SPPED,
    EUSART_ASYNCHRONOUS_MODE_16BIT_HIGH_SPPED, 
    EUSART_SYNCHRONOUS_MODE_8BIT_REG,
    EUSART_SYNCHRONOUS_MODE_16BIT_REG,
            
}Baud_Rate_Generator_confg_t;

typedef struct
{
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* EUSART_TX_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    uint8 EUSART_Transmitter_reserved : 5;
    uint8 EUSART_Transmitter_Enable : 1;
    uint8 EUSART_Transmitter_Interrupt_Enable : 1;
    uint8 EUSART_9Bit_Transmission_confg : 1;
}EUSART_Transmitter_Type;

typedef struct
{
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* EUSART_RX_Interrupt_Handler)(void);
    void (* EUSART_RX_Framing_Error_Interrupt_Handler)(void);
    void (* EUSART_RX_Overrun_Error_Interrupt_Handler)(void);
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    uint8 EUSART_Receiver_reserved : 5;
    uint8 EUSART_Receiver_Enable : 1;
    uint8 EUSART_Receiver_Interrupt_Enable : 1;
    uint8 EUSART_9Bit_Receiver_confg : 1;
}EUSART_Receiver_Type;

typedef struct
{
    uint8 EUSART_sync_Async_Mode : 1;
    Pin_Config_Type EUSART_TX_Pin_Config;
    Pin_Config_Type EUSART_RX_Pin_Config;
    
    uint32 baudRate_Generator;
    Baud_Rate_Generator_confg_t Baud_Rate_Generator_confg;
    
    EUSART_Transmitter_Type EUSART_Transmitter_Confg;
    EUSART_Receiver_Type    EUSART_Receiver_Confg;
    
}EUSART_Type;

/*************************************************/

/*********** Function Declarations ***************/

Std_ReturnType EUSART_Initilization(const EUSART_Type* _eusart);
Std_ReturnType EUSART_DeInitilization(const EUSART_Type* _eusart);

Std_ReturnType EUSART_Read_Value_Blocking(uint8 *_Data);
Std_ReturnType EUSART_Write_Value_Blocking(uint8 _Data);

Std_ReturnType EUSART_Read_Value_Non_Blocking(uint8 *_Data);
Std_ReturnType EUSART_Write_Value_Non_Blocking(uint8 _Data);

Std_ReturnType EUSART_Write_String(uint8 *_Data , uint16 str_length);

Std_ReturnType EUSART_Receiver_Restart(void);
/*************************************************/

#endif	/* HAL_USART_H */

