/*
 * LM35_Temp_Sensor.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_LM35_TEMP_SENSOR_LM35_TEMP_SENSOR_H_
#define ECUAL_LAYER_LM35_TEMP_SENSOR_LM35_TEMP_SENSOR_H_

/******************* Includes ****************/
#include "../../MCAL_Layer/ADC/ADC.h"
/*******************************************/
/***************** Macros *****************/

#define Max_Temperature      150
#define Max_Valtage          2.56
#define SENSOR_Max_Valtage   1.5
#define ADC_Resolution       1023

#define Sensor_Channal       ADC_CHANNEL_AN2
/*****************************************/
/******************* APIs ******************/
uint8 Get_Sensor_Value(uint8 Sensor_channal);
/******************************************/

#endif /* ECUAL_LAYER_LM35_TEMP_SENSOR_LM35_TEMP_SENSOR_H_ */
