/*******************************************************************************
* File Name    : riic.h
* Version      : 1.00
* Description  : RIIC program header
******************************************************************************/
#ifndef RIIC_H_
#define RIIC_H_


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>


/******************************************************************************
Typedef definitions
******************************************************************************/


#ifndef RIICRESULT_DEF
#define RIICRESULT_DEF
typedef enum 
{
	IR_OK = 0,				/* Return value for function 'IIC_EepWrite' and 'IIC_RandomRead' */
	IR_BUS_BUSY,			/* Return value for function 'IIC_EepWrite' and 'IIC_RandomRead' */
	IR_MODE_ERROR,			/* Return value for function 'IIC_EepWrite' and 'IIC_RandomRead' */
	IR_PRM_ERROR			/* Return value for function 'IIC_EepWrite' and 'IIC_RandomRead' */
} RIICRESULT;
#endif

#ifndef RIICSTATUS_DEF
#define RIICSTATUS_DEF
typedef enum 
{
	IS_IDLE = 0,			/* Return value for function 'IIC_GetStatus' */
	IS_ON_COMMUNICATION,	/* Return value for function 'IIC_GetStatus' */
	IS_NACK,				/* Return value for function 'IIC_GetStatus' */
	IS_FAILED				/* Return value for function 'IIC_GetStatus' */
} RIICSTATUS;
#endif

#ifndef RIICBUS_DEF
#define RIICBUS_DEF
typedef enum 
{
	IB_FREE = 0,			/* Return value for function 'IIC_GetStatus' */
	IB_BBSY					/* Return value for function 'IIC_GetStatus' */
} RIICBUS;
#endif

#ifndef RIICMODE_DEF
#define RIICMODE_DEF
typedef enum 
{
	IM_IDLE = 0,			/* For internal variable 'iic_mode' */
	IM_READ,				/* For internal variable 'iic_mode' */
	IM_WRITE				/* For internal variable 'iic_mode' */
} RIICMODE;
#endif

#ifndef RIICERROR_DEF
#define RIICERROR_DEF
typedef enum 
{
	IE_MODE_SP_INT = 0,		/* Return value for function 'IIC_Error' */
	IE_MODE_RX_INT_WRITE,	/* Return value for function 'IIC_Error' */
	IE_MODE_RX_INT,			/* Return value for function 'IIC_Error' */
	IE_MODE_TX_INT,			/* Return value for function 'IIC_Error' */
	IE_MODE_TE_INT,			/* Return value for function 'IIC_Error' */
	IE_SCL_LOCK,			/* Return value for function 'IIC_Error' */
	IE_SDA_LOCK,			/* Return value for function 'IIC_Error' */
	IE_GEN_CLK_BBSY			/* Return value for function 'IIC_Error' */
} RIICERROR;
#endif

extern RIICMODE riic0_mode;
extern RIICSTATUS riic0_status;
//extern DWORD riic0_tx_cnt;
//extern DWORD riic0_rx_cnt;

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern RIICMODE riic_mode;
extern RIICSTATUS riic_status;
//extern DWORD riic_tx_cnt;
//extern DWORD riic_rx_cnt;
/******************************************************************************
Functions Prototypes
******************************************************************************/
void IIC_Create(void);
void IIC_Destroy(void);
void IIC_IntCreate(void);

RIICRESULT riic_write(RIICAPI);
RIICRESULT riic_read(RIICAPI);
void riic_getstatus(RIICSTATUS*, RIICBUS*);
void riic_iceei_timeout(void);
void riic_iceei_al(void);
void riic_iceei_sp(void);
void riic_iceei_st(void);
void riic_iceei_nack(void);
void riic_icrxi_read(void);
void riic_ictxi_write(void);
void riic_ictxi_read(void);
void riic_ictei_write(void);
void riic_ictei_read(void);
void riic_gen_sp(void);
void riic_error(RIICERROR);

/* Interrupt fumctions for IIC */
void IIC_EEI_Int(void);
void IIC_RXI_Int(void);
void IIC_TXI_Int(void);
void IIC_TEI_Int(void);

uint8_t I2C_readBytesFromAddress(uint8_t , uint8_t , uint8_t , uint8_t*);
uint8_t I2C_writeBytesToAddress(uint8_t , uint8_t , uint8_t , uint8_t*);
void I2C_Delay_ms(uint32_t);
void I2C_get_tick_count(unsigned long *);

#endif /* I2C_H_ */
