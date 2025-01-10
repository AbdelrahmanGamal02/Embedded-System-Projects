/* 
 * File:   HAL_GPIO.h
 * Author: abdo
 *
 * Created on September 19, 2023, 4:58 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*************** Includes  ***********************/
#include "../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../Device_config/Device_Config.h"
#include "GPIO_CONFIG.h"

/*************************************************/

/************** Marcos Declarations **************/
#define HWREG(_x)       (*((volatile uint8 *)_x)) /* To Define Any Register From His Address */

#define Bit_Mainpu_Mask           1
#define Max_Number_Of_Pins        8
#define Max_Number_Of_Ports       5
/*************************************************/
/********** Marcos Function Declarations *********/
#define SET_BIT(REG ,BIT_POSITION)      (REG |= (Bit_Mainpu_Mask << BIT_POSITION))
#define CLEAR_BIT(REG ,BIT_POSITION)    (REG &= ~(Bit_Mainpu_Mask << BIT_POSITION))
#define TOGGLE_BIT(REG ,BIT_POSITION)   (REG ^= (Bit_Mainpu_Mask << BIT_POSITION))
#define READ_BIT(REG ,BIT_POSITION)     ((REG >> BIT_POSITION) & Bit_Mainpu_Mask)

/*************************************************/
/************ Data Type Declarations **************/

/**************** Helper Declarations *************/
/* TRIS Registers To Define pin Output Or Input */
volatile uint8 *Tris_Registers[] = { &TRISA , &TRISB , &TRISC , &TRISD , &TRISE};
/* LAT Registers To Write On Pins 1 or 0 */
volatile uint8 *Lat_Registers[] = { &LATA , &LATB , &LATC , &LATD , &LATE};
/* PORT Registers To read Data On  pins  */
volatile uint8 *Port_Registers[] = { &PORTA , &PORTB , &PORTC , &PORTD , &PORTE};
/****************************************************/

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}Logic_Type;

typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT        
}Direction_Type;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}Pin_Index_Type;
        
typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}Port_Index_Type;

typedef struct {
    uint8 Port      : 3 ;  /* @ref Port_Index_Type*/
    uint8 Pin       : 3 ;  /* @ref Pin_Index_Type*/
    uint8 Direction : 1 ;  /* @ref Direction_Type*/
    uint8 Logic     : 1 ;  /* @ref Logic_Type*/
}Pin_Config_Type;
        
/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType GPIO_Pin_Initilization(const Pin_Config_Type* Pin_Config);
Std_ReturnType GPIO_Pin_Direction_Initilization(const Pin_Config_Type* Pin_Config);
Std_ReturnType GPIO_Pin_Write_Logic(const Pin_Config_Type* Pin_Config , Logic_Type Logic);
Std_ReturnType GPIO_Pin_Read_Logic(const Pin_Config_Type* Pin_Config , Logic_Type* Ret_Logic);
Std_ReturnType GPIO_Pin_Toggle_Pin(const Pin_Config_Type* Pin_Config);

Std_ReturnType GPIO_Port_Direction_Initilization(Port_Index_Type Port , uint8 Direction);
Std_ReturnType GPIO_Port_Get_Direction_Status(Port_Index_Type Port , uint8* Direction);
Std_ReturnType GPIO_Port_Write_Logic(Port_Index_Type Port , uint8 Logic);
Std_ReturnType GPIO_Port_Read_Logic(Port_Index_Type Port , uint8* Logic);
Std_ReturnType GPIO_Port_Toggle(Port_Index_Type Port);


/*************************************************/


#endif	/* HAL_GPIO_H */

