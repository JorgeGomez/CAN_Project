/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: Can_Manager.h
 * $Revision: version 1.0
 * $Author: Francisco Martinez
 * $Date: 16/08/2015
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 *  Provide Can Services for CAN
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |       			    |              1.0                */
/*					   |					|       					      */
/*============================================================================*/
/* added variables and |      CAN_project   |              1.1                */
/*	some operations    |					|   Jorge Gomez 			      */
/*============================================================================*/
/*
 * $Log: Can_Manager.h  $
  ============================================================================*/
#ifndef __CAN_MANAGER
#define __CAN_MANAGER

/* Includes */
/*============================================================================*/
#include "HAL/Can.h"

/* Constants and types */
/*============================================================================*/

typedef union{		
	struct{
		T_UWORD RPM;
		T_UBYTE Engine_Active_Status;
	}E_RPM;
	
	T_UBYTE A_RPM[3];
	
}M_ENG_RPM;

typedef union{
	struct{
		T_ULONG DutyCycle;
		T_UWORD Period;
		T_UWORD Current;
	}E_SPEED;
	T_UBYTE A_SPEED[8];
}M_ENG_SPEED;

typedef union{
	struct{
		struct{
				T_UBYTE HSB;
				T_UBYTE MSB;
				T_UBYTE LSB;
			}DTC;

			T_UBYTE DTC_Status;
		}E_DTC;

	T_UBYTE A_DTC[4];

}M_ENG_DTC;

/* Exported Variables */
/*============================================================================*/ 
extern M_ENG_RPM Eng_RPM;
extern M_ENG_SPEED Eng_Speed;
extern M_ENG_DTC Eng_DTC;

/* Exported functions prototypes */
/*============================================================================*/
extern void CanManager_SendMessage_RPM(void);
extern void CanManager_SendMessage_SPEED(void);
extern void CanManager_SendMessage_DTC(void);

#endif 
/* __CAN_MANAGER */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
