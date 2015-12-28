/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: bspi.h
 * $Revision: version 1.0
 * $Author: 
 * $Date: 
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 * This file provides the headers to configure the SPI module 
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
 * $Log: bspi.h  $
  ============================================================================*/
#ifndef _BSPI_H_
#define _BSPI_H_


/* Includes */
/*============================================================================*/
#include "HAL/typedefs.h"

/* Constants and types */
/*============================================================================*/

/* Exported Variables */
/*============================================================================*/
 

/* Exported functions prototypes */
/*============================================================================*/

/*******************************************************************************/
extern void InitDSPI_1(void);

/********************************************************************************/
extern void ReadDataDSPI_1(void); 

/*******************************************************************************/
extern void ConfigureMZC33905DSPI_1(void);

/* Functions prototypes */
/*============================================================================*/


#endif
/*BSPI_H_ */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
