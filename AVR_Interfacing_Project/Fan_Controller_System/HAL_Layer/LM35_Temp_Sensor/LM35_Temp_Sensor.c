/*
 * LM35_Temp_Sensor.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */


#include "LM35_Temp_Sensor.h"

uint8 Get_Sensor_Value(uint8 Sensor_channal)
{
	uint16 read_value = 0;
	uint8 Sens_Value = 0;

	read_value = ADC_ReadValue(Sensor_channal);

	/* (max_temp(150) * max voltage(2.56) / (sensor voltage(1.5) * resolution of ADC(1023)) = 0.25 */
	Sens_Value = (uint8)((read_value * 2.5f) / 10);

	return Sens_Value;
}
