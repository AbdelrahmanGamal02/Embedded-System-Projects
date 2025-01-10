/*
 *  main.c
 *
 *  Created on: 17/9/2022
 *      Author: Abdelrahman Gamal
*/

#include "HAL_Layer/LCD/LCD.h"
#include "HAL_Layer/LM35_Temp_Sensor/LM35_Temp_Sensor.h"
#include "HAL_Layer/DC_Motor/DC_Motor.h"


ADC_ConfigType ADC_CONFIG = {.Ref_Voltage = ADC_INTERNAL_Reference_Voltage , .prescaler = ADC_Prescaler_DIV_8};

uint8 Temp_Value = 0;
uint8 string_Temp_Value_1[5] = {'\0'};
int main(void)
{
	ADC_Init(&ADC_CONFIG);
	LCD_8bit_Init();
	DC_Motor_Init();

	while(1)
	{
		Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);

		while(Temp_Value < 30)
		{
			LCD_8bit_DisplayStringDataWithPosition(1,5,"Fan Is OFF");
			LCD_8bit_DisplayStringDataWithPosition(2,2,"Temp Value =");
			LCD_Convert_uint8_to_string(Temp_Value , string_Temp_Value_1);
			LCD_8bit_DisplayStringDataWithPosition(2,15,string_Temp_Value_1);
			LCD_8bit_DisplayCharacter('C');

			DC_Motor_Rotate(DC_MOTOR_STOP , 0);
			Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);
		}
		LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);

		while(Temp_Value >= 30 && Temp_Value < 60)
		{
			LCD_8bit_DisplayStringDataWithPosition(1,5,"Fan Is ON");
			LCD_8bit_DisplayStringDataWithPosition(2,2,"Temp Value =");
			LCD_Convert_uint8_to_string(Temp_Value , string_Temp_Value_1);
			LCD_8bit_DisplayStringDataWithPosition(2,15,string_Temp_Value_1);
			LCD_8bit_DisplayCharacter('C');


			DC_Motor_Rotate(DC_MOTOR_ROTATE_CLOCKWISE , 25);
			Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);
		}
		LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);

		while(Temp_Value >= 60 && Temp_Value < 90)
		{
			LCD_8bit_DisplayStringDataWithPosition(1,5,"Fan Is ON");
			LCD_8bit_DisplayStringDataWithPosition(2,2,"Temp Value =");
			LCD_Convert_uint8_to_string(Temp_Value , string_Temp_Value_1);
			LCD_8bit_DisplayStringDataWithPosition(2,15,string_Temp_Value_1);
			LCD_8bit_DisplayCharacter('C');


			DC_Motor_Rotate(DC_MOTOR_ROTATE_CLOCKWISE , 50);
			Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);
		}
		LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);

		while(Temp_Value >= 90 && Temp_Value < 120)
		{
			LCD_8bit_DisplayStringDataWithPosition(1,5,"Fan Is ON");
			LCD_8bit_DisplayStringDataWithPosition(2,2,"Temp Value =");
			LCD_Convert_uint8_to_string(Temp_Value , string_Temp_Value_1);

			LCD_8bit_DisplayStringDataWithPosition(2,15,string_Temp_Value_1);
			LCD_8bit_DisplayCharacter('C');
			LCD_8bit_DisplayCharacter(' ');

			DC_Motor_Rotate(DC_MOTOR_ROTATE_CLOCKWISE , 75);
			Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);
		}
		LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);

		while(Temp_Value >= 120)
		{
			LCD_8bit_DisplayStringDataWithPosition(1,5,"Fan Is ON");
			LCD_8bit_DisplayStringDataWithPosition(2,2,"Temp Value =");
			LCD_Convert_uint8_to_string(Temp_Value , string_Temp_Value_1);

			LCD_8bit_DisplayStringDataWithPosition(2,15,string_Temp_Value_1);
			LCD_8bit_DisplayCharacter('C');

			DC_Motor_Rotate(DC_MOTOR_ROTATE_CLOCKWISE , 100);
			Temp_Value = Get_Sensor_Value(ADC_CHANNEL_AN2);
		}
		LCD_8bit_SendCommand(_LCD_CLEAR_DIPLAY);
	}
}
