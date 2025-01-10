/* 
 * File:   Ecu_Layer_Init.c
 * Author: abdo
 *
 * Created on February 17, 2024, 1:45 PM
 */

#include "Ecu_Layer_Init.h"


LED_Type Admin_Led = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN0 , .init_state = GPIO_LOW };
LED_Type Guest_Led = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN1 , .init_state = GPIO_LOW };
LED_Type Block_Led = { .port_name = PORTC_INDEX , .pin_number = GPIO_PIN2 , .init_state = GPIO_LOW };

Chr_LCD_Type LCD = 
{
    .LCD_Enable.Port = PORTA_INDEX,
    .LCD_Enable.Pin  = GPIO_PIN2,
    .LCD_Enable.Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_Enable.Logic = GPIO_LOW,
    
    .LCD_RS.Port = PORTA_INDEX,
    .LCD_RS.Pin  = GPIO_PIN4,
    .LCD_RS.Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_RS.Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[0].Port = PORTD_INDEX,
    .LCD_8BIT_Data[0].Pin  = GPIO_PIN0,
    .LCD_8BIT_Data[0].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[0].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[1].Port = PORTD_INDEX,
    .LCD_8BIT_Data[1].Pin  = GPIO_PIN1,
    .LCD_8BIT_Data[1].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[1].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[2].Port = PORTD_INDEX,
    .LCD_8BIT_Data[2].Pin  = GPIO_PIN2,
    .LCD_8BIT_Data[2].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[2].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[3].Port = PORTD_INDEX,
    .LCD_8BIT_Data[3].Pin  = GPIO_PIN3,
    .LCD_8BIT_Data[3].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[3].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[4].Port = PORTD_INDEX,
    .LCD_8BIT_Data[4].Pin  = GPIO_PIN4,
    .LCD_8BIT_Data[4].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[4].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[5].Port = PORTD_INDEX,
    .LCD_8BIT_Data[5].Pin  = GPIO_PIN5,
    .LCD_8BIT_Data[5].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[5].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[6].Port = PORTD_INDEX,
    .LCD_8BIT_Data[6].Pin  = GPIO_PIN6,
    .LCD_8BIT_Data[6].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[6].Logic = GPIO_LOW,
    
    .LCD_8BIT_Data[7].Port = PORTD_INDEX,
    .LCD_8BIT_Data[7].Pin  = GPIO_PIN7,
    .LCD_8BIT_Data[7].Direction = GPIO_DIRECTION_OUTPUT,
    .LCD_8BIT_Data[7].Logic = GPIO_LOW,
};

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

MSSP_SPI_Type Spi = 
{
    .SPI_Mode = MSSP_SPI_MASTER_MODE,
    .SPI_Mode_confg = MSSP_SPI_MASTER_MODE_FOSC_DIV_BY_4,
    .SPI_Sample_Data = MSSP_SPI_SAMPLE_AT_THE_MIDDLE_OF_DATA,
    .SPI_Clock_Polarity = MSSP_SPI_CLOCK_IDLE_STATE_IS_HIGH,
    .SPI_Clock_Phase = MSSP_SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE,
    .SPI_Interrupt_Handler = _interrupt_handler,
};

Pin_Config_Type Spi_SS = {.Port = PORTA_INDEX , .Pin = GPIO_PIN5 , .Direction = GPIO_DIRECTION_OUTPUT , .Logic = GPIO_HIGH};


void Ecu_Layer_Initalization(void)
{
    Std_ReturnType ret = Func_Not_OK;
    
    ret = Led_Initialization(&Admin_Led);
    
    ret &= Led_Initialization(&Guest_Led);
    
    ret &= Led_Initialization(&Block_Led);
    
    ret &= LCD_8BIT_Initilization(&LCD);
    
    ret &= Keypad_Initialization(&Keypad);
    
    ret &= MSSP_SPI_Initilization(&Spi);
    
    ret &= GPIO_Pin_Initilization(&Spi_SS);
    
    ADC_PORT_CONFIGURATION_CONTROL(ADC_AN0_ANALOG_FUNCTIONALITY);
    
}