/*******************************************************************************	
* File Name    : riic.c
* Version      : 1.00
* Description  : RIIC single master program
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <machine.h>
#include <iodefine.h>
#include <typedefine.h>
#include "riic.h"

/******************************************************************************
/*global variables 
/******************************************************************************/
RIICMODE riic_mode;
RIICSTATUS riic_status;
DWORD riic_tx_cnt;
DWORD riic_rx_cnt;

//extern DWORD riic0_tx_cnt;
//extern DWORD riic0_rx_cnt;
//extern DWORD riic_tx_cnt;
//extern DWORD riic_rx_cnt;

/******************************************************************************
Typedef definitions
******************************************************************************/
enum RiicInternalMode_t
{
	IIC_MODE_IDLE,			/* For internal variable 'iic_mode' */
	IIC_MODE_EEP_READ,		/* For internal variable 'iic_mode' */
	IIC_MODE_EEP_WRITE		/* For internal variable 'iic_mode' */
};

#ifndef RIICAPI_DEF
#define RIICAPI_DEF
typedef struct 
{
	BYTE		SlvAdr;		/* Slave Address, Don't set bit0. It's a Read/Write bit */
	WORD		PreCnt;		/* Number of Predata */
	BYTE		*pPreData;	/* Pointer for PreData (Memory Addr of EEPROM) */
	DWORD		RWCnt;		/* Number of Data */
	BYTE		*pRWData;	/* Pointer for Data buffer */
} RIICAPI;
#endif

static RIICAPI riic_buff;	/* Structure for IIC function */

#define RIIC_CH1			/* When use channel1, define 'RIIC_CH1' */
#define RIIC	RIIC1		/* Replace I/O define */

// I2C Bus Mode Register 1 (ICMR1)
// b6 to b4 CKS[2:0] Internal Reference Clock Selection
// 0 0 0: PCLK/1 clock
// 0 0 1: PCLK/2 clock
// 0 1 0: PCLK/4 clock
// 0 1 1: PCLK/8 clock
// 1 0 0: PCLK/16 clock
// 1 0 1: PCLK/32 clock
// 1 1 0: PCLK/64 clock
// 1 1 1: PCLK/128 clock
#define PCLK_DIVIDER		(0x01)

// I2C Bus Bit Rate High-Level Register (ICBRH)
// b4 to b0 BRH[4:0] Bit Rate High-Level Period 
#define SCL_HIGH_WIDTH		(14)

// I2C Bus Bit Rate Low-Level Register (ICBRL)
// b4 to b0 BRL[4:0] Bit Rate Low-Level Period 
#define SCL_LOW_WIDTH		(29)//(16)

// I2C Bus Status Enable Register (ICSER)
#define ADDRESS_DISABLE		(0x0)

// I2C Bus Mode Register 3 (ICMR3)
// b4 ACKWP ACKBT Write Protect
// 0: Modification of the ACKBT bit is disabled
// 1: Modification of the ACKBT bit is enabled
#define WRITE_ENABLE_ACKBT	(0x1)

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: IIC_Create
* Description  : Initialize and enable RIIC
* Arguments    : none
* Return Value : none
******************************************************************************/
void IIC_Create(void)
{
	SYSTEM.PRCR.WORD = 0xA502;	// Enable write protection
	MSTP(RIIC1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;	// Disable write protection
	
	RIIC.ICCR1.BIT.ICE 		= 0; 	// RIIC disable
	RIIC.ICCR1.BIT.IICRST	= 1;	// RIIC all reset 
	RIIC.ICCR1.BIT.IICRST	= 0;	// Clear reset 

	RIIC.ICMR1.BIT.CKS	= PCLK_DIVIDER;		// about 400kbps
	RIIC.ICBRH.BIT.BRH	= SCL_HIGH_WIDTH;	// Set High width of SCL 
	RIIC.ICBRL.BIT.BRL	= SCL_LOW_WIDTH;	// Set Low width of SCL
	
	// Time out setting
	RIIC.ICMR2.BIT.TMOL = 0;		// Disable SCL=Low time out
	RIIC.ICMR2.BIT.TMOH = 1;		// Enable SCL=High time out
	RIIC.ICMR2.BIT.TMOS = 0;		// Long mode (16bits counter).
									// PCLK=48MHz, IIC phi=48MHz,
									// Long mode is about 1.365 ms

	RIIC.ICFER.BIT.TMOE = 1;		// Enable time out detection
	
	// Disable all address detection. This sample code is for only master mode 
	RIIC.ICSER.BYTE		= ADDRESS_DISABLE;
	
	// ACKWP is protect bit for ACKBT. 
	RIIC.ICMR3.BIT.ACKWP= WRITE_ENABLE_ACKBT;

	// Set port direction to input
	PORT2.PDR.BIT.B6 = 0;		// SDA1 Set port direction to input 
	PORT2.PDR.BIT.B5 = 0;		// SCL1 Set port direction to input 
	PORT2.PMR.BIT.B6 = 1;		// SDA1
	PORT2.PMR.BIT.B5 = 1;		// SCL1
	
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P26PFS.BIT.PSEL = 0x0F;
	MPC.P25PFS.BIT.PSEL = 0x0F;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;

	// Enable/Disable each interrupt
	RIIC.ICIER.BYTE = 0xBB;		
					// b0: Enable Time Out interrupt
					// b1: Enable Arbitration Lost interrupt
					// b2: Disable Start Condition Detection Interrupt
					// b3: Enable Stop condition detection interrupt
					// b4: Enable NACK reception interrupt
					// b5: Enable Receive Data Full Interrupt
					// b6: Disable Transmit End Interrupt
					// b7: Enable Transmit Data Empty Interrupt
	
	IIC_IntCreate();
	
	// Initialize ram for RIIC
	riic_mode = IIC_MODE_IDLE;	// Internal IIC mode
	riic_status = IS_IDLE;	// Status buffer for function 'IIC_GetStatus'
	riic_tx_cnt = 0;		// Clear the internal transmission counter for IIC */
	riic_rx_cnt = 0;		// Clear the internal reception counter for IIC */

	// Enable RIIC
	RIIC.ICCR1.BIT.ICE = 1;		// Enable RIIC
}

/******************************************************************************
* Function Name: IntCreate
* Description  : Initialize interrupt registers for RIIC
* Arguments    : none
* Return Value : none
******************************************************************************/
void IIC_IntCreate(void)
{
	// The IPR register is used to set the priority level of an interrupt
	// source.
	// Here, IPR registers for RIIC1 are set priprity level 4.
	IPR(RIIC1,EEI1) = 0x04;
	IPR(RIIC1,RXI1) = 0x04;
	IPR(RIIC1,TXI1) = 0x04;
	IPR(RIIC1,TEI1) = 0x04;

	// Clear the interrupt request flags. On PowerOnReset, these bit are
	// cleared to 0. This process is for fail-safe
	IR(RIIC1,EEI1) = 0;
	IR(RIIC1,RXI1) = 0;
	IR(RIIC1,TXI1) = 0;
	IR(RIIC1,TEI1) = 0;

	// The IERi register is used to enable or disable an interrupt request.
	// Enable all interrupt for CPU.
	IEN(RIIC1,EEI1) = 1;
	IEN(RIIC1,RXI1) = 1;
	IEN(RIIC1,TXI1) = 1;
	IEN(RIIC1,TEI1) = 1;
}

/******************************************************************************
* Function Name: IIC_Destroy
* Description  : Disable RIIC
* Arguments    : none
* Return Value : none
******************************************************************************/
void IIC_Destroy(void)
{
	// When clear ICE and set IICRST, all RIIC registers are reset.
	RIIC.ICCR1.BIT.ICE = 0;		// RIIC disable for RIIC initial
	RIIC.ICCR1.BIT.IICRST = 1;	// RIIC all reset
	RIIC.ICCR1.BIT.IICRST = 0;	// Clear reset
}


/******************************************************************************
* Function Name: IIC_EEI_Int
* Description  : IIC EEI interrupt function
* Argument     : none
* Return Value : none
******************************************************************************/
void IIC_EEI_Int(void)
{
	/* Check Timeout */
	if((RIIC.ICSR2.BIT.TMOF!=0) && (RIIC.ICIER.BIT.TMOIE!=0))
		riic_iceei_timeout();

	/* Check Arbitration Lost */
	if((RIIC.ICSR2.BIT.AL!=0) && (RIIC.ICIER.BIT.ALIE!=0))
		riic_iceei_al();

	/* Check stop condition detection */
	if((RIIC.ICSR2.BIT.STOP!=0) && (RIIC.ICIER.BIT.SPIE!=0))
		riic_iceei_sp();

	/* Check NACK reception */
	if((RIIC.ICSR2.BIT.NACKF != 0) && (RIIC.ICIER.BIT.NAKIE!=0))
		riic_iceei_nack();

	/* Check start condition detection */
	if((RIIC.ICSR2.BIT.START != 0) && (RIIC.ICIER.BIT.STIE!=0))
		riic_iceei_st();
}

/******************************************************************************
* Function Name: IIC_RXI_Int
* Description  : Receive Data Full interrupt function
* Argument     : none
* Return Value : none
******************************************************************************/
void IIC_RXI_Int(void)
{
	switch(riic_mode)
	{
		case IM_READ:
			riic_icrxi_read();
			break;
		case IM_WRITE:
			riic_error(IE_MODE_RX_INT_WRITE);		/* Internal mode error */
			break;
		default:
			riic_error(IE_MODE_RX_INT);				/* Internal mode error */
			break;
	}
}

/******************************************************************************
* Function Name: IIC_RXI_IntEepRead
* Description  : RXI interrupt function for EepRead process
*              : This function is called by IIC_RXI_Int
* Argument     : none
* Return Value : none
******************************************************************************/

/******************************************************************************
* Function Name: IIC_TXI_Int
* Description  : Transmit Data Empty Interrupt function
* Argument     : none
* Return Value : none
******************************************************************************/
void IIC_TXI_Int(void)
{
	switch(riic_mode)
	{
		case IM_WRITE:
			riic_ictxi_write();
			break;
		case IM_READ:
			riic_ictxi_read();
			break;
		default:
			riic_error(IE_MODE_TX_INT);		/* Internal mode error */
			break;
	}
}

/******************************************************************************
* Function Name: IIC_TEI_Int
* Description  : Transmit End Interrupt function
* Argument     : none
* Return Value : none
******************************************************************************/
void IIC_TEI_Int(void)
{
	switch(riic_mode)
	{
		case IM_WRITE:
			riic_ictei_write();
			break;
		case IM_READ:
			riic_ictei_read();
			break;
		default:
			riic_error(IE_MODE_TE_INT);	/* Internal mode error */
			break;
	}
}

/******************************************************************************
* Function Name: riic_write
* Description  : Start EEPROM write process or Acknowledge polling.
*              : When data1.PreCnt = 0 and data1.RWCnt = 0, this function do as acknowledge polling.
* Argument     : data1
*              : 	SlvAdr - 0x00-0xFE				// Slave Device Address.
*              : 									// Don't set bit0. It's a Read/Write bit
*              : 	PreCnt - 0x0000-0xFFFF			// Memory Addr of EEPROM
*              : 	*pPreData						// Pointer for EEPROM addr buffer
*              : 	RWCnt - 0x00000000-0xFFFFFFFF	// Number of Data
*              : 	*pRWData						// Pointer for Data
* Return Value : RIIC_OK			 - Start Write process correctly
*              : RIIC_MODE_ERROR	 - Running IIC on other mode
*              : RIIC_BUS_BUSY		 - IIC Bus busy
******************************************************************************/
RIICRESULT riic_write(RIICAPI data1)
{
	/* Check the IIC mode (controled by software) */
	if(riic_mode != IM_IDLE)
	{
		return IR_MODE_ERROR;					/* Running IIC on other mode */
	}

	/* Store the parameter data to ram for IIC */
	riic_buff = data1;

	/* Check IIC bus busy								*/
	/* If IIC bus is not free, return 'RIIC_BUS_BUSY'	*/
	if(RIIC.ICCR2.BIT.BBSY != 0)
	{
		return IR_BUS_BUSY;
	}

	/* Set each RAM */
	riic_mode = IM_WRITE;				/* Change the internal mode to EEPROM write mode */
	riic_status = IS_ON_COMMUNICATION;	/* Change the status to ON COMMUNICATION */
	riic_tx_cnt = 0;					/* Clear the internal transmission counter for IIC */

	/* Generate start condition */
	RIIC.ICCR2.BIT.ST = 1;

	return IR_OK;
}

/******************************************************************************
* Function Name: riic_read
* Description  : Start Randam read process
* Argument     : data1
*              : 	SlvAdr - 0x00-0xFE				// Slave Device Address.
*              : 									// Don't set bit0. It's a Read/Write bit
*              : 	PreCnt - 0x0000-0xFFFF			// Memory Addr of EEPROM
*              : 	*pPreData						// Pointer for EEPROM addr buffer
*              : 	RWCnt - 0x00000000-0xFFFFFFFF	// Number of Data
*              : 	*pRWData						// Pointer for Data
* Return Value : RIIC_OK			 - Start RandomRead process correctly
*              : RIIC_MODE_ERROR	 - Running IIC on other mode
*              : RIIC_PRM_ERROR		 - Parameter error
*              : RIIC_BUS_BUSY		 - IIC Bus busy
******************************************************************************/
RIICRESULT riic_read(RIICAPI data1)
{
	volatile BYTE tmp;
	volatile DWORD cnt;

	/* Check the IIC mode (controled by software) */
	if(riic_mode != IM_IDLE)
	{
		return IR_MODE_ERROR;					/* Running IIC on other mode */
	}

	/* Store the parameter data to ram for IIC */
	riic_buff = data1;

	/* Check parameter */
	if((riic_buff.RWCnt == 0) || ((riic_buff.PreCnt == 0)))
	{
		return IR_MODE_ERROR;					/* Parameter error */
	}

	/* Check IIC bus busy								*/
	/* If IIC bus is not free, return 'RIIC_BUS_BUSY'	*/
	if(RIIC.ICCR2.BIT.BBSY != 0)
	{
		return IR_BUS_BUSY;
	}

	/* Set each RAM */
	riic_mode = IM_READ;				/* Change the internal mode to EEPROM read mode */
	riic_status = IS_ON_COMMUNICATION;	/* Change the status to ON COMMUNICATION */
	riic_tx_cnt = 0;					/* Clear the internal transmission counter for IIC */
	riic_rx_cnt = 0;					/* Clear the internal reception counter for IIC */

	RIIC.ICCR2.BIT.ST = 1;				/* Generate start condition */

	return IR_OK;
}

/******************************************************************************
* Function Name: riic_getstatus
* Description  : Get IIC status
* Argument     : data1			// Pointer for IIC communication status buffer
*              : 	RIIC_STATUS_IDLE			 - RIIC is Idle mode. Users can start communication.
*              : 	RIIC_STATUS_ON_COMMUNICATION - RIIC is on communication.
*              : 									Users cannot start communication.
*              : 	RIIC_STATUS_NACK			 - RIIC has received NACK.
*              : 									Users can start next communication.
*              : 	RIIC_STATUS_FAILED			 - RIIC has stopped the communication.
*              : 									Users can start next communication.
*              : 									But the last communication was failed.
*              :
*              : data2			// Pointer for IIC Bus status buffer
*              : 	RIIC_BUS_STATUS_FREE - IIC bus is free
*              : 	RIIC_BUS_STATUS_BBSY - IIC bus is busy
* Return Value : none
******************************************************************************/
void riic_getstatus(RIICSTATUS *data1, RIICBUS *data2)
{
	*data1 = riic_status;

	/* Check bus busy */
	if(RIIC.ICCR2.BIT.BBSY == 0)
		*data2 = IB_FREE;
	else
		*data2 = IB_BBSY;
}
/******************************************************************************
* Function Name: riic0_iceei0_timeout
* Description  : Time out function
*              : This function is called by IIC_EEI_Int()
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_iceei_timeout(void)
{
	riic_gen_sp();
}

/******************************************************************************
* Function Name: riic_iceei_al
* Description  : Arbitration function
*              : This function is called by IIC_EEI_Int()
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_iceei_al(void)
{
	riic_gen_sp();
}

/******************************************************************************
* Function Name: riic_iceei_sp
* Description  : Stop condition detection function
*              : This function is called by IIC_EEI_Int()
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_iceei_sp(void)
{
	/* Clear each status flag */
	RIIC.ICSR2.BIT.NACKF = 0;
	RIIC.ICSR2.BIT.STOP = 0;

	/* Enable/Disable each interrupt */
	RIIC.ICIER.BYTE = 0xBB;				/* b0: Enable Time Out interrupt */
										/* b1: Enable Arbitration Lost interrupt */
										/* b2: Disable Start Condition Detection Interrupt */
										/* b3: Enable Stop condition detection interrupt */
										/* b4: Enable NACK reception interrupt */
										/* b5: Enable Receive Data Full Interrupt */
										/* b6: Disable Transmit End Interrupt */
										/* b7: Enable Transmit Data Empty Interrupt */
	switch(riic_mode)
	{
		case IM_WRITE:
			if(riic_buff.RWCnt != 0)		/* When the data number is not '0', */
			{							/* the communication is not complete  */
				riic_status = IS_FAILED;
			}else
			{
				if(riic_status != IS_NACK)
					riic_status = IS_IDLE;
			}
			break;
			
		case IM_READ:
			if(riic_buff.RWCnt != 0)		/* When the data number is not '0', */
			{							/* the communication is not complete */
				riic_status = IS_FAILED;
			}else
				riic_status = IS_IDLE;
			break;
			
		case IM_IDLE:
				/* Other device generates stop condition.			*/
				/* Note: This code is for single master.			*/
			break;
			
		default:
			riic_error(IE_MODE_SP_INT);		/* Internal mode error */
			break;
	}

	/* Initialize ram for RIIC */
	riic_mode = IM_IDLE;
	riic_tx_cnt = 0;			/* Clear the internal transmission counter for IIC */
	riic_rx_cnt = 0;			/* Clear the internal reception counter for IIC */
}

/******************************************************************************
* Function Name: riic0_iceei0_st
* Description  : Start condition detection function
*              : This function is called by IIC_EEI_Int()
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_iceei_st(void)
{
	/* Disable Start Condition Detection Interrupt */
	RIIC.ICSR2.BIT.START = 0;
	RIIC.ICIER.BIT.STIE = 0;

	/* Transfer slave device address (Read) */
	RIIC.ICDRT = riic_buff.SlvAdr | 0x01;	/* When master transfer, b0 must be '1' */
}

/******************************************************************************
* Function Name: IIC_EEI_Int
* Description  : NACK reception function
*              : This function is called by IIC_EEI_Int()
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_iceei_nack(void)
{
	/* Chenge the internal mode */
	riic_status = IS_NACK;

	/* Disable NACK reception interrupt */
	RIIC.ICIER.BIT.NAKIE = 0;

	/* Generate Stop Condition */
	RIIC.ICSR2.BIT.STOP = 0;
	RIIC.ICCR2.BIT.SP = 1;
}
/******************************************************************************
* Function Name: riic0_icrxi0_read
* Description  : RXI interrupt function for Read process
*              : This function is called by IIC_RXI_Int
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_icrxi_read (void)
{
	volatile BYTE tmp;

	/* Increase internal reception counter on RAM. It is a receive data counter. */
	riic_rx_cnt++;

	if(riic_rx_cnt == 1)
	{
		if(riic_buff.RWCnt == 1)				/* When read data is 1 byte,		*/
		{									/* prepare to receive last data		*/
			/* When WAIT bit is set, RIIC outputs SCL=Low after it receives 9th clock.	*/
			/* Then RIIC generates stop condition after it reads receive data.			*/
			RIIC.ICMR3.BIT.WAIT = 1;

			/* If RIIC sends ACK when it receives last data, EEPROM may prevent RIIC generating 	*/
			/* stop condition. Because EEPROM desn't know how many RIIC try to read data.		*/
			/* When RIIC sends ACK, EEPROM realizes the next rising SCL for stop condition as 	*/
			/* next first bit SCL.																*/
			RIIC.ICMR3.BIT.ACKBT = 1;		/* Set Nack for final data.*/
		}

		/* dummy read */
		tmp = RIIC.ICDRR;
	}
	else if(riic_buff.RWCnt == 2)
	{
		/* When WAIT bit is set, RIIC outputs SCL=Low after it receives 9th clock.	*/
		/* Then RIIC generates stop condition after it reads receive data.			*/
		RIIC.ICMR3.BIT.WAIT = 1;

		/* If RIIC sends ACK when it receive last data, EEPROM may prevent RIIC generating 	*/
		/* stop condition. Because EEPROM desn't know how mmany RIIC try to read data.		*/
		/* When RIIC sends ACK, EEPROM realizes the next rising SCL for stop condition as 	*/
		/* next first bit SCL.																*/
		RIIC.ICMR3.BIT.ACKBT = 1;			/* Set Nack for final data */

		/* Read data */
		*riic_buff.pRWData++ = RIIC.ICDRR;
		riic_buff.RWCnt--;
	}
	else if(riic_buff.RWCnt == 1)			/* Receive final data */
	{
		/* Prepare to generate Stop Condition */
		RIIC.ICSR2.BIT.STOP = 0;
		RIIC.ICCR2.BIT.SP = 1;

		/* After read final data, RIIC generates stop condtion */
		*riic_buff.pRWData++ = RIIC.ICDRR;	/* Read final data */
		riic_buff.RWCnt--;
		RIIC.ICMR3.BIT.WAIT = 0;
	}
	else
	{
		/* Read data */
		*riic_buff.pRWData++ = RIIC.ICDRR;
		riic_buff.RWCnt--;
	}
}
/******************************************************************************
* Function Name: riic_ictxi_write
* Description  : TXI interrupt function for Write process
*              : This function is called by IIC_TXI_Int
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_ictxi_write(void)
{
	/* Increase internal transmission counter on RAM. */
	riic_tx_cnt++;

	/* Transfer slave device address */
	if(riic_tx_cnt == 1)
	{
		/* Transfer slave device address */
		RIIC.ICDRT = riic_buff.SlvAdr & 0xFE;	/* When master transfer, b0 must be '0' */
		return;
	};

	/* Transfer eeprom address for writting */
	if(riic_buff.PreCnt != 0)
	{
		RIIC.ICDRT = *riic_buff.pPreData++;
		riic_buff.PreCnt--;
		return;
	}

	/* Transfer data for writting */
	if(riic_buff.RWCnt != 0)
	{
		RIIC.ICDRT = *riic_buff.pRWData++;
		riic_buff.RWCnt--;
		return;
	}
	else
		RIIC.ICIER.BIT.TEIE = 1;				/* Enable Transmit End Interrupt */
}

/******************************************************************************
* Function Name: riic_ictxi_read
* Description  : TXI interrupt function for Read process
*              : This function is called by IIC_TXI_Int
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_ictxi_read(void)
{
	/* Increase internal transmission counter on RAM. */
	riic_tx_cnt++;

	/* Transfer slave device address */
	if(riic_tx_cnt == 1)
	{
		/* Transfer slave device address */
		RIIC.ICDRT = riic_buff.SlvAdr & 0xFE;	/* When master transfer, b0 must be '0' */
		return;
	}

	/* Transfer eeprom address for writting */
	if(riic_buff.PreCnt != 0)
	{
		RIIC.ICDRT = *riic_buff.pPreData++;
		riic_buff.PreCnt--;
		return;
	}
	else
		RIIC.ICIER.BIT.TEIE = 1;				/* Enable Transmit End Interrupt */
}
/******************************************************************************
* Function Name: riic_ictei_write
* Description  : TEI interrupt function for Write process
*              : This function is called by IIC_TEI_Int
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_ictei_write(void)
{
	/* Disable Transmit End Interrupt */
	RIIC.ICIER.BIT.TEIE = 0;

	/* Generate stop condition */
	RIIC.ICSR2.BIT.STOP = 0;
	RIIC.ICCR2.BIT.SP = 1;
}

/******************************************************************************
* Function Name: riic_ictei_read
* Description  : TEI interrupt function for Read process
*              : This function is called by IIC_TEI_Int
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_ictei_read(void)
{
	RIIC.ICSR2.BIT.START = 0;		/* Clear Start Condition Detection flag */
	RIIC.ICIER.BIT.STIE = 1;		/* Enable Start Condition Detection Interrupt */
	RIIC.ICIER.BIT.TEIE = 0;		/* Disable Transmit End Interrupt */

	/* Generate restart condition */
	RIIC.ICCR2.BIT.RS = 1;
}

/******************************************************************************
* Function Name: riic_gen_sp
* Description  : This function reset RIIC. Then do return processing.
*              : Return processing is 
*              : Step1 - Rest RIIC (try to be SCL=High and SDA=Hgih)
*              :         If SCL=Low though reset RIIC, other device out put SCL=Low
*              : Step2 - If SDA=Low, RIIC generates some clocks
*              : Step3 - After SDA=High, RIIC generates stop condition.
* Argument     : none
* Return Value : none
******************************************************************************/
void riic_gen_sp(void)
{
	volatile WORD cnt;

	/* ICE=1 and IICRST=1 clear some status flags.									*/
	/* This reset desn't clear some settings, baud rate, slave address and so on.	*/
	RIIC.ICCR1.BIT.IICRST = 1;			/* Reset RIIC */

	/* Time out setting */
	RIIC.ICFER.BIT.TMOE = 0;			/* Disable time out detection */
	RIIC.ICMR2.BIT.TMOL = 1;			/* Disable SCL=Low time out */
	RIIC.ICMR2.BIT.TMOH = 1;			/* Enable SCL=High time out */
	RIIC.ICMR2.BIT.TMOS = 0;			/* Long mode (16bits counter), PCLK=48MHz,		*/
										/* IIC phi=48MHz, Long mode is about 1.364 ms	*/

	RIIC.ICCR1.BIT.IICRST = 0;			/* Clear reset */

	for(cnt=0; cnt<100; cnt++);			/* If RIIC output SDA=Low, SDA output is released	*/
										/* by IICRST=1. But IIC bus is pulluped therefore 	*/
										/* the SDA rising is not immediate.					*/

	RIIC.ICFER.BIT.TMOE = 1;			/* Enable time out detection */

	/* When SCL=Low though IICRST=1, other device output SCL=Low */
	if(RIIC.ICCR1.BIT.SCLI == 0)		/* Check SCL level */
		riic_error(IE_SCL_LOCK);

	/* After reset RIIC, this flow generates Stop condition.			*/
	/* But MST bit have to be set when RIIC generates Stop condition.	*/
	/* Here, disable protect, then set TRS and MST bits.				*/
	/* If set only MST, RIIC generates some clocks because RDRF=0.		*/
	/* When MST=1, TRS=0 and RDRF=0, RIIC starts Master Receive.		*/
	RIIC.ICMR1.BIT.MTWP = 1;
	RIIC.ICCR2.BIT.TRS = 1;
	RIIC.ICCR2.BIT.MST = 1;

	/* If other devices output SDA=Low, RIIC generates some clocks.		*/
	/* Usually, devices stop SDA=Low when they recieve some clocks.		*/
	if(RIIC.ICCR1.BIT.SDAI == 0)		/* Check SDA level */
	{
		for(cnt=0; cnt<10; cnt++){		/* Generate 10 clocks until SDA=High */
			if(RIIC.ICCR1.BIT.SDAI == 0)
			{
				RIIC.ICCR1.BIT.CLO = 1;				/* Generate a clock */
				while(RIIC.ICCR1.BIT.CLO != 0)		/* Wait for complete a generating clock */
				{
					if(RIIC.ICSR2.BIT.TMOF !=0)		/* When other device output SCL=Low,	*/
					{								/* time out occur.						*/
						RIIC.ICSR2.BIT.TMOF =0;
						break;
					}
				}
			}
			else
				break;					/* When SDA=High, stop generating clocks */

			/* Call error function if SDA = Low after RIIC generates some clocks */
			if((cnt == 9)&&(RIIC.ICCR1.BIT.SDAI == 0))
				riic_error(IE_SDA_LOCK);
		}
	}

	if(RIIC.ICCR2.BIT.BBSY == 0)		/* When Bus free, RIIC does't generate Stop condition */
	{
		RIIC.ICCR1.BIT.IICRST = 1;		/* Reset RIIC */
		RIIC.ICCR1.BIT.IICRST = 0;		/* Clear reset */
	}
	else
	{
		/* Generate stop condition */
		RIIC.ICSR2.BIT.STOP = 0;
		RIIC.ICCR2.BIT.SP = 1;
	}

	/* Enable MST/TRS Write Protect */
	RIIC.ICMR1.BIT.MTWP = 0;

	/* Set time out */
	RIIC.ICFER.BIT.TMOE = 0;			/* Disable time out detection */
	RIIC.ICMR2.BIT.TMOL = 0;			/* Disable SCL=Low time out */
	RIIC.ICMR2.BIT.TMOH = 1;			/* Enable SCL=High time out */
	RIIC.ICMR2.BIT.TMOS = 0;			/* Long mode (16bits counter), PCLK=48MHz,		*/
										/* IIC phi=48MHz. Long mode is about 1.365 ms	*/
	RIIC.ICFER.BIT.TMOE = 1;			/* Enable time out detection */
}

/******************************************************************************
* Function Name: riic_error
* Description  : Usually this function is not called.
* Argument     : error_code
*              :    RIIC_ERR_MODE_SP_INT
*              :    RIIC_ERR_MODE_RX_INT_WRITE
*              :    RIIC_ERR_MODE_RX_INT
*              :    RIIC_ERR_MODE_TX_INT
*              :    RIIC_ERR_MODE_TE_INT
*              :    RIIC_ERR_SCL_LOCK
*              :    RIIC_ERR_SDA_LOCK
*              :    RIIC_ERR_GEN_CLK_BBSY
* Return Value : none
******************************************************************************/
void riic_error(RIICERROR error_code)
{
	switch(error_code)
	{
		case IE_MODE_SP_INT:
			break;
		case IE_MODE_RX_INT_WRITE:
			break;
		case IE_MODE_RX_INT:
			break;
		case IE_MODE_TX_INT:
			break;
		case IE_MODE_TE_INT:
			break;
		case IE_SCL_LOCK:
			break;
		case IE_SDA_LOCK:
			break;
		case IE_GEN_CLK_BBSY:
			break;
		default:
			break;
	}

	while(1);
}


uint8_t I2C_readBytesFromAddress(uint8_t devaddr, uint8_t regaddr, uint8_t size, uint8_t *data)
{
	RIICAPI		i2c[1];
	RIICSTATUS 	tmp_status;
	RIICBUS		tmp_bus_status;

	i2c[0].SlvAdr = (devaddr<<1);
	i2c[0].PreCnt = 1;
	i2c[0].pPreData = &regaddr;
	i2c[0].RWCnt = size;
	i2c[0].pRWData = data;

	if( riic_read(i2c[0]) != IR_OK )
	{
		;
	}

	do{
		riic_getstatus(&tmp_status, &tmp_bus_status);
	}while(tmp_status == IS_ON_COMMUNICATION);

	do{
		riic_getstatus(&tmp_status, &tmp_bus_status);
	}while(tmp_bus_status != IB_FREE);
	
	return 0;
}

uint8_t I2C_writeBytesToAddress(uint8_t devaddr, uint8_t regaddr, uint8_t size, uint8_t *data)
{
	RIICAPI		i2c[1];
	RIICSTATUS 	tmp_status;
	RIICBUS		tmp_bus_status;

	i2c[0].SlvAdr	= devaddr<<1;
	i2c[0].PreCnt	= 1;
	i2c[0].pPreData = &regaddr;
	i2c[0].RWCnt	= size;
	i2c[0].pRWData	= data;

	if( riic_write(i2c[0]) != IR_OK )
	{
		;
	}
	
	do{
		riic_getstatus(&tmp_status, &tmp_bus_status);
	}while(tmp_status == IS_ON_COMMUNICATION);

	do{
		riic_getstatus(&tmp_status, &tmp_bus_status);
	}while(tmp_bus_status != IB_FREE);
	
	return 0;
}

void I2C_Delay_ms(uint32_t time)
{
	uint32_t i = 0;
	uint32_t j = 0;
	
	for ( j=0; j<=time; j++)
		for ( i=0; i<=9600; i++ )
			nop();
}

void I2C_get_tick_count(unsigned long *time)
{

}
