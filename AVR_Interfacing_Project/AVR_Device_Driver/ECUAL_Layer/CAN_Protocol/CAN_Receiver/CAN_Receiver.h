/*
 * CAN_Receiver.h
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_CAN_RECEIVER_CAN_RECEIVER_H_
#define ECUAL_LAYER_CAN_RECEIVER_CAN_RECEIVER_H_

/*********** Includes ******************/
#include "../../MCAL_Layer/GPIO/GPIO.h"
#include "../../MCAL_Layer/SPI/SPI.h"
/***************************************/
/************* Macros ******************/

#define READ_INST       			 0x03
#define WRITE_INST          		 0x02
#define BIT_MODIFY_INST     		 0x05
#define REST_INST            		 0xC0

#define BUFFER0              0
#define BUFFER1              1

#define CANF1                0x2A
#define CANF2                0x29
#define CANF3                0x28

#define CANCTRL              0x0F
#define NORMAL_MODE          0x04
#define CONFG_MODE           0x84

#define RXB0CTRL             0x60
#define RXB1CTRL             0x70

#define RXM0SIDH             0x20
#define RXM1SIDH             0x24

#define CANINTE              0x2B
#define CANINTF              0x2C


/***************************************/
/*************** Data Types ************/

/***************************************/
/************** APIs *****************/

uint8 CAN_vReceiverReadRegister(uint8 address);

void CAN_vReceiverWriteRegister(uint8 address , uint8 data);

void CAN_vBitModifyReceiverRegister(uint8 address , uint8 Mask ,uint8 data);

void CAN_vSetBitTimingReceiver(uint8 CANF1_value , uint8 CANF2_value , uint8 CANF3_value);

void CAN_vReceiverSetMode(uint8 mode);

void CAN_vSetMask(uint8 mask_adress , uint32 value);

void CAN_vReceiverInit(void);

void CAN_vReadMessage(uint8 BufferID , uint8 *data);
/***************************************/

#endif /* ECUAL_LAYER_CAN_RECEIVER_CAN_RECEIVER_H_ */
