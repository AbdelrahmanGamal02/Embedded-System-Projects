/* 
 * File:   First_Application.c
 * Author: abdo
 *
 * Created on September 19, 2023, 4:53 PM
 */

#include "First_Application.h"

Std_ReturnType Func_State = Func_OK;

uint16 Conversion_Result = 0;
uint16 Temperature_Result_in_Celusis = 0;

uint8 Temperature_Result_in_Celusis_txt[7];


int main() { 
    
    Application_Initilization();
    
            Func_State = LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 4,"Hello Sir :)");
        __delay_ms(2000);
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
        
        Func_State = ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
        Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
        Temperature_Result_in_Celusis /= 10;
    
    
    while(1)
    {
        
        
        while(Temperature_Result_in_Celusis <= 90)
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 1,"Motor Temperature");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 5,"is Too Low");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Temperature : ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 15, Temperature_Result_in_Celusis_txt);
            
            Func_State &= Led_Turn_OFF(&LED1);
            Func_State &= Led_Turn_OFF(&LED2);
            
            Func_State &= DC_Motor_Stop(&Motor1);
            Func_State &= DC_Motor_Stop(&Motor2);
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
        }
        
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
            
        while(Temperature_Result_in_Celusis <= 105)
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 1,"Motor Temperature");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 6,"is Normal");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Temperature : ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 15, Temperature_Result_in_Celusis_txt);
            
            Func_State &= Led_Turn_OFF(&LED1);
            Func_State &= Led_Turn_OFF(&LED2);
            
            Func_State &= DC_Motor_Stop(&Motor1);
            Func_State &= DC_Motor_Stop(&Motor2);
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
        }
        
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
        
        while((Temperature_Result_in_Celusis > 105) && (Temperature_Result_in_Celusis <= 116))
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 6,"Warming");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1,"Temperature is ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1,"Increased to ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 15, Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Motor is Overheating");
            
            Func_State &= Led_Turn_ON(&LED1);
            
            Func_State &= DC_Motor_Move_Right(&Motor1);
            Func_State &= DC_Motor_Move_Right(&Motor2);
            
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
        }
        
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
        
        while((Temperature_Result_in_Celusis > 116) && (Temperature_Result_in_Celusis < 121))
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 6,"Emergency");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1,"You Should Stop");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1,"Your Car Now");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Temperature : ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 15, Temperature_Result_in_Celusis_txt);
            
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Func_State &= Led_Turn_ON(&LED1);
            Func_State &= Led_Turn_ON(&LED2);
            
            Func_State &= DC_Motor_Move_Right(&Motor1);
            Func_State &= DC_Motor_Move_Right(&Motor2);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
        }
        
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
        
        /*while(Temperature_Result_in_Celusis >= 121)
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 6,"Dangerous");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1,"Motor Temperature");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1,"is UnSafe");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Temperature : ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 15, Temperature_Result_in_Celusis_txt);
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Func_State &= Led_Turn_ON(&LED1);
            Func_State &= Led_Turn_ON(&LED2);
            
            Func_State &= DC_Motor_Move_Right(&Motor1);
            Func_State &= DC_Motor_Move_Right(&Motor2);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
            
        }
        while(Temperature_Result_in_Celusis > 121)
        {
            
            Func_State = Convert_uint16_to_string(Temperature_Result_in_Celusis , Temperature_Result_in_Celusis_txt);
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1,"Undefined Area");
            
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 1,"Temperature : ");
            Func_State &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 4 , 15, Temperature_Result_in_Celusis_txt);
            
            Func_State &= ADC_Get_Conversion_Blocking(&_adc_1 , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Func_State &= Led_Turn_ON(&LED1);
            Func_State &= Led_Turn_ON(&LED2);
            
            Func_State &= DC_Motor_Move_Right(&Motor1);
            Func_State &= DC_Motor_Move_Right(&Motor2);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;
            
        }*/
        
        Func_State = LCD_4BIT_Send_Command(&_4BIT_LCD , _LCD_CLEAR_DIPLAY);
    }
   
    return (EXIT_SUCCESS);
}
void Application_Initilization(void)
{
    Ecu_Layer_Initalization();
}
