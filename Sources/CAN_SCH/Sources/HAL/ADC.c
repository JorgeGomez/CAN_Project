/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: ADC.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Dec/28/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \ADC
    Provide the functions to enable the ADC and get its information
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
/*   1.1 		|  	Dec/28/15 |Added Corrections and fixes 	  |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.2 		|  	Dec/29/15 |Added more comments			  |  Jorge Gomez  */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: ADC.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/ADC.h"

/* Constants and types  */
/*============================================================================*/
#define  ADC0_P1            21	/*PCR for PB5*/
#define  ADC0_P2            22	/*PCR for PB6*/
#define  ADC0_P3            23	/*PCR for PB7*/

/* Variables */
/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/

/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  ADC_Config
 *  Description          :  Init function of the input pins
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The input pins are configured.
 **************************************************************/
 void ADC_Config(void)
 {
	 SIU.PCR[ADC0_P1].R = 0x2000;
	 SIU.PCR[ADC0_P2].R = 0x2000;
	 SIU.PCR[ADC0_P3].R = 0x2000;
 }
 
 /**************************************************************
  *  Name                 :  ADCModeSelector
  *  Description          :  Selects the mode of lecture for the ADC0
  *  Parameters           :  T_UBYTE		(ADCMode : ONE_SHOT_MODE or SCAN_MODE)
  *  Return               :  void
  *  Precondition         :  This function must be called after cpu initialization.
  *  Postcondition        :  The lecture mode of the ADC is configured.
  **************************************************************/
 void ADCModeSelector(T_UBYTE lub_AdcMode)
 {		
 	if(lub_AdcMode == ONE_SHOT_MODE) 	/*if One shot mode has been selected*/
	{
 		ADC_0.MCR.R = 0x00000000;		/*Chooses the mode : One shot*/
 		ADC_0.NCMR0.R = 0x0E; 			/*Enable PChannels 1, 2, 3*/
 		ADC_0.CTR0.R = 0x00008606;
 		ADC_0.MCR.B.NSTART=1;			/*Starts the conventions*/
	}
	
	else if(lub_AdcMode == SCAN_MODE)	/*if Scan mode has been selected*/
	{
		ADC_0.MCR.R = 0x20000000;		/*Chooses the mode : Scan mode*/
		ADC_0.NCMR0.R = 0x0E; 			/*Enable PChannels 1, 2, 3*/
		ADC_0.CTR0.R = 0x00008606;
		ADC_0.MCR.B.NSTART=1;			/*Starts the conventions*/
	}
	else
	{
		/*do nothing*/
	}
}

 /**************************************************************
  *  Name                 :  Read_ADC
  *  Description          :  Returns the value of the selected channel
  *  Parameters           :  T_UBYTE	(Channel of ADC0 : PWM_DUTY, PWM_FREC or M_CURRENT)
  *  Return               :  T_ULONG	(0 < AdcValue < 1023)
  *  Precondition         :  A correct lecture of the ADC.
  *  Postcondition        :  Returns the value of the channel.
  **************************************************************/
 T_ULONG Read_ADC(T_UBYTE lub_Channel)
 {
	 T_ULONG lul_AdcValue = 0;
	 lul_AdcValue = ADC_0.CDR[lub_Channel].B.CDATA;
	 return lul_AdcValue;
 }

 /* Notice: the file ends with a blank new line to avoid compiler warnings */
