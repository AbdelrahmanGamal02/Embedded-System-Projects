/* 
 * File:   Hal_Timer0.h
 * Author: win 10-11
 *
 * Created on 03 ?????, 2024, 04:51 ?
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*************** Includes  ***********************/

#include "../../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../../Interrupt/Internal_Interrupt.h"
#include "../../GPIO/HAL_GPIO.h"

/*************************************************/
/************** Marcos Declarations **************/

#define _8BIT_CONFIG            1 
#define _16BIT_CONFIG           0

#define  TIMER0_REGISTER_CONFIG      _16BIT_CONFIG

#define  TIMER0_PRESCALER_ENABLE_CONFG        0
#define  TIMER0_PRESCALER_DISABLE_CONFG       1

#define TIMER0_RISING_SOURCE_EDGE_CONFG       0
#define TIMER0_FALLING_SOURCE_EDGE_CONFG      1

#define TIMER0_TIMER_MODE_CONFG               0
#define TIMER0_COUNTER_MODE_CONFG             1

#define TIMER0_16BIT_REGISTER_CONFG           0
#define TIMER0_8BIT_REGISTER_CONFG            1

/*************************************************/

/********** Marcos Function Declarations *********/

#define TIMER0_PRESCALER_ENABLE()     (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()    (T0CONbits.PSA = 1)

#define TIMER0_RISING_SOURCE_EDGE()   (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_SOURCE_EDGE()  (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE()           (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()         (T0CONbits.T0CS = 1)

#define TIMER0_16BIT_CONFG()          (T0CONbits.T08BIT = 0)
#define TIMER0_8BIT_CONFG()           (T0CONbits.T08BIT = 1)

#define TIMER0_DISABLE()             (T0CONbits.TMR0ON = 0)
#define TIMER0_ENABLE()              (T0CONbits.TMR0ON = 1)
/*************************************************/


/************ Data Type Declarations **************/

typedef enum
{
    TIMER0_PRESCALER_VALUE_DIV_BY_2 = 0,
    TIMER0_PRESCALER_VALUE_DIV_BY_4,
    TIMER0_PRESCALER_VALUE_DIV_BY_8,
    TIMER0_PRESCALER_VALUE_DIV_BY_16,
    TIMER0_PRESCALER_VALUE_DIV_BY_32,
    TIMER0_PRESCALER_VALUE_DIV_BY_64,
    TIMER0_PRESCALER_VALUE_DIV_BY_128,
    TIMER0_PRESCALER_VALUE_DIV_BY_256
            
} Timer0_Prescaler_Select_Type;

typedef struct
{
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER0_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    Timer0_Prescaler_Select_Type Prescaler_Value;
    uint8 Prescaler_Enable  : 1 ;
    uint8 Source_Edge  : 1;
    uint8 Timer0_Mode  : 1;
    uint8 Timer0_16_8_bit_Confg  : 1;
    uint8 Timer0_Reserved : 4;
    
#if TIMER0_REGISTER_CONFIG == _16BIT_CONFIG
    uint16 _16bit_Preload_Value;
    
#elif TIMER0_REGISTER_CONFIG == _8BIT_CONFIG
    uint8 _8bit_Preload_Value;
#endif    
    
}Timer0_Type;
/*************************************************/


/*********** Function Declarations ***************/

Std_ReturnType Timer0_Initilization(const Timer0_Type* _Timer);
Std_ReturnType Timer0_DeInitilization(const Timer0_Type* _Timer);

#if TIMER0_REGISTER_CONFIG == _16BIT_CONFIG
Std_ReturnType Timer0_Write_16Bit_Value(const Timer0_Type* _Timer , uint16 _Value);
Std_ReturnType Timer0_Read_16Bit_Value(const Timer0_Type* _Timer , uint16 *_Value);
    
#elif TIMER0_REGISTER_CONFIG == _8BIT_CONFIG
Std_ReturnType Timer0_Write_8Bit_Value(const Timer0_Type* _Timer , uint8 _Value);
Std_ReturnType Timer0_Read_8Bit_Value(const Timer0_Type* _Timer , uint8 *_Value);
#endif

/*************************************************/

#endif	/* HAL_TIMER0_H */

