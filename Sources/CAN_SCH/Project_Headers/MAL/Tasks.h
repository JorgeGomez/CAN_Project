/*============================================================================*/
/*                                  AEP                                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*      This file provides the headers of the functions of Tasks.c            */
/*============================================================================*/
/*!
 * $Source: Tasks.h $
 * $Revision: version 1.0 $
 * $Author: Jose Luis Martinez Vicuña $
 * $Date: Nov/13/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
 * This file provides the headers of the functions of the Tasks which are defined
 * in Tasks.c, also is the structure S__TASK which receives the function, period
 * and an offset and the number of tasks to be executed.
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
/*                     |      Scheduler     |            1.0                  */
/*					   |					|      Project_Headers/MAL  	  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/* 		 1.0	|     11/13/2015     | 		   Jose Luis Martinez Vicuña      */
/*============================================================================*/
/*   1.1		|   Dic/03/15       |Unnecessary tasks were   |Jose Luis Mtz  */
/*  			|					|		removed			  |	 	          */
/*============================================================================*/
/*   1.2		|   Dic/22/15       |Added necessaries task   |Jorge Gomez	  */
/*  			|					|and dummy functions 	  |	 	          */
/*============================================================================*/
/*
 * $Log: Tasks.h  $
  ============================================================================*/
#ifndef TASKS_H_
#define TASKS_H_

/* Includes */
/*============================================================================*/
#include "HAL/stdtypedef.h"
#include "HAL/ADC.h"
#include "MAL/Can_Manager.h"
#include "Application/RPM.h"
#include "Application/Speed.h"


/* Constants and types */
/*============================================================================*/
typedef void(*T_PFUNC)(void);

typedef struct{
	T_PFUNC PtrFunc;
	T_ULONG Period;
	T_UBYTE Offset;
}S_TASK;

typedef enum {
	TASK1,
	TASK2,
	TASK3,
	TASK4,
	TASK5,
	TASK6,
	TASK7,
	/*number of task*/
	NUMBER_OF_TASKS
}E_NUMTASK;

/* Exported Variables */
/*============================================================================*/



/* Exported functions prototypes */
/*============================================================================*/


/* Functions prototypes */
/*============================================================================*/
void Task1_3p125ms(void);
void Task2_6p25ms(void);
void Task3_12p5ms(void);
void Task4_25ms(void);
void Task5_50ms(void);
void Task6_100ms(void);
void Task7_10ms(void);

#endif /* TASKS_H_ */  /* Notice: the file ends with a blank new line to avoid compiler warnings */
