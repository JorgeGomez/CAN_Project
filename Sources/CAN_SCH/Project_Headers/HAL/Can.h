/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: Can.h
 * $Revision: version 1.0
 * $Author: Alicia Álvarez
 * $Date: 
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 * This file provides the headers for CAN protocol
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
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |       			    |              1.0                */
/*					   |					|       					       */
/*============================================================================*/
/*
 * $Log: Can.h  $
  ============================================================================*/

#ifndef CAN_H
#define CAN_H

/* Includes */
/*============================================================================*/
#include "HAL/Can_Types.h"

/* Constants and types */
/*============================================================================*/

#define MAX_MSG_TO_DISP (10)
#define MAX_MSG_TX_TO_DISP (3)

/* Exported Variables */
/*============================================================================*/
extern CAN_MessageDataType    received_messages[64];
extern CAN_MessageDataType    txd_messages[64];

/* Exported functions prototypes */
/*============================================================================*/
extern void CAN_Initialization(CAN_ConfigType *can_config);
extern void CAN_SendFrame(CAN_PduType *pdu_handler);
extern uint8_t CAN_ReceiveFrame(uint8_t message_buffer, CAN_MessageDataType *can_message );
extern void CAN_Stop(void);

#endif
/*CAN_H_ */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
