/*
 * DC_Motor.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_
#define ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_

/**************** Includes ********************/
#include "../../MCAL_Layer/GPIO/GPIO.h"
#include "../../MCAL_Layer/PWM_Timer0/PWM_Timer0.h"
/********************************************/
/*************** Macros ******************/
#define DC_MOTOR_PORT         PORTB_INDEX
#define DC_MOTOR_PIN1         GPIO_PIN0
#define DC_MOTOR_PIN2         GPIO_PIN1
/********************************************/
/**************** Data Types ****************/
typedef enum
{
	DC_MOTOR_STOP = 0,
	DC_MOTOR_ROTATE_CLOCKWISE,
	DC_MOTOR_ROTATE_ANTICLOCKWISE
}DCMotor_State;
/********************************************/

/***************** APIs **********************/
void DC_Motor_Init(void);

void DC_Motor_Rotate(DCMotor_State State , uint8 Speed);
/********************************************/
#endif /* ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_ */
