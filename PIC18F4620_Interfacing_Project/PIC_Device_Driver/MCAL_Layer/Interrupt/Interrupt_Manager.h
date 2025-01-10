/* 
 * File:   Interrupt_Manager.h
 * Author: abdo
 *
 * Created on April 13, 2024, 11:16 PM
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

#include "Interrupt_Config.h"

/***************** Macro Declaration ***********/

/**
 * SPI and I2C modes Has the same flags
 * so we use this macro to determine Source of interrupt(From SPI or I2C)
 * Values can Assigned  (  SPI_MODE  or  I2C_MODE)
 */

#define SPI_MODE     0
#define I2C_MODE     1

#define MSSP_MODE          SPI_MODE

/*********** Function Declarations ***************/
/************** External Interrupt ***************/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);
/****************************************************/

/************** Internal Interrupt ***************/

void ADC_ISR(void);

void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void SPI_ISR(void);

void I2C_ISR(void);
void I2C_Bus_Collision_ISR(void);
/*************************************************/
/*************************************************/

#endif	/* INTERRUPT_MANAGER_H */

