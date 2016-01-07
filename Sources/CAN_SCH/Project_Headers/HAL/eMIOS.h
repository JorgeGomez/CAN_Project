/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: eMIOS.h $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Jan/05/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \eMIOS
    Provide the functions to enable the eMIOS and gives the functionality of 
    Output Pulse Width and Frequency Modulation Buffered to eMIOS1 and 
    Modulus Up Counter Buffered to eMIOS0.
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
/*   1.0 		|  	Jan/05/15 |Creation of the file and added |  			  */
/* 				|			  |the functionality of MCB for	  |	Jorge Gomez	  */
/* 				|			  |eMIOS0.		  				  |				  */
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Jan/07/15 |Added the functionality of     |			      */
/* 				|			  | OPWFMB for	eMIOS0.           | Jorge Gomez	  */
/*============================================================================*/
/*
 * $Log: eMIOS.h  $
  ============================================================================*/

#ifndef EMIOS_H_			/* To avoid double inclusion */
#define EMIOS_H_

/* Includes */
/*============================================================================*/
#include "MPC5606B.h"
#include "stdtypedef.h"
#include "IntcInterrupts.h"

/* Constants and types */
/*============================================================================*/

/*----------------------------------Modulus Up Counter Buffered----------------------------------------------------------------*/
/* Counts*/
#define DEG_CNT						0x02						/* Number for the a 45° degree movement*/

/* eMIOS0 channels*/
#define DEG_CNT_CH16					16							/* Channel E0UC[16]*/

/* Vector numbers for the interruptions*/
#define VECTNUM_CH_EMIOS0_16_17		149							/* Interruption vector number for the channels 16 and 17*/

/* PCR*/
#define PCR_CNT_PE0					64							/* PCR for PE0 configured as an input for the counter*/

/*-----------------------Output Pulse Width and Frequency Modulation Buffered----------------------------------------------------*/
/* eMIOS1 channels*/
#define MOTOR_CH 					16							/* Channel E1UC[16]*/
#define PCR_MOTOR_PG7 				103							/* PCR for PG7 configured as an output for PWM*/

/* Exported Variables */
/*============================================================================*/
PUBLIC_DATA T_BOOLEAN rbi_Flag45Deg;	/*Flag for an interruption every 45 degree*/
PUBLIC_DATA T_UWORD ruw_DutyCycle_PWM;	/*DutyCycle goes from 0 to 1000*/
PUBLIC_DATA T_UWORD ruw_Period_PWM;		/*Period goes from 0 to 1000*/

/* Exported functions prototypes */
/*============================================================================*/
void init_eMIOS0(void);
void init_eMIOS0_MCB(void);
void eMIOS0_isr_CH_16_17(void);

void init_eMIOS1(void);
void init_eMIOS1_PWM(void);
void Set_DutyCycle_eMIOS1(void);
void Set_PeriodPWM_eMIOS1(void);

/* Functions prototypes */
/*============================================================================*/

#endif
/*  EMIOS_H_  Notice: the file ends with a blank new line to avoid compiler warnings */
