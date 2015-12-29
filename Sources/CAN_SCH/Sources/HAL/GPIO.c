/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO.c $
 * $Revision: 1.0 $
 * $Author: Abraham Tezmol $
 * $Date: 31/10/2008 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \brief
    General purpose IO functions
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
/*   1.0 		|  31/10/2008 |								  |Abraham Tezmol */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: GPIO.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/

/** Core modules */
/** MCU derivative information */
#include "HAL/MCU_derivative.h"
/** Variable types and common definitions */
#include "HAL/typedefs.h"

/** Own headers */
/* GPIO routines prototypes */ 
#include "HAL/GPIO.h"

/** Used modules */


/* Constants and types  */
/*============================================================================*/

/* Variables */
/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/


/* Inline functions */
/*============================================================================*/


/* Private functions */
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/****************************************************************************************************/
/**
* \brief    Configures individual GPIO pins to either input or output functionality.  
* \author   Abraham Tezmol
* \param    uint8_t channel - GPIO channel to be configured
* \param    uint8_t input_output - selection of input/output functionality (has impact on output impedance selection)
* \param    uint8_t Open_drain - Push pull or open drain selection modes 
* \return   void
*/

void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain)
{
    if (input_output == GPIO_OUTPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.OBE = 1;					/* Output buffer enable */
    	if (Open_drain == GPIO_OPEN_DRAIN_ENABLE)
    	{
    		SIU.PCR[channel].B.ODE = 1;				/* Open drain option enable */	
    	}
    	else
    	{	
    		SIU.PCR[channel].B.ODE = 0;				/* Push-pull option enable */	
    	}
    }
    else if (input_output == GPIO_INPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.IBE = 1;					/* Input buffer enable */	
    }

}

/****************************************************************************************************/
/**
* \brief    Configures individual GPIO pins to either input or output functionality.  
* \author   Abraham Tezmol
* \param    uint8_t channel - GPIO channel to be configured
* \param    uint8_t input_output - selection of input/output functionality (has impact on output impedance selection)
* \param    uint8_t Open_drain - Push pull or open drain selection modes 
* \return   void
*/
void vfnGPIO_Output(uint8_t channel, uint8_t logical_value)
{
    SIU.GPDO[channel].B.PDO  = logical_value;  		/* Drive the logical output value to the pin */

}



/****************************************************************************************************/
/**
* \brief    Turn a combination of 3 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnGPIO_FlashMainLED(void)
{
    static uint8_t u8Counter = 0;
    
    u8Counter++;
    switch (u8Counter)
    {
    case  1:
            LED_ON(LED1);
            LED_ON(LED2);
            break;
    case  11:
            LED_ON(LED3);
            LED_ON(LED4);                     
            break;
    case  21:
            LED_ON(LED2);
            LED_ON(LED3);                     
            break;        
    case  3:
            LED_OFF(LED1);
            LED_OFF(LED2);
            break;
    case  13:
            LED_OFF(LED3);
            LED_OFF(LED4);
            break;                          
    case  23:
            LED_OFF(LED2);
            LED_OFF(LED3);
            break;        
	case 100:
		u8Counter = 0;
		break;
    }
}


/****************************************************************************************************/
/**
* \brief    Initialize GPIO port connected to LEDs on eval board
* \author   Abraham Tezmol
* \param    void 
* \return   void
*/
void vfnGPIO_LED_Init(void)
{
    /* Data Port A initialization */
	vfnGPIO_Init_channel(LED1,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE4 --> LED1*/
	vfnGPIO_Output (LED1, 1);
	vfnGPIO_Init_channel(LED2,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE5 --> LED2*/
	vfnGPIO_Output (LED2, 1);
	vfnGPIO_Init_channel(LED3,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE6 --> LED3*/
	vfnGPIO_Output (LED3, 1);
	vfnGPIO_Init_channel(LED4,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE7 --> LED4*/
	vfnGPIO_Output (LED4, 1);
	
}

/* Notice: the file ends with a blank new line to avoid compiler warnings */
