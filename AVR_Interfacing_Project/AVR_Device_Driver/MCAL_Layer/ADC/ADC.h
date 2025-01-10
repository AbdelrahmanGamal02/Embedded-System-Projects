/*
 * ADC.h
 *
 *  Created on: ٠٢‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef MCAL_LAYER_ADC_ADC_H_
#define MCAL_LAYER_ADC_ADC_H_

/*********** Includes ******************/
#include "../GPIO/GPIO.h"
#include "util/delay.h"
/***************************************/
/************* Macros ******************/
#define ADC_INTERRUPT_ENABLE      0x01
#define ADC_INTERRUPT_DISABLE     0x00

#define ADC_INTERRUPT_FEATURE     ADC_INTERRUPT_DISABLE

#define MAX_OF_VALUE       1023
#define MAX_VOLTAGE        2.56
#define CHANNAL_NUMBERS    8
/****************************************/
/*************** Data Types ************/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
}ADC_Channel_Select_Type;

typedef enum
{
	ADC_AREF_Reference_Voltage0V_5V,
	ADC_AVCC_Reference_Voltage_5V,
	ADC_INTERNAL_Reference_Voltage = 3, // Internal voltage = 2.56V
}ADC_ReferenceVoltage;

typedef enum
{
	ADC_Prescaler_DIV_2 = 1,
	ADC_Prescaler_DIV_4,
	ADC_Prescaler_DIV_8,
	ADC_Prescaler_DIV_16,
	ADC_Prescaler_DIV_32,
	ADC_Prescaler_DIV_64,
	ADC_Prescaler_DIV_128
}ADC_Prescaler;

typedef struct
{
	ADC_ReferenceVoltage Ref_Voltage;
	ADC_Prescaler prescaler;
}ADC_ConfigType;


/***************************************/
/************** APIs *****************/

void ADC_Init(ADC_ConfigType* ADC_Config);
uint16 ADC_ReadValue(uint8 channal);
void ADC_ReadValue_with_interrupt(uint8 channal);

/************************************/


#endif /* MCAL_LAYER_ADC_ADC_H_ */
