/* 
 * File:   HAL_CCP1.h
 * Author: win 10-11
 *
 * Created on 13 ?????, 2024, 09:21 ?
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*************** Includes  ***********************/

#include "HAL_CCP1_CFG.h"
#include "../proc/pic18f4620.h"
#include "../../Std_Types.h"
#include "../../GPIO/HAL_GPIO.h"
#include "../../Interrupt/Internal_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

#define CPP1_MODULE_DISABLE                                  ((uint8)0x00)
#define CPP1_Capture_MODE_EVERY_FALLING_EDGE                 ((uint8)0x04)
#define CPP1_Capture_MODE_EVERY_1TH_RISING_EDGE              ((uint8)0x05)
#define CPP1_Capture_MODE_EVERY_4TH_RISING_EDGE              ((uint8)0x06)
#define CPP1_Capture_MODE_EVERY_16TH_RISING_EDGE             ((uint8)0x07)
#define CPP1_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH             ((uint8)0x02)
#define CPP1_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH           ((uint8)0x08)
#define CPP1_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH            ((uint8)0x09)
#define CPP1_Compare_MODE_SOFT_INTERRUPT_ON_MATCH            ((uint8)0x0A)
#define CPP1_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH      ((uint8)0x0B)
#define CPP1_PWM_MODE_ENABLE                                 ((uint8)0x0C)

/** TIMER2 post-scaler configuration */
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_1       1     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_2       2     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_3       3 
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_4       4     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_5       5     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_6       6 
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_7       7     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_8       8     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_9       9 
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_10      10     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_11      11     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_12      12 
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_13      13     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_14      14     
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_15      15 
#define  CCP1_TIMER2_POSTSCALER_VALUE_DIV_BY_16      16     
 

/** TIMER2 pre-scaler configuration */
#define  CCP1_TIMER2_PRESCALER_VALUE_DIV_BY_1        1     
#define  CCP1_TIMER2_PRESCALER_VALUE_DIV_BY_4        2     
#define  CCP1_TIMER2_PRESCALER_VALUE_DIV_BY_16       3

#define CAPTURE_IS_READY             1
#define CAPTURE_IS_NOT_READY         0

#define COMPARE_IS_READY             1
#define COMPARE_IS_NOT_READY         0


/*************************************************/

/********** Marcos Function Declarations *********/

#define CPP1_CONFG_SET(_CONFG_)          (CCP1CONbits.CCP1M = _CONFG_)

/*************************************************/

/************ Data Type Declarations **************/

typedef enum{
    CPP1_CAPTURE_MODE = 0,
    CPP1_COMPARE_MODE ,
    CPP1_PWM_MODE         
}CCP1_Mode_t;

typedef enum{
    CCP1_TMR1_TWO_CCP_MODULES = 0,
    CCP1_TMR3_CCP2_TMR1_CCP1,
    CCP1_TMR3_TWO_CCP_MODULES,       
}CCP1_CaptureMode_Timer_Confg_t;

typedef union
{
    struct
    {
        uint8 _8bit_reg_low_value;
        uint8 _8bit_reg_high_value;
    };
    struct
    {
        uint16 _16bit_reg_value;
    };
}CCP1_Reg_Confg_t;

typedef struct
{
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* CPP1_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    
    CCP1_Mode_t CCP1_Mode;
    uint8 CCP1_Mode_Variant;
    Pin_Config_Type CCP1_pin;

#if ((CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT) || (CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT))
    CCP1_CaptureMode_Timer_Confg_t Timer_Confg;
#endif 
    
#if CPP1_PWM_MODE_SELECTED == CPP1_MODE_SELECT
    uint32 PWM_Frequency;
    uint8  Timer2_Prescaler_Value  : 2 ;
    uint8  Timer2_Postscaler_Value  : 4 ;
#endif   
    
    
}CCP1_Type;

/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType CCP1_Initilization(const CCP1_Type* _CCP1);
Std_ReturnType CCP1_DeInitilization(const CCP1_Type* _CCP1);

#if CPP1_CAPTURE_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType IS_CPP1_CAPTURE_MODE_READY(uint8 *Capture_Status);
Std_ReturnType CPP1_CAPTURE_MODE_Read_Value(const CCP1_Type* _CCP1 , uint16 *_Value);
#endif
    
#if CPP1_COMPARE_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType IS_CPP1_COMPARE_MODE_READY(uint8 *Compare_Status);
Std_ReturnType CPP1_COMPARE_MODE_Write_Value(const CCP1_Type* _CCP1 , uint16 _Value);
#endif

#if CPP1_PWM_MODE_SELECTED == CPP1_MODE_SELECT
Std_ReturnType CCP1_PWM_Duty_Cycle(const CCP1_Type* _CCP1 , uint8 duty_cycle);
Std_ReturnType CPP1_PWM_MODE_START(void);
Std_ReturnType CPP1_PWM_MODE_STOP(void);
#endif


/*************************************************/

#endif	/* HAL_CCP1_H */

