/*******************************************************************************/
/**
\file       dummy.c
\brief      Dummy Functions
\author     Francisco Martinez
\version    1.0
\date       04/04/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include "HAL/typedefs.h"

/** Own headers */
#include "Application/dummy.h"

/* GPIO routines prototypes */ 
#include "HAL/GPIO.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Turn a combination of 4 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Francisco Martinez
* \return   void
*/
void Test(T_UBYTE lub_LED)
{

	switch (lub_LED)
	{
	case 1:
	{
		LED_TOGGLE(LED1);
		break;
	}
	case 2:
	{
		LED_TOGGLE(LED2);
		break;
	}
	case 3:
	{
		LED_TOGGLE(LED3);
		break;
	}
	case 4:
	{
		LED_TOGGLE(LED4);
		break;
	}

	}


}
