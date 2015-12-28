/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: can_cfg.h
 * $Revision: version 1.0
 * $Author: Alicia Álvarez
 * $Date: 
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 * This file provides the headers and defines for the configuration of FlexCan
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
 * $Log: can_cfg.h  $
  ============================================================================*/

#ifndef CAN_CFG_H 
#define CAN_CFG_H 

/* Includes */
/*============================================================================*/
#include "HAL/Can_Types.h"

/* Constants and types */
/*============================================================================*/

#define CNF_CAN_BUS_CLK (1) /* System Clock Source */
#define CNF_CAN_OSC_CLK (0) /* Oscillator Clock Source */

/* Lowest Buffer Transmitted First */
#define CNF_CAN_LBUF_ON  (1) /* Lowest number buffer is transmitted first */
#define CNF_CAN_LBUF_OFF (0) /* Buffer with highest priority is transmitted first */

/* FIFO Enable */
#define CNF_CAN_FIFO_EN  (1) /* FIFO enabled */
#define CNF_CAN_FIFO_DIS (0) /* FIFO not enabled */

/* Message buffer filter mode */
/*AlAl check about queue*/
#define CNF_CAN_IND_MASK     (1) /* Individual Rx masking enabled */
#define CNF_CAN_GLOBAL_MASK  (0) /* Individual Rx masking disabled */

/* Bus Off Recovery Mode */
#define CNF_CAN_BOFF_EN  (1) /* Automatic recovering from Bus Off state enabled */
#define CNF_CAN_BOFF_DIS (0) /* Automatic recovering from Bus Off state disabled, according to CAN Spec 2.0 part B */

/* Remote Transmission Request */
#define CNF_CAN_REMOTE_FRAME (1) /* Indicates the current MB has a Remote Frame to be transmitted  */
#define CNF_CAN_DATA_FRAME   (0) /* Indicates the current MB has a Data Frame to be transmitted  */

/* Frame Format */
#define CNF_CAN_IDE_EXT      (1) /* Frame Extended Format  */
#define CNF_CAN_IDE_STD      (0) /* Frame Standard Format */

/* Channel Operation Mode */
#define CNF_CAN_CH_TX    (1) /* Channel Mode Tx */
#define CNF_CAN_CH_RX    (0) /* Channel Mode Rx */

/* CAN Engine Devices */
#define CANA    (0) /* CAN A */
#define CANB    (1) /* CAN B */
#define CANC    (2) /* CAN C */
#define CAND    (3) /* CAN D */

/* Exported Variables */
/*============================================================================*/

extern CAN_ConfigType can_driver_config; /* CAN Driver configuration structure */

/* Functions prototypes */
/*============================================================================*/

#endif
/*CAN_CFG_H_ */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
