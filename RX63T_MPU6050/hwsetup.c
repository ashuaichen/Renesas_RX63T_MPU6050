/************************************************************************
*
* Device     : RX/RX600/RX63T
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 2.00  (2013-09-27)  [Hardware Manual Revision : 2.10]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
************************************************************************/

/***********************************************************************
Includes <System Includes> , "Project Includes"
***********************************************************************/
#include <machine.h>
#include "iodefine.h"
#include "qbrx63th_if.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************
Macro definitions
******************************************************************************/
/* -- Please set wait processing for the clock oscillation stabilization -- */
#define WAIT_TIME_FOR_MAIN_OSCILLATION      (16487000L)
#define WAIT_TIME_FOR_PLL_OSCILLATION       (2320000L)

/* CMT0 count use LOCO is the main clock */
#define FOR_CMT0_TIME    (222608)
/*Time for one count of CMT0 is approximately 222608 ns
  when the count source is LOCO devided by 32 (max. of LOCO = 143.75 kHz) */
  
#define MODULE_STOP_ENABLE    (1)
#define MODULE_STOP_DISABLE   (0)

#define MSTP_STATE_DMACDTC (MODULE_STOP_DISABLE)  // DMAC/DTC trans to module-stop state
#define MSTP_STATE_RAM0    (MODULE_STOP_DISABLE)  // RAM0 trans to module-stop state

/******************************************************************************
Private global variables and functions
******************************************************************************/
void Clock_Setting(void);
void R_INIT_StopModule(void);
void CGC_oscillation_main(void);
void CGC_oscillation_PLL(void);
void Port_Setting(void);

void HardwareSetup(void)
{
	// Disable maskable interrupts
	clrpsw_i();
    
	// Stopping the peripherals which start operations
	R_INIT_StopModule();
	
	// Initialization of the clock
	Clock_Setting();
	
	// Enable maskable interrupts
	setpsw_i();
	
	Port_Setting();
}//End of HardwareSetup()

/******************************************************************************
* Outline                  : Initialization of module stop control
* Function Name            : R_INIT_StopModule
* Description              : Stopping the peripherals which start operations 
*                            after a reset
* Argument                 : none
* Return Value             : none
******************************************************************************/
void R_INIT_StopModule(void)
{
    /* ---- Protection ---- Write Enable  */
    /* PRCR - Protect Register 
    b15:b8 PRKEY - PRC Key Code - a5h 
                  (The write value shoul be A5 to permission writing PRCi bit)
    b1     PRC1 - Protect Bit 1 - Write enabled
    b0     PRC0 - Protect Bit 0 - Write enabled */
    SYSTEM.PRCR.WORD = 0xA503;

    /* ---- Set transion to module-stop state ---- */
#if MSTP_STATE_DMACDTC == MODULE_STOP_ENABLE
    MSTP(DTC) = 1;            /* DMAC/DTC trans to module-stop state */
#endif
#if MSTP_STATE_RAM0 == MODULE_STOP_ENABLE
    MSTP(RAM0) = 1;           /* RAM0 trans to module-stop state  */
#endif

    /* ---- Protection ---- Write Disable  */
    /* PRCR - Protect Register 
    b15:b8 PRKEY - PRC Key Code - a5h 
                  (The write value shoul be A5 to permission writing PRCi bit)
    b1     PRC1 - Protect Bit 1 - Write disable
    b0     PRC0 - Protect Bit 0 - Write disable */
    SYSTEM.PRCR.WORD = 0xA500;
}

/*****************************************************************************/
/* Outline      : Clock_Setting                                              */
/* Description  : System Clock setting                             			 */
/*****************************************************************************/
void Clock_Setting(void)
{
	int  i;  
	SYSTEM.PRCR.WORD = 0xA503;		// Disable write protection 

	SYSTEM.MOSCWTCR.BYTE = 0x0D;	// 131072cyc Oscillator Waiting Time 
	SYSTEM.MOSCCR.BYTE = 0x00;		// Operate the main clock oscillator 
	while( SYSTEM.MOSCCR.BYTE )		// Confirm that the written value 
		nop( );

	SYSTEM.PLLCR.WORD = 0x0F00;		// 12MHz/1*16=192MHz (multiply-by-16)  
	SYSTEM.PLLWTCR.BYTE = 0x0E;		// Set wait time  2097152cyc  
	SYSTEM.PLLCR2.BYTE = 0x00;		// PLL is operating 

	for( i=0 ; i<556 ; i++ )		// 22.1053ms  Wait processing 
  		nop( );
// ===========================================================================================	
	SYSTEM.SCKCR.LONG = 0x21021212;	// Set the internal clock division ratio 
	// ---- Set the internal clock division ratio ----
	// ----   SCKCR - System Clock Control Register  ----
	//    b31:b28 FCK      2 (48MHz)- FlashIF Clock(FCLK) Select - divide-by-4
	//    b27:b24 ICK      1 (96MHz)- System Clock (ICLK) Select - divide-by-2
	//    b22     PSTOP1   0 		- BCLK Pin Output Control - BCLK pin output is disabled.
	//    b22:b20 Reserved   		- The write value should be 0.
	//    b19:b16 BCK      2 (48MHz)- External Bus Clock (BCLK) Select - divide-by-4
	//                       		  (In the case of 64- and the 48-pin products, the write value should be 0010b.)
	//    b15:b12 PCKA     1 (96MHz)- Periheral Module Clock A(PCLKA) Select - divide-by-2  
	//    b10:b8  PCKB     2 (48MHz)- Periheral Module Clock B(PCLKB) Select - divide-by-4 
	//    b7:b4   PCKC     1 (96MHz)- AD Clock (PCLKC) Select - divide-by-2
	//                       		  (In the case of 64- and the 48-pin products, the write value should be 0010b.)
	//    b3:b0   PCKD     2 (48MHz)- Periheral Module (S12AD) Clock D(PCLKD) Select - divide-by-4
	while( SYSTEM.SCKCR.LONG != 0x21021212)   
		nop( );						// Confirm that the written value  
 
	SYSTEM.SCKCR3.WORD = 0x0400;	// PLL circuit is selected. 
	while( SYSTEM.SCKCR3.WORD != 0x0400 )   
		nop( );						// Confirm that the written value
// ===========================================================================================		
	SYSTEM.LOCOCR.BYTE = 0x01;		// Stop LOCO 
	SYSTEM.PRCR.WORD = 0xA500;		// Protect setting 
}//End of Clock_Setting()


void Port_Setting(void)
{
	LED3DIR = P_OUT;
	LED2DIR = P_OUT;
	LED1DIR = P_OUT;
	LED0DIR = P_OUT;
	
	LED3 = LED_OFF;
	LED2 = LED_OFF;
	LED1 = LED_OFF;
	LED0 = LED_OFF;
}

////////////////////////////////////////////////////////////////////////////////
//                                 End  File                                  //
////////////////////////////////////////////////////////////////////////////////
