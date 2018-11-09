#ifndef UART_H
#define UART_H
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

/******************************************************************************
File: UART.H

Revision History
Date        OSO-UID     Description
******************************************************************************/
  
/******************************************************************************
System includes (Compiler Level Includes)
******************************************************************************/
/******************************************************************************
User includes (Project level includes)
******************************************************************************/
//#include "r_can_api.h"
//#include "iodefine.h"
#include <stdint.h>

/******************************************************************************
Typedef definitions
******************************************************************************/
/******************************************************************************
Macro definitions
******************************************************************************/
/* Baudrate for SCI transferring (bps) */
//extern const uint8_t baudrate_str[];

/******************************************************************************
Global variables and functions imported (externs)
******************************************************************************/
/* Data */
/* Functions */
                  
/******************************************************************************
Constant definitions
*****************************************************************************/
#define SCI1_INT_LVL		7

#define WAIT_FOR_TX_TO_COMPLETE_SCI1	while (SCI1.SSR.BIT.TEND == 0){;}

/******************************************************************************
Global variables and functions exported
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/* Data */

/* Functions */
void InitSCI1(void);
void UART_Create(void);
void TextWrite( const uint8_t * msg_string);
void TextWriteNrBytes(const uint8_t * msg_string, const uint8_t nr_bytes);
void sendCRLF(void);

#ifdef __cplusplus
}
#endif

#endif  //UART_H
/* eof */