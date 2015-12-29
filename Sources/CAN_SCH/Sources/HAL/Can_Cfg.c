/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: can_cfg.c $
 * $Revision: 1.0 $
 * $Author: Alicia Álvarez $
 * $Date:   $
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
/*   1.0 		|  			  |								  |Alicia Álvarez */
/*============================================================================*/
/*                               			 	                              */
/*============================================================================*/
/*
 * $Log: can_cfg.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/Can_Cfg.h"
#include "MAL/Can_Manager.h"

/* Constants and types  */
/*============================================================================*/
#define MAX_NUM_RX_FILTERS  (4)
#define MAX_NUM_TX_FILTERS  (2)

/* Variables */
/*============================================================================*/
extern uint8_t CAN_SendFrameInt(uint8_t can_eng, uint8_t can_channel, uint8_t *can_msg_buf, uint8_t len);

/*~+:CAN Baudrate Configuration*/
CAN_DevBaudrateType bios_cnf_can_baudrate_options[] = {
/***********************************************************************************/
/* Propagation Segment------------------------------+                              */
/* Phase Segment 2-------------------------------+  |                              */
/* Phase Segment 1----------------------------+  |  |                              */
/* Resync Jump Width-----------------------+  |  |  |                              */
/* Baudrate Prescaler------------------+   |  |  |  |                              */
/* Clock Source ------------+          |   |  |  |  |                              */
/*                          |          |   |  |  |  |                              */
                     {CNF_CAN_OSC_CLK, 1,  2, 2, 2, 3},     /* BR 1Mbps            */
                     {CNF_CAN_OSC_CLK, 2,  2, 2, 2, 3},     /* BR 500kbps          */
                     {CNF_CAN_OSC_CLK, 4,  2, 2, 2, 3},     /* BR 250kbps          */
                     {CNF_CAN_OSC_CLK, 8,  2, 2, 2, 3}      /* BR 125kbps          */
};



/*~+:CAN Messages Configuration*/
CAN_ConfigMsgType bios_cnf_can_messages[] = {
 /* MB#, Message      , Message transmit ,  Message length , Message   ,	Message	  ,	Callback function 
  *     operation		remote request							ID			Mask
  *      TX / RX
  */
	/*Messages buffer not used*/
	/*-----------------------------------------------------------------------------------------*/
	{ 0, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x1A0,    		0x000,   	NULL  },
	{ 1, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x123,   		0x000, 		NULL  },
	{ 2, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x1B0,    		0x000,      NULL  },
	{ 3, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x135,    		0x000, 		NULL  },
	/*-----------------------------------------------------------------------------------------*/
	
	/*Messages for the ECM*/
	/*-----------------------------------------------------------------------------------------*/
	{ 4, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x100,    		0x1F8,      NULL  },
	{ 5, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x101,    		0x1F8, 		NULL  },
	{ 6, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x102,    		0x1F8,      NULL  },
	/*-----------------------------------------------------------------------------------------*/
	
	/*Messages buffer not used*/
	/*-----------------------------------------------------------------------------------------*/
	{ 7, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x123456AA,    0x000, 		NULL  },
	{ 8, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x1CF,         0x000, 		NULL  },
	{ 9, CNF_CAN_CH_TX, CNF_CAN_DATA_FRAME, CNF_CAN_IDE_STD, 0x1A654321,    0x000, 		NULL  }
	/*-----------------------------------------------------------------------------------------*/
};


/*~+:CAN Device Configuration*/
CAN_ConfigDeviceType bios_cnf_can_dev[] = 
{
	{
		CANB,                                           						/* CAN Device */
		( sizeof(bios_cnf_can_messages)/sizeof(bios_cnf_can_messages[0]) ),		/* Number of channels */
		CNF_CAN_BOFF_DIS,                               						/* Automatic Recovery OFF */
		CNF_CAN_LBUF_ON,                                						/* Lower buffer is transmitted first */
		CNF_CAN_FIFO_DIS,                               						/* FIFO Disabled */
		CNF_CAN_IND_MASK,                               						/* Filter mode Individual Mask */
		&bios_cnf_can_baudrate_options[1],              						/* CAN Baud rate Configuration */
		bios_cnf_can_messages,                  								/* Configured channels for this CAN Engine */
	}
};


/*~+:CAN Driver Configuration*/
CAN_ConfigType can_driver_config = {
( sizeof(bios_cnf_can_dev)/sizeof(bios_cnf_can_dev[0]) ),   /* Number of devices */
bios_cnf_can_dev                                            /* Pointer to devices configuration */
};

/* Notice: the file ends with a blank new line to avoid compiler warnings */
