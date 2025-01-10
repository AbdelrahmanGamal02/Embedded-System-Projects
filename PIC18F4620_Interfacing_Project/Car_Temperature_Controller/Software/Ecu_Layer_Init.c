/* 
 * File:   Ecu_Layer_Init.c
 * Author: abdo
 *
 * Created on February 17, 2024, 1:45 PM
 */

#include "Ecu_Layer_Init.h"

LED_Type LED1 = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN6 , .init_state = GPIO_LOW };
LED_Type LED2 = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN7 , .init_state = GPIO_LOW };

DC_Motor_Type Motor1 = {
    .DC_Motor_Pins[0].Port = PORTD_INDEX,
    .DC_Motor_Pins[0].Pin = GPIO_PIN0,
    .DC_Motor_Pins[0].Direction = GPIO_DIRECTION_OUTPUT,
    .DC_Motor_Pins[0].Logic = GPIO_LOW,
    
    .DC_Motor_Pins[1].Port = PORTD_INDEX,
    .DC_Motor_Pins[1].Pin = GPIO_PIN1,
    .DC_Motor_Pins[1].Direction = GPIO_DIRECTION_OUTPUT,
    .DC_Motor_Pins[1].Logic = GPIO_LOW,
};

DC_Motor_Type Motor2 = {
    .DC_Motor_Pins[0].Port = PORTD_INDEX,
    .DC_Motor_Pins[0].Pin = GPIO_PIN2,
    .DC_Motor_Pins[0].Direction = GPIO_DIRECTION_OUTPUT,
    .DC_Motor_Pins[0].Logic = GPIO_LOW,
    
    .DC_Motor_Pins[1].Port = PORTD_INDEX,
    .DC_Motor_Pins[1].Pin = GPIO_PIN3,
    .DC_Motor_Pins[1].Direction = GPIO_DIRECTION_OUTPUT,
    .DC_Motor_Pins[1].Logic = GPIO_LOW,
};

Chr_LCD_Type _4BIT_LCD = 
{
    .LCD_RS.Port = PORTC_INDEX,
    .LCD_RS.Pin = GPIO_PIN0,
    .LCD_RS.Direction = GPIO_DIRECTION_OUTPUT,
    
    .LCD_Enable.Port = PORTC_INDEX,
    .LCD_Enable.Pin = GPIO_PIN1,
    .LCD_Enable.Direction = GPIO_DIRECTION_OUTPUT,
    
    .LCD_4BIT_Data[0].Port = PORTC_INDEX,
    .LCD_4BIT_Data[0].Pin = GPIO_PIN2,
    .LCD_4BIT_Data[0].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[0].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[1].Port = PORTC_INDEX,
    .LCD_4BIT_Data[1].Pin = GPIO_PIN3,
    .LCD_4BIT_Data[1].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[1].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[2].Port = PORTC_INDEX,
    .LCD_4BIT_Data[2].Pin = GPIO_PIN4,
    .LCD_4BIT_Data[2].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[2].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[3].Port = PORTC_INDEX,
    .LCD_4BIT_Data[3].Pin = GPIO_PIN5,
    .LCD_4BIT_Data[3].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[3].Logic = GPIO_LOW,
};

ADC_Configeration_type _adc_1 = {
    .Conversion_Clock = ADC_VOLTAGE_SOURCE_FOSC_DIV_16,
    .acquisition_time = ADC_12_TAD,
    .channel = ADC_CHANNEL_AN0,
    .result_format = ADC_RESULT_RIGHT_FORMAT,
    .voltage_referance = ADC_Vdd_Vss_VOLATAGE_REFERENCE
};





void Ecu_Layer_Initalization(void)
{
    Std_ReturnType Func_State = Func_OK;
    
    Func_State &= Led_Initialization(&LED1);
    Func_State &= Led_Initialization(&LED2);
    
    Func_State &= DC_Motor_Initialization(&Motor1);
    Func_State &= DC_Motor_Initialization(&Motor2);
    
    Func_State &= LCD_4BIT_Initilization(&_4BIT_LCD);

    Func_State &= ADC_Initilization(&_adc_1);
    
    ADC_PORT_CONFIGURATION_CONTROL(ADC_AN0_ANALOG_FUNCTIONALITY);
    
}