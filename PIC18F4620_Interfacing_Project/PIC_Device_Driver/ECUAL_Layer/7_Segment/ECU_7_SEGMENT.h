/* 
 * File:   ECU_7_SEGMENT.h
 * Author: abdo
 *
 * Created on February 12, 2024, 10:55 AM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H


/*************** Includes  ***********************/
#include "ECU_7_SEGMENT_cfg.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

/*************************************************/

/************** Marcos Declarations **************/

#define _7_SEGMENT_PIN0    0
#define _7_SEGMENT_PIN1    1
#define _7_SEGMENT_PIN2    2
#define _7_SEGMENT_PIN3    3


/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE        
}Segment_Type_t;

typedef struct
{
    Pin_Config_Type Segment_Pins[4];
    Segment_Type_t _7_Segment_Type;
}Segment_Type;

/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType _7_Segment_Initilization(const Segment_Type* Segment);

Std_ReturnType _7_Segment_Write_Number(const Segment_Type* Segment , uint8 Number);


/*************************************************/

#endif	/* ECU_7_SEGMENT_H */

