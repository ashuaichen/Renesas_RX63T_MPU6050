/*******************************************************************************
* FILE        :	qbrx63th_if.h
* DATE        :	JUN. 11, 2013
* CPU TYPE    : Renesas RX63TH
* H/W Platform:	QB-RX63TH-TB
* Programmer  :	Ziyuan Chen (VICTRON TECHNOLOGY, TAIWAN)
* Description : This Header file contains the Macro Definitions & prototypes  
*				for the QB-RX63TH-TB platform.
*******************************************************************************/
/*******************************************************************************
* History       : 11 JUN. 2013  Ver. 1.00 First Release
*******************************************************************************/

/***********************************************************************
//  Fixed number definition
***********************************************************************/

/****************************************************
// LEDs PIN DEFINE
****************************************************/
#define LED3DIR	PORT3.PDR.BIT.B3
#define LED2DIR	PORT7.PDR.BIT.B3
#define LED1DIR	PORT7.PDR.BIT.B2
#define LED0DIR	PORT7.PDR.BIT.B1
#define LED3	PORT3.PODR.BIT.B3
#define LED2	PORT7.PODR.BIT.B3
#define LED1	PORT7.PODR.BIT.B2
#define LED0	PORT7.PODR.BIT.B1
#define P_IN				(0)
#define P_OUT				(1)
#define LED_ON				(0)
#define LED_OFF				(1)
#define INVERT				(1)

/****************************************************
// Switches DEFINE
****************************************************/
#define SW3DIR	PORT0.PDR.BIT.B3
#define SW2DIR	PORT1.PDR.BIT.B1
#define SW1DIR	PORT1.PDR.BIT.B0
#define SW3		PORT0.PIDR.BIT.B3
#define SW2		PORT1.PIDR.BIT.B1
#define SW1		PORT1.PIDR.BIT.B0
#define SW_ON				(0)
#define SW_OFF				(1)


