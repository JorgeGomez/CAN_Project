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
/*----------------------------------------------------------------------------*/
/*   1.3		|  	Jan/04/15 |Correction in function ReadADC |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.4		|  	Jan/12/15 | Added interruption of Watchdog|  Jose Martinez*/
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

/*Interrupt vector number for a watchdog interrupt*/
#define	 VECNUM_ADC0_WD 	64
/* */
#define	 MAX_CURRENT		1023
#define	 THRESHOLD_CURRENT	400
#define	 MIN_CURRENT		0
/* Variables */
/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/

/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/
 void ADC_isr_WD_CH3(void);
 
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
	 SIU.PCR[ADC0_P1].R = 0x2100;
	 SIU.PCR[ADC0_P2].R = 0x2100;
	 SIU.PCR[ADC0_P3].R = 0x2100;
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
	 if(lub_AdcMode == ONE_SHOT_MODE) 												/* If One shot mode has been selected*/
	 {
		 ADC_0.MCR.R = 0x00000000;													/* Chooses the mode : One shot*/
		 ADC_0.NCMR0.R = 0x0E; 														/* Enable PChannels 1, 2, 3*/
		 ADC_0.CTR0.R = 0x00008602;
		 ADC_0.MCR.B.NSTART=1;														/* Starts the conventions*/
		 ADC_0.CWSELR0.B.WSEL_CH3 = 0x0;											/* THRHLR0 register is selected*/ 
		 ADC_0.CWENR0.B.CWEN3 = 1;													/* Channel 3 Watchdog enable*/
		 ADC_0.THRHLR0.B.THRH = THRESHOLD_CURRENT;									/* High threshold value for an interruption*/
		 ADC_0.THRHLR0.B.THRL = THRESHOLD_CURRENT;									/* Low threshold value for an interruption*/

		 INTC_InstallINTCInterruptHandler(&ADC_isr_WD_CH3, VECNUM_ADC0_WD, 10);		/* Initialises the interrupt handler*/
		 INTC.CPR.R = 0;															/* Sets the priority*/
		 ADC_0.WTIMR.B.MSKWDG0H = 1;												/* Enables the Channe0 for a high threshold interrupt */
		 ADC_0.WTIMR.B.MSKWDG0L = 1;												/* Enables the Channe0 for a low threshold interrupt */
		 ADC_0.WTISR.B.WDG0H = 1;													/* Clears the high threshold flag of the Channel0*/
	 }

	 else if(lub_AdcMode == SCAN_MODE)												/* If Scan mode has been selected*/
	 {
		 ADC_0.MCR.R = 0x20000000;													/* Chooses the mode : Scan mode*/
		 ADC_0.NCMR0.B.CH1 = 1;														/* Enable PChannel 1 Dutycycle*/
		 ADC_0.NCMR0.B.CH2 = 1;														/* Enable PChannel 2 Period*/
		 ADC_0.NCMR0.B.CH3 = 1;														/* Enable SChannel 3 Current*/
		 ADC_0.CTR0.R = 0x00008607;		
		 ADC_0.MCR.B.NSTART = 1;													/* Starts the conventions*/

		 ADC_0.CWSELR0.B.WSEL_CH3 = 0x0;											/* THRHLR0 register is selected*/ 
		 ADC_0.CWENR0.B.CWEN3 = 1;													/* Channel 3 Watchdog enable*/
		 ADC_0.THRHLR0.B.THRH = THRESHOLD_CURRENT;									/* High threshold value for an interruption*/
		 ADC_0.THRHLR0.B.THRL = THRESHOLD_CURRENT;									/* Low threshold value for an interruption*/

		 INTC_InstallINTCInterruptHandler(&ADC_isr_WD_CH3, VECNUM_ADC0_WD, 10);		/* Initialises the interrupt handler*/
		 INTC.CPR.R = 0;															/* Sets the priority*/
		 ADC_0.WTIMR.B.MSKWDG0H = 1;												/* Enables the Channe0 for a high threshold interrupt */
		 ADC_0.WTIMR.B.MSKWDG0L = 1;												/* Enables the Channe0 for a low threshold interrupt */
		 ADC_0.WTISR.B.WDG0H = 1;													/* Clears the high threshold flag of the Channel0*/
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
  *  Return               :  T_ULONG	(0 < AdcValue < 1000)
  *  Precondition         :  A correct lecture of the ADC.
  *  Postcondition        :  Returns the value of the channel.
  **************************************************************/
 T_UWORD Read_ADC(T_UBYTE lub_Channel)
 {
	 T_UWORD luw_AdcValue = 0;
	 luw_AdcValue = (T_UWORD)(ADC_0.CDR[lub_Channel].B.CDATA);
	 if(luw_AdcValue > 1000)
	 {
		 luw_AdcValue = 1000;
	 }
	 else {	/*Do nothing*/	 }
	 ADC_0.CDR[lub_Channel].B.CDATA = 0;
	 return luw_AdcValue;
 }
 
 /**************************************************************
  *  Name                 :  Read_ADC
  *  Description          :  Returns the value of the selected channel
  *  Parameters           :  T_UBYTE	(Channel of ADC0 : PWM_DUTY, PWM_FREC or M_CURRENT)
  *  Return               :  T_ULONG	(0 < AdcValue < 1023)
  *  Precondition         :  A correct lecture of the ADC.
  *  Postcondition        :  Returns the value of the channel.
  **************************************************************/
 T_UWORD Read_ADC_1024(T_UBYTE lub_Channel)
 {
	 T_UWORD luw_AdcValue = 0;
	 luw_AdcValue = (T_UWORD)(ADC_0.CDR[lub_Channel].B.CDATA);
	 ADC_0.CDR[lub_Channel].B.CDATA = 0;
	 return luw_AdcValue;
 }
 
 /**************************************************************
  *  Name                 :  ADC_isr_WD_CH3
  *  Description          :  Watchdog ADC0 ISR of the  channels 3
  *  Parameters           :  void
  *  Return               :  void
  *  Precondition         :  This function must be called after an ADC0 Watchdog interruption.
  *  Postcondition        :  The CAN message DTC has been sent.
  *  SW design			  :	 5.4
  *  Requirement		  :	 Req_CAN_Mess 4.4
   **************************************************************/
 void ADC_isr_WD_CH3(void)
 {
	 if(ADC_0.WTISR.B.WDG0H == 1)
	 {
		 DTC_Function(HIGH_CURRENT);
		 ADC_0.THRHLR0.B.THRH = MAX_CURRENT;									/* Sets the High threshold value to 1023*/
		 ADC_0.THRHLR0.B.THRL = THRESHOLD_CURRENT;									/* Sets the Low threshold value to 800*/
		 ADC_0.WTISR.B.WDG0H = 1;										/* Resets the High threshold flag*/
	 }
	 else if(ADC_0.WTISR.B.WDG0L == 1)
	 { 
		 DTC_Function(OK_CURRENT);
		 ADC_0.THRHLR0.B.THRH = THRESHOLD_CURRENT;									/* Sets the High threshold value to 800*/
		 ADC_0.THRHLR0.B.THRL = MIN_CURRENT;										/* Sets the Low threshold value to 0*/
		 ADC_0.WTISR.B.WDG0L = 1;										/* Resets the High threshold flag*/
	 }

 }
 /* Notice: the file ends with a blank new line to avoid compiler warnings */
