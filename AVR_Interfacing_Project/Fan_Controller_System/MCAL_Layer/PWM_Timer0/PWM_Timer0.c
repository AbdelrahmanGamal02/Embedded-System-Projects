/*
 * PWM_Timer0.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "PWM_Timer0.h"

void PWM_Timer0_Start(uint8 Set_duty_cycle)
{
	TCNT0 = 0;

	OCR0 = (uint8)((Set_duty_cycle * 255) / 100);

	GPIO_PinDirection(PORTB_INDEX , GPIO_PIN3 , GPIO_PIN_DIRECTION_OUTPUT);

	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}

void PWM_Timer0_Stop(void)
{
	/* write 0 on WGM00 and WGM01 to return to normal mode */
	CLEAR_BIT(TCCR0 , 6);
	CLEAR_BIT(TCCR0 , 3);
}
