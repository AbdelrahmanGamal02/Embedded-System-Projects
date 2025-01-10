/*
 * KeyPad.c
 *
 *  Created on: ٠٨‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */


#include "KeyPad.h"


uint8 arr[KEYPAD_NUMBER_OF_ROW][KEYPAD_NUMBER_OF_COLUMN]={
			{1 , 2 , 3},
			{4 , 5 , 6},
			{7 , 8 , 9},
			{'*', 0 ,'#'}
}; //keypad buttons

void keypad_vInit(void)
{
	/* Initialize first four bits in keypad as output pins */
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_FIRST_PIN,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_SECOND_PIN,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_THIRD_PIN,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_FOURTH_PIN,GPIO_PIN_DIRECTION_OUTPUT);
	/******************************************************/
	/* initialize second four bits in keypad as input pins */
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_FIFTH_PIN,GPIO_PIN_DIRECTION_INPUT);
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_SIXTH_PIN,GPIO_PIN_DIRECTION_INPUT);
	GPIO_PinDirection(KEYPAD_PORT,KEYPAD_SEVENTH_PIN,GPIO_PIN_DIRECTION_INPUT);
	//GPIO_PinDirection(KEYPAD_PORT,KEYPAD_EIGHTH_PIN,GPIO_PIN_DIRECTION_INPUT);
	/*****************************************************/

}
uint8 keypad_u8check_press(void)
{
    uint8 key_pressed = 0x7F;
	uint8 row; //which indicate the given output  pin
	uint8 coloumn; //which indicate the given input pin

	for(row=0;row<4;row++)
	{
		/*stop the work of keypad firstly*/
		GPIO_PinWriteLogic(KEYPAD_PORT,KEYPAD_FIRST_PIN,GPIO_LOGIC_HIGH);
		GPIO_PinWriteLogic(KEYPAD_PORT,KEYPAD_SECOND_PIN,GPIO_LOGIC_HIGH);
		GPIO_PinWriteLogic(KEYPAD_PORT,KEYPAD_THIRD_PIN,GPIO_LOGIC_HIGH);
		GPIO_PinWriteLogic(KEYPAD_PORT,KEYPAD_FOURTH_PIN,GPIO_LOGIC_HIGH);
		/*************************************/
        _delay_ms(20);
		GPIO_PinWriteLogic(KEYPAD_PORT,row,GPIO_LOGIC_LOW);//write 0 to the first pin in keypad (output pin from MC)

		for(coloumn=0;coloumn<3;coloumn++)
		{
			if(GPIO_PinReadLogic(KEYPAD_PORT,(coloumn+KEYPAD_FIFTH_PIN)) == 0) // read the input pins of MC which connected to keypad
			{
                // debouncing of keys
                _delay_ms(10);
                if(GPIO_PinReadLogic(KEYPAD_PORT,(coloumn+KEYPAD_FIFTH_PIN)) == 0)
                {
                    key_pressed =  arr[row][coloumn]; //put the selected pressed key to the retrurnval
                    break;
                }
            }
		}
	}
    return key_pressed;
}
