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
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Dec/28/15 |Added  corrections and fixes   |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.2		|  	Dec/29/15 |Added more comments			  |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.3		|  	Jan/04/15 |Correction in function ReadADC |  Jorge Gomez  */
/*============================================================================*/
/*
 * $Log: ADC.h  $
  ============================================================================*/

#ifndef ADC_H                               /* To avoid double inclusion */
#define ADC_H

/* Includes */
/*============================================================================*/

#include "HAL/MPC5606B.h"
#include "HAL/stdtypedef.h"

/* Constants and types */
/*============================================================================*/
/*ADC0 Modes*/
#define  ONE_SHOT_MODE      0
#define  SCAN_MODE          1

/*Channels for ADC0*/
#define  PWM_DUTY		    1	/*Channel 1 in PB5*/
#define  PWM_FREC	 	    2	/*Channel 1 in PB6*/
#define  M_CURRENT		    3	/*Channel 1 in PB7*/

/* Exported Variables */
/*============================================================================*/

/* Exported functions prototypes */
/*============================================================================*/

PUBLIC_FCT void ADCModeSelector(T_UBYTE lub_AdcMode);
PUBLIC_FCT void ADC_Config(void);
PUBLIC_FCT T_UWORD Read_ADC(T_UBYTE lub_Channel);

/* Functions prototypes */
/*============================================================================*/

#endif
/* ADC_H_  Notice: the file ends with a blank new line to avoid compiler warnings */
