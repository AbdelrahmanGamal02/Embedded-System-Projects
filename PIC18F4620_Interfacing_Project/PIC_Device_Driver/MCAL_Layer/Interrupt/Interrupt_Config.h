/* 
 * File:   Interrupt_Config.h
 * Author: abdo
 *
 * Created on April 13, 2024, 11:14 PM
 */

#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H


/*************** Includes  ***********************/
#include "../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "Interrupt_Generation_Confg.h"
#include "../GPIO/HAL_GPIO.h"
/*************************************************/
/************** Marcos Declarations **************/

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  1
#define RBx_Interrupt_High_Rising   0
#define RBx_Interrupt_Low_Falling   1

/*************************************************/
/********** Marcos Function Declarations *********/

#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define INTERRUPT_PRIORTY_LEVELS_ENABLE()           (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORTY_LEVELS_DISABLE()          (RCONbits.IPEN = 0)

#define INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE()   (INTCONbits.GIEH = 1)
#define INTERRUPT_HIGH_PRIORTY_INTERRUPT_DISABLE()  (INTCONbits.GIEH = 0)

#define INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE()    (INTCONbits.GIEL = 1)
#define INTERRUPT_LOW_PRIORTY_INTERRUPT_DISABLE()   (INTCONbits.GIEL = 0)

#else

#define INTERRUPT_GLOBAL_INTERRUPT_ENABLE()             (INTCONbits.GIE = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_DISABLE()            (INTCONbits.GIE = 0)

#define INTERRUPT_Preipheral_INTERRUPT_ENABLE()         (INTCONbits.PEIE = 1)
#define INTERRUPT_Preipheral_INTERRUPT_DISABLE()        (INTCONbits.PEIE = 0)

#endif

/*************************************************/
/************ Data Type Declarations **************/

typedef enum{
    
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY,        
}Interrupt_Priority_Type;
        
/*************************************************/
/*********** Function Declarations ***************/




/*************************************************/

#endif	/* INTERRUPT_CONFIG_H */

