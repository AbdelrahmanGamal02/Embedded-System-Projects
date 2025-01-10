/* 
 * File:   First_Application.c
 * Author: abdo
 *
 * Created on September 19, 2023, 4:53 PM
 */

#include "First_Application.h"

Std_ReturnType Main_ret = Func_OK;

uint8 Slave_Spi_Data = 0;

volatile uint16 Conversion_Result = 0;
volatile uint16 Temperature_Result_in_Celusis = 0;
volatile uint8 Temperature_Spi_Read = 0;
volatile uint8 counter = 0;
volatile uint8 COND_last_status = 0;



void main(void) {
    
    // initialize modules
    Application_Initilization();
    while(1)
    {
        Main_ret = MSSP_SPI_Read_Value_Blocking(&Slave_Spi_Data);

        switch(Slave_Spi_Data)
        {
            case '1' :
            {
                Main_ret &= Led_Turn_ON(&Slave_ROOM1);
            }
            break;
            
            case '2' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_ROOM1);

            }
            break;
            
            case '4' :
            {
                Main_ret &= Led_Turn_ON(&Slave_ROOM2);

            }
            break;
            
            case '5' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_ROOM2);

            }
            break;
            
            case '7' :
            {
                Main_ret &= Led_Turn_ON(&Slave_ROOM3);

            }
            break;
            
            case '8' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_ROOM3);

            }
            break;
            
            case 'a' :
            {
                Main_ret &= Led_Turn_ON(&Slave_ROOM4);

            }
            break;
            
            case 'b' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_ROOM4);

            }
            break;
            
            case 'l' :
            {
                Main_ret &= Led_Turn_ON(&Slave_TV);

            }
            break;
            
            case 'm' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_TV);

            }
            break;
            
            case 'f' :
            {
                Main_ret &= MSSP_SPI_Read_Value_Blocking(&Temperature_Spi_Read); 
            }
            break;
            
            case 'i' :
            {
                Main_ret &= Led_Turn_ON(&Slave_COND);
                Main_ret &= Timer1_Initilization(&Timer);
            }
            break;
            
            case 'n' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_COND);
                Main_ret &= Timer1_DeInitilization(&Timer);
                Main_ret &= Timer1_Write_Value(&Timer , 0x01);
            }
            break;
            

            
            case 'z' :
            {
                Main_ret &= Led_Turn_OFF(&Slave_COND);
                Main_ret &= Led_Turn_OFF(&Slave_TV);
                
                Main_ret &= Led_Turn_OFF(&Slave_ROOM4);
                Main_ret &= Led_Turn_OFF(&Slave_ROOM3);
                Main_ret &= Led_Turn_OFF(&Slave_ROOM2);
                Main_ret &= Led_Turn_OFF(&Slave_ROOM1);
                
            }
            break;
        }
        Slave_Spi_Data = 0;
    }
}

void Application_Initilization(void)
{
    Ecu_Layer_Initalization();
}

void Timer_Interrupt(void)
{
    counter++;
    
    if(10 >= counter)
    {
        counter = 0; 
        Main_ret &= ADC_Get_Conversion_Blocking(&Temp_Sens , ADC_CHANNEL_AN0,&Conversion_Result);
            
        Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
        Temperature_Result_in_Celusis /= 10;
                
        Temperature_Result_in_Celusis = (uint8)Temperature_Result_in_Celusis;
        
        if(Temperature_Result_in_Celusis >= (Temperature_Spi_Read + 1))
        {
            Main_ret &= Led_Turn_ON(&Slave_COND);
            COND_last_status = 1;
        }
        else if(Temperature_Result_in_Celusis <= (Temperature_Spi_Read - 1))
        {
            Main_ret &= Led_Turn_OFF(&Slave_COND);
            COND_last_status = 0;
        }
        else if(Temperature_Result_in_Celusis == Temperature_Spi_Read)
        {
            if(0 == COND_last_status)
            {
                Main_ret &= Led_Turn_OFF(&Slave_COND);
            }
            else if(1 == COND_last_status)
            {
                Main_ret &= Led_Turn_ON(&Slave_COND);
            }
        }
    }
}