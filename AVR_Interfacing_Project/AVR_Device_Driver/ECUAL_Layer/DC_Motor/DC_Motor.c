/*
 * DC_Motor.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "DC_Motor.h"

void DC_Motor_Init(void)
{
	GPIO_PinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_PIN_DIRECTION_OUTPUT);

	GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
	GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_LOW);
}

void DC_Motor_Rotate(DCMotor_State State , uint8 Speed)
{
	if(DC_MOTOR_ROTATE_CLOCKWISE == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_HIGH);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_LOW);

		PWM_Timer0_Start(Speed);
	}
	else if(DC_MOTOR_ROTATE_ANTICLOCKWISE == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_HIGH);

		PWM_Timer0_Start(Speed);
	}
	else if(DC_MOTOR_STOP == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_HIGH);

		PWM_Timer0_Stop();
	}
	else { /* Nothing */ }

}
