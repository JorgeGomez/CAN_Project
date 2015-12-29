/*============================================================================*/
/*                        			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: ADC.h $
 * $Revision: version 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Dec/28/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \ADC
 *  Provide the functions to enable the ADC and get its information
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
/*   1.0 		|  	Dec/28/15 |Creation of the file			  |  Jorge Gomez  */
/*============================================================================*/
/*
 * $Log: ADC.h  $
  ============================================================================*/

#ifndef ADC_H                               /* To avoid double inclusion */
#define ADC_H

/* Includes */
/*============================================================================*/

#include "MPC5606B.h"
#include "stdtypedef.h"

/* Constants and types */
/*============================================================================*/

#define  ONE_SHOT_MODE      0
#define  SCAN_MODE          1

#define  PWM_DUTY		    1	/*Channel 1 in PB5*/
#define  PWM_FREC	 	    2	/*Channel 1 in PB6*/
#define  M_CURRENT		    3	/*Channel 1 in PB7*/

/* Exported Variables */
/*============================================================================*/

/* Exported functions prototypes */
/*============================================================================*/

PUBLIC_DATA void ADCModeSelector(T_UBYTE lub_AdcMode);
PUBLIC_DATA void ADC_Config(void);
PUBLIC_DATA T_ULONG Read_ADC(T_UBYTE channel);

/* Functions prototypes */
/*============================================================================*/

#endif
/* ADC_H_  Notice: the file ends with a blank new line to avoid compiler warnings */
