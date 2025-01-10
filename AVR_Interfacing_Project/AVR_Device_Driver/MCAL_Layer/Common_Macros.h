/*
 * Common_Marcos.c
 *
 *  Created on: 17/9/2022
 *      Author: Abdelrahman Gamal
 */

#ifndef MCAL_LAYER_COMMON_MACROS_H_
#define MCAL_LAYER_COMMON_MACROS_H_

#define READ_BIT(reg , bit_position)    (reg & (1<<bit_position))

#define SET_BIT(reg , bit_position)     (reg |= (1<<bit_position))

#define TOGGLE_BIT(reg , bit_position)  (reg ^= (1<<bit_position))

#define CLEAR_BIT(reg , bit_position)   (reg &= ~(1<<bit_position))

#define BIT_IS_CLEAR(reg , bit_position) (!(reg & (1<<bit_position)))

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )


#endif /* MCAL_LAYER_COMMON_MACROS_H_ */
