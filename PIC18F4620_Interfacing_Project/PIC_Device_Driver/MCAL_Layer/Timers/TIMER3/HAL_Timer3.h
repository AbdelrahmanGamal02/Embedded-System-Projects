/* 
 * File:   HAL_Timer3.h
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:55 ?
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*************** Includes  ***********************/

#include "../../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../../Interrupt/Internal_Interrupt.h"
#include "../../GPIO/HAL_GPIO.h"

/*************************************************/
/************** Marcos Declarations **************/

/* Timer3 mode */
#define TIMER3_TIMER_MODE_CONFG               0
#define TIMER3_COUNTER_MODE_CONFG             1

/*  Timer3 External Clock Input Synchronization Select  */
#define TIMER3_COUNTER_SYNC_MODE_CONFG        0
#define TIMER3_COUNTER_ASYNC_MODE_CONFG       1


/** pre-scaler configuration */
#define  TIMER3_PRESCALER_VALUE_DIV_BY_1      0     
#define  TIMER3_PRESCALER_VALUE_DIV_BY_2      1     
#define  TIMER3_PRESCALER_VALUE_DIV_BY_4      2     
#define  TIMER3_PRESCALER_VALUE_DIV_BY_8      3     

/* 16-Bit Read/Write Mode */
#define TIMER3_8BIT_REGISTER_CONFG            0
#define TIMER3_16BIT_REGISTER_CONFG           1




/*************************************************/

/********** Marcos Function Declarations *********/

#define TIMER3_DISABLE()                      (T3CONbits.TMR3ON = 0)
#define TIMER3_ENABLE()                       (T3CONbits.TMR3ON = 1)

#define TIMER3_TIMER_MODE()                   (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE()                 (T3CONbits.TMR3CS = 1)

#define TIMER3_COUNTER_SYNC_MODE()            (T3CONbits.T3SYNC = 0)
#define TIMER3_COUNTER_ASYNC_MODE()           (T3CONbits.T3SYNC = 1)


#define TIMER3_PRESCALER_Value(_PRESCALER_)   (T3CONbits.T3CKPS = _PRESCALER_)


#define TIMER3_16BIT_CONFG()                  (T3CONbits.RD16 = 1)
#define TIMER3_8BIT_CONFG()                   (T3CONbits.RD16 = 0)


/*************************************************/


/************ Data Type Declarations **************/



typedef struct
{
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER3_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    uint16 Preload_Value;
    uint8 Timer3_Mode  : 1;
    uint8 Timer3_counter_sync_Mode  : 1;
    uint8 Prescaler_Value  : 2 ;
    uint8 Timer3_16_8_bit_Confg  : 1;
    uint8 Timer3_Reserved : 2;
   
}Timer3_Type;
/*************************************************/


/*********** Function Declarations ***************/

Std_ReturnType Timer3_Initilization(const Timer3_Type* _Timer);
Std_ReturnType Timer3_DeInitilization(const Timer3_Type* _Timer);
Std_ReturnType Timer3_Write_Value(const Timer3_Type* _Timer , uint16 _Value);
Std_ReturnType Timer3_Read_Value(const Timer3_Type* _Timer , uint16 *_Value);
    
/*************************************************/

#endif	/* HAL_TIMER3_H */

