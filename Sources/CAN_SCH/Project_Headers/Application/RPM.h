/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: RPM.h $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Jan/10/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \RPM
 * This file provides the functions of the Angular Tasks. 
 * The structure S__ANGULARTASK which receives the function and 
 * its angular execution.
 * Also gives the function that calculates the RPM of the motor and publishes
 * the CAN messages. 
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
/*                    			OBJECT HISTORY                          	  */
/*============================================================================*/
/*  REVISION 	|  		DATE  |     COMMENT	     	 	 	  |AUTHOR  		  */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Jan/10/15 |Creation of the file and added |  Jorge Gomez  */
/*				|			  |	the functions 				  |				  */
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Jan/12/15 |Added the functions:			  |  Jorge Gomez  */
/*				|			  |RPM_NextSample & Calculate_RPMs|				  */
/*----------------------------------------------------------------------------*/
/*   1.2 		|  	Jan/13/15 |Added the function:			  | Jose Luis Mtz */
/*				|			  |DTC_Function					  |				  */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: RPM.h  $
  ============================================================================*/
#ifndef RPM_H_
#define RPM_H_

/* Includes */
/*============================================================================*/
#include "HAL/eMIOS.h"
#include "HAL/stdtypedef.h"
#include "MAL/Can_Manager.h"
#include "HAL/GPIO.h"
#include "Application/Speed.h"

/* Constants and types */
/*============================================================================*/
typedef void(*T_ANG_FUNC)(void);

typedef struct{
	T_ANG_FUNC PtrFunc;
	T_UBYTE Angle;
}S_ANGULARTASK;

typedef enum {
	ANGULARTASK1,
	ANGULARTASK2,
	ANGULARTASK3,
	/*number of task*/
	NUMBER_OF_ANG_TASKS
}E_NUM_ANGULARTASK;

#define HIGH_CURRENT 		1
#define OK_CURRENT 			0

/* Exported Variables */
/*============================================================================*/
PUBLIC_DATA const S_ANGULARTASK cas_AngularTaskList[NUMBER_OF_ANG_TASKS];
PUBLIC_DATA T_UWORD ruw_MotorRPMs;
PUBLIC_DATA T_UWORD rauw_RPMsArray[10];
PUBLIC_DATA T_UBYTE rub_SamplerIndex;

/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void AngularTask_LowRes(void);
PUBLIC_FCT void AngularTask_MidRes(void);
PUBLIC_FCT void AngularTask_HiRes(void);
PUBLIC_FCT void RPM_NextSample(void);
PUBLIC_FCT void Calculate_RPMs(void);
PUBLIC_FCT void DTC_Function(T_UBYTE lub_DTCEvent);
PUBLIC_FCT void Motor_Status(void);

#endif /* RPM_H_ */
