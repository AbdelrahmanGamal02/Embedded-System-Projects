/* 
 * File:   Ecu_Layer_Init.h
 * Author: abdo
 *
 * Created on February 17, 2024, 1:45 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


/*************** Includes  ***********************/

#include "LED/ECUAL_LED.h"
#include "Push_Buttom/Push_Buttom.h"
#include "Relay/ECUAL_Relay.h"
#include "DC_Motor/DC_Motor.h"
#include "7_Segment/ECU_7_SEGMENT.h"
#include "Character_LCD/Ecu_chr_LCD.h"
#include "Keypad/ECU_Keypad.h"
#include "../MCAL_Layer/Interrupt/External_Interrupt.h"
#include "../MCAL_Layer/Interrupt/Internal_Interrupt.h"
#include "../MCAL_Layer/EEPROM/hal_EEPROM.h"
#include "../MCAL_Layer/ADC/HAL_ADC.h"

/*************************************************/

/************ Data Type Declarations **************/

extern LED_Type LED1;
extern LED_Type LED2;

extern DC_Motor_Type Motor1;
extern DC_Motor_Type Motor2;

extern Chr_LCD_Type _4BIT_LCD;

extern ADC_Configeration_type _adc_1;




/*************************************************/
/*********** Function Declarations ***************/

void Ecu_Layer_Initalization();

/*************************************************/


#endif	/* ECU_LAYER_INIT_H */

