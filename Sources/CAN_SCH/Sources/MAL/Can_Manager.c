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


/* Variables */
/*============================================================================*/

M_ENG_RPM Eng_RPM;
M_ENG_SPEED Eng_Speed;
M_ENG_DTC Eng_DTC;

/** PDU: Protocol data unit */
CAN_PduType    pdu_handler4_RPM 	= { 4, 3, Eng_RPM.A_RPM};
CAN_PduType    pdu_handler5_SPEED 	= { 5, 7, (Eng_Speed.A_SPEED + 1)};
CAN_PduType    pdu_handler6_DTC 	= { 6, 4, Eng_DTC.A_DTC};

/* Private functions prototypes */
/*============================================================================*/


/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  CanManager_SendMessage_RPM
 *  Description          :  Function that sends the RPM 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called every 10 ms.
 *  Postcondition        :  A CAN message has been sent.
 **************************************************************/
void CanManager_SendMessage_RPM(void)
{
	CAN_SendFrame(&pdu_handler4_RPM);
}


/**************************************************************
 *  Name                 :  CanManager_SendMessage_SPEED
 *  Description          :  Function that sends the Speed of the motor and other parameters 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after a MidRes event.
 *  Postcondition        :  A CAN message has been sent.
 **************************************************************/
void CanManager_SendMessage_SPEED(void)
{
	CAN_SendFrame(&pdu_handler5_SPEED);
}

/**************************************************************
 *  Name                 :  CanManager_SendMessage_DTC
 *  Description          :  Function that sends the information of an error 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after an over current error.
 *  Postcondition        :  A CAN message has been sent.
 **************************************************************/
void CanManager_SendMessage_DTC(void)
{
	CAN_SendFrame(&pdu_handler6_DTC);
}
/* Notice: the file ends with a blank new line to avoid compiler warnings */
