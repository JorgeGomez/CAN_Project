/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: GPIO.h
 * $Revision: version 1.0
 * $Author: Abraham Tezmol
 * $Date: 09/05/2013
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 *  Macro definitions for registers access and I/O handling
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
/*   1.0 		|  31/10/2008 |								  |Abraham Tezmol */
/*----------------------------------------------------------------------------*/
/*   1.1 		|  13/01/2016 |	Added External LED			  |Jorge Gomez	  */
/*============================================================================*/
/*
 * $Log: GPIO.h  $
  ============================================================================*/

#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/* Includes */
/*============================================================================*/
/** Core modules */
/** MCU derivative information */
#include "HAL/MCU_derivative.h"
/** Variable types and common definitions */
#include "HAL/typedefs.h"
/* Constants and types */
/*============================================================================*/

#define LED1      					68
#define LED2       					69
#define LED3       					70
#define LED4        				71
#define EXTERNAL_LED1				79

#define GPIO_INPUT					0
#define GPIO_OUTPUT					1

#define GPIO_OPEN_DRAIN_DISABLE		0
#define GPIO_OPEN_DRAIN_ENABLE		1

/*-- Macros ------------------------------------------------------------------*/
/* Indicator LEDs handling */

/** Set LED */ 
#define LED_ON(channel)                     (SIU.GPDO[channel].B.PDO =  0)
/** Clear LED */ 
#define LED_OFF(channel)                    (SIU.GPDO[channel].B.PDO =  1)
/** Toggle LED */ 
#define LED_TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 


/* Exported Variables */
/*============================================================================*/
 

/* Exported functions prototypes */
/*============================================================================*/


void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain);
void vfnGPIO_Output(uint8_t channel, uint8_t logical_value);
void vfnGPIO_LED_Init(void);


#endif

/* _GPIO_H */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
