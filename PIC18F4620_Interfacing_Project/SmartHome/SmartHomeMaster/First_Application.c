/* 
 * File:   First_Application.c
 * Author: abdo
 *
 * Created on September 19, 2023, 4:53 PM
 */

#include "First_Application.h"

Std_ReturnType Main_ret = Func_OK;

void _interrupt_handler(void)
{
    
}

uint32 Entered_Admin_Password = 0;
uint32 Saved_Admin_Password = 0;
uint8 Number_of_tries = 1;

uint32 Entered_Guest_Password = 0;
uint32 Saved_Guest_Password = 0;

uint8 eeprom_set_value;
uint32 eeprom_address = 0x01;
        
uint8 Keypad_pressed = KEYPAD_NOT_PRESSED;
uint8 Keypad_Value = 0;
uint8 Keypad_counter = 0;
uint8 _Temp_Val = 0;


uint8 LCD_Temp1_string[5] = {0};
uint8 LCD_Temp2_string[5] = {0};
uint8 LCD_Temp3_string[5] = {0};
uint8 cursor = 0;

uint8 Entered_Temperature;

void main(void) {
    
    // initialize modules
    Ecu_Layer_Initalization();
    
    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Welcome to Smart");
    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Home System");
    __delay_ms(1000);
    Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
  
    Main_ret &= EEPROM_Read_Data(0x0000 ,  &eeprom_set_value);

    if(255 == eeprom_set_value)
    {
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Set Password For");
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "First Login");
        __delay_ms(1000);
        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
        
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Set Admin Password");
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Admin Pass : ");
        
        while(Keypad_counter < 4)
        {
            while(KEYPAD_NOT_PRESSED == Keypad_pressed)
            {
                Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
            }

            Main_ret &= EEPROM_Write_Data(eeprom_address ,  Keypad_Value);
            eeprom_address++;

            Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , (Keypad_counter + 14), LCD_Temp1_string);
            __delay_ms(300);

            Main_ret = LCD_8BIT_Send_char_data_With_Position(&LCD , 3 , (Keypad_counter + 14) , '*' );
            
            Keypad_counter++;
            Keypad_pressed = KEYPAD_NOT_PRESSED;
        }
        
        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
        
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Set Guest Password");
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Guest Pass : ");
        
        Keypad_counter = 0;
        Keypad_pressed = KEYPAD_NOT_PRESSED;
        eeprom_address = 0x05;
        
        while(Keypad_counter < 4)
        {
            while(KEYPAD_NOT_PRESSED == Keypad_pressed)
            {
                Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
            }

            Main_ret &= EEPROM_Write_Data(eeprom_address ,  Keypad_Value);
            eeprom_address++;

            Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , (Keypad_counter + 14), LCD_Temp1_string);
            __delay_ms(300);

            Main_ret = LCD_8BIT_Send_char_data_With_Position(&LCD , 3 , (Keypad_counter + 14) , '*' );
            
            Keypad_counter++;
            Keypad_pressed = KEYPAD_NOT_PRESSED;
        }
        
        Main_ret &= EEPROM_Write_Data(0x0000 ,  0x01);
            
        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Saved Successfully");
        __delay_ms(1000);
        
    }else { /* Nothing */ }
    
    while(1)
    {
        
        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);

        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Select Mode :");
        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "0:Admin     1:Guest");
        
        Keypad_pressed = KEYPAD_NOT_PRESSED;
        Main_ret &= LCD_8BIT_Set_Cursor(&LCD , 4 , 1);
               
        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
        {
            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
            __delay_ms(100);
        }
        
        if(0 == Keypad_Value)
        {
            label:
            Entered_Admin_Password = 0;
            Saved_Admin_Password = 0;
            
            Main_ret &= Led_Turn_ON(&Admin_Led);
            
            
            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
        
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Admin Mode");
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Admin Pass : ");
            
            Keypad_counter = 0;
            Keypad_pressed = KEYPAD_NOT_PRESSED;
            eeprom_address = 0x01;

            while(Keypad_counter < 4)
            {
                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                {
                    Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                }

                Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , (Keypad_counter + 14), LCD_Temp1_string);
                __delay_ms(300);

                Main_ret = LCD_8BIT_Send_char_data_With_Position(&LCD , 3 , (Keypad_counter + 14) , '*' );

                Keypad_counter++;
                Keypad_pressed = KEYPAD_NOT_PRESSED;
                
                Entered_Admin_Password += (Keypad_Value * (pow(10 , Keypad_counter - 1))); 
                
                Main_ret &= EEPROM_Read_Data(eeprom_address ,  &eeprom_set_value);
                
                Saved_Admin_Password += (eeprom_set_value * (pow(10 , Keypad_counter - 1)));
                
                eeprom_address++;
            }
            
            if(Entered_Admin_Password == Saved_Admin_Password)
            {
                Def:
                Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "0:ROOM1    1:ROOM2");
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "2:ROOM3    3:ROOM4");
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "4:COND     5:TV");
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 4 , 1, "6:Turn OFF ALL");
                
                Keypad_pressed = KEYPAD_NOT_PRESSED;
                Main_ret &= LCD_8BIT_Set_Cursor(&LCD , 5 , 18);
                
                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                {
                    Main_ret &= Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                    __delay_ms(100); 
                }
                _Temp_Val = Keypad_Value;
                
                switch(_Temp_Val)
                {
                    case 0:
                    {
                        ROOM1:
                         
                        
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('1');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('2');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value){
                            
                            goto Def;
                            
                        }else
                        {
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto ROOM1;
                        }
                    }
                    break;
                    
                    case 1:
                    {
                        ROOM2:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                       
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100); 
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('4');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('5');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value){
                            
                            goto Def;
                            
                        }else
                        {
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto ROOM2;
                        }
                    }
                    
                    break;
                    
                    case 2:
                    {
                        ROOM3:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100); 
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('7');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('8');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value){
                            
                            goto Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto ROOM3;
                        }
                    }
                    
                    break;
                    
                    case 3:
                    {
                        ROOM4:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");

                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100); 
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('a');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('b');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value){
                            
                            goto Def;
                        }
                        
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto ROOM4;
                        }
                    }
                    
                    break;
                    
                    case 4:
                    {
                        COND:
                        cursor = 0;
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "0: Set Temperature");
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "1: Controller");
                        
                        
                        
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Temperature = ");
                            
                            Entered_Temperature = 0;
                            Keypad_pressed = KEYPAD_NOT_PRESSED;
                            Keypad_counter = 2;
                            Keypad_Value = 0;
                            
                            while(Keypad_counter > 0)
                            {
                                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                                {
                                    Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                                    __delay_ms(100);
                                }

                                Main_ret &= Convert_uint8_to_string(Keypad_Value ,LCD_Temp3_string);
                                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , (cursor+15), LCD_Temp3_string);
                                
                                Entered_Temperature += (Keypad_Value * (pow(10 , Keypad_counter - 1)));
                                
                                __delay_ms(300);
                                
                                Keypad_counter--;
                                cursor++;
                                Keypad_pressed = KEYPAD_NOT_PRESSED;

                            }

                        }else if(1 == Keypad_Value)
                        {

                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");

                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");

                            Keypad_pressed = KEYPAD_NOT_PRESSED;

                            while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                            {
                                Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                                __delay_ms(100);
                            }

                            if(0 == Keypad_Value)
                            {
                                Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                                Main_ret &= MSSP_SPI_Write_Value_Blocking('i');
                                Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            }
                            else if(1 == Keypad_Value)
                            {
                                Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                                Main_ret &= MSSP_SPI_Write_Value_Blocking('n');
                                Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);

                            }
                        }else if (2 == Keypad_Value)
                        {
                            goto COND;
                        }
                        else
                        {
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto COND;
                        }
                        
                        Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                        Main_ret &= MSSP_SPI_Write_Value_Blocking('f');
                        __delay_ms(100);
                        Main_ret &= MSSP_SPI_Write_Value_Blocking(Entered_Temperature);
                        Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        
                    }
                    
                    break;
                    
                    case 5:
                    {
                        TV:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);          
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('l');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('m');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value){
                            
                            goto Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto ROOM3;
                        }
                        
                    }
                    
                    break;
                    
                    case 6:
                    {
                        Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                        Main_ret &= MSSP_SPI_Write_Value_Blocking('z');
                        Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        
                    }
                    
                    break;
                    
                    default: 
                    {
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                        __delay_ms(100);
                            
                            goto Def;
                    }
                    break;
                
                }
            }
            else
            {
                if(0 == Number_of_tries)
                {
                    Main_ret &= Led_Turn_OFF(&Admin_Led);
                    Main_ret &= Led_Turn_ON(&Block_Led);
                    
                    Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "You Blocked");
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Wait 10 Seconds");
                    __delay_ms(10000);
                    Main_ret &= Led_Turn_OFF(&Block_Led);
                    
                    Number_of_tries = 1;
                }
                else
                {
                    
                    Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Wrong Input");
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Tries : ");
                    Main_ret &= Convert_uint8_to_string(Number_of_tries , LCD_Temp2_string);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 9, LCD_Temp2_string);
                    __delay_ms(1000);
                    
                    Number_of_tries--;
                    
                }
                goto label;
            }
            
        }
        else if(1 == Keypad_Value)
        {
            label2:
            Entered_Guest_Password = 0;
            Saved_Guest_Password = 0;
            
            Main_ret &= Led_Turn_ON(&Guest_Led);
            
            
            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
        
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Enter Guest Password");
            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Guest Pass : ");
            
            Keypad_counter = 0;
            Keypad_pressed = KEYPAD_NOT_PRESSED;
            eeprom_address = 0x05;

            while(Keypad_counter < 4)
            {
                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                {
                    Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                }

                Main_ret &= Convert_uint8_to_string(Keypad_Value , LCD_Temp1_string);
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , (Keypad_counter + 14), LCD_Temp1_string);
                __delay_ms(300);

                Main_ret = LCD_8BIT_Send_char_data_With_Position(&LCD , 3 , (Keypad_counter + 14) , '*' );

                Keypad_counter++;
                Keypad_pressed = KEYPAD_NOT_PRESSED;
                
                Entered_Guest_Password += (Keypad_Value * (pow(10 , Keypad_counter - 1))); 
                
                Main_ret &= EEPROM_Read_Data(eeprom_address ,  &eeprom_set_value);
                
                Saved_Guest_Password += (eeprom_set_value * (pow(10 , Keypad_counter - 1)));
                
                eeprom_address++;
            }
            
            if(Entered_Guest_Password == Saved_Guest_Password)
            {
                G_Def:
                Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ROOM1    1:ROOM2");
                Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "2:ROOM3    3:ROOM4");
 
                
                Keypad_pressed = KEYPAD_NOT_PRESSED;
                Main_ret &= LCD_8BIT_Set_Cursor(&LCD , 5 , 18);
                
                while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                {
                    Main_ret &= Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                    __delay_ms(100); 
                }
                _Temp_Val = Keypad_Value;
                
                switch(_Temp_Val)
                {
                    case 0:
                    {
                        G_ROOM1:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('1');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('2');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value)
                        {
                            goto G_Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto G_ROOM1;
                        }
                    }
                    break;
                    
                    case 1:
                    {
                        G_ROOM2:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('4');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('5');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value)
                        {
                            goto G_Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto G_ROOM2;
                        }
                    }
                    
                    break;
                    
                    case 2:
                    {
                        G_ROOM3:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");
                        
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('7');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('8');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value)
                        {
                            goto G_Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto G_ROOM3;
                        }
                    }
                    
                    break;
                    
                    case 3:
                    {
                        G_ROOM4:
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Operation Required");

                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "0:ON   1:OFF  2:Ret");
                        
                        Keypad_pressed = KEYPAD_NOT_PRESSED;

                        while(KEYPAD_NOT_PRESSED == Keypad_pressed)
                        {
                            Main_ret = Keypad_Get_Value(&Keypad , &Keypad_Value , &Keypad_pressed);
                            __delay_ms(100);
                        }
                        
                        if(0 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('a');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                        }
                        else if(1 == Keypad_Value)
                        {
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_LOW);
                            Main_ret &= MSSP_SPI_Write_Value_Blocking('b');
                            Main_ret &= GPIO_Pin_Write_Logic(&Spi_SS , GPIO_HIGH);
                            
                        }else if(2 == Keypad_Value)
                        {
                            goto G_Def;
                        }
                        else{
                            Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                            Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                            __delay_ms(100);
                            
                            goto G_ROOM4;
                        }
                    }
                    
                    break;
                    
                    default: 
                    {
                        Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                        Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 1 , 1, "Wrong Input");
                        __delay_ms(100);
                            
                            goto G_Def;
                    }
                    break;
                
                }
            }
            else
            {
                if(0 == Number_of_tries)
                {
                    Main_ret &= Led_Turn_OFF(&Guest_Led);
                    Main_ret &= Led_Turn_ON(&Block_Led);
                    
                    Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "You Blocked");
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Wait 10 Seconds");
                    __delay_ms(10000);
                    Main_ret &= Led_Turn_OFF(&Block_Led);
                    
                    Number_of_tries = 1;
                }
                else
                {
                    
                    Main_ret &= LCD_8BIT_Send_Command(&LCD ,_LCD_CLEAR_DIPLAY);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 2 , 1, "Wrong Input");
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 1, "Tries : ");
                    Main_ret &= Convert_uint8_to_string(Number_of_tries , LCD_Temp2_string);
                    Main_ret &= LCD_8BIT_Send_String_Data_With_Position(&LCD , 3 , 9, LCD_Temp2_string);
                    __delay_ms(1000);
                    
                    Number_of_tries--;
                    
                }
                goto label2;
            }
        }
        else{ /* Nothing */ }
        
        Main_ret &= Led_Turn_OFF(&Admin_Led);
        Main_ret &= Led_Turn_OFF(&Guest_Led);
                
    }
    
}

void Application_Initilization(void)
{
    Ecu_Layer_Initalization();
}
