/*
 * GPIO.c
 *
 *  Created on: 17/9/2022
 *      Author: Abdelrahman Gamal
 */

#ifndef MCAL_LAYER_GPIO_GPIO_H_
#define MCAL_LAYER_GPIO_GPIO_H_

/*********** Includes ******************/
#include "../Std_Libraries.h"
#include "../Common_Macros.h"
#include "../Std_types.h"
/***************************************/
/************* Macros ******************/
#define NUM_OF_PORTS        4
#define NUM_OF_PINS         8

#define PORTA_INDEX         0
#define PORTB_INDEX         1
#define PORTC_INDEX         2
#define PORTD_INDEX         3

#define GPIO_PIN0           0
#define GPIO_PIN1           1
#define GPIO_PIN2           2
#define GPIO_PIN3           3
#define GPIO_PIN4           4
#define GPIO_PIN5           5
#define GPIO_PIN6           6
#define GPIO_PIN7           7


/****************************************/
/*************** Data Types ************/
typedef enum
{
	GPIO_PIN_DIRECTION_INPUT = 0,
	GPIO_PIN_DIRECTION_OUTPUT
}GPIO_Direction_Type;

typedef enum
{
	GPIO_LOGIC_LOW = 0,
	GPIO_LOGIC_HIGH
}GPIO_PIN_Logic_Type;


/***************************************/
/************** APIs *****************/
void GPIO_PinDirection(uint8 Port_Number , uint8 Pin_number, GPIO_Direction_Type Pin_Direction);

void GPIO_PinWriteLogic(uint8 Port_Number , uint8 Pin_number, GPIO_PIN_Logic_Type Pin_Logic);

uint8 GPIO_PinReadLogic(uint8 Port_Number , uint8 Pin_number);

void GPIO_PortDirection(uint8 Port_Number, GPIO_Direction_Type Pin_Direction);

void GPIO_PORTWriteLogic(uint8 Port_Number , uint8 value);

uint8 GPIO_PortReadLogic(uint8 Port_Number);
/************************************/

#endif /* MCAL_LAYER_GPIO_GPIO_H_ */
