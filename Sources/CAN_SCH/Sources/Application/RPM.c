/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: RPM.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Jan/10/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \RPM
 * This file provides the functions of the Angular Tasks. 
 * The structure S__ANGULARTASK which receives the function and 
 * its angular execution.
 * Also gives the function that calculates the RPM of the motor and publishes
 * the CAN messages. 
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
/*----------------------------------------------------------------------------*/
/*   1.1 		|  	Jan/12/15 |Added the functions:			  |  Jorge Gomez  */
/*				|			  |RPM_NextSample & Calculate_RPMs|				  */
/*----------------------------------------------------------------------------*/
/*   1.2 		|  	Jan/13/15 |Added the function:			  | Jose Luis Mtz */
/*				|			  |DTC_Function					  |				  */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: RPM.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/RPM.h"

/* Constants and types  */
/*============================================================================*/
#define MAX_VALUE_RPM 		9000
#define NUM_CNT_PER_REV		18
#define CONST_60000			60000
#define CONST_50			50
#define CONST_100			100
#define MOTOR_ON			1
/*Angles*/
typedef enum{
	ANG_45DEG = 0,
	ANG_90DEG = 1,
	ANG_180DEG = 3,
	ANG_360DEG = 7
};


/* */
const S_ANGULARTASK cas_AngularTaskList[NUMBER_OF_ANG_TASKS] = 
{
	/*		Function			      		Angular execution(Pulses)*/
		{	AngularTask_LowRes		 ,				ANG_45DEG	},
		{	AngularTask_MidRes		 ,				ANG_90DEG	},
		{	AngularTask_HiRes		 ,				ANG_180DEG	},
};

/* Variables */
/*============================================================================*/
T_UWORD rauw_RPMsArray[10] = {0};
T_UBYTE rub_SamplerIndex = 0;
T_UWORD ruw_MotorRPMs = 0;

/* Private functions prototypes */
/*============================================================================*/


/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  AngularTask_LowRes
 *  Description          :  This task is going to be called every motor angular movement of 45°.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  An angular movement of 45° must have occur.
 *  Postcondition        :  The function has been execute. 
 *  SW design			 :	5.4
 *  Requirement			 :	Req_OS. 2.10
 **************************************************************/
void AngularTask_LowRes(void)
{
	
}

/**************************************************************
 *  Name                 :  AngularTask_MidRes
 *  Description          :  This task is going to be called every motor angular movement of 90°.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  An angular movement of 90° must have occur.
 *  Postcondition        :  The function has been execute. 
 *  SW design			 :	5.4
 *  Requirement			 :	Req_OS. 2.11
 **************************************************************/
void AngularTask_MidRes(void)
{
	CanManager_SendMessage_SPEED();
}

/**************************************************************
 *  Name                 :  AngularTask_HiRes
 *  Description          :  This task is going to be called every motor angular movement of 180°.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  An angular movement of 180° must have occur.
 *  Postcondition        :  The function has been execute. 
 *  SW design			 :	5.4
 *  Requirement			 :	Req_OS. 2.12
 **************************************************************/
void AngularTask_HiRes(void)
{
	
}

/**************************************************************
 *  Name                 :  RPM_NextSample
 *  Description          :  Increments the value of the sample to get 10 of them.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after 10 ms.
 *  Postcondition        :  The next sample is going to get it.
 *  SW design			 :	5.9
 *  Requirement		  	 :	Req_CAN_Mess 5.0
   **************************************************************/
void RPM_NextSample(void)
{
	T_UBYTE lub_IndexToClear = 0;
	if(rub_SamplerIndex < 10)
	{
		rub_SamplerIndex++;
		rauw_RPMsArray[rub_SamplerIndex] = 0;
	}
	else
	{
		rub_SamplerIndex = 0;
		rauw_RPMsArray[rub_SamplerIndex] = 0;
	}
}

/**************************************************************
 *  Name                 :  Calculate_RPMs
 *  Description          :  Calculates the Motor's RPMs
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after 100 ms
 *  Postcondition        :  The RPMs have been given
 *  SW design			 :	5.10
 *  Requirement		  	 :	Req_CAN_Mess 5.0
   **************************************************************/
void Calculate_RPMs(void)
{
	T_UBYTE lub_Index = 0;
	T_UWORD luw_Count = 0;
	T_ULONG lul_PartialRPMs = 0;
	for( ; lub_Index < 10; lub_Index++)
	{
		luw_Count += rauw_RPMsArray[lub_Index];
	}
	lul_PartialRPMs = (T_ULONG)((luw_Count * CONST_60000) / NUM_CNT_PER_REV);
	if((lul_PartialRPMs % CONST_100) >= CONST_50)
	{
		lul_PartialRPMs += CONST_100;
	}
	lul_PartialRPMs =lul_PartialRPMs/CONST_100;
	ruw_MotorRPMs = (T_UWORD)(lul_PartialRPMs); 
}

/**************************************************************
 *  Name                 :  DTC_Function
 *  Description          :  Sends the DTC CAN message 
 *  Parameters           :  T_UBYTE  (HIGH_CURRENT or OK_CURRENT)
 *  Return               :  void
 *  Precondition         :  A high current interrupt occurs.
 *  Postcondition        :  The DTC CAN message is sent. 
 *  SW design			 :	 5.5
 *  Requirement		  	 :	 Req_CAN_Mess 4.3, 4.4, 4.5
   **************************************************************/
void DTC_Function(T_UBYTE lub_DTCEvent)
{
	if(lub_DTCEvent == HIGH_CURRENT)
	{
		Eng_DTC.E_DTC.DTC_Status = 1;
		CanManager_SendMessage_DTC();
		LED_ON(EXTERNAL_LED1);
	}
	else if(lub_DTCEvent == OK_CURRENT)
	{
		Eng_DTC.E_DTC.DTC_Status = 0;
		CanManager_SendMessage_DTC();
		LED_OFF(EXTERNAL_LED1);
	}
	else{/*Do nothing*/}
}

/**************************************************************
 *  Name                 :  Motor_Status
 *  Description          :  Evaluates the staus of the motor 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The Task of 10ms must be called.
 *  Postcondition        :  Sets the status of the motor. 
 *  SW design			 :	5.6
 *  Requirement		  	 :	Req_CAN_Mess 4.6
   **************************************************************/
void Motor_Status(void)
{
	if(ruw_MotorRPMs > MOTOR_ON)
	{
		Eng_RPM.E_RPM.Engine_Active_Status = 1;
	}
	else
	{
		Eng_RPM.E_RPM.Engine_Active_Status = 0;
	}
}


/* Notice: the file ends with a blank new line to avoid compiler warnings */
