/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Tasks.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \Tasks
    This file contain the tasks.
    Modify this file to add a new task.
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
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION 	|  		DATE  		|     COMMENT	     	  |		AUTHOR 	  */
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Nov/13/15		| 	  Added new tasks  	  |  Jorge Gomez  */
/*============================================================================*/
/*   1.1		|   Dic/03/15       |Unnecessary tasks were   |Jose Luis Mtz  */
/*  			|					|		removed			  |	 	          */
/*============================================================================*/
/*   1.2		|   Dic/22/15       |Added necessaries task   |Jorge Gomez	  */
/*  			|					|and dummy functions 	  |	 	          */
/*============================================================================*/
/*                      				 		                              */
/*============================================================================*/
/*
 * $Log: Tasks.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/

#include "MAL/Tasks.h"


/* Constants and types  */
/*============================================================================*/

/*
 * --------------------List of task for the scheduler-----------------------------
 * */
const S_TASK cas_TaskList[NUMBER_OF_TASKS] = 
{
	/*	Name					Execution Period(ticks)		Startup delay(ticks)	*/
		{	Task1_3p125ms	,				25	, 						0	},
		{	Task2_6p25ms	,				50	, 						1	},
		{	Task3_12p5ms	,				100	, 						2	},
		{	Task4_25ms		,				200	, 						3	},
		{	Task5_50ms		,				400	, 						4	},
		{	Task6_100ms		,				800	, 						5	},
		{	Task7_10ms		,				80	,						6	}
/*	{	Taskn,							Period, 				  offset}	Add if you need a new task*/
};


/* Variables */
/*============================================================================*/



/* Private functions prototypes */
/*============================================================================*/



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/*
 * --------Add a new definition if you need a new task--------------------------
 * */

/**************************************************************
 *  Name                 :  Task1_3p125ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task1_3p125ms(void)
{
	if(Read_ADC(M_CURRENT)>512)
	{
		Test(5);
	}
	else
	{
		Test(6);
	}
}

/**************************************************************
 *  Name                 :  Task2_6p25ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task2_6p25ms(void)
{
	
}

 /**************************************************************
  *  Name                 :  Task3_12p5ms
  *  Description          :  Init function of Scheduler module
  *  Parameters           :  void
  *  Return               :  void
  *  Precondition         :  This function must be called after cpu initialization.
  *  Postcondition        :  Function gsc_sch_core_exec can be called.
  **************************************************************/
void Task3_12p5ms(void)
{
	Test(1);
}

/**************************************************************
 *  Name                 :  Task4_25ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task4_25ms(void)
{
	Test(2);
}

/**************************************************************
 *  Name                 :  Task5_50ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task5_50ms(void)
{
	CanManager_SendMessage_SPEED();
	Test(3);
}

/**************************************************************
 *  Name                 :  Task6_100ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task6_100ms(void)
{
	CanManager_SendMessage_DTC();
//	Test(4);
}

/**************************************************************
 *  Name                 :  Task7_10ms
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Function gsc_sch_core_exec can be called.
 **************************************************************/
void Task7_10ms(void)
{
	CanManager_SendMessage_RPM();
}

/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
