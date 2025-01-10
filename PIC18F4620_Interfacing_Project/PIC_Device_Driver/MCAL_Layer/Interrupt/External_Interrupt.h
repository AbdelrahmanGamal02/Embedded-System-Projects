/* 
 * File:   External_Interrupt.h
 * Author: abdo
 *
 * Created on April 13, 2024, 11:15 PM
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H

#include "Interrupt_Config.h"

/************** Marcos Declarations **************/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == EXTERNAL_FEATURE_ENABLE

#define Ext_INT0_INTERRUPT_Clear_FLAG()                (INTCONbits.INT0IF = 0)
#define Ext_INT0_INTERRUPT_ENABLE()                    (INTCONbits.INT0IE = 1)
#define Ext_INT0_INTERRUPT_DISABLE()                   (INTCONbits.INT0IE = 0)
#define Ext_INT0_INTERRUPT_Rising_Edge_Select()        (INTCON2bits.INTEDG0 = 1)
#define Ext_INT0_INTERRUPT_Falling_Edge_Select()       (INTCON2bits.INTEDG0 = 0)

#define Ext_INT1_INTERRUPT_Clear_FLAG()                (INTCON3bits.INT1IF = 0 )
#define Ext_INT1_INTERRUPT_ENABLE()                    (INTCON3bits.INT1IE = 1)
#define Ext_INT1_INTERRUPT_DISABLE()                   (INTCON3bits.INT1IE = 0)
#define Ext_INT1_INTERRUPT_Rising_Edge_Select()        (INTCON2bits.INTEDG1 = 1)
#define Ext_INT1_INTERRUPT_Falling_Edge_Select()       (INTCON2bits.INTEDG1 = 0)

#define Ext_INT2_INTERRUPT_Clear_FLAG()                (INTCON3bits.INT2IF = 0)
#define Ext_INT2_INTERRUPT_ENABLE()                    (INTCON3bits.INT2IE = 1)
#define Ext_INT2_INTERRUPT_DISABLE()                   (INTCON3bits.INT2IE = 0)
#define Ext_INT2_INTERRUPT_Rising_Edge_Select()        (INTCON2bits.INTEDG2 = 1)
#define Ext_INT2_INTERRUPT_Falling_Edge_Select()       (INTCON2bits.INTEDG2 = 0)



#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define Ext_INT1_INTERRUPT_High_Priority()          (INTCON3bits.INT1IP = 1)
#define Ext_INT1_INTERRUPT_LOW_Priority()           (INTCON3bits.INT1IP = 0)

#define Ext_INT2_INTERRUPT_High_Priority()          (INTCON3bits.INT2IP = 1)
#define Ext_INT2_INTERRUPT_LOW_Priority()           (INTCON3bits.INT2IP = 0)

#endif

#endif

#if EXTERNAL_INTERRUPT_onChange_FEATURE_ENABLE == EXTERNAL_FEATURE_ENABLE

#define Ext_PORTB_onChange_INTERRUPT_Clear_FLAG()      (INTCONbits.RBIF = 0)

#define Ext_PORTB_onChange_INTERRUPT_ENABLE()          (INTCONbits.RBIE = 1)
#define Ext_PORTB_onChange_INTERRUPT_DISABLE()         (INTCONbits.RBIE = 0)

#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define Ext_PORTB_onChange_High_Priority()          (INTCON2bits.RBIP = 1)
#define Ext_PORTB_onChange_LOW_Priority()           (INTCON2bits.RBIP = 0)

#endif

#endif

/*************************************************/
/************ Data Type Declarations **************/

typedef void (* Interrupt_Handler) (void);

typedef enum{
    
    INTERRUPT_FALLING_Edge = 0,
    INTERRUPT_RISING_Edge   
}EXTInterrupt_Edge_Type;

typedef enum{
    
    EXTINTERRUPT_INT0 = 0,
    EXTINTERRUPT_INT1,
    EXTINTERRUPT_INT2                   
}EXTInterrupt_Source_Type;

typedef struct{
    void (* Ext_Interrupt_Handler) (void);
    Pin_Config_Type Interrupt_Pins;
    EXTInterrupt_Edge_Type Edge;
    EXTInterrupt_Source_Type Source;
    #if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
    #endif

}EXTInterrupt_INTx_Type;

typedef struct{
    void (* Interrupt_Handler_LOW) (void);
    void (* Interrupt_Handler_HIGH) (void);
    Pin_Config_Type Interrupt_Pins;
    #if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
    #endif
    
}EXTInterrupt_PBx_Type;
/*************************************************/
/*********** Function Declarations ***************/
Std_ReturnType Ext_Interrupt_INTx_Initilization(const EXTInterrupt_INTx_Type* Int_Obj);
Std_ReturnType Ext_Interrupt_INTx_deInitilization(const EXTInterrupt_INTx_Type* Int_Obj);

Std_ReturnType Ext_Interrupt_PBx_Initilization(const EXTInterrupt_PBx_Type* Int_Obj);
Std_ReturnType Ext_Interrupt_PBx_deInitilization(const EXTInterrupt_PBx_Type* Int_Obj);
/*************************************************/
#endif	/* EXTERNAL_INTERRUPT_H */

