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
#include "../MCAL_Layer/Timers/TIMER0/Hal_Timer0.h"
#include "../MCAL_Layer/Timers/TIMER1/HAL_Timer1.h"
#include "../MCAL_Layer/Timers/TIMER2/HAL_Timer2.h"
#include "../MCAL_Layer/Timers/TIMER3/HAL_Timer3.h"
#include "../MCAL_Layer/CCP/CCP1/HAL_CCP1.h"
#include "../MCAL_Layer/CCP/CCP2/HAL_CCP2.h"
#include "../MCAL_Layer/HAL_USART/HAL_USART.h"
#include "../MCAL_Layer/HAL_SPI/HAL_SPI.h"
#include "../MCAL_Layer/HAL_I2C/HAL_I2C.h"


/*************************************************/

/************ Data Type Declarations **************/

extern LED_Type Admin_Led;
extern LED_Type Guest_Led;
extern LED_Type Block_Led;

extern Chr_LCD_Type LCD;

extern Keypad_Type Keypad;

extern MSSP_SPI_Type Spi;

extern Pin_Config_Type Spi_SS;

/*************************************************/
/*********** Function Declarations ***************/

void Ecu_Layer_Initalization();

void _interrupt_handler(void);
/*************************************************/


#endif	/* ECU_LAYER_INIT_H */

