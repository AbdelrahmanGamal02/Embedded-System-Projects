/* 
 * File:   ECUAL_LED.h
 * Author: abdo
 *
 * Created on September 19, 2023, 5:04 PM
 */

#ifndef ECUAL_LED_H
#define	ECUAL_LED_H


/*************** Includes  ***********************/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ECUAL_LED_cfg.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef enum{
    LED_OFF,
    LED_ON 
}LED_State;

typedef struct
{
    uint8 port_name : 3;
    uint8 pin_number: 3;
    uint8 init_state: 1;
    uint8 reversed  : 1;
   
}LED_Type;


/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType Led_Initialization(const LED_Type *LED_cfg);

Std_ReturnType Led_Turn_ON(const LED_Type *LED_cfg);

Std_ReturnType Led_Turn_OFF(const LED_Type *LED_cfg);

Std_ReturnType Led_Turn_TOGGLE(const LED_Type *LED_cfg);


/*************************************************/

#endif	/* ECUAL_LED_H */

