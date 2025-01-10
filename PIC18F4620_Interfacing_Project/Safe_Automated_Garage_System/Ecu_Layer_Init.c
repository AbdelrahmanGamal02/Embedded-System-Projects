/* 
 * File:   Ecu_Layer_Init.c
 * Author: abdo
 *
 * Created on February 17, 2024, 1:45 PM
 */

#include "Ecu_Layer_Init.h"

LED_Type Red_Entry_Led_Identication = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN6 , .init_state = GPIO_LOW };
LED_Type Red_Exit_Led_Identication  = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN7 , .init_state = GPIO_LOW };

LED_Type Green_Entry_Led_Identication = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN4 , .init_state = GPIO_LOW };
LED_Type Green_Exit_Led_Identication  = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN5 , .init_state = GPIO_LOW };



Keypad_Type Keypad = 
{
    .Keypad_Rows_Pins[0].Port = PORTB_INDEX,
    .Keypad_Rows_Pins[0].Direction = GPIO_DIRECTION_OUTPUT,
    .Keypad_Rows_Pins[0].Logic = GPIO_LOW,
    .Keypad_Rows_Pins[0].Pin = GPIO_PIN0,
    .Keypad_Rows_Pins[1].Port = PORTB_INDEX,
    .Keypad_Rows_Pins[1].Direction = GPIO_DIRECTION_OUTPUT,
    .Keypad_Rows_Pins[1].Logic = GPIO_LOW,
    .Keypad_Rows_Pins[1].Pin = GPIO_PIN1,
    .Keypad_Rows_Pins[2].Port = PORTB_INDEX,
    .Keypad_Rows_Pins[2].Direction = GPIO_DIRECTION_OUTPUT,
    .Keypad_Rows_Pins[2].Logic = GPIO_LOW,
    .Keypad_Rows_Pins[2].Pin = GPIO_PIN2,
    .Keypad_Rows_Pins[3].Port = PORTB_INDEX,
    .Keypad_Rows_Pins[3].Direction = GPIO_DIRECTION_OUTPUT,
    .Keypad_Rows_Pins[3].Logic = GPIO_LOW,
    .Keypad_Rows_Pins[3].Pin = GPIO_PIN3,
    .Keypad_Columns_Pins[0].Port = PORTB_INDEX,
    .Keypad_Columns_Pins[0].Direction = GPIO_DIRECTION_INPUT,
    .Keypad_Columns_Pins[0].Logic = GPIO_LOW,
    .Keypad_Columns_Pins[0].Pin = GPIO_PIN4,
    .Keypad_Columns_Pins[1].Port = PORTB_INDEX,
    .Keypad_Columns_Pins[1].Direction = GPIO_DIRECTION_INPUT,
    .Keypad_Columns_Pins[1].Logic = GPIO_LOW,
    .Keypad_Columns_Pins[1].Pin = GPIO_PIN5,
    .Keypad_Columns_Pins[2].Port = PORTB_INDEX,
    .Keypad_Columns_Pins[2].Direction = GPIO_DIRECTION_INPUT,
    .Keypad_Columns_Pins[2].Logic = GPIO_LOW,
    .Keypad_Columns_Pins[2].Pin = GPIO_PIN6,
    .Keypad_Columns_Pins[3].Port = PORTB_INDEX,
    .Keypad_Columns_Pins[3].Direction = GPIO_DIRECTION_INPUT,
    .Keypad_Columns_Pins[3].Logic = GPIO_LOW,
    .Keypad_Columns_Pins[3].Pin = GPIO_PIN7, 
};

Chr_LCD_Type _4BIT_LCD = 
{
    .LCD_RS.Port = PORTD_INDEX,
    .LCD_RS.Pin = GPIO_PIN1,
    .LCD_RS.Direction = GPIO_DIRECTION_OUTPUT,
    
    .LCD_Enable.Port = PORTD_INDEX,
    .LCD_Enable.Pin = GPIO_PIN0,
    .LCD_Enable.Direction = GPIO_DIRECTION_OUTPUT,
    
    .LCD_4BIT_Data[0].Port = PORTD_INDEX,
    .LCD_4BIT_Data[0].Pin = GPIO_PIN2,
    .LCD_4BIT_Data[0].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[0].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[1].Port = PORTD_INDEX,
    .LCD_4BIT_Data[1].Pin = GPIO_PIN3,
    .LCD_4BIT_Data[1].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[1].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[2].Port = PORTD_INDEX,
    .LCD_4BIT_Data[2].Pin = GPIO_PIN4,
    .LCD_4BIT_Data[2].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[2].Logic = GPIO_LOW,
    
    .LCD_4BIT_Data[3].Port = PORTD_INDEX,
    .LCD_4BIT_Data[3].Pin = GPIO_PIN5,
    .LCD_4BIT_Data[3].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_4BIT_Data[3].Logic = GPIO_LOW,
};

ADC_Configeration_type Temp_Sens = 
{
    .channel = ADC_CHANNEL_AN0,
    .Conversion_Clock = ADC_VOLTAGE_SOURCE_FOSC_DIV_16,
    .acquisition_time = ADC_12_TAD,
    .result_format = ADC_RESULT_RIGHT_FORMAT,
    .voltage_referance = ADC_Vdd_Vss_VOLATAGE_REFERENCE,
    .ADC_Interrupt_Handler = NULL,
    
};

Pin_Config_Type Buzzer = 
{
    .Port = PORTD_INDEX,
    .Pin = GPIO_PIN6,
    .Direction = GPIO_DIRECTION_OUTPUT,
    .Logic = GPIO_LOW
};

Pin_Config_Type Entry_PIR_Sensor = 
{
    .Port = PORTC_INDEX,
    .Pin = GPIO_PIN0,
    .Direction = GPIO_DIRECTION_INPUT,
};

Pin_Config_Type Exit_PIR_Sensor = 
{
    .Port = PORTC_INDEX,
    .Pin = GPIO_PIN3,
    .Direction = GPIO_DIRECTION_INPUT,
};


Pin_Config_Type Entry_Motor = 
{
    .Port = PORTC_INDEX,
    .Pin = GPIO_PIN2,
    .Direction = GPIO_DIRECTION_OUTPUT,
    .Logic = GPIO_LOW
};

Pin_Config_Type Exit_Motor = 
{
    .Port = PORTC_INDEX,
    .Pin = GPIO_PIN1,
    .Direction = GPIO_DIRECTION_OUTPUT,
    .Logic = GPIO_LOW
};

Timer1_Type Timer = 
{
    .Timer1_Mode = TIMER1_TIMER_MODE_CONFG,
    .Preload_Value = 0,
    .Prescaler_Value = TIMER1_PRESCALER_VALUE_DIV_BY_1,
    .Timer1_16_8_bit_Confg = TIMER1_16BIT_REGISTER_CONFG,
    .Timer1_OSC_Confg = TIMER1_OSC_DISABLE_CONFG,
    .Timer1_counter_sync_Mode = TIMER1_COUNTER_SYNC_MODE_CONFG,
    .TIMER1_Interrupt_Handler = Temperature_Interrupt,
};



void Ecu_Layer_Initalization(void)
{
    Std_ReturnType ret = Func_Not_OK;
    
    
    ret = Led_Initialization(&Red_Entry_Led_Identication);
    
    ret = Led_Initialization(&Red_Exit_Led_Identication);
    
    ret = Led_Initialization(&Green_Entry_Led_Identication);
    
    ret = Led_Initialization(&Green_Exit_Led_Identication);
    
    ret = GPIO_Pin_Initilization(&Entry_PIR_Sensor);
    
    ret = GPIO_Pin_Initilization(&Exit_PIR_Sensor);
    
    ret &= ADC_Initilization(&Temp_Sens);
    
    ret &= LCD_4BIT_Initilization(&_4BIT_LCD);
    
    ret &= Keypad_Initialization(&Keypad);
    
    ret = GPIO_Pin_Initilization(&Buzzer);
    
    ret = GPIO_Pin_Initilization(&Entry_Motor);
    
    ret = GPIO_Pin_Initilization(&Exit_Motor);
    
    ret = Timer1_Initilization(&Timer);
    
    
    ADC_PORT_CONFIGURATION_CONTROL(ADC_AN0_ANALOG_FUNCTIONALITY);
    
}