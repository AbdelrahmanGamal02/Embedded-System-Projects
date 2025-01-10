/* 
 * File:   DC_Motor.h
 * Author: abdo
 *
 * Created on December 6, 2023, 9:28 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/*************** Includes  ***********************/
#include "DC_Motor_CFG.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

/*************************************************/

/************** Marcos Declarations **************/
#define DC_MOTOR_STATUS_OFF   0x00U
#define DC_MOTOR_STATUS_ON    0x01U

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef struct{
    Pin_Config_Type DC_Motor_Pins[2];
    
}DC_Motor_Type;


/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType DC_Motor_Initialization(const DC_Motor_Type *DC_Motor_cfg);

Std_ReturnType DC_Motor_Move_Right(const DC_Motor_Type *DC_Motor_cfg);

Std_ReturnType DC_Motor_Move_Left(const DC_Motor_Type *DC_Motor_cfg);

Std_ReturnType DC_Motor_Stop(const DC_Motor_Type *DC_Motor_cfg);

/*************************************************/
#endif	/* DC_MOTOR_H */

