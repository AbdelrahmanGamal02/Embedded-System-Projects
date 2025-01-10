/* 
 * File:   Interrupt_Manager.c
 * Author: abdo
 *
 * Created on April 13, 2024, 11:16 PM
 */

#include "Interrupt_Manager.h"

/********** it is a variable to define and defer between cases *********/
static volatile uint8 RB4_Flag = 1 ,RB5_Flag = 1 ,RB6_Flag = 1 ,RB7_Flag = 1 ;


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

void __interrupt() High_priority_interrupt_Manager(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }
    else{ /* NoThing */ }
}

void __interrupt(low_priority) Low_priority_interrupt_Manager(void)
{
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else{ /* NoThing */ }
}

#else

void __interrupt() interrupt_Manager(void)
{
    /*********** Internal Interrupt PORTB on change ******************/
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{ /* NoThing */ }
    /**************************************************************************/
    
    /*********** External Interrupt PORTB on change ******************/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (1 == RB4_Flag))
    {
        RB4_Flag = 0;
        RB4_ISR(0);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) &&(0 == RB4_Flag))
    {
        RB4_Flag = 1;
        RB4_ISR(1);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (1 == RB5_Flag))
    {
        RB5_Flag = 0;
        RB5_ISR(0);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) &&(0 == RB5_Flag))
    {
        RB5_Flag = 1;
        RB5_ISR(1);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (1 == RB6_Flag))
    {
        RB6_Flag = 0;
        RB6_ISR(0);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW) &&(0 == RB6_Flag))
    {
        RB6_Flag = 1;
        RB6_ISR(1);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (1 == RB7_Flag))
    {
        RB7_Flag = 0;
        RB7_ISR(0);
    } 
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW) &&(0 == RB7_Flag))
    {
        RB7_Flag = 1;
        RB7_ISR(1);
    } 
    else{ /* NoThing */ }
    
    /**************************************************************************/
    /*********** Internal Interrupt ******************/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_TX_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_RX_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE ) && (INTERRUPT_OCCUR == PIR1bits.SSPIF) && (SPI_MODE == MSSP_MODE))
    {
        SPI_ISR();
    }
    else{ /* NoThing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE ) && (INTERRUPT_OCCUR == PIR1bits.SSPIF) && (I2C_MODE == MSSP_MODE))
    {
        I2C_ISR();
    }
    else{ /* NoThing */ }
    
     if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        I2C_Bus_Collision_ISR();
    }
    else{ /* NoThing */ }
    /**************************************************************************/
}


#endif