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
/*   1.1		|   Dic/03/15       |Changes were added to the|Jose Luis Mtz  */
/*  			|					|  configuration for LIN  |	 	          */
/*============================================================================*/
/*                              					                          */
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
void init_modes_and_clocks(void);
void disableWatchdog(void);
void initPeriClkGen(void);
void config_Emb_IO(void);
void pit_config_fnc(void);
void pit_isr(void);
void init_pit_interrupts(void);


/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_modes_and_clocks
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The cpu are running on RUN mode 1.
 **************************************************************/
void init_modes_and_clocks(void) 
{
	ME.MER.R = 0x0000001D;          	/* Enable DRUN, RUN0, SAFE, RESET modes */
	
	/* Initialize PLL before turning it on: */
	CGM.FMPLL_CR.R = 0x02400100;    	/* 8 MHz xtal: Set PLL0 to 64 MHz */   
	ME.RUN[0].R = 0x001F0074;       	/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
	ME.RUNPC[1].R = 0x00000010; 	  	/* Peri. Cfg. 1 settings: only run in RUN0 mode */
  	ME.PCTL[68].R = 0x01; 	    		/*MPC56xxB/S SIU: select ME.RUNPC[1] */  
  	ME.PCTL[92].R = 0x01; 	      		/* MPC56xxB/S PIT: select ME.RUNPC[1] */
  	
  	/* Mode Transition to enter RUN0 mode: */
  	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  	while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  	
  	/* Note: could wait here using timer and/or I_TC IRQ */
  	while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}

/**************************************************************
 *  Name                 :  disableWatchdog
 *  Description          :  Function to disable the watchdog
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The watchdog is disabled.
 **************************************************************/
void disableWatchdog(void) 
{
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  	SWT.SR.R = 0x0000d928; 
  	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        

/**************************************************************
 *  Name                 :  initPeriClkGen
 *  Description          :  Init function of peripherials set 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The pheripherial set can be used.
 **************************************************************/
void initPeriClkGen(void) 
{
	/* Use the following code as required for MPC56xxB or MPC56xxS:*/
	CGM.SC_DC0.R = 0x80;
  	CGM.SC_DC1.R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
  	CGM.SC_DC2.R = 0x80;   
}

/**************************************************************
 *  Name                 :  config_Emb_IO
 *  Description          :  Init function of GPIO embedded
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The GPIOs can be used.
 **************************************************************/
void config_Emb_IO(void)
{
  	/* led is seted as outputs */
  	SIU.PCR[LED_1].R = 0x200;
  	
  	/* Configure pad PB2 for AF1 func: LIN0TX */
    SIU.PCR[18].B.SRC = 1; 
    SIU.PCR[18].B.OBE = 1;
    SIU.PCR[18].B.PA = 1; 
    
    SIU.PCR[19].B.IBE = 1;     /* Configure pad PB3 for LIN0RX */

  	/* led init led in off */
	SIU.GPDO[LED_1].R = ON;

} 



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
	init_modes_and_clocks();
	initPeriClkGen();
	config_Emb_IO();
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

    PIT.CH[0].LDVAL.R  = 64000;    
        /*value loaded in the Timer0: 64k    */

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
