/*
 * KeyPad.h
 *
 *  Created on: ٠٨‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */


#ifndef ECUAL_LAYER_KEYPAD_KEYPAD_H_
#define ECUAL_LAYER_KEYPAD_KEYPAD_H_

/************* Includes *********************/
#include <util/delay.h>
#include "../../MCAL_Layer/GPIO/GPIO.h"
/*******************************************/
/************* Macros *********************/
#define NOT_PRESSED 0x7f
// Keypad configuration
#define KEYPAD_NUMBER_OF_ROW       4
#define KEYPAD_NUMBER_OF_COLUMN    3

// keypad pin configuration
#define KEYPAD_PORT      	PORTB_INDEX

#define KEYPAD_FIRST_PIN 	GPIO_PIN0
#define KEYPAD_SECOND_PIN 	GPIO_PIN1
#define KEYPAD_THIRD_PIN 	GPIO_PIN2
#define KEYPAD_FOURTH_PIN 	GPIO_PIN3

#define KEYPAD_FIFTH_PIN 	GPIO_PIN4
#define KEYPAD_SIXTH_PIN 	GPIO_PIN5
#define KEYPAD_SEVENTH_PIN 	GPIO_PIN6
#define KEYPAD_EIGHTH_PIN 	GPIO_PIN7



/*******************************************/
/************* APIs *********************/
/*
	Function Name        : keypad_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize the keypad.
*/
void keypad_vInit(void);

/*
	Function Name        : keypad_u8check_press
	Function Returns     : uint8
	Function Arguments   : void
	Function Description : Returns the pressed key or return NOT_PRESSED if no keys are pressed.
*/
uint8 keypad_u8check_press(void);

void DIO_vconnectpullup(uint8 portname ,uint8 pinnumber, uint8 connect_pullup);
/*******************************************/

#endif /* ECUAL_LAYER_KEYPAD_KEYPAD_H_ */
