/* 
 * File:   Ecu_Layer_Init.c
 * Author: abdo
 *
 * Created on February 17, 2024, 1:45 PM
 */

#include "Ecu_Layer_Init.h"


LED_Type Slave_ROOM1 = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN0 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_ROOM_1 = { .Port = PORTD_INDEX , .Pin = GPIO_PIN0 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

LED_Type Slave_ROOM2 = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN1 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_ROOM_2 = { .Port = PORTD_INDEX , .Pin = GPIO_PIN1 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

LED_Type Slave_ROOM3 = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN2 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_ROOM_3 = { .Port = PORTD_INDEX , .Pin = GPIO_PIN2 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

LED_Type Slave_ROOM4 = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN3 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_ROOM_4 = { .Port = PORTD_INDEX , .Pin = GPIO_PIN3 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

LED_Type Slave_TV   = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN5 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_TV_PIN = { .Port = PORTD_INDEX , .Pin = GPIO_PIN5 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

LED_Type Slave_COND = { .port_name = PORTD_INDEX , .pin_number = GPIO_PIN4 , .init_state = GPIO_LOW };

Pin_Config_Type Slave_COND_pin = { .Port = PORTD_INDEX , .Pin = GPIO_PIN4 , .Logic = GPIO_LOW , .Direction = GPIO_DIRECTION_OUTPUT };

ADC_Configeration_type Temp_Sens = 
{
    .channel = ADC_CHANNEL_AN0,
    .Conversion_Clock = ADC_VOLTAGE_SOURCE_FOSC_DIV_16,
    .acquisition_time = ADC_12_TAD,
    .result_format = ADC_RESULT_RIGHT_FORMAT,
    .voltage_referance = ADC_Vdd_Vss_VOLATAGE_REFERENCE,
    .ADC_Interrupt_Handler = NULL,
    
};

MSSP_SPI_Type Spi = 
{
    .SPI_Mode = MSSP_SPI_SLAVE_MODE,
    .SPI_Mode_confg = MSSP_SPI_SLAVE_MODE_PIN_CONTROL_ENABLE,
    .SPI_Sample_Data = MSSP_SPI_SAMPLE_AT_THE_MIDDLE_OF_DATA,
    .SPI_Clock_Polarity = MSSP_SPI_CLOCK_IDLE_STATE_IS_HIGH,
    .SPI_Clock_Phase = MSSP_SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE,
    .SPI_Interrupt_Handler = NULL,
};

Pin_Config_Type Spi_SS = {.Port = PORTA_INDEX , .Pin = GPIO_PIN5 , .Direction = GPIO_DIRECTION_INPUT , .Logic = GPIO_HIGH};

Timer1_Type Timer = 
{
    .Timer1_Mode = TIMER1_TIMER_MODE_CONFG,
    .Preload_Value = 0,
    .Prescaler_Value = TIMER1_PRESCALER_VALUE_DIV_BY_1,
    .Timer1_16_8_bit_Confg = TIMER1_8BIT_REGISTER_CONFG,
    .Timer1_OSC_Confg = TIMER1_OSC_DISABLE_CONFG,
    .Timer1_counter_sync_Mode = TIMER1_COUNTER_SYNC_MODE_CONFG,
    .TIMER1_Interrupt_Handler = Timer_Interrupt,
};


void Ecu_Layer_Initalization(void)
{
    Std_ReturnType ret = Func_Not_OK;
    
    ret = Led_Initialization(&Slave_ROOM1);
    
    ret &= Led_Initialization(&Slave_ROOM2);
    
    ret &= Led_Initialization(&Slave_ROOM3);
    
    ret &= Led_Initialization(&Slave_ROOM4);
    
    ret &= Led_Initialization(&Slave_TV);
    
    ret &= Led_Initialization(&Slave_COND);
    
    ret &= ADC_Initilization(&Temp_Sens);
    
    ret &= MSSP_SPI_Initilization(&Spi);
    
    ret &= GPIO_Pin_Initilization(&Spi_SS);
    
    
    ADC_PORT_CONFIGURATION_CONTROL(ADC_AN0_ANALOG_FUNCTIONALITY);
    
}