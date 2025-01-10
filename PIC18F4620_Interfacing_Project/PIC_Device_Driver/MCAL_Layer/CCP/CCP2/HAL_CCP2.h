/* 
 * File:   HAL_CCP2.h
 * Author: win 10-11
 *
 * Created on 14 ?????, 2024, 08:15 ?
 */

#ifndef HAL_CCP2_H
#define	HAL_CCP2_H

/*************** Includes  ***********************/

#include "HAL_CCP2_CONFG.h"
#include "../proc/pic18f4620.h"
#include "../../Std_Types.h"
#include "../../GPIO/HAL_GPIO.h"
#include "../../Interrupt/Internal_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

#define CPP2_MODULE_DISABLE                                  ((uint8)0x00)
#define CPP2_Capture_MODE_EVERY_FALLING_EDGE                 ((uint8)0x04)
#define CPP2_Capture_MODE_EVERY_1TH_RISING_EDGE              ((uint8)0x05)
#define CPP2_Capture_MODE_EVERY_4TH_RISING_EDGE              ((uint8)0x06)
#define CPP2_Capture_MODE_EVERY_16TH_RISING_EDGE             ((uint8)0x07)
#define CPP2_Compare_MODE_TOGGLE_OUTPUT_ON_MATCH             ((uint8)0x02)
#define CPP2_Compare_MODE_PIN_OUTPUT_HIGH_ON_MATCH           ((uint8)0x08)
#define CPP2_Compare_MODE_PIN_OUTPUT_LOW_ON_MATCH            ((uint8)0x09)
#define CPP2_Compare_MODE_SOFT_INTERRUPT_ON_MATCH            ((uint8)0x0A)
#define CPP2_Compare_MODE_TRIGER_SPECIAL_EVENT_ON_MATCH      ((uint8)0x0B)
#define CPP2_PWM_MODE_ENABLE                                 ((uint8)0x0C)

/** TIMER2 post-scaler configuration */
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_1       1     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_2       2     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_3       3 
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_4       4     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_5       5     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_6       6 
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_7       7     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_8       8     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_9       9 
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_10      10     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_11      11     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_12      12 
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_13      13     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_14      14     
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_15      15 
#define  CCP2_TIMER2_POSTSCALER_VALUE_DIV_BY_16      16     
 

/** TIMER2 pre-scaler configuration */
#define  CCP2_TIMER2_PRESCALER_VALUE_DIV_BY_1        1     
#define  CCP2_TIMER2_PRESCALER_VALUE_DIV_BY_4        2     
#define  CCP2_TIMER2_PRESCALER_VALUE_DIV_BY_16       3

#define CAPTURE_IS_READY             1
#define CAPTURE_IS_NOT_READY         0

#define COMPARE_IS_READY             1
#define COMPARE_IS_NOT_READY         0


/*************************************************/

/********** Marcos Function Declarations *********/

#define CPP2_CONFG_SET(_CONFG_)          (CCP2CONbits.CCP2M = _CONFG_)

/*************************************************/

/************ Data Type Declarations **************/

typedef enum{
    CPP2_CAPTURE_MODE = 0,
    CPP2_COMPARE_MODE ,
    CPP2_PWM_MODE         
}CCP2_Mode_t;

typedef enum{
    CCP2_TMR1_TWO_CCP_MODULES = 0,
    CCP2_TMR3_CCP2_TMR1_CCP1,
    CCP2_TMR3_TWO_CCP_MODULES,       
}CCP2_CaptureMode_Timer_Confg_t;

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
}CCP2_Reg_Confg_t;

typedef struct
{
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* CPP2_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    
    CCP2_Mode_t CCP2_Mode;
    uint8 CCP2_Mode_Variant;
    Pin_Config_Type CCP2_pin;

#if ((CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT) || (CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT))
    CCP2_CaptureMode_Timer_Confg_t Timer_Confg;
#endif 
    
#if CPP2_PWM_MODE_SELECTED == CPP2_MODE_SELECT
    uint32 PWM_Frequency;
    uint8  Timer2_Prescaler_Value  : 2 ;
    uint8  Timer2_Postscaler_Value  : 4 ;
#endif   
    
    
}CCP2_Type;

/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType CCP2_Initilization(const CCP2_Type* _CCP2);
Std_ReturnType CCP2_DeInitilization(const CCP2_Type* _CCP2);

#if CPP2_CAPTURE_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType IS_CPP2_CAPTURE_MODE_READY(uint8 *Capture_Status);
Std_ReturnType CPP2_CAPTURE_MODE_Read_Value(const CCP2_Type* _CCP2 , uint16 *_Value);
#endif
    
#if CPP2_COMPARE_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType IS_CPP2_COMPARE_MODE_READY(uint8 *Compare_Status);
Std_ReturnType CPP2_COMPARE_MODE_Write_Value(const CCP2_Type* _CCP2 , uint16 _Value);
#endif

#if CPP2_PWM_MODE_SELECTED == CPP2_MODE_SELECT
Std_ReturnType CCP2_PWM_Duty_Cycle(const CCP2_Type* _CCP2 , uint8 duty_cycle);
Std_ReturnType CPP2_PWM_MODE_START(void);
Std_ReturnType CPP2_PWM_MODE_STOP(void);
#endif


/*************************************************/

#endif	/* HAL_CCP2_H */

