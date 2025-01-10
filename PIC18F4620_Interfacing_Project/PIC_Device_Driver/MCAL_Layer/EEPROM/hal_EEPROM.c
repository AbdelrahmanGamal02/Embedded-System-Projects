/* 
 * File:   hal_EEPROM.c
 * Author: abdo
 *
 * Created on April 23, 2024, 4:29 PM
 */

#include "hal_EEPROM.h"

/************* Helper Function ***************/

static Std_ReturnType EEPROM_SET_ADDRESS(uint16 Address)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(Address > 0x3FF)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        EEADRH = (uint8)((Address >> 8) & 0x03);
        
        EEADR = (uint8)(Address  & 0xFF);
        
        Ret_state = Func_OK;
    }
    
    return Ret_state;
}

/********************************************/

/**************** Function Definition **************/
Std_ReturnType EEPROM_Read_Data(uint16 Address , uint8 *Data)
{
    Std_ReturnType Ret_state = Func_Not_OK;
    if(Address > 0x3FF || (NULL == Data))
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        /* Set the Address in which the data will be read from */
        Ret_state = EEPROM_SET_ADDRESS(Address);
        /* clear the CFGS control bit (EECON1<6>) */
        EEPROM_DATA_ACEESS_Or_FLASH_MEMORY();
        /* clear the EEPGD control bit (EECON1<7>) */
        EEPROM_Selection_Bit();  
        /* set control bit, RD (EECON1<0>)*/
        EEPROM_INITIATE_READ_CYCLE();
        /* Wait Two Cycles (Recommended in high frequencies */
        NOP();
        NOP();
        /* Read The data from EEDATA */
        *Data = EEDATA;
    }
    
    return Ret_state;
}

Std_ReturnType EEPROM_Write_Data(uint16 Address , uint8 Data)
{
    uint8 interrupt_state = 0;
    Std_ReturnType Ret_state = Func_Not_OK;
    if(Address > 0x3FF)
    {
       Ret_state = Func_Not_OK; 
    }
    else
    {
        /* Set the Address in which the data will be read from */
        Ret_state = EEPROM_SET_ADDRESS(Address);
        /* Write The data to EEDATA */
        EEDATA = Data;
         /* clear the CFGS control bit (EECON1<6>) */
        EEPROM_DATA_ACEESS_Or_FLASH_MEMORY();
        /* clear the EEPGD control bit (EECON1<7>) */
        EEPROM_Selection_Bit();  
        /* Enable writes */
        EEPROM_ALLOWS_WRITE_CYCLES();
        /* Disable interrupt */
        interrupt_state = INTCONbits.GIE;
        
        #if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_DISABLE();
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_DISABLE();
        
        #else
            INTERRUPT_GLOBAL_INTERRUPT_DISABLE();
        #endif
        /* write 55h to EECON2, write 0AAh to EECON2 */
        EECON2 = 0x55;
        EECON2 = 0x0AA;
        /* set WR bit */
        EEPROM_INITIATE_WRITE_CYCLE();
        /* wait until write operation finished */
        while(EECON1bits.WR);
        /* Disable writes on write complete */
        EEPROM_PERVENT_WRITE_CYCLES();
        /* Enable interrupt */
        INTCONbits.GIE = interrupt_state;
        
        #if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
        
        #else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        #endif
        
    }
    
    return Ret_state;
}

/********************************************/