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
/*   1.0 		|  	Dic/22/15		|   Added main function   |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Dic/23/15		|Added spi and Can drivers|  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.2 		|  	Dic/22/15		|Added the ADC drivers    |  Jorge Gomez  */
/*----------------------------------------------------------------------------*/
/*   1.3 		|  	Jan/07/15		|Added eMIOS drivers      |  Jorge Gomez  */
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
#include "HAL/ADC.h"
#include "HAL/bspi.h"
#include "HAL/Can.h"
#include "HAL/Can_Cfg.h"
#include "HAL/sysinit.h"
#include "HAL/Exceptions.h"
#include "HAL/IntcInterrupts.h"
#include "HAL/eMIOS.h"

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
 *  Requirement			 :	Req_Init. 1.1
 **************************************************************/
void main(void) 
{
	/* Mode initializations */
	sysinit_InitMode();
	/* Clock initializations */
	sysinit_InitSysClock();
	/*Initialize LEDs on TRK-MPC560xB board */
	vfnGPIO_LED_Init(); 
	/* SBC (System Basis Chip dependencies */
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
	/*Configure the ADC0*/
	ADCModeSelector(SCAN_MODE);
	ADC_Config();
	/*Configure the eMIOS*/
	init_eMIOS0();
	init_eMIOS0_MCB();
	init_eMIOS1();
	init_eMIOS1_PWM();
	/*Initializes the counters with the offsets*/
	init_Sch_TimeCntrs();
	/*Starts the scheduler execution*/
	Sch_function_execution();	
}


/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
