/* 
 * File:   Internal_Interrupt.h
 * Author: abdo
 *
 * Created on April 13, 2024, 11:15 PM
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

/*************** Includes  ***********************/
#include "Interrupt_Config.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/

/********** Marcos Function Declarations *********/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_Clear_FLAG()   (PIR1bits.ADIF = 0)

#define ADC_INTERRUPT_ENABLE()       (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()      (PIE1bits.ADIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define ADC_INTERRUPT_HIGH_Priority()    (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_LOW_Priority()     (IPR1bits.ADIP = 0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_CLEAR_FLAG()   (INTCONbits.TMR0IF = 0)

#define TIMER0_INTERRUPT_ENABLE()       (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()      (INTCONbits.TMR0IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define TIMER0_INTERRUPT_HIGH_Priority()    (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_Priority()     (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_CLEAR_FLAG()   (PIR1bits.TMR1IF = 0)

#define TIMER1_INTERRUPT_ENABLE()       (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()      (PIE1bits.TMR1IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define TIMER1_INTERRUPT_HIGH_Priority()    (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_LOW_Priority()     (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER2_INTERRUPT_CLEAR_FLAG()   (PIR1bits.TMR2IF = 0)

#define TIMER2_INTERRUPT_ENABLE()       (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()      (PIE1bits.TMR2IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define TIMER2_INTERRUPT_HIGH_Priority()    (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_LOW_Priority()     (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER3_INTERRUPT_CLEAR_FLAG()   (PIR2bits.TMR3IF = 0)

#define TIMER3_INTERRUPT_ENABLE()       (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()      (PIE2bits.TMR3IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define TIMER3_INTERRUPT_HIGH_Priority()    (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_LOW_Priority()     (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_CLEAR_FLAG()   (PIR1bits.CCP1IF = 0)

#define CCP1_INTERRUPT_ENABLE()       (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()      (PIE1bits.CCP1IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define CCP1_INTERRUPT_HIGH_Priority()    (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_LOW_Priority()     (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define CCP2_INTERRUPT_CLEAR_FLAG()   (PIR2bits.CCP2IF = 0)

#define CCP2_INTERRUPT_ENABLE()       (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()      (PIE2bits.CCP2IE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define CCP2_INTERRUPT_HIGH_Priority()    (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_LOW_Priority()     (IPR2bits.CCP2IP = 0)
#endif
#endif

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_ENABLE()       (PIE1bits.TXIE = 1)
#define EUSART_TX_INTERRUPT_DISABLE()      (PIE1bits.TXIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_HIGH_Priority()    (IPR1bits.TXIP = 1)
#define EUSART_TX_INTERRUPT_LOW_Priority()     (IPR1bits.TXIP = 0)
#endif
#endif

#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define EUSART_RX_INTERRUPT_ENABLE()       (PIE1bits.RCIE = 1)
#define EUSART_RX_INTERRUPT_DISABLE()      (PIE1bits.RCIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define EUSART_RX_INTERRUPT_HIGH_Priority()    (IPR1bits.RCIP = 1)
#define EUSART_RX_INTERRUPT_LOW_Priority()     (IPR1bits.RCIP = 0)
#endif
#endif

#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_SPI_INTERRUPT_CLEAR_FLAG()   (PIR1bits.SSPIF = 0)

#define MSSP_SPI_INTERRUPT_ENABLE()       (PIE1bits.SSPIE = 1)
#define MSSP_SPI_INTERRUPT_DISABLE()      (PIE1bits.SSPIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define MSSP_SPI_INTERRUPT_HIGH_Priority()    (IPR1bits.SSPIP = 1)
#define MSSP_SPI_INTERRUPT_LOW_Priority()     (IPR1bits.SSPIP = 0)
#endif
#endif

/*****************************************************************************/
#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_CLEAR_FLAG()   (PIR1bits.SSPIF = 0)

#define MSSP_I2C_INTERRUPT_ENABLE()       (PIE1bits.SSPIE = 1)
#define MSSP_I2C_INTERRUPT_DISABLE()      (PIE1bits.SSPIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_HIGH_Priority()    (IPR1bits.SSPIP = 1)
#define MSSP_I2C_INTERRUPT_LOW_Priority()     (IPR1bits.SSPIP = 0)
#endif
#endif

#if MSSP_I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG()   (PIR2bits.BCLIF = 0)

#define MSSP_I2C_BUS_COLLISION_INTERRUPT_ENABLE()       (PIE2bits.BCLIE = 1)
#define MSSP_I2C_BUS_COLLISION_INTERRUPT_DISABLE()      (PIE2bits.BCLIE = 0)


#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE

#define MSSP_I2C_BUS_COLLISION_INTERRUPT_HIGH_Priority()    (IPR2bits.BCLIP = 1)
#define MSSP_I2C_BUS_COLLISION_INTERRUPT_LOW_Priority()     (IPR2bits.BCLIP = 0)
#endif
#endif
/*************************************************/

#endif	/* INTERNAL_INTERRUPT_H */

