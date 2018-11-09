/******************************************************************************
* DISCLAIMER:                                                        
* The software supplied by Renesas Electronics America Inc. is        
* intended and supplied for use on Renesas Electronics products.      
* This software is owned by Renesas Electronics America, Inc. or      
* Renesas Electronics Corporation and is protected under applicable   
* copyright laws. All rights are reserved.                           
*                                                                    
* THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, 
* IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO IMPLIED         
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
* APPLY TO THIS SOFTWARE. RENESAS ELECTRONICS AMERICA, INC. AND       
* AND RENESAS ELECTRONICS CORPORATION RESERVE THE RIGHT, WITHOUT      
* NOTICE, TO MAKE CHANGES TO THIS SOFTWARE. NEITHER RENESAS          
* ELECTRONICS AMERICA, INC. NOR RENESAS ELECTRONICS CORPORATION SHALL, 
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR        
* CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER ARISING OUT OF THE 
* USE OR APPLICATION OF THIS SOFTWARE.                               
******************************************************************************/

/* Copyright (C) 2010,2011 Renesas Electronics Corp., All Rights Reserved.   */

/*""FILE COMMENT""************************ Technical reference data ***********
* File Name    : UART.C
* Version      : 01.00
* Device       : R5F5630X0DFP
* Tool-Chain   :
* OS           : -
* H/W Platform : RSK RX630 Eval Board.
* Description  : See CAN_UART_BRIDGE.C
* Operation    :
* Limitations  : -
*******************************************************************************

*""FILE COMMENT END""*********************************************************/

/******************************************************************************
System includes (Compiler Level Includes)
******************************************************************************/
/*	Following header file provides access to intrinsic functions to control interrupt
	levels. */
#include <machine.h>

/**********************************************************************************
User Includes
***********************************************************************************/
#include "uart.h"
#include <iodefine.h>
#include <stdint.h>

/*****************************************************************************
Name:       	InitSCI1
Parameters:		- 
Returns:		-
Description:	Initialize SCI1 to operate asynchronously at 115200 baud.
*****************************************************************************/
void InitSCI1(void)
{
	uint16_t i = 0u;

	SYSTEM.PRCR.WORD = 0xA503u;	/* Protection off */
	MSTP(SCI1) = 0u;		/* Cancel the SCI1 module clock stop mode */
	SYSTEM.PRCR.WORD = 0xA500u;	/* Protection on */
    
	/* Clear bits TIE, RIE, RE, and TEIE in SCR to 0. Set CKE to internal. */
	SCI1.SCR.BYTE = 0x00;

	/* Configure SCI1's TXD1, RXD1 and SCK1 pins for peripheral functions */
	PORTD.PMR.BYTE = 0x38u;

	MPC.PWPR.BIT.B0WI  = 0;		/* PFSWE Bit Write disable */
	MPC.PWPR.BIT.PFSWE = 1;		/* PFS Register Write Enable */

	/* Configure SCI1's communication pins */
	MPC.PD3PFS.BYTE = 0x0Au;	/* Set PortD's pin 3 function to TXD1 */
	MPC.PD5PFS.BYTE = 0x0Au;	/* Set PortD's pin 5 function to RXD1 */
//	MPC.PD4PFS.BYTE = 0x0Au;	/* Set PortD's pin 4 function to SCK1 */

	PORTD.PDR.BIT.B3 = 1u;		/* Set output port TXD1(PD3) */
	PORTD.PDR.BIT.B5 = 1u;		/* Set Receive port RXD1(PD5)*/

	MPC.PWPR.BIT.PFSWE = 0;		/* PFS Register Write disable */
	MPC.PWPR.BIT.B0WI  = 1;		/* PFSWE Bit Write Enable */

	/* Set data transfer format in Serial Mode Register (SMR)*/ 
	// -Asynchronous Mode`
	// -8 bits
	// -no parity
	// -1 stop bit
	// -PCLK clock (n = 0)
	SCI1.SMR.BYTE = 0x00u;   

	/* SMIF Set to 0 for serial communications interface mode.*/
	SCI1.SCMR.BIT.SMIF = 0;
	
	/* Set bit rate register. */
       	//    Example: set to 115200 baud
        //    N = (PCLK Frequency) / (64 * 2^(2*n - 1) * Bit Rate) - 1
        //    N = (48,000,000)     / (64 * 2^(2*0 - 1) * Bit Rate) - 1
	SCI1.BRR = 12;		// Bitrate                                   

	/* Wait at least one bit interval */
    	/* TODO: check this for sufficient delay */
    	for (i = 0; i < 1000; i++) 	/* assume minimum of 2 instructions at 98MHz? */
    	{;}
	
	/* Clear bits ORER, PER and FER */
	SCI1.SSR.BYTE &= 0xC7u;
	
	/* Enable RXI and TXI interrupts in SCI peripheral */
    SCI1.SCR.BIT.RIE  = 1;   	/* Set Receive Interrupt (RX buffer full) enable. */
    SCI1.SCR.BIT.TIE  = 1;		/* Set Transmit Interrupt (TX data register empty) enable. */
    SCI1.SCR.BIT.TEIE = 0;		/* Set Transmit End interrupt disable */
        
	/* RXI and TXI interrupts in ICU. */
	/* Designer option--handle ICU interrupt diaable */
	IEN(SCI1, RXI1) = 0;
	IEN(SCI1, TXI1) = 0;
	
	/* Clear IR bits for TIE and RIE */
    IR(SCI1, RXI1) = 0;
    IR(SCI1, TXI1) = 0;
	
	/* Set interrupt prio for SCI. */
    IPR(SCI1, TXI1) = SCI1_INT_LVL;
    IPR(SCI1, RXI1) = SCI1_INT_LVL;
	
	/* Enable Tx/Rx */
	/* Note: A 1 can only be written to these bits when TE = 0 and RE = 0. */
	/* After setting TE or RE to 1, only 0 can be written in TE and RE.    */
	/* So to enable both, write them simultaneously.                       */
	SCI1.SCR.BYTE |= 0x30; 
}/* end InitSCI0() */

/*****************************************************************************
Name:       	UART_Create
Parameters:		- 
Returns:		-
Description:	init uart and write some test strings
*****************************************************************************/
void UART_Create(void)
{
	/* SCI1 in Async mode at 115k */
    InitSCI1();

    /* Output message */
	TextWrite("\r\nRenesas QB-RX63TH-TB.\r\n");
    TextWrite(" UART set to BAUD_RATE 115200, 8-bit data, no parity, 1 stop bit.\r\n");
}/* end UartInitAndTest() */

/*****************************************************************************
Name:   	 TextWrite
Parameters:  msg_string: The text string to write to the UART0
Returns:     none   
Description: The following sends a text string to the terminal program     
*****************************************************************************/
void TextWrite( const uint8_t * msg_string)
{    
	uint8_t i;
        
	/* This loop reads in the text string and puts it in the SCI0 transmit buffer */
	for (i=0; msg_string[i]; i++)
	{	 
        /* Wait for transmit buffer to be empty */
		while (SCI1.SSR.BIT.TEND == 0) {;}
        //while(IR(SCI0, TXI0) == 0);
        
        #ifndef USE_SCI0_INTERRUPTS
			/* Clear TXI IR bit */
			IR(SCI1, TXI1) = 0;
		#endif

		/* Write the character out */ 
		SCI1.TDR = msg_string[i];
	}
}/* end TextWrite() */

/*****************************************************************************
Name:   	 TextWriteNrBytes
Parameters:  msg_string: The text string to write to the UART0
Returns:     none   
Description: The following sends a text string to the terminal program     
*****************************************************************************/
void TextWriteNrBytes(const uint8_t * msg_string, const uint8_t nr_bytes)
{    
	uint8_t i;
        
	/* This loop reads in the text string and puts it in the SCI0 transmit buffer */
	for (i = 0; i < nr_bytes; i++)
	{	 
        /* Wait for transmit buffer to be empty */
		while (SCI1.SSR.BIT.TEND == 0) {;}
        //while(IR(SCI0, TXI0) == 0);
        
        #ifndef USE_SCI0_INTERRUPTS
			/* Clear TXI IR bit */
			IR(SCI1, TXI1) = 0;
		#endif

		/* Write the character out */ 
		SCI1.TDR = msg_string[i];
	}
}/* TextWriteNrBytes() */

/*****************************************************************************
Name:   	 sendCRLF
Parameters:  -
Returns:     -
Description: Send a Carriage Return and a Line Feed to UART0.
*****************************************************************************/
void sendCRLF(void)
{
    /* Add CR + LF */

    /* Send Carriage Return */
    WAIT_FOR_TX_TO_COMPLETE_SCI1
    SCI1.TDR = '\n';
    //SCI0.TDR = 0x0D;

    /* Line Feed */
    WAIT_FOR_TX_TO_COMPLETE_SCI1
    SCI1.TDR = '\r';
    //SCI0.TDR = 0x0A;

    WAIT_FOR_TX_TO_COMPLETE_SCI1
}/* end sendCRLF() */


/******************************************************************************
* Function Name: charput
* Description  : Outputs a character on a serial port
* Arguments    : character to output
* Return Value : none
******************************************************************************/
void charput(uint8_t output_char)
{
	/* Wait for transmit buffer to be empty */
	while(IR(SCI1, TXI1) == 0);

	/* Clear TXI IR bit */
	IR(SCI1, TXI1) = 0;

	/* Write the character out */ 
	SCI1.TDR = output_char;	
}
/******************************************************************************
End of function  charput
******************************************************************************/

/******************************************************************************
* Function Name: charget
* Description  : Gets a character on a serial port
* Arguments    : character to output
* Return Value : none
******************************************************************************/
uint8_t charget(void)
{
	uint8_t temp;
	
	/* Read any 'junk' out of receive buffer */
	temp = SCI1.RDR;
	
	/* Clear flag to receive next byte */
    IR(SCI1, RXI1) = 0;
	
	/* Wait for next receive data */
	while(IR(SCI1, RXI1) == 0);
	
	/* Read data */
	temp = SCI1.RDR;
	
	/* Echo data back out */
	if(temp == 0x0d)
	{
		/* Enter was pressed, output newline */
		charput('\r');
		charput('\n');
	}
	else
	{
		/* Echo back character */
		charput(temp);
	}

	/* Receive data acquired, send back up */
	return temp;		
}
/******************************************************************************
End of function  charget
******************************************************************************/


/*****************************************************************************
Name:		  	SCI1 ISRs
Parameters:		-
Returns:	   	-
Description:   	-
*****************************************************************************/
/*****************************************************************************/
/* Outline      : TXI1 data transmit interrupt                               */
/* Description  : Transmit '1' for LED invert.                               */
/*****************************************************************************/
//void Excep_SCI1_TXI1(void)
//{
//
//}


/*****************************************************************************/
/* Outline      : RXI1 data receive interrupt                                */
/* Description  : If receive data is '1', then LED invert.                   */
/*****************************************************************************/
//void Excep_SCI1_RXI1(void)
//{
//
//}
/* eof */
