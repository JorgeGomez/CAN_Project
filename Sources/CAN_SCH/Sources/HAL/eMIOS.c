/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: eMIOS.c $
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
/*   1.0 		|  	Jan/05/15 |Creation of the file			  |  Jorge Gomez  */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: eMIOS.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/eMIOS.h"

/* Constants and types  */
/*============================================================================*/
#define INITIAL_PERIOD		10000						/* Initial Period*/
#define INITIAL_DUTYCYCLE 	5000						/* Initial value for Duty cycle*/

/* Variables */
/*============================================================================*/
T_UWORD ruw_DutyCycle_PWM;			/*DutyCycle goes from 0 to 1000*/
T_UWORD ruw_Period_PWM;				/*Period goes from 0 to 1000*/
T_BOOLEAN rbi_Flag45Deg = FALSE;	/*Flag for an interruption every 45 degree*/

/* Private functions prototypes */
/*============================================================================*/

/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_eMIOS0
 *  Description          :  Init function to enable the eMIOS0
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The eMIOS0 is enabled.
 **************************************************************/
void init_eMIOS0(void)
{
	EMIOS_0.MCR.B.GPRE= 0;   							/* Divide 64 MHz sysclk by 0+1 = 1 for 64MHz eMIOS0 clk*/
  	EMIOS_0.MCR.B.GPREN = 1;  							/* Enable eMIOS0 clock */
  	EMIOS_0.MCR.B.GTBE = 1;   							/* Enable global time base */
  	EMIOS_0.MCR.B.FRZ = 1;    							/* Enable stopping channels when in debug mode */
}

/**************************************************************
 *  Name                 :  init_eMIOS0_MCB
 *  Description          :  Configures the operation mode of eMIOS0 and assign the ISR for the counter
 *  						as Modulus Up Counter Buffered and configures the pin PE0 as its intput
 *  Parameters           :  lp_InterruptFncPtr (Pointer to a function)
 *  Return               :  void
 *  Precondition         :  This function must be called after eMIOS0 initialization.
 *  Postcondition        :  The input pin (PE0) and the eMIOS0 are configured.
 **************************************************************/
void init_eMIOS0_MCB()
{								
	EMIOS_0.CH[DEG_CNT_CH16].CADR.R = DEG_CNT;												/* Initialises the number of pulses for the interruption */
  	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.MODE = 0x51; 											/* Set as Modulus Up Counter Buffered (MCB) */
  	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.BSL = 0x1;												/* Use counter bus B,C,D,or E */
 	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.UCPRE = 0;    											/* Set channel prescaler divide by 1 */
  	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.UCPEN = 1;    											/* Enable prescaler*/
  	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.FREN = 1; 												/* Freeze channel counting when in debug mode */
  	SIU.PCR[PCR_CNT_PE0].R = 0x500;         												/* MPC56xxB: Assign EMIOS_0 Input to pad */
  	EMIOS_0.CH[DEG_CNT_CH16].CSR.B.FLAG = 1;												/* Clear the flag of the channel*/
	INTC_InstallINTCInterruptHandler(&eMIOS0_isr_CH_16_17, VECTNUM_CH_EMIOS0_16_17, 1);		/* Initialises the interrupt handler*/
	INTC.CPR.R = 0;																			/* Sets the priority*/
	EMIOS_0.CH[DEG_CNT_CH16].CCR.B.FEN = 1;													/* Enables the interruption for the channel*/
}

/**************************************************************
 *  Name                 :  eMIOS0_isr_CH_16_17
 *  Description          :  ISR of the interruption of the eMIOS0 channels 16 and 17
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after an interruption.
 *  Postcondition        :  
 **************************************************************/
void eMIOS0_isr_CH_16_17(void)
{
	if(EMIOS_0.CH[DEG_CNT_CH16].CSR.B.FLAG == 1)					/* Checks if the flag of the channel 16 is set*/
	{
		rbi_Flag45Deg = TRUE;
		EMIOS_0.CH[DEG_CNT_CH16].CSR.B.FLAG = 1;					/* Clears the flag of the channel 16*/
	}
}

/* Notice: the file ends with a blank new line to avoid compiler warnings */
