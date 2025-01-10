/* 
 * File:   HAL_Timer2.h
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:54 ?
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*************** Includes  ***********************/

#include "../../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../../Interrupt/Internal_Interrupt.h"
#include "../../GPIO/HAL_GPIO.h"

/*************************************************/
/************** Marcos Declarations **************/

/** post-scaler configuration */
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_1       0     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_2       1     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_3       2 
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_4       3     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_5       4     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_6       5 
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_7       6     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_8       7     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_9       8 
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_10      9     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_11      10     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_12      11 
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_13      12     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_14      13     
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_15      14 
#define  TIMER2_POSTSCALER_VALUE_DIV_BY_16      15     
 

/** pre-scaler configuration */
#define  TIMER2_PRESCALER_VALUE_DIV_BY_1       0     
#define  TIMER2_PRESCALER_VALUE_DIV_BY_4       1     
#define  TIMER2_PRESCALER_VALUE_DIV_BY_16      2     

/*************************************************/

/********** Marcos Function Declarations *********/

#define TIMER2_DISABLE()                      (T2CONbits.TMR2ON = 0)
#define TIMER2_ENABLE()                       (T2CONbits.TMR2ON = 1)


#define TIMER2_PRESCALER_Value(_PRESCALER_)   (T2CONbits.T2CKPS = _PRESCALER_)

#define TIMER2_POSTSCALER_Value(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)

/*************************************************/


/************ Data Type Declarations **************/



typedef struct
{
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    uint8 Preload_Value;
    uint8 Prescaler_Value  : 2 ;
    uint8 Postscaler_Value  : 4 ;
    uint8 Timer2_Reserved : 2;
   
}Timer2_Type;
/*************************************************/


/*********** Function Declarations ***************/

Std_ReturnType Timer2_Initilization(const Timer2_Type* _Timer);
Std_ReturnType Timer2_DeInitilization(const Timer2_Type* _Timer);
Std_ReturnType Timer2_Write_Value(const Timer2_Type* _Timer , uint8 _Value);
Std_ReturnType Timer2_Read_Value(const Timer2_Type* _Timer , uint8 *_Value);
    
/*************************************************/

#endif	/* HAL_TIMER2_H */

