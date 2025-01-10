/*
 * CAN_Transmitter.h
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_CAN_TRANSMITTER_CAN_TRANSMITTER_H_
#define ECUAL_LAYER_CAN_TRANSMITTER_CAN_TRANSMITTER_H_

/*********** Includes ******************/
#include "../../MCAL_Layer/GPIO/GPIO.h"
#include "../../MCAL_Layer/SPI/SPI.h"
/***************************************/
/************* Macros ******************/

#define READ_INST       			 0x03
#define WRITE_INST          		 0x02
#define BIT_MODIFY_INST     		 0x05
#define REST_INST            		 0xC0
#define BUFFER0_REQU_TO_SEND_INST    0x81
#define BUFFER1_REQU_TO_SEND_INST    0x82
#define BUFFER2_REQU_TO_SEND_INST    0x84

#define BUFFER0              0
#define BUFFER1              1
#define BUFFER2              2

#define CANF1                0x2A
#define CANF2                0x29
#define CANF3                0x28

#define CANCTRL              0x0F
#define NORMAL_MODE          0x04
#define CONFG_MODE           0x84

#define TXB0CTRL             0x30
#define TXB1CTRL             0x40
#define TXB2CTRL             0x50


/***************************************/
/*************** Data Types ************/

/***************************************/
/************** APIs *****************/

uint8 CAN_u8ReadRegister(uint8 address);

void CAN_vWriteRegister(uint8 address , uint8 data);

void CAN_vBitModifyRegister(uint8 address , uint8 Mask ,uint8 data);

void CAN_vBitTiming(uint8 CANF1_value , uint8 CANF2_value , uint8 CANF3_value);

void CAN_vSetMode(uint8 mode);

void CAN_vTransmitterInit(void);

void CAN_vSendMessage(uint8 BufferID , uint32 ID , uint8 DLC , uint8* data);
/***************************************/
#endif /* ECUAL_LAYER_CAN_TRANSMITTER_CAN_TRANSMITTER_H_ */
