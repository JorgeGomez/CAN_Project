/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Speed.h $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Jan/10/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \Speed
    Provide the functions to control the Period and the DutyCycle of the PWM.
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
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: Speed.h  $
  ============================================================================*/

#ifndef SPEED_H_
#define SPEED_H_

/* Includes */
/*============================================================================*/
#include "HAL/eMIOS.h"
#include "HAL/stdtypedef.h"

/* Constants and types */
/*============================================================================*/


/* Exported Variables */
/*============================================================================*/
PUBLIC_DATA T_UWORD ruw_DutyCycle_PWM;	/*DutyCycle goes from 0 to 1000*/
PUBLIC_DATA T_UWORD ruw_Period_PWM;		/*Period goes from 0 to 1000*/
PUBLIC_DATA T_UWORD ruw_Current;		/*Current goes from 0 to 1000*/

/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void Set_DutyCycle_eMIOS1(void);
PUBLIC_FCT void Set_PeriodPWM_eMIOS1(void);

#endif /* SPEED_H_ */
