/*
 * ADC.c
 *
 *  Created on: ٠٢‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "ADC.h"

void ADC_Init(ADC_ConfigType* ADC_Config)
{
	if(NULL == ADC_Config)
	{
		/* Nothing */
	}
	else
	{
		ADMUX |= ((ADC_Config->Ref_Voltage) << 6); // To put value in pin 6 and pin 7
		SET_BIT(ADCSRA , 7);
		ADCSRA |= (ADC_Config->prescaler);
#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_ENABLE
		SET_BIT(ADCSRA , 3);
#endif
	}
}

uint16 ADC_ReadValue(uint8 channal)
{

	ADMUX &= 0xE0;
	ADMUX |= channal;
	SET_BIT(ADCSRA , 6);
	while(BIT_IS_CLEAR(ADCSRA , 4));
	SET_BIT(ADCSRA , 4);
	return ADC;
}

#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_ENABLE
void ADC_ReadValue_with_interrupt(uint8 channal)
{
	ADMUX &= 0xE0;
	ADMUX |= channal;
	SET_BIT(ADCSRA , 6);
}
#endif



