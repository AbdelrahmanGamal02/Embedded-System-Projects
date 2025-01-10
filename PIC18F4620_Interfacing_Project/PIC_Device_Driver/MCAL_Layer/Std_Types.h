/*
 * File:   Std_Types.h
 * Author: abdo
 *
 * Created on September 19, 2023, 4:59 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/*************** Includes  ***********************/
#include "Std_Libraries.h"
#include "compile.h"
/*************************************************/

/************** Marcos Declarations **************/

#define Func_OK        (Std_ReturnType)0x01
#define Func_Not_OK    (Std_ReturnType)0x00

/*************************************************/
/********** Marcos Function Declarations *********/

/*************************************************/
/************ Data Type Declarations **************/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef float float32;
typedef double float64;

typedef uint8 Std_ReturnType;

/*************************************************/

#endif	/* STD_TYPES_H */

