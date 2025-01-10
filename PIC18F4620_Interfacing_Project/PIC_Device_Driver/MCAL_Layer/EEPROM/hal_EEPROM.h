/* 
 * File:   hal_EEPROM.h
 * Author: abdo
 *
 * Created on April 23, 2024, 4:29 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*************** Includes  ***********************/
#include "hal_EEPROM_cfg.h"
#include "../Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/External_Interrupt.h"

/*************************************************/

/************** Marcos Declarations **************/

/*************************************************/
/********** Marcos Function Declarations *********/

#define EEPROM_DATA_ACEESS_Or_FLASH_MEMORY()  (EECON1bits.CFGS = 0)
#define Access_Configuration_registers()      (EECON1bits.CFGS = 1)

#define EEPROM_Selection_Bit()                (EECON1bits.EEPGD = 0)
#define FLASH_Selection_Bit()                 (EECON1bits.EEPGD = 1)

#define EEPROM_ALLOWS_WRITE_CYCLES()          (EECON1bits.WREN = 1)
#define EEPROM_PERVENT_WRITE_CYCLES()         (EECON1bits.WREN = 0)

#define EEPROM_INITIATE_WRITE_CYCLE()         (EECON1bits.WR = 1)  

#define EEPROM_INITIATE_READ_CYCLE()          (EECON1bits.RD = 1)  



/*************************************************/
/************ Data Type Declarations **************/


/*************************************************/
/*********** Function Declarations ***************/

Std_ReturnType EEPROM_Read_Data(uint16 Address , uint8 *Data);

Std_ReturnType EEPROM_Write_Data(uint16 Address , uint8 Data);

/*************************************************/


#endif	/* HAL_EEPROM_H */

