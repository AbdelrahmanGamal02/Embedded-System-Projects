/* 
 * File:   First_Application.c
 * Author: abdo
 *
 * Created on September 19, 2023, 4:53 PM
 */

#include "First_Application.h"

Std_ReturnType Main_ret = Func_OK;

volatile uint16 counter3 = 0;
volatile uint16 Conversion_Result = 0;
volatile uint16 Temperature_Result_in_Celusis = 0;

uint8 Keypad_pressed = KEYPAD_NOT_PRESSED;
uint8 Keypad_Value = 0;
uint8 Keypad_counter = 1;

uint8 LCD_Temp1_string[5] = {0};
uint8 LCD_Temp2_string[5] = {0};

volatile sint8 Car_counter = 5;
uint16 Password = 0;
uint16 G_Password = 0;

uint8 eeprom_set_value = 0;
uint32 eeprom_address = 0x01;
 
uint8 flag = 0;

Logic_Type Entry_Logic = GPIO_LOW;
Logic_Type Exit_Logic = GPIO_LOW; 

void Temperature_Interrupt(void)
{
    counter3++;
    
    if(1000 >= counter3)
    {
        counter3 = 0; 
        Main_ret &= ADC_Get_Conversion_Blocking(&Temp_Sens , ADC_CHANNEL_AN0,&Conversion_Result);
            
        Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
        Temperature_Result_in_Celusis /= 10;
                
        Temperature_Result_in_Celusis = (uint8)Temperature_Result_in_Celusis;
        
        while(50 <= Temperature_Result_in_Celusis)
        {
            Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "There is a Fire");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Get Out");
            
            Main_ret &= GPIO_Pin_Write_Logic(&Buzzer , GPIO_HIGH);
            
            /* Open Gates */
            Main_ret &= Led_Turn_OFF(&Red_Exit_Led_Identication);
            Main_ret &= Led_Turn_ON(&Green_Exit_Led_Identication);
                    
            Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_HIGH);
            __delay_ms(2);
            Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_LOW);
            /*********************************************************/
            Main_ret &= Led_Turn_OFF(&Red_Entry_Led_Identication);
            Main_ret &= Led_Turn_ON(&Green_Entry_Led_Identication);
                    
            Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_HIGH);
            __delay_ms(2);
            Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_LOW);
            
            flag = 1;
            /************/

            Main_ret &= ADC_Get_Conversion_Blocking(&Temp_Sens , ADC_CHANNEL_AN0,&Conversion_Result);
            
            Temperature_Result_in_Celusis = Conversion_Result * 4.88f;
            Temperature_Result_in_Celusis /= 10;

            Temperature_Result_in_Celusis = (uint8)Temperature_Result_in_Celusis;
            
            __delay_ms(100);
        }
        
        Main_ret &= GPIO_Pin_Write_Logic(&Buzzer , GPIO_LOW);
        if(1 == flag)
        {
            Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_HIGH);
            __delay_ms(1.441);
            Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_LOW);
                    
                    
            Main_ret &= Led_Turn_OFF(&Green_Exit_Led_Identication);
            Main_ret &= Led_Turn_ON(&Red_Exit_Led_Identication);
            /***************************************************************/
            Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_HIGH);
            __delay_ms(1.441);
            Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_LOW);
                           
            Main_ret &= Led_Turn_OFF(&Green_Entry_Led_Identication);
            Main_ret &= Led_Turn_ON(&Red_Entry_Led_Identication);
            
            
            flag = 0;
            
        }
                
        
    }
}


int main()

{
    
    Application_Initilization();
    
    Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Welcome to Smart");
    Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "Garage System");
    __delay_ms(1000);
    Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
  
    Main_ret &= EEPROM_Read_Data(0x0000 ,  &eeprom_set_value);

    if(255 == eeprom_set_value)
    {
        Keypad_pressed = KEYPAD_NOT_PRESSED;
        Keypad_Value = 0;
        Keypad_counter = 1;
            
        Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Set Password For");
        Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "First Login");
        __delay_ms(1000);
        Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
        
        Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Set Password : ");
        
        while(Keypad_counter <= 4)
        {
            while(KEYPAD_NOT_PRESSED == Keypad_pressed)
            {
                Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
            }
            
            Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , (Keypad_counter + 7), LCD_Temp1_string);
            __delay_ms(300);
             
            
            Main_ret = LCD_4BIT_Send_char_data_With_Position(&_4BIT_LCD , 3 , (Keypad_counter + 7) , '*' );
            
            Keypad_counter++;
            Keypad_pressed = KEYPAD_NOT_PRESSED;
        }
        
        Main_ret &= EEPROM_Write_Data(0x0000 ,  0x01);
        
        Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
        Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Saved Successfully");
        __delay_ms(1000);
    }
    
    while(1)
    {
        
        if(0 != Car_counter)
        {
            Main_ret &= Convert_uint8_to_string(Car_counter , LCD_Temp2_string);
            Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "There are ");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 11, LCD_Temp2_string);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 13, "Spaces");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "You Can Enter");
            __delay_ms(100);
        }
        
        
        if(GPIO_HIGH == Entry_Logic || GPIO_HIGH == Exit_Logic)
        {
            __delay_ms(5000);
        }
        
        
        Main_ret &= GPIO_Pin_Read_Logic(&Entry_PIR_Sensor , &Entry_Logic);
        Main_ret &= GPIO_Pin_Read_Logic(&Exit_PIR_Sensor , &Exit_Logic);
        
        Main_ret &= Led_Turn_ON(&Red_Entry_Led_Identication);
        Main_ret &= Led_Turn_ON(&Red_Exit_Led_Identication);
        
        while((GPIO_LOW == Entry_Logic) && (GPIO_LOW == Exit_Logic))
        {
            
            Main_ret &= Convert_uint8_to_string(Car_counter , LCD_Temp2_string);
            Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "There are ");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 11, LCD_Temp2_string);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 13, "Spaces");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "You Can Enter");
            
            Main_ret &= GPIO_Pin_Read_Logic(&Entry_PIR_Sensor , &Entry_Logic);
            Main_ret &= GPIO_Pin_Read_Logic(&Exit_PIR_Sensor , &Exit_Logic);
            
            __delay_ms(300);
            
        }
        
        if(GPIO_HIGH == Exit_Logic)
        {
            if(Car_counter < 5)
            {
                Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 1, "Exit Door is Opened");
                
                /** open Gate */
                TIMER1_INTERRUPT_DISABLE();
                    Main_ret &= Led_Turn_OFF(&Red_Exit_Led_Identication);
                    Main_ret &= Led_Turn_ON(&Green_Exit_Led_Identication);
                    
                    Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_HIGH);
                    __delay_ms(3);
                    Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_LOW);
                    
                    __delay_ms(3000);
                    
                    Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_HIGH);
                    __delay_ms(1.441);
                    Main_ret &= GPIO_Pin_Write_Logic(&Exit_Motor , GPIO_LOW);
                    
                    __delay_ms(500);
                    
                    Main_ret &= Led_Turn_OFF(&Green_Exit_Led_Identication);
                    Main_ret &= Led_Turn_ON(&Red_Exit_Led_Identication);
                TIMER1_INTERRUPT_ENABLE();
                /**************/
                Car_counter++;
            }
            else
            {
                Car_counter = 5;
                Main_ret &= Convert_uint8_to_string(Car_counter , LCD_Temp2_string);
                Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "There are ");
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 11, LCD_Temp2_string);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 13, "Spaces");
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "You Can Enter");
            }
            
        }
        
        if((GPIO_HIGH == Entry_Logic) && (0 != Car_counter))
        {
            label:
            Keypad_pressed = KEYPAD_NOT_PRESSED;
            Keypad_Value = 0;
            Keypad_counter = 1;
            
            Password = 0;
            G_Password = 0;
            eeprom_address = 0x01;
            
            Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "check Password :");
            while(Keypad_counter <= 4)
            {
                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                {
                    Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                }
                
                Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , (Keypad_counter + 7), LCD_Temp1_string);
                __delay_ms(300);

                Main_ret = LCD_4BIT_Send_char_data_With_Position(&_4BIT_LCD , 3 , (Keypad_counter + 7) , '*' );
                
                Main_ret &= EEPROM_Read_Data(eeprom_address ,  &eeprom_set_value);
                
                G_Password += (eeprom_set_value * (pow(10 , Keypad_counter - 1)));
                
                eeprom_address++;
                
                Password += (Keypad_Value * (pow(10 , Keypad_counter - 1))); 

                Keypad_counter++;
                Keypad_pressed = KEYPAD_NOT_PRESSED;
            }
 
            if(Password == G_Password)
            {
                
                Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 1 , 1, "Right Password");
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 4, "You Can Enter");
                __delay_ms(100);
                    /** Open Entry Gates  and turn on led */
                TIMER1_INTERRUPT_DISABLE();
                Main_ret &= Led_Turn_OFF(&Red_Entry_Led_Identication);
                Main_ret &= Led_Turn_ON(&Green_Entry_Led_Identication);
                    
                Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_HIGH);
                __delay_ms(2);
                Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_LOW);
                    
                __delay_ms(3000);
                    
                Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_HIGH);
                __delay_ms(1.441);
                Main_ret &= GPIO_Pin_Write_Logic(&Entry_Motor , GPIO_LOW);
                    
                __delay_ms(500);
                    
                Main_ret &= Led_Turn_OFF(&Green_Entry_Led_Identication);
                Main_ret &= Led_Turn_ON(&Red_Entry_Led_Identication);
                TIMER1_INTERRUPT_ENABLE();
                    /***************/
                Car_counter--;     
                 
            }
            else
            {
                Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Wrong Password");
                Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Try Again");
                __delay_ms(300);
                goto label;
            }
        }
        if(0 ==  Car_counter)
        {
            Main_ret &= LCD_4BIT_Send_Command(&_4BIT_LCD ,_LCD_CLEAR_DIPLAY);
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 2 , 1, "Garage is Full");
            Main_ret &= LCD_4BIT_Send_String_Data_With_Position(&_4BIT_LCD , 3 , 1, "You Can't Enter");
                    
        }
        
    }

    return 0;

}

void Application_Initilization(void)
{
    Ecu_Layer_Initalization();
}

