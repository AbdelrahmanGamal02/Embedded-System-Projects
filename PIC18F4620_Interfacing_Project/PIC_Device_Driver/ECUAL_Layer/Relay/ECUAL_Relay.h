/* 
 * File:   ECUAL_Relay.h
 * Author: abdo
 *
 * Created on November 16, 2023, 9:25 PM
 */

#ifndef ECUAL_RELAY_H
#define	ECUAL_RELAY_H

/*************** Includes  ***********************/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ECUAL_Relay_cfg.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef enum{
    RELAY_OFF,
    RELAY_ON
}Relay_State;

typedef struct
{
    uint8 port_name : 4;
    uint8 pin_number: 3;
    Relay_State Relay_state;
    
}Relay_Type;


/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType Relay_Initialization(const Relay_Type *Relay_cfg);

Std_ReturnType Relay_Turn_ON(const Relay_Type *Relay_cfg);

Std_ReturnType Relay_Turn_OFF(const Relay_Type *Relay_cfg);


/*************************************************/

#endif	/* ECUAL_RELAY_H */

