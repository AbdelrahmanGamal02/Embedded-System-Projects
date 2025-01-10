/*
 * _7_Segment.h
 *
 *  Created on: ٠٨‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER__7_SEGMENT__7_SEGMENT_H_
#define ECUAL_LAYER__7_SEGMENT__7_SEGMENT_H_

/************* Includes *********************/
#include "../../MCAL_Layer/GPIO/GPIO.h"
/*******************************************/
/************* Macros *********************/
// 7 Segment configuration
#define _7_SEGMENT_WITH_DECODER       0
#define _7_SEGMENT_WITHOUT_DECODER    1

#define _7_SEGMENT_CONNECTION        _7_SEGMENT_WITHOUT_DECODER

#define _7_SEGMENT_COMMON_CATHODE       0
#define _7_SEGMENT_COMMON_ANODE    		1

#define _7_SEGMENT_TYPE        _7_SEGMENT_COMMON_CATHODE
// keypad pin configuration
#define _7_SEGMENT_PORT      	PORTC_INDEX

#if _7_SEGMENT_CONNECTION == _7_SEGMENT_WITHOUT_DECODER
#define _7_SEGMENT_FIRST_PIN 	GPIO_PIN0
#define _7_SEGMENT_SECOND_PIN 	GPIO_PIN1
#define _7_SEGMENT_THIRD_PIN 	GPIO_PIN2
#define _7_SEGMENT_FOURTH_PIN 	GPIO_PIN3

#define _7_SEGMENT_FIFTH_PIN 	GPIO_PIN4
#define _7_SEGMENT_SIXTH_PIN 	GPIO_PIN5
#define _7_SEGMENT_SEVENTH_PIN 	GPIO_PIN6

#elif _7_SEGMENT_CONNECTION == _7_SEGMENT_WITH_DECODER
#define _7_SEGMENT_FIRST_PIN 	GPIO_PIN0
#define _7_SEGMENT_SECOND_PIN 	GPIO_PIN1
#define _7_SEGMENT_THIRD_PIN 	GPIO_PIN2
#define _7_SEGMENT_FOURTH_PIN 	GPIO_PIN3

#endif


/*******************************************/
/************* APIs *********************/
/*
	Function Name        : _7_SEGMENT_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize the _7_SEGMENT.
*/
void _7_SEGMENT_vInit(void);

/*
	Function Name        : _7_SEGMENT_Write_Number_without_decoder
	Function Returns     : void
	Function Arguments   : uint8 number
	Function Description : Display number on 7 segment without decoder
*/
#if _7_SEGMENT_CONNECTION == _7_SEGMENT_WITHOUT_DECODER
void _7_SEGMENT_Write_Number_without_decoder(uint8 number);
#endif

/*
	Function Name        : _7_SEGMENT_Write_Number_without_decoder
	Function Returns     : void
	Function Arguments   : uint8 number
	Function Description : Display number on 7 segment using decoder
*/
#if _7_SEGMENT_CONNECTION == _7_SEGMENT_WITH_DECODER
void _7_SEGMENT_Write_Number_with_decoder(uint8 number);
#endif

/*******************************************/

#endif /* ECUAL_LAYER__7_SEGMENT__7_SEGMENT_H_ */
