/* 
 * File:   HAL_SPI.h
 * Author: win 10-11
 *
 * Created on 31 ?????, 2024, 02:23 ?
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*************** Includes  ***********************/
#include "../Std_Types.h"
#include "../GPIO/HAL_GPIO.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/Internal_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

#define MSSP_SPI_MASTER_MODE      0
#define MSSP_SPI_SLAVE_MODE       1

#define MSSP_SPI_NO_COLLISION                      0 
#define MSSP_SPI_COLLISION_HAPPENED                1 

#define MSSP_SPI_MASTER_MODE_FOSC_DIV_BY_4         0
#define MSSP_SPI_MASTER_MODE_FOSC_DIV_BY_16        1
#define MSSP_SPI_MASTER_MODE_FOSC_DIV_BY_64        2
#define MSSP_SPI_MASTER_MODE_TMR2_OUT_DIV_BY_2     3
#define MSSP_SPI_SLAVE_MODE_PIN_CONTROL_ENABLE     4
#define MSSP_SPI_SLAVE_MODE_PIN_CONTROL_DSIABLE    5

#define SPI_GPIO_DIRECTION_OUTPUT                  0
#define SPI_GPIO_DIRECTION_INPUT                   1

#define MSSP_SPI_CLOCK_IDLE_STATE_IS_LOW           0
#define MSSP_SPI_CLOCK_IDLE_STATE_IS_HIGH          1

#define MSSP_SPI_SAMPLE_AT_THE_MIDDLE_OF_DATA      0
#define MSSP_SPI_SAMPLE_AT_THE_END_OF_DATA         1

#define MSSP_SPI_TRANSMIT_FROM_IDLE_TO_ACTINE      0
#define MSSP_SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE      1

/*************************************************/

/********** Marcos Function Declarations *********/

#define MSSP_SPI_MODULE_ENABLE()               (SSPCON1bits.SSPEN = 1)
#define MSSP_SPI_MODULE_DISABLE()              (SSPCON1bits.SSPEN = 0)

#define MSSP_SPI_MODE(_CONFG_)                 (SSPCON1bits.SSPM = _CONFG_)

#define MSSP_SPI_HIGH_CLOCK_POLARITY()         (SSPCON1bits.CKP = 1) 
#define MSSP_SPI_LOW_CLOCK_POLARITY()          (SSPCON1bits.CKP = 0) 

#define MSSP_SPI_END_SAMPLE()                  (SSPSTATbits.SMP = 1) 
#define MSSP_SPI_MIDDLE_SAMPLE()               (SSPSTATbits.SMP = 0) 

/*************************************************/

/************ Data Type Declarations **************/

typedef struct
{
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* SPI_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    
    uint8 SPI_Mode           : 1;
    uint8 SPI_Mode_confg     : 3;
    uint8 SPI_Clock_Polarity : 1;
    uint8 SPI_Sample_Data    : 1;
    uint8 SPI_Clock_Phase    : 1;

    uint8 SPI_Reserved       : 1;
}MSSP_SPI_Type;

/*************************************************/

/*********** Function Declarations ***************/

Std_ReturnType MSSP_SPI_Initilization(const MSSP_SPI_Type* _SPI);
Std_ReturnType MSSP_SPI_DeInitilization(const MSSP_SPI_Type* _SPI);

Std_ReturnType MSSP_SPI_Read_Value_Blocking(uint8 *_Data);
Std_ReturnType MSSP_SPI_Write_Value_Blocking(uint8 _Data);

/*************************************************/

#endif	/* HAL_SPI_H */

