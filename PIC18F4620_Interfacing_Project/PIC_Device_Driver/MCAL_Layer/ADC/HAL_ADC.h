/* 
 * File:   HAL_ADC.h
 * Author: abdo
 *
 * Created on May 4, 2024, 11:32 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*************** Includes  ***********************/

#include "HAL_ADC_config.h"
#include "../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/Internal_Interrupt.h"
#include "../GPIO/HAL_GPIO.h"
/*************************************************/
/************** Marcos Declarations **************/

/** IF you choose ADC_AN3_ANALOG_FUNCTIONALITY it is mean that AN0,AN1,AN2,AN3 has analog functionality */
#define ALL_PINS_DIGITAL_FUNCTIONALITY    0x0F

#define ADC_AN0_ANALOG_FUNCTIONALITY      0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY      0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY      0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY      0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY      0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY      0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY      0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY      0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY      0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY      0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY     0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY     0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY     0x02

#define ALL_PINS_ANALOG_FUNCTIONALITY     0x01



/*************************************************/
/********** Marcos Function Declarations *********/

#define ADC_CONVERTER_ENABLE()                (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()               (ADCON0bits.ADON = 0)

#define ADC_START_CONVERSION()                (ADCON0bits.GODONE = 1) 
#define ADC_GET_CONVERSION_STATUS()           (ADCON0bits.GO_nDONE) 

#define VOLATAGE_REFERENCE_Vdd_Vss_Enable()   do{ ADCON1bits.VCFG0 = 0;\
                                                  ADCON1bits.VCFG1 = 0;\
                                              }while(0);

#define CUSTOM_VOLATAGE_REFERENCE_Enable()    do{ ADCON1bits.VCFG0 = 1;\
                                                ADCON1bits.VCFG1 = 1;\
                                              }while(0); 

#define ADC_PORT_CONFIGURATION_CONTROL(_Config) (ADCON1bits.PCFG = _Config)


#define ADC_Acquisition_Time_CONTROL(_Config)   (ADCON2bits.ACQT = _Config)


#define ADC_Conversion_Clock_CONTROL(_Config)   (ADCON2bits.ADCS = _Config)


#define ADC_Select_Chanal_CONTROL(_Config)      (ADCON0bits.CHS = _Config)


#define ADC_RESULT_RIGHT_FORMAT_CONTROL()        (ADCON2bits.ADFM = 1) 
#define ADC_RESULT_LEFT_FORMAT_CONTROL()        (ADCON2bits.ADFM = 0) 
                                                    


/*************************************************/
/************ Data Type Declarations **************/

typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,        
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,        
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,        
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,        
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,        
        
}ADC_Channel_Select_Type;

typedef enum{
    ADC_RESULT_LEFT_FORMAT = 0,
    ADC_RESULT_RIGHT_FORMAT          
}ADC_Result_Format_Type;

typedef enum{
    ADC_Vdd_Vss_VOLATAGE_REFERENCE = 0,
    ADC_CUSTOM_VOLATAGE_REFERENCE          
}ADC_Voltage_Reference_Type;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,        
    ADC_12_TAD,
    ADC_16_TAD,        
    ADC_20_TAD,       
        
}ADC_Acquisition_Time_Type;

typedef enum{
    ADC_VOLTAGE_SOURCE_FOSC_DIV_2 = 0,
    ADC_VOLTAGE_SOURCE_FOSC_DIV_8,
    ADC_VOLTAGE_SOURCE_FOSC_DIV_32,
    ADC_VOLTAGE_SOURCE_FRC,
    ADC_VOLTAGE_SOURCE_FOSC_DIV_4,        
    ADC_VOLTAGE_SOURCE_FOSC_DIV_16,
    ADC_VOLTAGE_SOURCE_FOSC_DIV_64,               
        
}ADC_Conversion_Clock_Type;

typedef struct{
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_Interrupt_Handler)(void);
    
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
    Interrupt_Priority_Type Priority;
#endif
#endif    
    ADC_Channel_Select_Type channel;
    ADC_Result_Format_Type result_format;
    ADC_Voltage_Reference_Type voltage_referance;
    ADC_Acquisition_Time_Type acquisition_time;
    ADC_Conversion_Clock_Type Conversion_Clock;  
}ADC_Configeration_type;

/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType ADC_Initilization(const ADC_Configeration_type* _adc);
Std_ReturnType ADC_DeInitilization(const ADC_Configeration_type* _adc);
Std_ReturnType ADC_Select_Channel(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel);
Std_ReturnType ADC_Start_Conversion(const ADC_Configeration_type* _adc);
Std_ReturnType ADC_Is_Conversion_Done(const ADC_Configeration_type* _adc , uint8 *Conversion_state);
Std_ReturnType ADC_Get_Conversion_Result(const ADC_Configeration_type* _adc , uint16 *Conversion_result);
Std_ReturnType ADC_Get_Conversion_Blocking(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel,
                                           uint16 *Conversion_result);
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
Std_ReturnType ADC_Conversion_Interrupt(const ADC_Configeration_type* _adc , ADC_Channel_Select_Type channel);
#endif




/*************************************************/

#endif	/* HAL_ADC_H */

