/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: eMIOS.c $
 * $Revision: 1.2 $
 * $Author: Jorge Gomez $
 * $Date: Jan/05/16 $
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
/*   1.0 		|  	Jan/05/16 |Creation of the file and added |  			  */
/* 				|			  |the functionality of MCB for	  |	Jorge Gomez	  */
/* 				|			  |eMIOS0.		  				  |				  */
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Jan/07/16 |Added the functionality of     |			      */
/* 				|			  | OPWFMB for	eMIOS0.           | Jorge Gomez	  */
/*----------------------------------------------------------------------------*/
/*   1.2 		|  	Jan/08/16 |Added the functions and		  |			      */
/* 				|			  |errors correction.             | Jorge Gomez	  */
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
T_BOOLEAN rbi_Flag45Deg = FALSE;	/*Flag for an interruption every 45 degree*/

/* Private functions prototypes */
/*============================================================================*/
void eMIOS0_isr_CH_16_17(void);

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
 *  Description          :  ISR of the interruption of the eMIOS0 channels 16 and 17. 
 *  						Called every 45°.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after an interruption.
 *  Postcondition        :  The flag for a 45° is set.
 **************************************************************/
void eMIOS0_isr_CH_16_17(void)
{
	if(EMIOS_0.CH[DEG_CNT_CH16].CSR.B.FLAG == 1)					/* Checks if the flag of the channel 16 is set*/
	{
		rbi_Flag45Deg = TRUE;
		EMIOS_0.CH[DEG_CNT_CH16].CSR.B.FLAG = 1;					/* Clears the flag of the channel 16*/
	}
}

/**************************************************************
 *  Name                 :  init_eMIOS1
 *  Description          :  Init function to enable the eMIOS1
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The eMIOS1 is enabled.
 **************************************************************/
void init_eMIOS1(void)
{
	EMIOS_1.MCR.B.GPRE= 127;   							/* Divide 64 MHz sysclk by 127+1 = 128 for 500KHz eMIOS1 clk*/
  	EMIOS_1.MCR.B.GPREN = 1;  							/* Enable eMIOS1 clock */
  	EMIOS_1.MCR.B.GTBE = 1;   							/* Enable global time base */
  	EMIOS_1.MCR.B.FRZ = 1;    							/* Enable stopping channels when in debug mode */
}

/**************************************************************
 *  Name                 :  init_eMIOS1_PWM
 *  Description          :  Configures the operation mode of eMIOS1
 *  						as Output Pulse Width and Frequency Modulation Buffered 
 *  						and configures the pin PG7 as its output
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after eMIOS0 initialization.
 *  Postcondition        :  The output pin (PG7) and the eMIOS1 are configured.
 **************************************************************/
void init_eMIOS1_PWM(void)
{								
  	EMIOS_1.CH[MOTOR_CH].CADR.R = INITIAL_DUTYCYCLE;    /* Sets the initial Duty cycle*/
  	EMIOS_1.CH[MOTOR_CH].CBDR.R = INITIAL_PERIOD;       /* Sets the initial Period*/
  	EMIOS_1.CH[MOTOR_CH].CCR.B.FORCMB = 1;				/*Compare to the register A*/
  	EMIOS_1.CH[MOTOR_CH].CCR.B.FORCMA = 1;				/*Compare to the register B*/
  	EMIOS_1.CH[MOTOR_CH].CCR.B.BSL = 0x0;				/* Use counter bus B,C,D,or E */
  	EMIOS_1.CH[MOTOR_CH].CCR.B.EDPOL = 0;				/* Polarity-leading edge sets output/trailing clears */
  	EMIOS_1.CH[MOTOR_CH].CCR.B.MODE = 0x5A; 			/* Mode is Output Pulse Width and Frequency Modulation Buffered */
  	EMIOS_1.CH[MOTOR_CH].CCR.B.UCPRE = 0;				/* Set channel prescaler divide by 1 */
  	EMIOS_1.CH[MOTOR_CH].CCR.B.UCPEN = 1;    			/* Enable prescaler*/
  	EMIOS_1.CH[MOTOR_CH].CCR.B.FREN  = 1; 				/* Enable stopping channels when in debug mode */
  	SIU.PCR[PCR_MOTOR_PG7].R = 0x0600;           		/* MPC56xxB: Assign eMIOS1 PCR to pad */
}

/**************************************************************
 *  Name                 :  Read_eMIOS1_RegB
 *  Description          :  Returns the value of the B register
 *  Parameters           :  void
 *  Return               :  T_UWORD (0 <= Value of the B Register <= 65535)
 *  Precondition         :  This function must be called after initialization of the eMIOS1.
 *  Postcondition        :  The value of the B register is given.
 **************************************************************/
T_UWORD Read_eMIOS1_RegB(void)
{
	return (T_UWORD)(EMIOS_1.CH[MOTOR_CH].CBDR.R);		/*Returns the value of the B register*/
}

/**************************************************************
 *  Name                 :  Write_eMIOS1_RegB
 *  Description          :  Writes the value on the B register
 *  Parameters           :  void
 *  Return               :  T_UWORD (0 <= Value to set in the B Register <= 65535)
 *  Precondition         :  This function must be called after initialization of the eMIOS1.
 *  Postcondition        :  The value in the B register is changed.
 **************************************************************/
void Write_eMIOS1_RegB(T_UWORD luw_BValue)
{
	EMIOS_1.CH[MOTOR_CH].CBDR.R = luw_BValue;			/* Writes the value on the B register*/
}

/**************************************************************
 *  Name                 :  Read_eMIOS1_RegA
 *  Description          :  Returns the value of the A register
 *  Parameters           :  void
 *  Return               :  T_UWORD (0 <= Value of the A Register <= 65535)
 *  Precondition         :  This function must be called after initialization of the eMIOS1.
 *  Postcondition        :  The value of the A register is given.
 **************************************************************/
T_UWORD Read_eMIOS1_RegA(void)
{
	return (T_UWORD)(EMIOS_1.CH[MOTOR_CH].CADR.R);		/*Returns the value of the A register*/
}

/**************************************************************
 *  Name                 :  Write_eMIOS1_RegA
 *  Description          :  Writes the value on the A register
 *  Parameters           :  void
 *  Return               :  T_UWORD (0 <= Value to set in the A Register <= 65535)
 *  Precondition         :  This function must be called after initialization of the eMIOS1.
 *  Postcondition        :  The value in the A register is changed.
 **************************************************************/
void Write_eMIOS1_RegA(T_UWORD luw_AValue)
{
	EMIOS_1.CH[MOTOR_CH].CADR.R = luw_AValue;			/* Writes the value on the A register*/
}

/**************************************************************
 *  Name                 :  Set_Global_Prescaler
 *  Description          :  Sets the value in the global prescaler.
 *  Parameters           :  void
 *  Return               :  T_UWORD (0 <= GlobalPrescalerValue <= 255)
 *  Precondition         :  This function must be called after initialization of the eMIOS1 mode.
 *  Postcondition        :  The Duty cycle is set.
 **************************************************************/
void Set_Global_Prescaler(T_UWORD luw_GlobalPrescalerValue)
{
	if(luw_GlobalPrescalerValue != 0)
	{
		if(luw_GlobalPrescalerValue > 256)
		{
			luw_GlobalPrescalerValue = 256;
		}
		EMIOS_1.MCR.B.GPRE = luw_GlobalPrescalerValue - 1;	/* Set the Global prescaler - 1 to get the wanted value*/
	}
	else
	{
		EMIOS_1.MCR.B.GPRE = luw_GlobalPrescalerValue;		/*If the value of the prescaler is 0 assign the value directly*/
	}
}

/* Notice: the file ends with a blank new line to avoid compiler warnings */
