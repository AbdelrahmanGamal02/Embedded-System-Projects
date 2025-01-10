/*
 * PWM_Timer0.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef MCAL_LAYER_PWM_TIMER0_PWM_TIMER0_H_
#define MCAL_LAYER_PWM_TIMER0_PWM_TIMER0_H_

/***************** Includes ****************/
#include "../GPIO/GPIO.h"
/*******************************************/

/****************** APIs *********************/
void PWM_Timer0_Start(uint8 Set_duty_cycle);

void PWM_Timer0_Stop(void);
/*********************************************/

#endif /* MCAL_LAYER_PWM_TIMER0_PWM_TIMER0_H_ */
