/*
 *  main.c
 *
 *  Created on: 17/9/2022
 *      Author: Abdelrahman Gamal
 */

#include "ECUAL_Layer/LCD/LCD.h"
#include "MCAL_Layer/ADC/ADC.h"

ADC_ConfigType ADC_1 = {.Ref_Voltage = ADC_AVCC_Reference_Voltage_5V , .prescaler = ADC_Prescaler_DIV_128};
uint8 A[5] = {'\0'};
uint8 A1[5] = {'\0'};
uint8 A2[5] = {'\0'};
uint8 b = 9;
uint16 val = 0;
float32 V_val = 0;
uint8 num = 0;
uint8 fraction = 0;
int main(void)
{
	LCD_8bit_Init();
	ADC_Init(&ADC_1);

	while(1)
	{

		val = ADC_ReadValue(ADC_CHANNEL_AN0);
		V_val = (float32)((val / 1023.0) * 5);
		num = (uint8)V_val;
		fraction = (uint8)((V_val - num) * 100);

		LCD_8bit_SetCursor(1,0);
		LCD_8bit_DisplayStringData("Voltage Value =");

		LCD_Convert_uint8_to_string(num , A);

		for(uint8 i = 0; A[i] != ' ' ;i++)
		{
			A1[i] = A[i];
		}

		LCD_8bit_SetCursor(1,16);
		LCD_8bit_DisplayStringData(A1);
		LCD_8bit_DisplayCharacter('.');
		LCD_Convert_uint8_to_string(fraction , A2);
		LCD_8bit_DisplayStringData(A2);
	}

}

