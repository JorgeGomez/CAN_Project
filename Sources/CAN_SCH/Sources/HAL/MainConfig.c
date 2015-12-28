/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: MainConfig.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \MainConfig
    Provide the function to initialize the differents periphereals of the uc.
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
/*  REVISION 	|  		DATE  		|     	COMMENT     	  |		AUTHOR 	  */
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Nov/13/15		| initialize the GPIO     |  Jorge Gomez  */
/*============================================================================*/
/*   1.1		|   Dic/22/15       |Unnecessary func've been |	Jorge Gomez   */
/*  			|					|removed and the tick time|	 	          */
/*  			|					|has been changed to 125us|	 	          */
/*============================================================================*/
/*
 * $Log: MainConfig.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/MPC5606B.h"
#include "HAL/MainConfig.h"
#include "HAL/IntcInterrupts.h"
#include "HAL/stdtypedef.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/
T_BOOLEAN rbi_TickFlag = FALSE;

/* Private functions prototypes */
/*============================================================================*/

void pit_config_fnc(void);
void pit_isr(void);
void init_pit_interrupts(void);


/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/


/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_system
 *  Description          :  Initialize all the modules of the cpu
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after correct startup.
 *  Postcondition        :  All the cpu and the peripherials are initialized.
 *  SW design			 :	5.2
 **************************************************************/
void init_system(void)
{
	init_pit_interrupts();
}

/**************************************************************
 *  Name                 :  read_button
 *  Description          :  Read the status of a selected button
 *  Parameters           :  T_UBYTE
 *  Return               :  E_BUTTON
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Return the value of the input.
 **************************************************************/
E_BUTTON read_button(T_UBYTE lub_Ch)
{
	return SIU.GPDI[lub_Ch].B.PDI;
}

/**************************************************************
 *  Name                 :  led_on
 *  Description          :  Turn on the selected LED
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The LED selected is going to turn on.
 **************************************************************/
void led_on(T_UBYTE lub_Ch)
{
	SIU.GPDO[lub_Ch].R = ON;
}

/**************************************************************
 *  Name                 :  led_off
 *  Description          :  Turn off the selected LED
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LED  is going to turn off.
 **************************************************************/
void led_off(T_UBYTE lub_Ch)
{
	SIU.GPDO[lub_Ch].R = OFF;
}

/**************************************************************
 *  Name                 :  led_toggle
 *  Description          :  Toggle the LED status selected
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LED is going to toggle its status.
 **************************************************************/
void led_toggle(T_UBYTE lub_Ch)
{
	SIU.GPDO[lub_Ch].R ^= 1;
}

/**************************************************************
 *  Name                 :  pit_config_fnc
 *  Description          :  Init function of PIT module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  Function init_pit_interrupts can be called.
 **************************************************************/
void pit_config_fnc(void)
{
    PIT.PITMCR.B.MDIS   = 1;    
        /*Disable PIT for initialization         */

    PIT.CH[0].LDVAL.R  = 8000;    
        /*value loaded in the Timer0: 8000 = (64Mhz * 125us)   */

    PIT.CH[0].TCTRL.B.TIE  = 1;    
        /*Timer 0 Interrupt : Enable    */

    PIT.CH[0].TCTRL.B.TEN = 1;    
        /*Start Timer 0 is : Enable    */ 
    
    PIT.PITMCR.B.FRZ = 1;
    	/*Freeze enable*/

    PIT.PITMCR.B.MDIS = 0;    
        /*PIT Module : Enable        */

}

/**************************************************************
 *  Name                 :  init_pit_interrupts
 *  Description          :  Init function of PIT interrupt
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after the function pit_config_fnc.
 *  Postcondition        :  The Interrupt Service Routine can be called.
 **************************************************************/
void init_pit_interrupts(void)
{
	pit_config_fnc();
	INTC_InstallINTCInterruptHandler(pit_isr,59,1); 
		/* vector59 for PIT Timer 0 */
	INTC.CPR.R = 0;
		/*assign the priority*/
}

/**************************************************************
 *  Name                 :  pit_isr
 *  Description          :  Interrupt service routine for PIT
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called every ms.
 *  Postcondition        :  The TickFlag is setted.
 **************************************************************/
void pit_isr(void)
{    		
		/* There's single interrupt for the ch0 of the pit: */
	
		if(PIT.CH[0].TFLG.B.TIF == 1)  
		{			
			rbi_TickFlag = TRUE;		/* toggle LED */
			PIT.CH[0].TFLG.B.TIF = 1;	/* Clear interrupt flag */ 
		}
		else
		{
			/* ... */
		}
}



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
