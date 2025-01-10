/* 
 * File:   HAL_Timer1.h
 * Author: win 10-11
 *
 * Created on 04 ?????, 2024, 08:52 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*************** Includes  ***********************/

#include "../../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../../Interrupt/Internal_Interrupt.h"
#include "../../GPIO/HAL_GPIO.h"

/*************************************************/
/************** Marcos Declarations **************/

/* Timer1 mode */
#define TIMER1_TIMER_MODE_CONFG               0
#define TIMER1_COUNTER_MODE_CONFG             1

/*  Timer1 External Clock Input Synchronization Select  */
#define TIMER1_COUNTER_SYNC_MODE_CONFG        0
#define TIMER1_COUNTER_ASYNC_MODE_CONFG       1

/* Timer1 Oscillator Enable */
#define  TIMER1_OSC_DISABLE_CONFG             0
#define  TIMER1_OSC_ENABLE_CONFG              1

/** pre-scaler configuration */
#define  TIMER1_PRESCALER_VALUE_DIV_BY_1      0     
#define  TIMER1_PRESCALER_VALUE_DIV_BY_2      1     
#define  TIMER1_PRESCALER_VALUE_DIV_BY_4      2     
#define  TIMER1_PRESCALER_VALUE_DIV_BY_8      3     

/* 16-Bit Read/Write Mode */
#define TIMER1_8BIT_REGISTER_CONFG            0
#define TIMER1_16BIT_REGISTER_CONFG           1




/*************************************************/

/********** Marcos Function Declarations *********/

#define TIMER1_DISABLE()                      (T1CONbits.TMR1ON = 0)
#define TIMER1_ENABLE()                       (T1CONbits.TMR1ON = 1)

#define TIMER1_TIMER_MODE()                   (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE()                 (T1CONbits.TMR1CS = 1)

#define TIMER1_COUNTER_SYNC_MODE()            (T1CONbits.T1SYNC = 0)
#define TIMER1_COUNTER_ASYNC_MODE()           (T1CONbits.T1SYNC = 1)

#define TIMER1_OSC_CONFG_DISABLE()            (T1CONbits.T1OSCEN = 0)
#define TIMER1_OSC_CONFG_ENABLE()             (T1CONbits.T1OSCEN = 1)


#define TIMER1_PRESCALER_Value(_PRESCALER_)   (T1CONbits.T1CKPS = _PRESCALER_)


#define Timer1_System_Clock_Status()           (T1CONbits.T1RUN)

#define TIMER1_16BIT_CONFG()                  (T1CONbits.RD16 = 1)
#define TIMER1_8BIT_CONFG()                   (T1CONbits.RD16 = 0)


/*************************************************/


/************ Data Type Declarations **************/



typedef struct
{
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif
    uint16 Preload_Value;
    uint8 Timer1_Mode  : 1;
    uint8 Timer1_counter_sync_Mode  : 1;
    uint8 Timer1_OSC_Confg  : 1;
    uint8 Prescaler_Value  : 2 ;
    uint8 Timer1_16_8_bit_Confg  : 1;
    uint8 Timer1_Reserved : 2;
   
}Timer1_Type;
/*************************************************/


/*********** Function Declarations ***************/

Std_ReturnType Timer1_Initilization(const Timer1_Type* _Timer);
Std_ReturnType Timer1_DeInitilization(const Timer1_Type* _Timer);

Std_ReturnType Timer1_Write_Value(const Timer1_Type* _Timer , uint16 _Value);
Std_ReturnType Timer1_Read_Value(const Timer1_Type* _Timer , uint16 *_Value);
    
/*************************************************/

#endif	/* HAL_TIMER1_H */

