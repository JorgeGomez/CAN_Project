/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Speed.c $
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
 * $Log: Speed.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/Speed.h"

/* Constants and types  */
/*============================================================================*/

/* Resolution of the parameter */
#define INPUT_RESOLUTION	1000

/* Values for the prescaler*/
#define PRESCALER_BY2		2
#define PRESCALER_BY128		128

/* Constants */
#define P_COSTANT_50		50
#define P_COSTANT_320		320

/* Ranges of the PWM period*/
#define FIRST_RANGE			19
#define SECOND_RANGE		1000

/* Variables */
/*============================================================================*/
T_UWORD ruw_DutyCycle_PWM;			/*DutyCycle goes from 0 to 1000*/
T_UWORD ruw_Period_PWM;				/*Period goes from 0 to 1000*/
T_UWORD ruw_Current;				/*Current goes from 0 to 1023*/

/* Private functions prototypes */
/*============================================================================*/


/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  Set_DutyCycle_eMIOS1
 *  Description          :  Sets the Duty cycle of the PWM
 *  Parameters           :  T_UWORD (0 <= Duty <= 1000)
 *  Return               :  void
 *  Precondition         :  This function must be called after initialization of the eMIOS1 mode.
 *  Postcondition        :  The Duty cycle is set.
 *  SW design			 :	5.7
**************************************************************/
void Set_DutyCycle_eMIOS1(void)
{
	T_UWORD luw_RegA = 0;
	T_UWORD luw_RegB = 0;
	luw_RegB = Read_eMIOS1_RegB();												/*Gets the value of the period*/
	luw_RegA = (T_UWORD)((luw_RegB * ruw_DutyCycle_PWM)/INPUT_RESOLUTION);		/* Adjust the duty cycle for the new period*/
	Write_eMIOS1_RegA(luw_RegA);												/* Changes the duty cycle of the PWM */
}

/**************************************************************
 *  Name                 :  Set_PeriodPWM_eMIOS1
 *  Description          :  Sets the Period of the PWM goes from 0.1 to 100 ms
 *  Parameters           :  T_UWORD (0 <= Period <= 1000), T_UWORD (0 <= DutyCycle <= 1000)
 *  Return               :  void
 *  Precondition         :  This function must be called after initialization of the eMIOS1 mode.
 *  Postcondition        :  The Duty cycle is set.
 *  SW design			 :	5.8
**************************************************************/
void Set_PeriodPWM_eMIOS1(void)
{
	T_UWORD luw_RegisterB = 0;
	T_UWORD luw_RegisterA = 0;
	if(ruw_Period_PWM < FIRST_RANGE)
	{
		Set_Global_Prescaler(PRESCALER_BY2); 												/* Set the Global prescaler to 2*/
		luw_RegisterB = P_COSTANT_320 * (ruw_Period_PWM + 1);								/* This is the reduction for the equation luw_RegisterB = (SysClk)/[(GlobalPrescaler)*(f)]
																							/* Where SysClk = 64M, GlobalPrescaler = 2 and f = 10000/(luw_Period + 1)*/
		Write_eMIOS1_RegB(luw_RegisterB); 													/* Changes the Period of the PWM */
		luw_RegisterA = (T_UWORD)((luw_RegisterB * ruw_DutyCycle_PWM)/INPUT_RESOLUTION);	/* Adjust the duty cycle for the new period*/
		Write_eMIOS1_RegA(luw_RegisterA);													/* Changes the duty cycle of the PWM */
	}
	else if((ruw_Period_PWM >= FIRST_RANGE) && (ruw_Period_PWM <= SECOND_RANGE))
	{
		Set_Global_Prescaler(PRESCALER_BY128);  											/* Set the Global prescaler to 128*/
		luw_RegisterB = P_COSTANT_50 * (ruw_Period_PWM + 1);								/* This is the reduction for the equation luw_RegisterB = (SysClk)/[(GlobalPrescaler)*(f)]
																							/* Where SysClk = 64M, GlobalPrescaler = 128 and f = 10000/(luw_Period + 1)*/
		Write_eMIOS1_RegB(luw_RegisterB); 			 										/* Changes the Period of the PWM */
		luw_RegisterA = (T_UWORD)((luw_RegisterB * ruw_DutyCycle_PWM)/INPUT_RESOLUTION);	/* Adjust the duty cycle for the new period*/
		Write_eMIOS1_RegA(luw_RegisterA);													/* Changes the duty cycle of the PWM */
	}
	else{	/*Do nothing*/	}
	
}

/* Notice: the file ends with a blank new line to avoid compiler warnings */
