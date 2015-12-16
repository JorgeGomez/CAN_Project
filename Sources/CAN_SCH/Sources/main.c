/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: main.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \main
    MAIN FUNCTION.
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
/*  REVISION 	|  		DATE  		|     COMMENT 	     	  |		AUTHOR 	  */
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Nov/13/15		|   add main function     |  Jorge Gomez  */
/*============================================================================*/
/*                               				                              */
/*============================================================================*/
/*
 * $Log: main.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/MainConfig.h"
#include "MAL/Kernel.h"

#include "HAL/GPIO.h"
#include "HAL/bspi.h"
#include "HAL/Can.h"
#include "HAL/Can_Cfg.h"
#include "HAL/sysinit.h"
#include "HAL/Exceptions.h"
#include "HAL/IntcInterrupts.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/



/* Private functions prototypes */
/*============================================================================*/



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  main
 *  Description          :  Main function of the program
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialization of the startup code.
 *  Postcondition        :  The cpu can be configured and the program can start.
 *  SW design			 :	5.2
 **************************************************************/
void main(void) 
{
	/* Mode initializations */
	sysinit_InitMode();
	/* Clock initializations */
	sysinit_InitSysClock();
	/*Initialize LEDs on TRK-MPC560xB board */
	vfnGPIO_LED_Init(); 
	/* SBC (System Basis Chip (the transceiver, you know)) dependencies */
	/* The SBC is initialized by SPI */
	InitDSPI_1();
	/* SBC configuration */
	ConfigureMZC33905DSPI_1();
    /* CAN Initialization */
	CAN_Initialization(&can_driver_config);
	/* Initialize Interrupts */
	INTC_InitINTCInterrupts();
	/*Initialize Exception Handlers */
	EXCEP_InitExceptionHandlers();
	/*Initializes the system for the correct operation*/ 
	init_system();
	/*Initializes the counters with the offsets*/
	init_Sch_TimeCntrs();
	/*Starts the scheduler execution*/
	Sch_function_execution();	
}


/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
