/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Can_Manager.c $
 * $Revision: 1.0 $
 * $Author: Francisco Martinez $
 * $Date: 16/08/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \brief
    Provide Can Services
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
/*   1.0 		|  16/08/2015 |								  |Francisco Mtz  */
/*============================================================================*/
/*   1.1 		|  23/12/2015 |	added new functions			  |Jorge Gomez	  */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: Can_Manager.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "MAL/Can_Manager.h"

/* Constants and types  */
/*============================================================================*/
#define OFFSET			9
#define CONST_640616	640616
#define CONST_1677721	1677721
#define CONST_100		100
#define CONST_10000		10000

/* Variables */
/*============================================================================*/

M_ENG_RPM Eng_RPM;
M_ENG_SPEED Eng_Speed;
M_ENG_DTC Eng_DTC;

/** PDU: Protocol data unit */
CAN_PduType    pdu_handler4_RPM 	= { 4, 3, Eng_RPM.A_RPM};						/* ID:0x100*/
CAN_PduType    pdu_handler5_SPEED 	= { 5, 7, (&(Eng_Speed.A_SPEED[1]))};			/* ID:0x101*/
CAN_PduType    pdu_handler6_DTC 	= { 6, 4, Eng_DTC.A_DTC};						/* ID:0x102*/

/* Private functions prototypes */
/*============================================================================*/


/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  CanManager_SendMessage_RPM ID:0x100
 *  Description          :  Function that sends the RPM 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called every 10 ms.
 *  Postcondition        :  A CAN message has been sent.
 *  Requirement		  	 :	Req_CtrlSpeed 3.1 and Req_CAN_Mess 4.8
 **************************************************************/
void CanManager_SendMessage_RPM(void)
{
	Eng_RPM.E_RPM.RPM = ruw_MotorRPMs;
	Motor_Status();
	pdu_handler4_RPM.can_sdu = Eng_RPM.A_RPM;
	CAN_SendFrame(&pdu_handler4_RPM);
}


/**************************************************************
 *  Name                 :  CanManager_SendMessage_SPEED ID:0x101
 *  Description          :  Function that sends the Speed of the motor and other parameters 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after a MidRes event.
 *  Postcondition        :  A CAN message has been sent.
 *  Requirement		  	 :	Req_CtrlSpeed 3.1 and Req_CAN_Mess 4.8
 **************************************************************/
void CanManager_SendMessage_SPEED(void)
{
	Eng_Speed.E_SPEED.DutyCycle = (T_ULONG)((ruw_DutyCycle_PWM * CONST_1677721)/CONST_100);
	Eng_Speed.E_SPEED.Period = ruw_Period_PWM - OFFSET;
	Eng_Speed.E_SPEED.Current =(T_UWORD)((ruw_Current * CONST_640616)/CONST_10000);
	pdu_handler5_SPEED.can_sdu = (&(Eng_Speed.A_SPEED[1]));
	CAN_SendFrame(&pdu_handler5_SPEED);
}

/**************************************************************
 *  Name                 :  CanManager_SendMessage_DTC ID:0x102
 *  Description          :  Function that sends the information of an error 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after an over current error.
 *  Postcondition        :  A CAN message has been sent.
 *  Requirement		  	 :	Req_CtrlSpeed 3.1 and Req_CAN_Mess 4.8
 **************************************************************/
void CanManager_SendMessage_DTC(void)
{
	Eng_DTC.E_DTC.DTC.HSB = 'E';
	Eng_DTC.E_DTC.DTC.MSB = 'C';
	Eng_DTC.E_DTC.DTC.LSB = 'M';
	pdu_handler6_DTC.can_sdu = Eng_DTC.A_DTC;
	CAN_SendFrame(&pdu_handler6_DTC);
}
/* Notice: the file ends with a blank new line to avoid compiler warnings */
